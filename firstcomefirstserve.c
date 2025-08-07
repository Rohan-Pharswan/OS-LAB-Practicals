#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int waiting_time;
};

int main() {
    int n;
    printf("enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("enter arrival time and burst time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].waiting_time = p[i].tat - p[i].bt;

        time = p[i].ct;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].waiting_time);
    }
 return 0;
}