#include <stdio.h>
#include <stdlib.h>

#define MAXREQUEST 100 
#define DISKSIZE 200 

int compare(const void *a, const void *b)
{
   return (*(int*)a - *(int*)b);
}

int calculatetotal(int requests[MAXREQUEST], int n, int start, int direction)
{
    qsort(requests, n, sizeof(int), compare);
    int currenttrack = start;
    int totalseek = 0;

    if (direction == 1)  
    {
        
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                totalseek += abs(currenttrack - requests[i]);
                currenttrack = requests[i];
            }
        }
       
        if (currenttrack != DISKSIZE - 1) {
            totalseek += abs(currenttrack - (DISKSIZE - 1));
            currenttrack = DISKSIZE - 1;
        }
        
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < start) {
                totalseek += abs(currenttrack - requests[i]);
                currenttrack = requests[i];
            }
        }
    }
    else  
    {
        
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= start) {
                totalseek += abs(currenttrack - requests[i]);
                currenttrack = requests[i];
            }
        }
       
        if (currenttrack != 0) {
            totalseek += abs(currenttrack - 0);
            currenttrack = 0;
        }
        
        for (int i = 0; i < n; i++) {
            if (requests[i] > start) {
                totalseek += abs(currenttrack - requests[i]);
                currenttrack = requests[i];
            }
        }
    }

    return totalseek;
}

int main() {
    int n, start, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAXREQUEST) {
        printf("Error: invalid number of requests.\n");
        return 1;
    }

    int requests[n];
    for (int i = 0; i < n; i++) {
        printf("Enter request[%d]: ", i);
        scanf("%d", &requests[i]);
    }

    printf("Enter the start track: ");
    scanf("%d", &start);

    printf("Enter the direction (1 for right →, 0 for left ←): ");
    scanf("%d", &direction);

    int totalseek = calculatetotal(requests, n, start, direction);
    printf("Total seek time: %d\n", totalseek);

    return 0;
}
