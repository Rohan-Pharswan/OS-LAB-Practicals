#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    const int DISK_START = 0, DISK_END = 199;
    int total_seek = 0;

    printf("Enter number of disk requests : ");
    scanf("%d", &n);

    int *req = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    // Sort requests in ascending order
    sort(req, n);

    // Head starts from beginning (0)
    int head = DISK_START;

    // Service all requests from 0 -> 199
    for (int i = 0; i < n; i++) {
        total_seek += abs(head - req[i]);
        head = req[i];
    }

    // Go to end of disk (if not already)
    total_seek += abs(DISK_END - head);
    head = DISK_END;

    // Jump back to beginning without servicing (circular return)
    total_seek += abs(DISK_END - DISK_START);
    head = DISK_START;

    // Service again in the same direction (0 -> ...)
    for (int i = 0; i < n; i++) {
        total_seek += abs(head - req[i]);
        head = req[i];
    }

    printf("Total seek movement : %d\n", total_seek);

    free(req);
    return 0;
}
