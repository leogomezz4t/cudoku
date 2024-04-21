#ifndef CUDOKU_H
#define CUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"
#include "../include/grids.h"
#include "../include/constants.h"
#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/utils.h"

int solve(int **puzzle);

void solveRecursor(int **puzzle, int numRecursions, int method, int currentSolutions);

void obviousSingle(int **puzzle, int i, int j, int *possibleValues, int* solutionsFound);

void obviousPairs(int **puzzle, Point* obviousPair, Point* gridCoordinates, int* possibleValues, int possibleValuesLength, int* solutionsFound);

#endif