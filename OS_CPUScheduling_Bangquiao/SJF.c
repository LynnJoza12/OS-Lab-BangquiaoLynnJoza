#include <stdio.h>

void printTable(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[], float avgTAT, float avgWT) {
    printf("\nProcess Table:\n");
    printf("-------------------------------------------------\n");
    printf("%-5s %-5s %-5s %-5s %-5s %-5s\n", "PID", "AT", "BT", "CT", "TAT", "WT");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-5d %-5d %-5d %-5d %-5d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("-------------------------------------------------\n");
    printf("Average TAT = %.2f\n", avgTAT);
    printf("Average WT  = %.2f\n", avgWT);
}

void printGanttChart(int order[], int n, int timeline[]) {
    printf("\nGantt Chart (SJF Non-Preemptive):\n");
    printf("-------------------\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", order[i]);
    }
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf("%-6d", timeline[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], completed[n], order[n], timeline[n+1];
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i+1;
        completed[i] = 0;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int time = 0, done = 0, idx = 0;
    timeline[0] = 0;

    while (done < n) {
        int minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= time) {
                if (minIdx == -1 || bt[i] < bt[minIdx]) {
                    minIdx = i;
                }
            }
        }
        if (minIdx == -1) {
            time++;
            continue;
        }

        time += bt[minIdx];
        ct[minIdx] = time;
        tat[minIdx] = ct[minIdx] - at[minIdx];
        wt[minIdx] = tat[minIdx] - bt[minIdx];
        completed[minIdx] = 1;

        totalTAT += tat[minIdx];
        totalWT += wt[minIdx];

        order[idx] = pid[minIdx];
        timeline[idx+1] = time;
        idx++;
        done++;
    }

    printGanttChart(order, n, timeline);
    printTable(n, pid, at, bt, ct, tat, wt, totalTAT/n, totalWT/n);

    return 0;
}
