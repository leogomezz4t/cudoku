#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/cudoku.h"

void singleTest() {
    time_t beforeAll = clock();
    char path[] = "./example_puzzles/grid_01.txt";
    int **matrix = createPuzzle();
    int code = readPuzzle(path, matrix);
    
    if (code == -1) {
        printf("Error opening file\n");
        return;
    } else if (code == 0) {
        printf("Detected improper string\n");
        return;
    }

    solve(matrix);
    time_t afterAll = clock();
    double allTimeTaken = (double)(afterAll-beforeAll) / CLOCKS_PER_SEC;
    printf("time taken: %lfs\n",allTimeTaken);
    printPuzzle(matrix);
}
