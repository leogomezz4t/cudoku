#include <stdlib.h>
#include <stdio.h>
#include "../include/intersect.h"

/*
    Returns a Set struct pointer containing an int array with the intersection of two unique int arrays
*/
Set* intersection(int *setA, int aLen, int *setB, int bLen) {
    Set *ret = malloc(sizeof(Set));
    ret->array = (int*) malloc(sizeof(int) * (aLen + bLen));
    int len = 0;
    int current = 0;
    for (int i = 0; i < aLen; i++) {
        for (int j = 0; j < bLen; j++) {
            if (setA[i] != setB[j]) {
                continue;
            }
            ret->array[current] = setA[i];
            len++;
            current++;
        }
    }
    ret->array = (int*) realloc(ret->array, sizeof(int) * len);
    ret->length = len;
    return ret;
}