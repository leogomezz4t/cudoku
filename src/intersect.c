#include <stdlib.h>
#include "../include/intersect.h"

int intersection(int *buffer, int bufferLength, int *setA, int aLen, int *setB, int bLen, int *setC, int cLen) {
    
    // Populate array with -1s
    for (int i = 0; i < bufferLength; i++) {
        buffer[i] = -1;
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
                if (contains(buffer, bufferLength, setA[i])) {
                    continue;
                }
                buffer[current] = setA[i];
                len++;
                current++;

                if (len >= bufferLength) {
                    return -1;
                }
            }
        }
    }
    return len;
}

int getUniqueValues(int *buffer, int bufferLength, int* a, int aLength, int* b, int bLength, int* c, int cLength) {
    int index = 0;

    for (int i = 0; i < aLength; i++) {
        if (elementExistsIn(a[i], buffer, index)) {
            continue;
        }

        buffer[index] = buffer[i];
        index++;
    }

    for (int i = 0; i < bLength; i++) {
        if (elementExistsIn(b[i], buffer, index)) {
            continue;
        }

        buffer[index] = b[i];
        index++;
    }

    for (int i = 0; i < cLength; i++) {
        if (elementExistsIn(c[i], buffer, index)) {
            continue;
        }

        buffer[index] = c[i];
        index++;
    }

    return index;
}

int getMissingNumbers(int *buffer, int bufferLength, int *inputArray) {
    int currentIndex = 0;
    for (int i = 1; i <= GRID_SIZE; i++) {
        if (contains(inputArray, GRID_SIZE, i)) {
            continue;
        }
        buffer[currentIndex] = i;
        currentIndex++;
    }

    return currentIndex;
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

int onlyExistsIn(int *inputArray, int inputLen, int *matchedArray, int matchedLen) {
    for (int i = 0; i < inputLen; i++) {
        if (!elementExistsIn(inputArray[i], matchedArray, matchedLen)) {
            return 0;
        }
    }

    return 1;
}

int elementExistsIn(int element, int *array, int len) {
    for (int i = 0; i < len; i++) {
        if (element == array[i]) {
            return 1;
        }
    }

    return 0;
}

int contains(int *arr, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }

    return 0;
}

int getPossibleValues(int *buffer, int **puzzle, int i, int j) {
    int *row = puzzle[i];
    int *column = getColumn(puzzle, j); // Must be freed
    int *gridArray = getGridArray(puzzle, j, i); // Must be freed

    int missingRow[GRID_SIZE] = { 0 };
    int missingColumn[GRID_SIZE] = { 0 };
    int missingGrid[GRID_SIZE] = { 0 };

    int missingRowLength = getMissingNumbers(missingRow, GRID_SIZE, row); 
    int missingColumnLength = getMissingNumbers(missingColumn, GRID_SIZE, column);
    int missingGridLength = getMissingNumbers(missingGrid, GRID_SIZE, gridArray);

    int possibleValuesLength = intersection(
        buffer, GRID_SIZE*3,
        missingRow, missingRowLength,
        missingColumn, missingColumnLength,
        missingGrid, missingGridLength
    );

    // Free my boy
    free(column);
    free(gridArray);

    return possibleValuesLength;
}

int removeElements(int *input, int inputLength, int* elementsToRemove, int elementsToRemoveLength) {
    int index = 0;
    for (int i = 0; i < inputLength; i++) {
        int inputElement = input[i];

        if (elementExistsIn(inputElement, elementsToRemove, elementsToRemoveLength)) {
            continue;
        }

        // Add element
        input[index] = inputElement;
        index++;
    }
    
    return index;
}