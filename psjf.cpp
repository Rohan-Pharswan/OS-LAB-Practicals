#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion = 0, tat = 0, wt = 0;
};

void preemptive_sjf(vector<process>& proc, int n) {
    int completed = 0, curr_time = 0, prev = -1;
    while (completed < n) {
        int idx = -1, min_rem = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (proc[i].arrival <= curr_time && proc[i].remaining > 0) {
                if (proc[i].remaining < min_rem) {
                    min_rem = proc[i].remaining;
                    idx = i;
                }
                // If two processes have same remaining time, choose by arrival
                else if (proc[i].remaining == min_rem && proc[i].arrival < proc[idx].arrival) {
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            proc[idx].remaining--;
            curr_time++;
            if (proc[idx].remaining == 0) {
                proc[idx].completion = curr_time;
                proc[idx].tat = proc[idx].completion - proc[idx].arrival;
                proc[idx].wt = proc[idx].tat - proc[idx].burst;
                completed++;
            }
        } else {
            curr_time++; // No process is ready, advance time
        }
    }
}

int main() {
    int n;
    cout << "Enter no. of processes- ";
    cin >> n;
    vector<process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival and burst time of process " << i + 1 << "- ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst;
    }
    // Sort by arrival time for display
    sort(processes.begin(), processes.end(), [](const process &a, const process &b) {
        return a.arrival < b.arrival;
    });
    preemptive_sjf(processes, n);
    cout << "PID\tArrival\tBurst\tCompletion\tTurnAround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" << processes[i].arrival << "\t" << processes[i].burst << "\t"
             << processes[i].completion << "\t" << processes[i].tat << "\t" << processes[i].wt << "\n";
    }
}