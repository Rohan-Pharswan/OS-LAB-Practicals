#include <stdio.h>

int main() {
    int i, j, nb, np;
    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    int b[nb];
    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) scanf("%d", &b[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    int p[np], allocation[np];
    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &p[i]);
        allocation[i] = -1;
    }

    for (i = 0; i < np; i++) {
        int worst = -1;
        for (j = 0; j < nb; j++) {
            if (b[j] >= p[i]) {
                if (worst == -1 || b[j] > b[worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            allocation[i] = worst;
            b[worst] -= p[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, p[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, p[i]);
    }
    return 0;
}
