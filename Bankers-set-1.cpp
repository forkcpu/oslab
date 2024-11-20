/*Bankers Algorithm
#include <iostream>
using namespace std;

void calculateNeed(int need[][10], int max[][10], int alloc[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int max[][10], int alloc[][10], int n, int m) {
    int need[10][10];
    calculateNeed(need, max, alloc, n, m);

    bool finish[10] = {false};
    int safeSeq[10];
    int work[10];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool flag = true;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << safeSeq[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    int n = 5, m = 3;
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    isSafe(processes, avail, max, alloc, n, m);
    return 0;
}*/
