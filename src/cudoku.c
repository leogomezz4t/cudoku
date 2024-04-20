#include <stdio.h>
#include <stdlib.h>

#include "../include/cudoku.h"

#define OBVIOUS_SINGLE 1
#define OBVIOUS_PAIRS 2
#define OBVIOUS_TRIPLES 3

#define METHOD_END 4

int solve(int **puzzle) {
    int numRecursions = 0;
    solveRecursor(puzzle,0, OBVIOUS_SINGLE, 0);
    return numRecursions;
}


void obviousSingle(int **puzzle, int i, int j, Set* possibleValues, int* solutionsFound) {
    puzzle[i][j] = possibleValues->array[0];
    (*solutionsFound)++;
}

void obviousPairs(int **puzzle, Point* obviousPair, Point* gridCoordinates, Set* possibleValues, int* solutionsFound) {
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

            // If its not a zero it dont matter fr
            if (gridCell != 0) {
                continue;
            }

            /*
            printf("i: %d j: %d\n", gridI, gridJ);

            printf("The obvious pair values: ");
            printArray(possibleValues->array, possibleValues->length);
            */
            Set* gridPossibleValues = getPossibleValues(puzzle, gridI, gridJ);
            Set* trimmedElements = removeElements(gridPossibleValues, possibleValues);

            // Check if obvious single is left
            if (trimmedElements->length == 1) {
                printf("\nDEBUG FROM PAIRS: changing i: %d j: %d to %d\n", gridI, gridJ, trimmedElements->array[0]);
                obviousSingle(puzzle, gridI, gridJ, trimmedElements, solutionsFound);
            }

            // free everyone
            free(trimmedElements->array);
            free(trimmedElements);
            free(gridPossibleValues->array);
            free(gridPossibleValues);
        }
    }
}

void solveRecursor(int **puzzle, int numRecursions, int method, int currentSolutions) {
    printf("Currently using method: %d\n", method);
    numRecursions++;
    int zeroesFound = 0;
    int solutionsFound = 0;
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
            Set* possibleValues = getPossibleValues(puzzle, i, j);

            
            if (possibleValues->length == 0) {
                printf("ERROR WITH ZERO POSSIBLE VALUES\n");
                printf("i: %i j: %i\n", i, j);
            }
            
            if (possibleValues->length == 1 && method == OBVIOUS_SINGLE) { // Obvious Singles
                obviousSingle(puzzle, i, j, possibleValues, &solutionsFound);
            }
            if (possibleValues->length == 2 && method == OBVIOUS_PAIRS) { // Obvious Pairs
                Point* obviousPair = findObviousPair(puzzle, i, j, possibleValues); // must be freed
                // THE OBVIOUS PAIR IS THE COUNTERPART TO THIS CELL IN A PAIR
                if (obviousPair->x != -1) { // found obvious pair
                    obviousPairs(puzzle, obviousPair, gridCoordinates, possibleValues, &solutionsFound);
                }

                free(obviousPair);
            }
            if (method == OBVIOUS_TRIPLES) {
                obviousTriples(puzzle, i, j, gridCoordinates, &solutionsFound);
            }
            
            // Free everyone
            free(possibleValues->array);
            free(possibleValues);
            
            free(gridCoordinates);
        }
    }

    // check if it has been solved
    if (zeroesFound <= 0) {
        printf("Solved with %d recursions\n", numRecursions);
        return;
    }

    // update current solutions
    currentSolutions += solutionsFound;

    if (solutionsFound == 0) { // Method hasn't changed any zeroes
        method++; // Try the next method
        if (method == METHOD_END) {
            if (currentSolutions == 0) {
                printf("repeated number of zeroes detected and no more methods available. unsolvable\n");
                return;
            }
            printf("Resetting method.\n");
            method = OBVIOUS_SINGLE;
            solveRecursor(puzzle, numRecursions, method, 0);
        } else {
            printf("Trying new method: %d\n", method);
            solveRecursor(puzzle, numRecursions, method, currentSolutions);
        }
    } else {
        printf("another recursion with %d zeroes found\n", zeroesFound);
        solveRecursor(puzzle, numRecursions, method, currentSolutions);
    }
}