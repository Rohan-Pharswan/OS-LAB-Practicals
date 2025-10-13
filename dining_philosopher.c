#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define N 5
sem_t chopstick[N];
pthread_t philosopher[N];
int id[N];
void*dine(void*num){
int i=*(int*)num;
int left=i;
int right=(i+1)%N;
while(1){
printf("Philosopher %d is thinking\n",i);
sleep(1);
printf("Philosopher %d is hungry\n",i);
sem_wait(&chopstick[left]);
sem_wait(&chopstick[right]);
printf("Philosopher %d is eating\n",i);
sleep(2);
sem_post(&chopstick[left]);
sem_post(&chopstick[right]);
printf("Philosopher %d finished eating\n",i);
sleep(1);
}}
int main(){
for(int i=0;i<N;i++){sem_init(&chopstick[i],0,1);id[i]=i;}
for(int i=0;i<N;i++)pthread_create(&philosopher[i],NULL,dine,&id[i]);
for(int i=0;i<N;i++)pthread_join(philosopher[i],NULL);
for(int i=0;i<N;i++)sem_destroy(&chopstick[i]);
return 0;}
