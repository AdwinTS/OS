#include <stdio.h>

struct Process {
    int at, bt, ct, tat, wt, pid, completed, priority;
};

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int exec_order[n]; // to track execution order
    int eo_index = 0;

    for(int i=0; i<n; i++) {
        printf("Enter arrival time for P%d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time for P%d: ", i);
        scanf("%d", &p[i].bt);
        printf("Enter priority for P%d: ", i);
        scanf("%d", &p[i].priority);
        p[i].pid = i;
        p[i].completed = 0;
    }

    // Sort by arrival time
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time1 = 0, completed = 0;

    while(completed < n) {
        int min_priority = 9999;
        int idx = -1;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time1 && p[i].completed == 0) {
                if(p[i].priority < min_priority) {
                    min_priority = p[i].priority;
                    idx = i;
                }
                else if(p[i].priority == min_priority) {
                    if(p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            time1 = (time1 < p[idx].at) ? p[idx].at : time1;
            p[idx].ct = time1 + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            time1 += p[idx].bt;
            exec_order[eo_index++] = p[idx].pid;
            completed++;
        } else {
            time1++;
        }
    }

    printf("\n\tpid\tat\tbt\tct\ttat\twt\n");
    for(int i=0;i<n;i++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for(int i=0;i<n;i++) {
        printf("\tp[%d]\t|", exec_order[i]);
    }
    printf("\n0");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(exec_order[i] == p[j].pid) {
                printf("\t\t\t%d", p[j].ct);
                break;
            }
        }
    }

    // Averages
    float total_tat = 0, total_wt = 0;
    for(int i=0;i<n;i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("\n\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);
}
