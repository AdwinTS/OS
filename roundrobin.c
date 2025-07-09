#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt; // remaining time
    int ct;
    int tat;
    int wt;
};

struct Gantt {
    int pid;
    int start;
    int end;
};

void main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    struct Gantt gc[100];
int gc_index = 0;
    int completed = 0;
    int time = 0;
    int queue[100]; // to simulate ready queue
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
        p[i].pid = i;
        p[i].rt = p[i].bt;
        p[i].ct = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int visited[n];
    for(int i = 0; i < n; i++) visited[i] = 0;

    // Enqueue first arrived processes
    for(int i = 0; i < n; i++) {
        if(p[i].at == time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nGantt Chart:\n");
printf(" ");

int start_time = 0;

while(completed < n) {
    if(front == rear) {
        time++;
        for(int i = 0; i < n; i++) {
            if(p[i].at == time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        continue;
    }

    int idx = queue[front++];

    int exec_time = (p[idx].rt > tq) ? tq : p[idx].rt;
    start_time = time;
    time += exec_time;
    p[idx].rt -= exec_time;
    gc[gc_index].pid = p[idx].pid;
    gc[gc_index].start = start_time;
    gc[gc_index].end = time;
    gc_index++;


    // Print process box
    //printf("| P[%d] ", p[idx].pid+1);

    // Enqueue newly arrived processes
    for(int i = 0; i < n; i++) {
        if(p[i].at > (time - exec_time) && p[i].at <= time && visited[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    // If not completed, requeue
    if(p[idx].rt > 0) {
        queue[rear++] = idx;
    } else {
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        completed++;
    }
}
printf("|\n");

// Time markers
printf("\nGantt Chart:\n ");
for (int i = 0; i < gc_index; i++) {
    printf("| P[%d]\t", gc[i].pid + 1);
}
printf("|\n");

for (int i = 0; i < gc_index; i++) {
    printf("%d\t\t", gc[i].start);
}
printf("%d\n", gc[gc_index - 1].end);
printf("\n");
    // Print Table
    printf("\n\n\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    for(int i = 0; i < n; i++) {
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat/n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt/n);
}
