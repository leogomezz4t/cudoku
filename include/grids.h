#ifndef GRIDS_H
#define GRIDS_H

#include "../include/constants.h"
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

int** getGrid(int **puzzle, int x, int y);

Point *getGridCoordinates(int x, int y);

int *getGridArray(int **puzzle, int x, int y);

#endif