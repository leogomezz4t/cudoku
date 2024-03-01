#ifndef INTERSECT_H
#define INTERSECT_H

#include "../include/constants.h"
#include <stdlib.h>

typedef struct set {
    int *array;
    int length;
} Set;

/*
    Returns a Set struct pointer containing an int array with the intersection of three unique int arrays
*/
Set *intersection(int* setA, int aLen, int* setB, int bLen, int* setC, int cLen);

/*
    Returns a Set struct pointer containing an int array with the numbers from 1-9 that the input array does not have
*/
Set *getMissingNumbers(int *inputArray);

int contains(int *arr, int len, int val);

#endif