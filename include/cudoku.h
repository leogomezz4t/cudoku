#ifndef CUDOKU_H
#define CUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/grids.h"
#include "../include/constants.h"
#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/utils.h"

int* getColumn(int **puzzle, int x);

int solve(int **puzzle);

void solveRecursor(int **puzzle, int numRecursions, int lastZeroes);

#endif