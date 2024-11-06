#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    double start = omp_get_wtime();
    size_t n = 1000000000;
    double sum = 0.0, term;

    for (size_t i = 0; i < n; i++) {
        term = 1.0 / (i * 4.0 + 1.0) - 1.0 / (i * 4.0 + 3.0);
        sum += term;
    }

    double pi = 4.0 * sum;

    printf("%.20f --- approximate value of Pi\n", pi);
    printf("%.20f --- actual value of Pi\n", M_PI);
    printf("%.20f --- difference \n", M_PI - pi);

    double end = omp_get_wtime();
    printf("Time it took to compute: %.10f seconds\n", end - start);

    return EXIT_SUCCESS;
}
