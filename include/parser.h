#ifndef PARSER_H
#define PARSER_H

#include "../include/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
/*
    Returns an error code
    -1: opening file failed
    0: detected improper string
    1: valid
*/
int readPuzzle(char *filepath, int** puzzle);

/*
    Returns an int** malloced to GRID_SIZE to be used with readPuzzle()
*/
int** createPuzzle();

#endif