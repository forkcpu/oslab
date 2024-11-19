#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void fcfs(Process* processes, int n) {
    int totalWaitingTime = 0;
    int currentTime = 0;

    printf("\nProcess Execution Order (FCFS):\n");
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        totalWaitingTime += processes[i].waitingTime;
        currentTime += processes[i].burstTime;
        printf("Process %d executed at time %d\n", processes[i].id, currentTime);
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

void sjfNonPreemptive(Process* processes, int n) {
    int totalWaitingTime = 0;
    int currentTime = 0;

    // Sort processes based on arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrivalTime < processes[i].arrivalTime) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    printf("\nProcess Execution Order (SJF Non-Preemptive):\n");
    while (1) {
        int idx = -1;
        int minBurstTime = 999999;

        // Find the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime > 0 &&
                processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) break; // No process is ready to execute

        // Execute the selected process
        currentTime += processes[idx].burstTime;
        processes[idx].waitingTime = currentTime - processes[idx].arrivalTime - processes[idx].burstTime;
        totalWaitingTime += processes[idx].waitingTime;

        printf("Process %d executed at time %d\n", processes[idx].id, currentTime);

        // Mark this process as completed
        processes[idx].burstTime = 0; // Process is completed
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

void sjfPreemptive(Process* processes, int n) {
    int totalWaitingTime = 0;
    int currentTime = 0;
    int remainingBurst[n];

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingBurst[i] = processes[i].burstTime;
    }

    printf("\nProcess Execution Order (SJF Preemptive):\n");

    while (1) {
        int idx = -1;
        int minBurstTime = 999999;

        // Find the process with the smallest remaining burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime &&
                remainingBurst[i] > 0 &&
                remainingBurst[i] < minBurstTime) {
                minBurstTime = remainingBurst[i];
                idx = i;
            }
        }

        if (idx == -1) break; // No process is ready to execute

        // Execute the selected process for one time unit
        remainingBurst[idx]--;
        currentTime++;

        // If this process is completed
        if (remainingBurst[idx] == 0) {
            processes[idx].waitingTime = currentTime - processes[idx].arrivalTime - processes[idx].burstTime;
            totalWaitingTime += processes[idx].waitingTime;

            printf("Process %d completed at time %d\n", processes[idx].id, currentTime);
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process* processes = malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burstTime);
    }

    printf("Select the scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-Preemptive)\n");
    printf("3. SJF (Preemptive)\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            sjfNonPreemptive(processes, n);
            break;
        case 3:
            sjfPreemptive(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    free(processes);

    return 0;
}

