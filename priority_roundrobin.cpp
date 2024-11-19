  #include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

void calculate_average_times(Process proc[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void print_process_info(Process proc[], int n) {
    printf("\nProcess ID | Burst Time | Arrival Time | Priority | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%11d | %10d | %12d | %8d | %12d | %15d\n", 
               proc[i].id, 
               proc[i].burst_time, 
               proc[i].arrival_time, 
               proc[i].priority, 
               proc[i].waiting_time, 
               proc[i].turnaround_time);
    }
}

void priority_scheduling(Process proc[], int n, int preemptive) {
    // Sort processes based on arrival time and priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((proc[j].arrival_time > proc[j + 1].arrival_time) || 
                (proc[j].arrival_time == proc[j + 1].arrival_time && 
                 proc[j].priority > proc[j + 1].priority)) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    int current_time = 0;

    while (1) {
        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].burst_time > 0 && proc[i].arrival_time <= current_time) {
                all_done = 0;

                if (preemptive) {
                    // Preemptive Scheduling
                    current_time++;
                    proc[i].burst_time--;
                    if (proc[i].burst_time == 0) {
                        proc[i].turnaround_time = current_time - proc[i].arrival_time;
                        proc[i].waiting_time = proc[i].turnaround_time - (proc[i].burst_time + 1);
                    }
                } else {
                    // Non-Preemptive Scheduling
                    current_time += proc[i].burst_time;
                    proc[i].turnaround_time = current_time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - (proc[i].burst_time);
                    proc[i].burst_time = 0; // Mark as completed
                }
            }
        }
        if (all_done) break; // All processes are done
    }

    print_process_info(proc, n);
    calculate_average_times(proc, n);
}

void round_robin(Process proc[], int n, int quantum) {
    int remaining_burst[MAX], waiting_times[MAX] = {0};
    
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = proc[i].burst_time;
    }

    int current_time = 0;

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0) {
                done = 0; // There is a pending process
                if (remaining_burst[i] > quantum) {
                    current_time += quantum;
                    remaining_burst[i] -= quantum;
                } else {
                    current_time += remaining_burst[i];
                    waiting_times[i] += current_time - proc[i].burst_time;
                    remaining_burst[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++) {
        printf("Process ID: %d | Waiting Time: %d\n", 
               proc[i].id, 
               waiting_times[i]);
        proc[i].waiting_time = waiting_times[i];
        proc[i].turnaround_time = waiting_times[i] + proc[i].burst_time;
    }

    print_process_info(proc, n);
    calculate_average_times(proc, n);
}

int main() {
    Process processes[MAX];
    int n, choice, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Burst Time, Arrival Time and Priority for Process %d: ", processes[i].id);
        scanf("%d %d %d", &processes[i].burst_time, &processes[i].arrival_time, &processes[i].priority);
        processes[i].waiting_time = processes[i].turnaround_time = 0; // Initialize times
    }

    printf("Select Scheduling Algorithm:\n");
    printf("1. Preemptive Priority Scheduling\n");
    printf("2. Non-Preemptive Priority Scheduling\n");
    printf("3. Round Robin Scheduling\n");
    
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            priority_scheduling(processes, n, 1);
            break;
        case 2:
            priority_scheduling(processes, n, 0);
            break;
        case 3:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            round_robin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}

