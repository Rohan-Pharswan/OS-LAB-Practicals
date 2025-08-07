#include<bits/stdc++.h>
using namespace std;
typedef struct sjf{
    pair<int,int> stbt;
    int com;
    int tat;
    int wt;
} SJF;
double cpu_uti=0;
void compfinder(vector<SJF>&arr,int i,int prevcomp){
    if(prevcomp>=arr[i].stbt.first){
        arr[i].com=prevcomp+arr[i].stbt.second;
        arr[i].tat=arr[i].com-arr[i].stbt.first;
        arr[i].wt=arr[i-1].com-arr[i].stbt.first;
        return;
    }
    cpu_uti+=prevcomp-arr[i].stbt.first;
    arr[i].com=arr[i].stbt.first+arr[i].stbt.second;
    arr[i].tat=arr[i].com-arr[i].stbt.first;
    arr[i].wt=0;

}
int main(){
    int n;
    cout<<"enter number of processes";
    cin>>n;
    vector<pair<int,int>> process(n);
    cout<<"enter arriaval and burst time of n processes";
    for(int i=0;i<n;i++){
        cin>>process[i].first>>process[i].second;
    }
    sort(process.begin(),process.end());
    vector<SJF>  p(n);
    for(int i=0;i<n;i++){
        p[i].stbt=process[i];
    }
    compfinder(p,0,0);
    for(int i=1;i<n;i++){
        compfinder(p,i,p[i-1].com);
    }
    cout<<"process  "<<"start time  "<<"burst time  "<<" complete Time  "<<" turn around time  "<<"waiting time  "<<endl;
    for(int i=0;i<n;i++){
        cout<<"p"<<i<<"\t\t"<<p[i].stbt.first<<"\t\t"<<p[i].stbt.second<<"\t\t"<<p[i].com<<"\t\t"<<p[i].tat<<"\t\t"<<p[i].wt<<endl;
    }
    cout<<"CPU Utilization: "<<(p[n-1].com-cpu_uti)/p[n-1].com*100<<"%"<<endl;
    return 0;
}