

/* Problem Statement: Lab 3
Write a C program to compute and print the average waiting time,
average turnaround time and CPU burst times for the given list of
processes. Display/print the Gantt chart for first come first serve, shortest
job first, priority scheduling and round robin scheduling algorithm.
*/

#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
} Process;

void fcfs(Process p[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int bt[n];
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].burst_time;
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("FCFS Scheduling:\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);

    // Gantt Chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d |", p[i].pid);
    }
    printf("\n");
}

void sjf(Process p[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int bt[n];
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].burst_time;
    }

    // Sort processes by burst time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i].pid;
                p[i].pid = p[j].pid;
                p[j].pid = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("SJF Scheduling:\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);

    // Gantt Chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d |", p[i].pid);
    }
    printf("\n");
}

void priority(Process p[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int bt[n];
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].burst_time;
    }

    // Sort processes by priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority < p[j].priority) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Priority Scheduling:\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, bt[i], p[i].priority, wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);

    // Gantt Chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d |", p[i].pid);
    }
    printf("\n");
}

void round_robin(Process p[], int n, int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int bt[n];
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].burst_time;
    }

    int time = 0;
    int remaining[n];
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
    }

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = 0;
                if (remaining[i] > quantum) {
                    time += quantum;
                    remaining[i] -= quantum;
                } else {
                    time += remaining[i];
                    remaining[i] = 0;
                }
                printf("P%d |", p[i].pid);
            }
        }
        if (done) break;
    }
    printf("\n");

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Round Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    Process p[] = {
        {1, 0, 10, 3},
        {2, 1, 5, 1},
        {3, 2, 8, 2},
        {4, 3, 12, 4},
        {5, 4, 4, 5}
    };
    int n = sizeof(p) / sizeof(p[0]);

    fcfs(p, n);
    printf("\n");

    sjf(p, n);
    printf("\n");

    priority(p, n);
    printf("\n");

    round_robin(p, n, 2);
    printf("\n");

    return 0;
}

/*
Test Case: 
~/OS-Lab$ ./lab-3
FCFS Scheduling:
Process Burst Time  Waiting Time    Turnaround Time
P1  10      0       10
P2  5       10      15
P3  8       15      23
P4  12      23      35
P5  4       35      39
Average Waiting Time: 16.60
Average Turnaround Time: 24.40
Gantt Chart:
P1 |P2 |P3 |P4 |P5 |

SJF Scheduling:
Process Burst Time  Waiting Time    Turnaround Time
P5  4       0       4
P2  5       4       9
P3  8       9       17
P1  10      17      27
P4  12      27      39
Average Waiting Time: 11.40
Average Turnaround Time: 19.20
Gantt Chart:
P5 |P2 |P3 |P1 |P4 |

Priority Scheduling:
Process Burst Time  Priority    Waiting Time    Turnaround Time
P4  10      5       0       10
P1  5       4       10      15
P5  8       3       15      23
P3  12      2       23      35
P2  4       1       35      39
Average Waiting Time: 16.60
Average Turnaround Time: 24.40
Gantt Chart:
P4 |P1 |P5 |P3 |P2 |

P4 |P1 |P5 |P3 |P2 |P4 |P1 |P5 |P3 |P2 |P1 |P5 |P3 |P2 |P1 |P5 |P3 |P1 |P5 |P1 |
Round Robin Scheduling (Quantum = 2):
Process Burst Time  Waiting Time    Turnaround Time
P4  4       0       4
P1  12      4       16
P5  10      16      26
P3  8       26      34
P2  5       34      39
Average Waiting Time: 16.00
Average Turnaround Time: 23.80
*/
