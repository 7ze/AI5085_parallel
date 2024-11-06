#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int tid = 0;
#pragma omp parallel
    {
#pragma omp single
        printf("Total number of threads being used: %d\n",
               omp_get_num_threads());

        tid = omp_get_thread_num();
        printf("parallel thread id: %d\n", tid);
    }

    printf("Total number of threads being used: %d\n", omp_get_num_threads());
    printf("Non parallel thread id: %d\n", tid);

    return EXIT_SUCCESS;
}
