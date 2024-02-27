#ifndef INTERSECT_H
#define INTERSECT_H

#include <stdlib.h>

typedef struct set {
    int *array;
    int length;
} Set;

/*
    Returns a Set struct pointer containing an int array with the intersection of two unique int arrays
*/
Set *intersection(int* setA, int aLen, int* setB, int bLen);

#endif