#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/*
    Returns an error code
    -1: opening file failed
    0: detected improper string
    1: valid
*/
int readPuzzle(char *filepath, int** puzzle) {
    int pathLength = strlen(filepath);
    if (filepath[pathLength] != '\0') { // make sure the string is nul terminated
        return 0;
    }
    FILE *fptr = fopen(filepath, "r");

    if (fptr == NULL) { // check if it was valid
        return -1;
    }

    // readline
    char buffer[GRID_SIZE+1];
    int row = 0;
    while (fgets(buffer, GRID_SIZE+1, fptr) != NULL) {
        if (buffer[0] == '\n') {
            continue;
        }
        puzzle[row] = (int*) malloc(sizeof(int) * GRID_SIZE);
        for (int i = 0; i < GRID_SIZE; i++) {
            int numVal = buffer[i] - '0';
            puzzle[row][i] = numVal;
        }
        row++;
    }

    return 1;
}

/*
    Returns an int** malloced to GRID_SIZE to be used with readPuzzle()
*/
int** createPuzzle() {
    return (int**) malloc(sizeof(int*) * GRID_SIZE);
}