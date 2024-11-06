#include <math.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 4
#define MAX_ITERATIONS 5000000

void *calc(void *arg);

int main() {

    double start = omp_get_wtime();
    pthread_t threads[MAX_THREADS];
    int args[MAX_THREADS];
    double pi = 0;

    for (size_t i = 0; i < MAX_THREADS; i++) {
        args[i] = (2 * MAX_ITERATIONS * i) + 1;
        if (pthread_create(&threads[i], NULL, calc, &args[i]) != 0) {
            perror("Failed to create thread!\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < MAX_THREADS; i++) {
        double *res;
        if (pthread_join(threads[i], (void **)&res) != 0) {
            perror("Failed to join thread!\n");
        }
        pi += *res;
        free(res);
    }

    pi *= 4;

    double end = omp_get_wtime();

    printf("Actual value of PI: %.10f\n", M_PI);
    printf("Calculated value of PI: %.10f\n", pi);
    printf("Difference: %.10f\n", pi - M_PI);
    printf("Time it took to compute: %.10f seconds\n", end - start);

    return EXIT_SUCCESS;
}

void *calc(void *arg) {
    int d = *(int *)arg;

    double *res = (double *)malloc(sizeof(double));
    if (res == NULL) {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    *res = 0;
    for (size_t i = 0; i < MAX_ITERATIONS; i += 1) {
        *res += (1. / d) - (1. / (d + 2));
        d += 4;
    }
    return (void *)res;
}
