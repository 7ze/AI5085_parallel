#include <stdio.h>
#include <stdlib.h>

#define R1 3
#define C1 3
#define R2 3
#define C2 1

void matrix_calc(int m1[R1][C1], int m2[R2][C2]);

int main() {
    int m1[R1][C1] = {
        {5, 8, -4},
        {6, 9, -5},
        {4, 7, -2},
    };
    int m2[R2][C2] = {
        {2},
        {-3},
        {1},
    };

    if (C1 != R2) {
        printf("The number of columns of matrix 1 should be equal to the "
               "number of rows in matrix 2\n");
        printf("Incompatible matrix multiplication!\n");
        return EXIT_FAILURE;
    }

    matrix_calc(m1, m2);
    return EXIT_SUCCESS;
}

void matrix_calc(int m1[R1][C1], int m2[R2][C2]) {
    int result[R1][C2];
    for (size_t i = 0; i < R1; i++) {
        for (size_t j = 0; j < C2; j++) {
            result[i][j] = 0;
            for (size_t k = 0; k < R2; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    for (size_t i = 0; i < R1; i++) {
        for (size_t j = 0; j < C2; j++) {
            printf("%5d", result[i][j]);
        }
        printf("\n");
    }

    return;
}
