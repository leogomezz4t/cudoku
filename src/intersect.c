#include <stdlib.h>
#include "../include/constants.h"
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
                if (contains(ret->array, aLen+bLen+cLen, setA[i])) {
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

Set *getMissingNumbers(int *inputArray) {
    Set *ret = (Set*) malloc(sizeof(Set));
    ret->array = (int*) malloc(sizeof(int) * GRID_SIZE);
    int currentIndex = 0;
    for (int i = 1; i <= GRID_SIZE; i++) {
        if (contains(inputArray, GRID_SIZE, i)) {
            continue;
        }
        ret->array[currentIndex] = i;
        currentIndex++;
    }
    ret->length = currentIndex;
    ret->array = (int*) realloc(ret->array, sizeof(int) * ret->length);

    return ret;
}

int contains(int *arr, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }

    return 0;
}