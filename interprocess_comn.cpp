/*

Problem Statement -:Write a C program to implement inter process communication using 
shared memory, pipes, named pipes and signals
*/#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, i, j, k;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    // Allocation Matrix
    vector<vector<int>> alloc(n, vector<int>(m));
    cout << "Enter the Allocation Matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    // Maximum Matrix
    vector<vector<int>> max(n, vector<int>(m));
    cout << "Enter the Maximum Matrix:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    // Available Resources
    vector<int> avail(m);
    cout << "Enter the Available Resources:" << endl;
    for (i = 0; i < m; i++) {
        cin >> avail[i];
    }

    // Need Matrix calculation
    vector<vector<int>> need(n, vector<int>(m));
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    vector<int> f(n, 0); // Finish array
    vector<int> ans;     // Safe sequence

    int ind = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                bool flag = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    ans.push_back(i);
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    bool safe = true;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = false;
            cout << "The system is not safe." << endl;
            break;
        }
    }

    if (safe) {
        cout << "Following is the SAFE Sequence:" << endl;
        for (i = 0; i < n - 1; i++) {
            cout << "P" << ans[i] << " -> ";
        }
        cout << "P" << ans[n - 1] << endl;
    }

    return 0;
}
