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

void printGanttChart(int n, int pid[], int timeline[]) {
    printf("\nGantt Chart (FCFS):\n");
    printf("-------------------\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", pid[i]);
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

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], timeline[n+1];
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i+1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // FCFS Scheduling
    timeline[0] = (at[0] > 0) ? at[0] : 0;
    for (int i = 0; i < n; i++) {
        if (timeline[i] < at[i]) {
            timeline[i] = at[i]; // wait until process arrives
        }
        ct[i] = timeline[i] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        timeline[i+1] = ct[i];

        totalTAT += tat[i];
        totalWT += wt[i];
    }

    printGanttChart(n, pid, timeline);
    printTable(n, pid, at, bt, ct, tat, wt, totalTAT/n, totalWT/n);

    return 0;
}
