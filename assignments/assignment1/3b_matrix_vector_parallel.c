/*
 * parallel implementation
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define RND_UPPER_BOUND 10

static inline void fill_row(int *row, const int n_cols);
void display_square_matrix(int **matrix, const int n);
void display_column_vector(int **matrix, const int n_rows);
void multiply(int **mat, int **vec, int **product);

int main() {
    srand((unsigned int)time(NULL));
    double start_time = omp_get_wtime();

    int **matrix = malloc(N * sizeof(int *));
    int **vector = malloc(N * sizeof(int *));
    int **product = malloc(N * sizeof(int *));

    for (size_t i = 0; i < N; i++) {
        matrix[i] = malloc(N * sizeof(int));
        vector[i] = malloc(sizeof(int));
        product[i] = malloc(sizeof(int));
    }

    for (size_t i = 0; i < N; i++) {
        fill_row(matrix[i], N);
        fill_row(vector[i], 1);
    }

    /* printf("Matrix:\n"); */
    /* display_square_matrix(matrix, N); */

    /* printf("Vector:\n"); */
    /* display_column_vector(vector, N); */

    multiply(matrix, vector, product);

    /* printf("Product:\n"); */
    /* display_column_vector(product, N); */

    double end_time = omp_get_wtime();
    printf("Time it took to compute: %.10f seconds\n", end_time - start_time);

    for (size_t i = 0; i < N; i++) {
        free(matrix[i]);
        free(vector[i]);
        free(product[i]);
    }
    free(matrix);
    free(vector);
    free(product);

    return EXIT_SUCCESS;
}

static inline void fill_row(int *row, const int n_cols) {
    for (size_t i = 0; i < n_cols; i++) {
        row[i] = rand() % RND_UPPER_BOUND;
    }
}

void display_square_matrix(int **matrix, const int n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void display_column_vector(int **matrix, const int n_rows) {
    for (size_t i = 0; i < n_rows; i++) {
        printf("%4d\n", matrix[i][0]);
    }
    printf("\n");
}

void multiply(int **mat, int **vec, int **product) {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
        int sum = 0;
#pragma omp parallel for reduction(+ : sum)
        for (size_t j = 0; j < N; j++) {
            sum += mat[i][j] * vec[j][0];
        }
        product[i][0] = sum;
    }
}
