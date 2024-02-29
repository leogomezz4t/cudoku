#include <stdio.h>
#include "../include/parser.h"

void printPuzzle(int **matrix) {
    printf("[\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("\t[");
        for (int j = 0; j < GRID_SIZE; j++) {
            printf(" %d", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

void printGrid(int **grid) {
    printf("[\n]");
    for (int i = 0; i < 3; i++) {
        printf("\t[");
        for (int j = 0; j < 3; j++) {
            printf(" %d", grid[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

void printArray(int *arr, int len) {
    if (len <= 0) {
        return;
    }
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}