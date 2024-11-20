#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int id, burst_time, waiting_time, turnaround_time;
};

bool compare(Process a, Process b) {
    return a.burst_time < b.burst_time;
}

void findWaitingTime(Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void findTurnAroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void findAvgTime(Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);

    cout << "Processes\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].id << "\t\t" << proc[i].burst_time << "\t\t" << proc[i].waiting_time << "\t\t" << proc[i].turnaround_time << endl;
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }
    cout << "Average waiting time = " << total_wt / n << endl;
    cout << "Average turnaround time = " << total_tat / n << endl;
}

int main() {
    int n = 3;
    Process proc[] = {{1, 6, 0, 0}, {2, 8, 0, 0}, {3, 7, 0, 0}};
    sort(proc, proc + n, compare);
    findAvgTime(proc, n);
    return 0;
}
