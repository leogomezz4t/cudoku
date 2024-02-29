#include <stdio.h>
#include <stdlib.h>

#include "../include/grids.h"
#include "../include/constants.h"
#include "../include/intersect.h"
#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/cudoku.h"

int numRecursions = 0;

int* getColumn(int **puzzle, int x) {
    int *array = (int*) malloc(sizeof(int) * GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; i++) {
        array[i] = puzzle[i][x];
    }
    return array;
}

int solve(int **puzzle) {
    numRecursions++;
    int zeroesFound = 0;
    // Iterate through each cell
    for (int i = 0; i < GRID_SIZE; i++) {
        int *row = puzzle[i];
        for (int j = 0; j < GRID_SIZE; j++) {
            int cell = puzzle[i][j];
            if (cell != 0) { // If the element is already defined don't change it
                continue;
            }
            // increment zeroes
            zeroesFound++;
            // -----
            int *column = getColumn(puzzle, j); // Must be freed
            int *gridArray = getGridArray(puzzle, j, i); // Must be freed
            Set *missingRow, *missingColumn, *missingGrid; // all must be freed
            missingRow = getMissingNumbers(row); 
            missingColumn = getMissingNumbers(column);
            missingGrid = getMissingNumbers(gridArray);
            // free the original arrays
            free(gridArray);
            free(column);
            // ----

            Set *commonValues = intersection(
                missingRow->array, missingRow->length,
                missingColumn->array, missingColumn->length,
                missingGrid->array, missingGrid->length
            );

            if (commonValues->length == 1) {
                //printf("found answer at i: %d j: %d\n", i, j);
                puzzle[i][j] = commonValues->array[0];
                zeroesFound--;
            }
            
            // Free everyone
            free(gridArray);
            free(missingRow);
            free(missingColumn);
            free(missingGrid);
            free(commonValues);
        }
    }

    // check if it has been solved
    if (zeroesFound > 0) {
        printf("another recursion with %d zeroes found\n", zeroesFound);
        solve(puzzle);
    } else {
        printf("Solved with %d recursions\n", numRecursions);
    }
}