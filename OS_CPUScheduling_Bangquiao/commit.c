#include <stdio.h>
// HIIII
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

void printGanttChart(int order[], int timeline[], int idx) {
    printf("\nGantt Chart (Round Robin):\n");
    printf("-------------------------------------------------\n|");
    for (int i = 0; i < idx; i++) {
        printf("  P%d  |", order[i]);
    }
    printf("\n");
    for (int i = 0; i <= idx; i++) {
        printf("%-6d", timeline[i]);
    }
    printf("\n");
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n], order[100], timeline[101];
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i+1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, done = 0, idx = 0;
    timeline[0] = 0;

    while (done < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                flag = 1;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    totalTAT += tat[i];
                    totalWT += wt[i];
                    done++;
                }
                order[idx] = pid[i];
                timeline[idx+1] = time;
                idx++;
            }
        }
        if (!flag) time++;
    }

    printGanttChart(order, timeline, idx);
    printTable(n, pid, at, bt, ct, tat, wt, totalTAT/n, totalWT/n);

    return 0;
}
