#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File {
    char name[30];
    int startBlock;
    int numBlocks;
    int *blocks;
};

int main() {
    int n;
    printf("Enter number of files : ");
    scanf("%d", &n);

    struct File *files = (struct File *)malloc(n * sizeof(struct File));

    for (int i = 0; i < n; i++) {
        printf("Enter file %d name : ", i + 1);
        scanf("%s", files[i].name);

        printf("Enter starting block of file %d : ", i + 1);
        scanf("%d", &files[i].startBlock);

        printf("Enter no of blocks in file %d : ", i + 1);
        scanf("%d", &files[i].numBlocks);

        files[i].blocks = (int *)malloc(files[i].numBlocks * sizeof(int));

        printf("Enter blocks for file %d : ", i + 1);
        for (int j = 0; j < files[i].numBlocks; j++) {
            scanf("%d", &files[i].blocks[j]);
        }
    }

    char search[30];
    printf("Enter the file name to be searched : ");
    scanf("%s", search);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(files[i].name, search) == 0) {
            printf("\nFile Name\tStart block\tNo. of blocks\tBlocks occupied\n");
            printf("%s\t\t%d\t\t%d\t\t", files[i].name, files[i].startBlock, files[i].numBlocks);
            for (int j = 0; j < files[i].numBlocks; j++) {
                printf("%d", files[i].blocks[j]);
                if (j != files[i].numBlocks - 1) printf(", ");
            }
            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("File not found!\n");

    for (int i = 0; i < n; i++)
        free(files[i].blocks);
    free(files);

    return 0;
}
