#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int arr[]={0,1,2,3,4,5,6,7,8,9};
    int i=0;
    int x=fork();
    if(x>0){
        for(int i=0;i<10;i+=2){
            printf("%d\t",arr[i]);
        }
        printf("\n");
        wait(NULL);
    }   
    else if(x==0){
        for(int i=1;i<10;i+=2){
            printf("%d\t",arr[i]);
        }
        exit(0);
    }
    else{
        printf("rare case");
    }
    
    return 0;
}