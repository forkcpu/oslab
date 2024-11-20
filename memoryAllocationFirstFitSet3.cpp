#include <iostream>
using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store block index allocated to each process
    for (int i = 0; i < n; i++) allocation[i] = -1; // Initialize allocation as -1 (not allocated)

    // Allocate memory to processes using the First Fit algorithm
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) { // If block can fit the process
                allocation[i] = j; // Assign block j to process i
                blockSize[j] -= processSize[i]; // Reduce available memory in block
                break; // Move to the next process
            }
        }
    }

    // Calculate total fragmentation
    int totalFragmentation = 0;
    for (int i = 0; i < m; i++) {
        totalFragmentation += blockSize[i];
    }

    // Display the allocation and total fragmentation
    cout << "First Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << endl;
        } else {
            cout << "Not Allocated\n";
        }
    }
    cout << "Total Fragmentation: " << totalFragmentation << endl;
}

int main() {
    // Memory blocks and process sizes
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};

    int m = sizeof(blockSize) / sizeof(blockSize[0]); // Number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]); // Number of processes

    // Call the First Fit allocation function
    firstFit(blockSize, m, processSize, n);

    return 0;
}
