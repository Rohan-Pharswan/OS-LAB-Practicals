#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid = fork();
    if(pid==0){
        printf("Child Process\n");
        printf("Child pid %d \n", getpid());
        printf("Child's Parents pid %d \n", getppid());
    }
    else if(pid>=1){
        printf("Parent Processs\n");
        printf("Parent pid %d \n", getpid());
        printf("Child pid %d \n", pid);
    }
    else{
        printf("Nothing Created");
    }
    return 0;
}