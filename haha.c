#include <stdio.h>
#include <stdlib.h>

int main() {
    int **matrix;
    matrix = malloc(3 * sizeof(int *));

    if (matrix == NULL) {
        printf("Memory allocation failed!!!\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        matrix[i] = malloc(3 * sizeof(int));

        if (matrix[i] == NULL) {
            printf("Allocation failed\n");
            return 1;
        }
    }

    //fill
    int value = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *(*(matrix + i) + j) = value++;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++) {
        free(matrix[i]);
    }

    free(matrix);
    
    return 0;
}