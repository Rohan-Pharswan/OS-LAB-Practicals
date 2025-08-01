#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
    pid_t pid = fork();
    if(pid==0){
        printf("Child Process\n");
        printf("Child pid %d \n", getpid());
        printf("Listing files\n");
        execlp("ls", "ls", "-l", (char *)NULL);
        exit(0);
    }
    else if(pid>=1){
        wait(NULL);
        printf("Parent Processs\n");
        printf("Parent pid %d \n", getpid());
        pid_t pid2 = fork();
        if(pid2==0){
         printf("Child pid2 %d \n", getpid());
         exit(0);
        }
        else if(pid2>=1){
        printf("Parent pid2 %d \n", getpid());
        exit(0);
        }
        else {
            printf("Failed");
            return 1;
        }
        
    }
    else{
        printf("Nothing Created");
    }
    return 0;
}