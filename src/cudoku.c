#include <stdio.h>
#include <stdlib.h>

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

Point *getGridCoordinates(int **puzzle, int x, int y) {
    for (int i = (GRID_SIZE/3); i >= 0; i--) {
        int currentRowGrid = i*3;
        if (y < currentRowGrid) {
            continue;
        }
        for (int j = (GRID_SIZE/3); j >= 0; j--) {
            int currentColumnGrid = j*3;
            if (x < currentColumnGrid) {
                continue;
            }
            // Found grid
            Point *ret = (Point*) malloc(sizeof(Point));
            ret->x = j;
            ret->y = i;
            return ret;
        }
    }
}

int** getGrid(int **puzzle, int x, int y) {
    int **returnGrid = (int**) malloc(sizeof(int*) * 3);
    // Get the coordinates of the grid
    Point *coords = getGridCoordinates(puzzle, x, y);
    for (int i = 0; i < 3; i++) {
         returnGrid[i] = (int*) malloc(sizeof(int) * 3);
         for (int j = 0; j < 3; j++) {
            int adjustedRow = (coords->y) + i;
            int adjustedCol = (coords->x) + j;
            returnGrid[i][j] = puzzle[adjustedRow][adjustedCol];
         }
    }

    return returnGrid;
}

int solve(int **puzzle) {
    // Iterate through each cell
    for (int i = 0; i < GRID_SIZE; i++) {
        int *row = puzzle[i];
        for (int j = 0; j < GRID_SIZE; j++) {
            int *column = getColumn(puzzle, j);
            int **grid = getGrid(puzzle, j, i);
            int cell = puzzle[i][j];

            break;
        }
    }
}