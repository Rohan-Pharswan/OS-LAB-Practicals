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

    // Sort requests to process in order
    sort(req, n);

    // Head starts from beginning (0)
    int head = DISK_START;

    // Move from 0 -> 199 (servicing all requests)
    for (int i = 0; i < n; i++) {
        total_seek += abs(head - req[i]);
        head = req[i];
    }

    // Move from last request to end of disk (199)
    total_seek += abs(DISK_END - head);
    head = DISK_END;

    // Now reverse: move back toward 0
    for (int i = n - 1; i >= 0; i--) {
        total_seek += abs(head - req[i]);
        head = req[i];
    }

    printf("Total seek movement : %d\n", total_seek);

    free(req);
    return 0;
}
