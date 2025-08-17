#include <stdio.h>
struct sjf {
    int arrival;
    int burst;
    int com;
    int tat;
    int wt;
};
double cpu_uti = 0.0;
void compfinder(struct sjf arr[], int i, int prevcomp) {
    if (prevcomp >= arr[i].arrival) {
        arr[i].com = prevcomp + arr[i].burst;
        arr[i].tat = arr[i].com - arr[i].arrival;
        arr[i].wt  = prevcomp - arr[i].arrival;
    } else {
        cpu_uti += arr[i].arrival - prevcomp; // idle time
        arr[i].com = arr[i].arrival + arr[i].burst;
        arr[i].tat = arr[i].com - arr[i].arrival;
        arr[i].wt  = 0;
    }
}
void sort_by_arrival(struct sjf arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].arrival > arr[j + 1].arrival) {
                struct sjf temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct sjf p[n];
    printf("Enter arrival and burst time of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].com = p[i].tat = p[i].wt = 0;
    }
    sort_by_arrival(p, n);
    compfinder(p, 0, 0);
    // Remaining processes
    for (int i = 1; i < n; i++) {
        compfinder(p, i, p[i - 1].com);
    }
    printf("Process\tArrival\tBurst\tCompletion\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               i, p[i].arrival, p[i].burst,
               p[i].com, p[i].tat, p[i].wt);
    }
    double utilization = ((p[n - 1].com - cpu_uti) / p[n - 1].com) * 100.0;
    printf("CPU Utilization: %.2f%%\n", utilization);
    return 0;
}
