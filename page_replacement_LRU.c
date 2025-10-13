#include<stdio.h>
int findLRU(int time[],int n){
int i,pos=0,min=time[0];
for(i=1;i<n;i++)if(time[i]<min){min=time[i];pos=i;}
return pos;
}
int main(){
int n,f,i,j,k,pagefault=0,count=0,flag1,flag2,pos;
printf("Enter no. of pages: ");scanf("%d",&n);
int pages[n];
printf("Enter page sequence: ");
for(i=0;i<n;i++)scanf("%d",&pages[i]);
printf("Enter no. of frames: ");scanf("%d",&f);
int frame[f],time[f];
for(i=0;i<f;i++){frame[i]=-1;time[i]=0;}
printf("\nPage\tFrames\n");
for(i=0;i<n;i++){
flag1=flag2=0;
for(j=0;j<f;j++)
if(frame[j]==pages[i]){count++;time[j]=count;flag1=flag2=1;break;}
if(flag1==0)
for(j=0;j<f;j++)
if(frame[j]==-1){count++;frame[j]=pages[i];time[j]=count;pagefault++;flag2=1;break;}
if(flag2==0){
pos=findLRU(time,f);
count++;frame[pos]=pages[i];time[pos]=count;pagefault++;
}
printf("%d\t",pages[i]);
for(k=0;k<f;k++)
if(frame[k]!=-1)printf("%d ",frame[k]);
printf("\n");
}
printf("\nTotal Page Faults: %d\n",pagefault);
return 0;
}
