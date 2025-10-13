#include<stdio.h>
int main(){
int n,f,i,j,k,flag=0,pagefault=0;
printf("Enter no. of pages: ");scanf("%d",&n);
int pages[n];
printf("Enter page sequence: ");
for(i=0;i<n;i++)scanf("%d",&pages[i]);
printf("Enter no. of frames: ");scanf("%d",&f);
int frame[f];
for(i=0;i<f;i++)frame[i]=-1;
j=0;
printf("\nPage\tFrames\n");
for(i=0;i<n;i++){
flag=0;
for(k=0;k<f;k++)
if(frame[k]==pages[i]){flag=1;break;}
if(flag==0){
frame[j]=pages[i];
j=(j+1)%f;
pagefault++;
}
printf("%d\t",pages[i]);
for(k=0;k<f;k++)
if(frame[k]!=-1)printf("%d ",frame[k]);
printf("\n");
}
printf("\nTotal Page Faults: %d\n",pagefault);
return 0;
}
