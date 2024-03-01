#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/intersect.h"
#include "../include/cudoku.h"

int main() {
    double totalTime = 0;
    double highestTime = -1;
    double lowestTime = -1;
    for (int i = 1; i <= 50; i++) {
        time_t beforeAll = clock();
        char path[50];
        sprintf(path, "./example_puzzles/grid_%02d.txt", i);
        printf("Attempting to solve grid %d\n", i);
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

        totalTime += allTimeTaken;
        if (highestTime == -1) {
            highestTime = allTimeTaken;
        } else {
            if (allTimeTaken > highestTime) {
                highestTime = allTimeTaken;
            }
        }
        if (lowestTime == -1) {
            highestTime = allTimeTaken;
        } else {
            if (allTimeTaken < lowestTime) {
                lowestTime = allTimeTaken;
            }
        }
        // Free memory
        free(matrix);
        getc(stdin);
    }

    printf("Total time taken: %lf\n", totalTime);
    printf("Average time taken: %lf\n", totalTime/50.0);
}
