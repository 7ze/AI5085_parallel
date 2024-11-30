#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000
#define MAX_RND_BOUND 100

void fill_array(int *list, int size);
size_t get_sum_parallel(int *list, int size);

int main() {
    double start_time = omp_get_wtime();

    srand(time(NULL));
    int list[ARRAY_SIZE];

    fill_array(list, ARRAY_SIZE);
    printf("Filled the array with random values!\n");

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        printf("%3d", list[i]);
    }
    printf("\n\n");

    size_t sum = get_sum_parallel(list, ARRAY_SIZE);
    printf("Sum of the values in the array: %zu\n", sum);

    double end_time = omp_get_wtime();
    printf("Time it took to compute: %.10f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}

/*
 * fill_array: fills array with random values.
 * NOTE: mutates initial array!
 *
 * @list: pointer to the array of integers.
 * @size: size of the array.
 */
void fill_array(int *list, int size) {
    for (size_t i = 0; i < size; i++) {
        list[i] = rand() % MAX_RND_BOUND;
    }
}

/*
 * get_sum: returns the sum of the array.
 *
 * @list: pointer to the array of integers.
 * @size: size of the array.
 *
 * return: returns the sum as a size_t
 */
size_t get_sum_parallel(int *list, int size) {
    size_t sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < size; i++) {
        sum += list[i];
    }
    return sum;
}
