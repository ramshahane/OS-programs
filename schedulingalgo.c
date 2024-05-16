/*

Problem Statement -:Write a C program to compute and print the average waiting time, 
average turnaround time and CPU burst times for the given list of 
processes. Display/print the Gantt chart for first come first serve, shortest 
job first, priority scheduling and round robin scheduling algorithm. 
*/
#include<stdio.h>

float calculateAvgWaitingTime(int processes[], int n, int burstTime[], int waitingTime[])
{
    int i;
    float avgWaitingTime = 0;

   
    waitingTime[0] = 0;

    for(i = 1; i < n; i++)
    {
        waitingTime[i] = burstTime[i-1] + waitingTime[i-1];
        avgWaitingTime += waitingTime[i];
    }

    avgWaitingTime /= n; 

    return avgWaitingTime;
}


float calculateAvgTurnaroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[])
{
    int i;
    float avgTurnaroundTime = 0;

    for(i = 0; i < n; i++)
    {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }

    avgTurnaroundTime /= n; 

    return avgTurnaroundTime;
}

void displayGanttChart(int processes[], int n, int burstTime[], int choice)
{
    int i;
    char process_char = 'A';

    printf("\nGantt Chart:\n\n");
    printf(" ");
    for(i = 0; i < n; i++)
    {
        printf("-------");
    }
    printf("\n|");

    for(i = 0; i < n; i++)
    {
        printf("  P%c  |", process_char++);
    }
    printf("\n ");
    for(i = 0; i < n; i++)
    {
        printf("-------");
    }

    printf("\n0");
    for(i = 0; i < n; i++)
    {
        printf("      %d", burstTime[i]);
    }
    printf("\n\n");

    if(choice == 1)
    {
        printf("FCFS Scheduling Gantt Chart\n");
    }
    else if(choice == 2)
    {
        printf("SJF Scheduling Gantt Chart\n");
    }
}

void sortBurstTime(int processes[], int n, int burstTime[])
{
    int i, j, minIndex, temp;

    for(i = 0; i < n-1; i++)
    {
        minIndex = i;

        for(j = i+1; j < n; j++)
        {
            if(burstTime[j] < burstTime[minIndex])
            {
                minIndex = j;
            }
        }

        temp = burstTime[minIndex];
        burstTime[minIndex] = burstTime[i];
        burstTime[i] = temp;

        temp = processes[minIndex];
        processes[minIndex] = processes[i];
        processes[i] = temp;
    }
}

void sortPriority(int processes[], int n, int burstTime[], int priority[])
{
    int i, j, minIndex, temp;

    for(i = 0; i < n-1; i++)
    {
        minIndex = i;

        for(j = i+1; j < n; j++)
        {
            if(priority[j] < priority[minIndex])
            {
                minIndex = j;
            }
        }

        temp = burstTime[minIndex];
        burstTime[minIndex] = burstTime[i];
        burstTime[i] = temp;

        temp = priority[minIndex];
        priority[minIndex] = priority[i];
        priority[i] = temp;

        temp = processes[minIndex];
        processes[minIndex] = processes[i];
        processes[i] = temp;
    }
}

void roundRobinScheduling(int processes[], int n, int burstTime[], int quantum)
{
    int i, remainingTime[n], totalWaitingTime = 0, totalTime = 0;

    for(i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
    }

    while(1)
    {
        int done = 1;

        for(i = 0; i < n; i++)
        {
            if(remainingTime[i] > 0)
            {
                done = 0; 

                if(remainingTime[i] > quantum)
                {
                    totalTime += quantum;
                    remainingTime[i] -= quantum;
                }
                else
                {
                    totalTime += remainingTime[i];
                    totalWaitingTime += totalTime - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }

        if(done == 1)
            break;
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime/n);
    printf("\nAverage Turnaround Time: %.2f", (float)totalTime/n);
}

int main()
{
    int n, i, choice, quantum;
    char repeat;

    do {
        printf("\nEnter the number of processes: ");
        scanf("%d", &n);

        int processes[n];
        int burstTime[n];
        int waitingTime[n];
        int turnaroundTime[n];
        int priority[n];

        for(i = 0; i < n; i++)
        {
            printf("Enter the burst time for process P%d: ", i + 1);
            scanf("%d", &burstTime[i]);
            processes[i] = i + 1; 
        }

        do {
            printf("\nChoose a scheduling algorithm:\n");
            printf("1. First Come First Serve (FCFS)\n");
            printf("2. Shortest Job First (SJF)\n");
            printf("3. Priority Scheduling\n");
            printf("4. Round Robin Scheduling\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    displayGanttChart(processes, n, burstTime, choice);
                    printf("\nAverage Waiting Time: %.2f", calculateAvgWaitingTime(processes, n, burstTime, waitingTime));
                    printf("\nAverage Turnaround Time: %.2f", calculateAvgTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime));
                    break;

                case 2:
                    sortBurstTime(processes, n, burstTime);
                    displayGanttChart(processes, n, burstTime, choice);
                    printf("\nAverage Waiting Time: %.2f", calculateAvgWaitingTime(processes, n, burstTime, waitingTime));
                    printf("\nAverage Turnaround Time: %.2f", calculateAvgTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime));
                    break;

                case 3:
                    for(i = 0; i < n; i++)
                    {
                        printf("Enter the priority for process P%d: ", i + 1); // Start from P1
                        scanf("%d", &priority[i]);
                    }

                    sortPriority(processes, n, burstTime, priority);
                    displayGanttChart(processes, n, burstTime, choice);
                    printf("\nAverage Waiting Time: %.2f", calculateAvgWaitingTime(processes, n, burstTime, waitingTime));
                    printf("\nAverage Turnaround Time: %.2f", calculateAvgTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime));
                    break;

                case 4:
                    printf("Enter the time quantum: ");
                    scanf("%d", &quantum);
                    roundRobinScheduling(processes, n, burstTime, quantum);
                    break;

                default:
                    printf("Invalid choice. Please try again.\n");
            }

            printf("\nDo you want to repeat? (Y/N): ");
            scanf(" %c", &repeat);
        } while(repeat == 'Y' || repeat == 'y');

        printf("\nDo you want to enter new processes? (Y/N): ");
        scanf(" %c", &repeat);
    } while(repeat == 'Y' || repeat == 'y');

    return 0;
}