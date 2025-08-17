#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completed;
};

void schedule_processes(struct Process proc[], int n) {
    int time = 0, completed = 0, min_priority, idx;
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].completed = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }

    int last_idx = -1;
    while (completed < n) {
        min_priority = 1e9;
        idx = -1;
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].arrival_time <= time) {
                if (proc[i].priority < min_priority) {
                    min_priority = proc[i].priority;
                    idx = i;
                } else if (proc[i].priority == min_priority) {
                    if (proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            proc[idx].remaining_time--;
            time++;
            // Increase waiting time for all other ready processes
            for (int i = 0; i < n; i++) {
                if (i != idx && !proc[i].completed && proc[i].arrival_time <= time) {
                    proc[i].waiting_time++;
                }
            }
            if (proc[idx].remaining_time == 0) {
                proc[idx].completed = 1;
                proc[idx].turnaround_time = time - proc[idx].arrival_time;
                completed++;
            }
        } else {
            time++;
        }
    }
}

void print_table(struct Process proc[], int n) {
    printf("ID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d arrival time: ", i+1);
        scanf("%d", &proc[i].arrival_time);
        printf("Process %d burst time: ", i+1);
        scanf("%d", &proc[i].burst_time);
        printf("Process %d priority (lower number = higher priority): ", i+1);
        scanf("%d", &proc[i].priority);
        proc[i].id = i+1;
    }

    schedule_processes(proc, n);
    print_table(proc, n);

    return 0;
}