#include <stdio.h>
#include <stdlib.h>

#include "../include/intersect.h"
#include "../include/parser.h"
#include "../include/utils.h"

int* getColumn(int **puzzle, int x) {
    int *array = (int*) malloc(sizeof(int) * GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; i++) {
        array[i] = puzzle[i][x];
    }
    return array;
}

int solve(int **puzzle) {
    // Iterate through each cell
    for (int i = 0; i < GRID_SIZE; i++) {
        int *row = puzzle[i];
        for (int j = 0; j < GRID_SIZE; j++) {
            int *column = getColumn(puzzle, j);
            int cell = puzzle[i][j];

            printf("Cell: %d\nRow: ", cell);
            printArray(row, GRID_SIZE);
            printf("Column: ");
            printArray(column, GRID_SIZE);
            break;
        }
    }
}