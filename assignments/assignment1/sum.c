/*
100.000.000 Natural Numbers

Write a program "sum.c" which calculates the sum of the first 100,000,000
natural numbers.

    a) Distribute the work over 10 pthreads.
    b) What does the same program look like with OpenMP?
    c) Is a solution in which sections or tasks are used possible and sensible?

Justify in writing (max 1/2 page) and/or add code/functions to your program to
justify
*/

#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t N = 100000000;
const size_t THREADS = 10;
const size_t INTERVAL = N / THREADS;

enum Mode {
    DEFAULT_MODE,
    PTHREAD_MODE,
    OMP_MODE,
};

void print_help();
int default_sum();
int pthread_sum();
int omp_sum();
void *calc_partial_sum(void *arg);

int main(int argc, char **argv) {
    enum Mode mode = DEFAULT_MODE;
    double start_time = omp_get_wtime();

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) { // Check for help argument
            print_help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[1], "--pthread") == 0) {
            mode = PTHREAD_MODE;
        } else if (strcmp(argv[1], "--omp") == 0) {
            mode = OMP_MODE;
        } else {
            printf("Unknown argument %s!\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    switch (mode) {
    case DEFAULT_MODE:
        default_sum();
        break;

    case PTHREAD_MODE:
        pthread_sum();
        break;

    case OMP_MODE:
        omp_sum();
        break;
    }

    double end_time = omp_get_wtime();
    printf("Time it took to compute: %.10f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}

/*
 * print_help - Displays the help message for command-line arguments
 */
void print_help() {
    printf("Usage: ./sum [OPTION]\n");
    printf("Calculate the sum of the first %zu natural numbers using different "
           "methods.\n\n",
           N);
    printf("Options:\n");
    printf("  --pthread    Use pthreads to calculate the sum.\n");
    printf("  --omp        Use OpenMP to calculate the sum.\n");
    printf("  --help       Display this help message and exit.\n");
    printf("If no option is provided, the default sum method will be used.\n");
}

/*
 * default_sum - Calculates the sum of natural numbers using simple maths
 * formula
 */

int default_sum() {
    size_t sum = N * (N + 1) / 2;
    printf("Sum of first %zu natural numbers is %zu\n", N, sum);
    return EXIT_SUCCESS;
}

/*
 * pthread_sum - Calculates the sum of natural numbers using pthreads
 */

int pthread_sum() {
    pthread_t threads[THREADS];
    size_t start_interval[THREADS];
    size_t sum = 0;

    for (size_t i = 0; i < THREADS; i++) {
        start_interval[i] = i * INTERVAL + 1;
        if (pthread_create(&threads[i], NULL, calc_partial_sum,
                           &start_interval[i]) != 0) {
            perror("Failed to create thread!\n");
            fprintf(stderr, "Thread creation error at index %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < THREADS; i++) {
        size_t *partial_sum;
        if (pthread_join(threads[i], (void **)&partial_sum) != 0) {
            perror("Failed to join thread!\n");
            fprintf(stderr, "Thread join error at index %zu\n", i);
            return EXIT_FAILURE;
        }
        if (partial_sum != NULL) {
            sum += *partial_sum;
            free(partial_sum);
        } else {
            fprintf(stderr, "Returned NULL partial sum from thread %zu!\n", i);
        }
    }

    printf("Sum of first %zu natural numbers is %zu\n", N, sum);
    return EXIT_SUCCESS;
}

/*
 * calc_partial_sum - Calculates the sum of natural numbers in a range.
 *
 * @arg: A void pointer to a `size_t` that represents the start of the
 * interval.
 *
 * Return: void pointer to the dynamically allocated result (partial sum) or
 * NULL on failure.
 */

void *calc_partial_sum(void *arg) {
    size_t start = *(size_t *)arg;
    size_t *partial_sum = (size_t *)malloc(sizeof(size_t));

    if (partial_sum == NULL) {
        perror("Memory allocation failed.\n");
        return NULL;
    }

    *partial_sum = 0;
    for (size_t i = start; i < start + INTERVAL && i <= N; i++) {
        *partial_sum += i;
    }

    return (void *)partial_sum;
}

/*
 * omp_sum - Calculates the sum of natural numbers using Open MP directives
 */
int omp_sum() {
    size_t sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 1; i <= N; i++) {
        sum += i;
    }

    printf("Sum of first %zu natural numbers is %zu\n", N, sum);
    return EXIT_SUCCESS;
}
