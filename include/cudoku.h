#ifndef CUDOKU_H
#define CUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/utils.h"

Set* getColumn(int **puzzle, int x);

int solve(int **puzzle);

#endif