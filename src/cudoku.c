#include <stdio.h>
#include <stdlib.h>

#include "../include/cudoku.h"

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
            }
            if (possibleValues->length == 2) { // Obvious Pairs
                Point* obviousPair = findObviousPair(puzzle, i, j, possibleValues); // must be freed
                // THE OBVIOUS PAIR IS THE COUNTERPART TO THIS CELL IN A PAIR
                if (obviousPair->x != -1) { // found obvious pair
                    //printf("FOUND OBVIOUS PAIR\nCoordinates x: %i y: %i\n", obviousPair->x, obviousPair->y);
                    // iterate through the grid
                    for (int gi = 0; gi < 3; gi++) {
                        for (int gj = 0; gj < 3; gj++) {
                            int gridI = gridCoordinates->y + gi;
                            int gridJ = gridCoordinates->x + gj;
                            int gridCell = puzzle[gridI][gridJ];

                            // dont remove notes from the obvious pair
                            if (gridI == obviousPair->y && gridJ == obviousPair->x) {
                                continue;
                            }

                            Set *gridPossibleValues = getPossibleValues(puzzle, gridI, gridJ);

                            // TODO: remove the pair values from the grid possible values and check for obvious singles
                            //printf("BEFORE\n");
                            //printArray(gridPossibleValues->array, gridPossibleValues->length);
                            Set* trimmedElements = removeElements(gridPossibleValues, possibleValues);
                            //printf("AFTER\n");
                            //printArray(trimmedElements->array, trimmedElements->length);

                            // Check if obvious single is left
                            if (trimmedElements->length == 1) {
                                puzzle[gridI][gridJ] = trimmedElements->array[0];
                                zeroesFound--;
                            }

                            // free everyone
                            free(trimmedElements->array);
                            free(trimmedElements);
                            free(gridPossibleValues->array);
                            free(gridPossibleValues);
                        }
                    }
                }

                free(obviousPair);
            }
            
            // Free everyone
            free(possibleValues->array);
            free(possibleValues);
            
            free(gridCoordinates);
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