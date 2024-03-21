#ifndef GRIDS_H
#define GRIDS_H

#include "../include/constants.h"
#include "../include/types.h"
#include "../include/intersect.h"
#include <stdlib.h>

int* getColumn(int **puzzle, int x);

int** getGrid(int **puzzle, int x, int y);

Point *getGridCoordinates(int x, int y);

int *getGridArray(int **puzzle, int x, int y);

Point* findObviousPair(int **puzzle, int i, int j, Set* possibleValues);

#endif