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

void printArray(int *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}