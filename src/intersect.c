#include <stdlib.h>
#include <stdio.h>
#include "../include/intersect.h"

/*
    Returns a Set struct pointer containing an int array with the intersection of three unique int arrays
*/
Set* intersection(int *setA, int aLen, int *setB, int bLen, int *setC, int cLen) {
    Set *ret = (Set*) malloc(sizeof(Set));
    ret->array = (int*) malloc(sizeof(int) * (aLen + bLen + cLen));
    int len = 0;
    int current = 0;
    for (int i = 0; i < aLen; i++) {
        for (int j = 0; j < bLen; j++) {
            if (setA[i] != setB[j]) {
                continue;
            }
            for (int k = 0; k < cLen; k++) {
                if (setA[i] != setC[k]) {
                    continue;
                }
                ret->array[current] = setA[i];
                len++;
                current++;
            }
        }
    }
    ret->array = (int*) realloc(ret->array, sizeof(int) * len);
    ret->length = len;
    return ret;
}