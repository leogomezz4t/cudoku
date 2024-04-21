#ifndef INTERSECT_H
#define INTERSECT_H

#include "../include/constants.h"
#include "../include/types.h"
#include "../include/grids.h"
#include <stdlib.h>

/*
    Returns the length of the buffer modified
*/
int intersection(int* buffer, int bufferLength, int* setA, int aLen, int* setB, int bLen, int* setC, int cLen);

/*
    Returns a Set struct pointer containing an int array with the numbers from 1-9 that the input array does not have
*/
int getMissingNumbers(int *buffer, int bufferLength, int *inputArray);

int existsIn(int *arrayA, int aLen, int *arrayB, int bLen);

int getUniqueValues(int *buffer, int bufferLength, int* a, int aLength, int* b, int bLength, int* c, int cLength);

int elementExistsIn(int element, int *array, int len);

int onlyExistsIn(int *inputArray, int inputLen, int *matchedArray, int matchedLen);

int contains(int *arr, int len, int val);

int getPossibleValues(int *buffer, int **puzzle, int i, int j);

int removeElements(int *input, int inputLength, int* elementsToRemove, int elementsToRemoveLength);

#endif