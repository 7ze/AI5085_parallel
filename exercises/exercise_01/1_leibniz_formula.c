#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITERATIONS 20000000

int main() {
    double start = omp_get_wtime();
    double pi, res = 0;
    int d = 1;

    for (size_t i = 0; i < MAX_ITERATIONS; i += 1) {
        res += (1. / d) - (1. / (d + 2));
        d += 4;
    }

    pi = res * 4;

    double end = omp_get_wtime();

    printf("Actual value of PI: %.10f\n", M_PI);
    printf("Calculated value of PI: %.10f\n", pi);
    printf("Difference: %.10f\n", M_PI - pi);
    printf("Time it took to compute: %.10f seconds\n", end - start);

    return EXIT_SUCCESS;
}
