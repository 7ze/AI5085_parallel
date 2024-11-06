/*
 * serial implementation
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define RND_UPPER_BOUND 10

static inline void fill_row(int *row, const int n_cols);
void display_square_matrix(const int matrix[][N], const int n);
void display_column_vector(const int matrix[][1], const int n_rows);
void multiply(const int mat[][N], const int vec[][1], int product[][1]);

int main() {
    srand((unsigned int)time(NULL));
    double start_time = omp_get_wtime();

    int matrix[N][N], vector[N][1], product[N][1];

    // filling up the matrix and
    // the vector with random values
    for (size_t i = 0; i < N; i++) {
        fill_row(matrix[i], N);
        fill_row(vector[i], 1);
    }

    // displaying both the matrix
    printf("Matrix:\n");
    display_square_matrix(matrix, N);

    // and the vector
    printf("Vector:\n");
    display_column_vector(vector, N);

    // multiplying both and displaying
    // the product
    multiply(matrix, vector, product);
    printf("Product:\n");
    display_column_vector(product, N);

    double end_time = omp_get_wtime();
    printf("Time it took to compute: %.10f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}

static inline void fill_row(int *row, const int n_cols) {
    for (size_t i = 0; i < n_cols; i++) {
        row[i] = rand() % RND_UPPER_BOUND;
    }
}

void display_square_matrix(const int matrix[][N], const int n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void display_column_vector(const int matrix[][1], const int n_rows) {
    for (size_t i = 0; i < n_rows; i++) {
        printf("%4d\n", matrix[i][0]);
    }
    printf("\n");
}

void multiply(const int mat[][N], const int vec[][1], int product[][1]) {
    for (size_t i = 0; i < N; i++) {
        product[i][0] = 0;
        for (size_t j = 0; j < N; j++) {
            product[i][0] += mat[i][j] * vec[j][0];
        }
    }
}
