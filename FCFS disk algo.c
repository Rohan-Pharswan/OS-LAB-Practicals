#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, total_seek = 0;

    printf("Enter number of disk requests : ");
    scanf("%d", &n);

    int *req = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    for (i = 0; i < n - 1; i++) {
        int diff = req[i + 1] - req[i];
        if (diff < 0) diff = -diff;
        total_seek += diff;
    }

    printf("Total seek movement : %d\n", total_seek);

    free(req);
    return 0;
}
