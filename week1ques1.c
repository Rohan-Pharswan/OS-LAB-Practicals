#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
int main()
{
    int x=fork();
    if(x==0)
    {
        printf("child process");
    }
    if(x>=1)
    {
        printf("parent process");
    }
    else
    {
        printf("process not created");
    }

    return 0;
}