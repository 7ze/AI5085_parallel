#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 10
#define RND_UP_BOUND 100

void randomize_array(int *arr, int len);
void add_arrays(const int *A, const int *B, int *C, int len);

int main() {
    srand(time(NULL));

    int A[ARRAY_LEN] = {0}, B[ARRAY_LEN] = {0}, C[ARRAY_LEN] = {0};

    randomize_array(A, ARRAY_LEN);
    randomize_array(B, ARRAY_LEN);

    printf("Array A:\n");
    for (size_t i = 0; i < ARRAY_LEN; i++) {
        printf("%5d", A[i]);
    }
    printf("\n");

    printf("Array B:\n");
    for (size_t i = 0; i < ARRAY_LEN; i++) {
        printf("%5d", B[i]);
    }
    printf("\n");

    add_arrays(A, B, C, ARRAY_LEN);

    printf("Array C = A + B:\n");
    for (size_t i = 0; i < ARRAY_LEN; i++) {
        printf("%5d", C[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

/*
 * randomize_array: fills up the array with random numbers
 *  NOTE:  mutates the original array!
 */
void randomize_array(int *arr, int len) {
#pragma omp parallel for
    for (size_t i = 0; i < len; i++) {
        arr[i] = rand() % RND_UP_BOUND;
    }
}

/*
 * add_arrays: adds arrays A and B and stores the result in C
 *  NOTE:  mutates the third array!
 */
void add_arrays(const int *A, const int *B, int *C, int len) {
#pragma omp parallel for
    for (size_t i = 0; i < len; i++) {
        C[i] = A[i] + B[i];
    }
}
