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

Set* getPossibleValues(int **puzzle, int i, int j) {
    int *row = puzzle[i];
    int *column = getColumn(puzzle, j); // Must be freed
    int *gridArray = getGridArray(puzzle, j, i); // Must be freed
    Set *missingRow, *missingColumn, *missingGrid; // all must be freed
    missingRow = getMissingNumbers(row); 
    missingColumn = getMissingNumbers(column);
    missingGrid = getMissingNumbers(gridArray);

    Set *possibleValues = intersection(
        missingRow->array, missingRow->length,
        missingColumn->array, missingColumn->length,
        missingGrid->array, missingGrid->length
    );

    // Free my boy
    free(column);
    free(gridArray);

    free(missingRow->array);
    free(missingColumn->array);
    free(missingGrid->array);
    free(missingRow);
    free(missingColumn);
    free(missingGrid);

    return possibleValues;
}

int solve(int **puzzle) {
    int numRecursions = 0;
    solveRecursor(puzzle,0, -1);
    return numRecursions;
}

void solveRecursor(int **puzzle, int numRecursions, int lastZeroes) {
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

            Point* gridCoordinates = getGridCoordinates(j, i); // must be freed

            Set *possibleValues = getPossibleValues(puzzle, i, j);
            /*
            printf("intersect: ");
            printArray(possibleValues->array, possibleValues->length);
            printf("\n");
            */
            if (possibleValues->length == 1) { // Obvious Singles
                //printf("found answer at i: %d j: %d\n", i, j);
                puzzle[i][j] = possibleValues->array[0];
                zeroesFound--;
            } else if (possibleValues->length == 2) { // Obvious Pairs
                // Iterate through the zeroes in the grid
                for (int gi = 0; gi < 3; gi++) {
                    for (int gj = 0; gj < 3; gj++) {
                        int gridI = gridCoordinates->y + gi;
                        int gridJ = gridCoordinates->x + gj;
                        int gridCell = puzzle[gridI][gridJ];
                        
                        if (gridCell != 0) {
                            continue;
                        }

                        Set* gridCellPossibleValues = getPossibleValues(puzzle, gridI, gridJ);
                    }
                }
            }
            
            // Free everyone
            free(gridCoordinates);

            free(missingRow->array);
            free(missingColumn->array);
            free(missingGrid->array);
            free(possibleValues->array);

            free(missingRow);
            free(missingColumn);
            free(missingGrid);
            free(possibleValues);
        }
    }

    // check if it has been solved
    if (zeroesFound > 0) {
        if (zeroesFound == lastZeroes) {
            printf("repeated number of zeroes detected. unsolvable\n");
            return;
        }
        printf("another recursion with %d zeroes found\n", zeroesFound);
        solveRecursor(puzzle, numRecursions, zeroesFound);
    } else {
        printf("Solved with %d recursions\n", numRecursions);
    }
}