#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"
#include "../include/grids.h"
#include "../include/constants.h"
#include "../include/intersect.h"
#include "../include/parser.h"
#include "../include/utils.h"
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
                if (obviousPair->x != -1) { // found obvious pair
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
                        }
                    }
                }

                free(obviousPair);
            }
            
            // Free everyone
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