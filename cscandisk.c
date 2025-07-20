#include <stdio.h>
#include <stdlib.h>

#define MAXREQUEST 100
#define DISKSIZE 200

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cscan_total_seek(int requests[], int n, int start, int direction) {
    qsort(requests, n, sizeof(int), compare);

    int totalseek = 0;
    int current = start;
    printf("Service order:\n%d", current);

    if (direction == 1) {
        // Moving towards right
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                totalseek += abs(current - requests[i]);
                current = requests[i];
                printf(" → %d", current);
            }
        }

        if (current != DISKSIZE - 1) {
            totalseek += abs(current - (DISKSIZE - 1));
            current = DISKSIZE - 1;
            printf(" → %d", current);
        }

        // Jump to 0
        totalseek += DISKSIZE - 1;
        current = 0;
        printf(" → %d", current);

        for (int i = 0; i < n; i++) {
            if (requests[i] < start) {
                totalseek += abs(current - requests[i]);
                current = requests[i];
                printf(" → %d", current);
            }
        }
    } else {
        // Moving towards left
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= start) {
                totalseek += abs(current - requests[i]);
                current = requests[i];
                printf(" → %d", current);
            }
        }

        if (current != 0) {
            totalseek += current;
            current = 0;
            printf(" → %d", current);
        }

        // Jump to end
        totalseek += DISKSIZE - 1;
        current = DISKSIZE - 1;
        printf(" → %d", current);

        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] > start) {
                totalseek += abs(current - requests[i]);
                current = requests[i];
                printf(" → %d", current);
            }
        }
    }

    printf("\n");
    return totalseek;
}

int main() {
    int n, start, direction;
    int requests[MAXREQUEST];

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter request[%d]: ", i);
        scanf("%d", &requests[i]);
    }

    printf("Enter the start track: ");
    scanf("%d", &start);

    printf("Enter the direction (1 for right →, 0 for left ←): ");
    scanf("%d", &direction);

    int total = cscan_total_seek(requests, n, start, direction);
    printf("Total seek time: %d\n", total);

    return 0;
}
