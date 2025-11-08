#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

void use_pipe() {
    int fd[2];
    char buffer[100];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        char msg[] = "Hello from Child via Pipe";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("\n[Pipe] Parent read: %s\n", buffer);
        close(fd[0]);
    }
}

void use_message_queue() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0) {
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from Child via Message Queue");
        msgsnd(msgid, &message, sizeof(message), 0);
        exit(0);
    } else {
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("\n[Message Queue] Parent read: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL);
    }
}

void use_shared_memory() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);

    if (fork() == 0) {
        strcpy(str, "Hello from Child via Shared Memory");
        shmdt(str);
        exit(0);
    } else {
        sleep(1);
        printf("\n[Shared Memory] Parent read: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Inter Process Communication Menu ---\n");
        printf("1. Pipe\n");
        printf("2. Message Queue\n");
        printf("3. Shared Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                use_pipe();
                break;
            case 2:
                use_message_queue();
                break;
            case 3:
                use_shared_memory();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
