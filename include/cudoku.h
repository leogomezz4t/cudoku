#ifndef CUDOKU_H
#define CUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/utils.h"

typedef struct Point {
    int x;
    int y;
} Point;

int** getGrid(int **puzzle, int x, int y);

Point *getGridCoordinates(int **puzzle, int x, int y);

int* getColumn(int **puzzle, int x);

int solve(int **puzzle);

#endif