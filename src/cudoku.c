#include <stdio.h>
#include <stdlib.h>

#include "../include/grids.h"
#include "../include/constants.h"
#include "../include/intersect.h"
#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/cudoku.h"

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
            int *gridArray = getGridArray(puzzle, j, i);
            int cell = puzzle[i][j];

            Set * commonValues = intersection(row, GRID_SIZE, column, GRID_SIZE, gridArray, GRID_SIZE);
            printf("common len: %d\n", commonValues->length);
            /*
            printArray(row, GRID_SIZE);
            printArray(column, GRID_SIZE);
            printArray(gridArray, GRID_SIZE);
            */
            printf("intersection of x: %d y: %d is ", j, i);
            printArray(commonValues->array, commonValues->length);
            printf("\n");
            
            // Free everyone
            free(gridArray);
            free(commonValues);
        }
    }
}