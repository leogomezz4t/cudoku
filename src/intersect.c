#include <stdlib.h>
#include "../include/intersect.h"

/*
    Returns a Set struct pointer containing an int array with the intersection of three unique int arrays
*/
Set* intersection(int *setA, int aLen, int *setB, int bLen, int *setC, int cLen) {
    Set *ret = (Set*) malloc(sizeof(Set));
    ret->length = aLen + bLen + cLen;
    ret->array = (int*) malloc(sizeof(int) * (ret->length));
    // Populate array with -1s
    for (int i = 0; i < ret->length; i++) {
        ret->array[i] = -1;
    }
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
                if (contains(ret->array, ret->length, setA[i])) {
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

int existsIn(int *arrayA, int aLen, int *arrayB, int bLen) {
    if (aLen > bLen) {
        return 0;
    }
    
    for (int i = 0; i < aLen; i++) {
        int found = 0;
        for (int j = 0; j < bLen; j++) {
            if (arrayA[i] == arrayB[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }

    return 1;
}

int contains(int *arr, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }

    return 0;
}

Set* getPossibleValues(int **puzzle, int i, int j) {
    int *row = puzzle[i];
    int *column = getColumn(puzzle, j); // Must be freed
    int *gridArray = getGridArray(puzzle, j, i); // Must be freed
    Set *missingRow, *missingColumn, *missingGrid; // all must be freed
    missingRow = getMissingNumbers(row); 
    missingColumn = getMissingNumbers(column);
    missingGrid = getMissingNumbers(gridArray);

    Set *possibleValues = intersection(
        missingRow->array, missingRow->length,
        missingColumn->array, missingColumn->length,
        missingGrid->array, missingGrid->length
    );

    // Free my boy
    free(column);
    free(gridArray);

    free(missingRow->array);
    free(missingColumn->array);
    free(missingGrid->array);
    free(missingRow);
    free(missingColumn);
    free(missingGrid);

    return possibleValues;
}

void removeElements(Set* inputSet, int* elementsToRemove, int lengthOfElements) {
    Set* ret;
    ret->array = (int*) malloc(sizeof(int) * inputSet->length);
    ret->length = 0;

    for (int i = 0; i < inputSet->length; i++) {
        int matched = 0;
        int inputElement = inputSet->array[i];

        for (int j = 0; j < lengthOfElements; j++) {
            int removeElement = elementsToRemove[j];

            if (inputElement == removeElement) {
                matched = 1;
                continue;
            }
        }

        if (matched) {
            continue;
        }

        // Add element
        ret->array[ret->length] = inputElement;
        ret->length++;
    }

    realloc(ret->array, sizeof(int) * ret->length);
    free(inputSet->array);
    free(inputSet);
    // Assign ret's address to inputSet
    inputSet = ret;
    // free ret
    free(ret->array);
    free(ret);
}