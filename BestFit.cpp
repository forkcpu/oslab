Write a program using C/C++/Java to simulate the first fit, best fit and worst fit memory
allocation strategy. Assume memory chunk and initial requirement for memory block from
your side.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MemoryAllocator {
private:
    vector<int> memoryChunks; // Available memory chunks
    vector<bool> allocated;    // Allocation status of memory chunks

public:
    MemoryAllocator(vector<int> chunks) : memoryChunks(chunks), allocated(chunks.size(), false) {}

    // First Fit Memory Allocation
    void firstFit(int request) {
        for (size_t i = 0; i < memoryChunks.size(); i++) {
            if (!allocated[i] && memoryChunks[i] >= request) {
                allocated[i] = true;
                cout << "First Fit: Allocated " << request << " to memory chunk of size " << memoryChunks[i] << endl;
                return;
            }
        }
        cout << "First Fit: Not enough memory to allocate " << request << endl;
    }

    // Best Fit Memory Allocation
    void bestFit(int request) {
        int bestIndex = -1;
        for (size_t i = 0; i < memoryChunks.size(); i++) {
            if (!allocated[i] && memoryChunks[i] >= request) {
                if (bestIndex == -1 || memoryChunks[i] < memoryChunks[bestIndex]) {
                    bestIndex = i;
                }
            }
        }
        if (bestIndex != -1) {
            allocated[bestIndex] = true;
            cout << "Best Fit: Allocated " << request << " to memory chunk of size " << memoryChunks[bestIndex] << endl;
        } else {
            cout << "Best Fit: Not enough memory to allocate " << request << endl;
        }
    }

    // Worst Fit Memory Allocation
    void worstFit(int request) {
        int worstIndex = -1;
        for (size_t i = 0; i < memoryChunks.size(); i++) {
            if (!allocated[i] && memoryChunks[i] >= request) {
                if (worstIndex == -1 || memoryChunks[i] > memoryChunks[worstIndex]) {
                    worstIndex = i;
                }
            }
        }
        if (worstIndex != -1) {
            allocated[worstIndex] = true;
            cout << "Worst Fit: Allocated " << request << " to memory chunk of size " << memoryChunks[worstIndex] << endl;
        } else {
            cout << "Worst Fit: Not enough memory to allocate " << request << endl;
        }
    }
};

int main() {
    // Initial memory chunks
    vector<int> memoryChunks = {100, 500, 200, 300, 600};
    MemoryAllocator allocator(memoryChunks);

    // Memory requests
    vector<int> requests = {212, 417, 112, 426};

    cout << "Memory Allocation Simulation:" << endl;

    for (int request : requests) {
        allocator.firstFit(request);
    }

    cout << endl;

    // Reset allocation status for next strategy
    allocator = MemoryAllocator(memoryChunks);
    for (int request : requests) {
        allocator.bestFit(request);
    }

    cout << endl;

    // Reset allocation status for next strategy
    allocator = MemoryAllocator(memoryChunks);
    for (int request : requests) {
        allocator.worstFit(request);
    }

    return 0;
}

