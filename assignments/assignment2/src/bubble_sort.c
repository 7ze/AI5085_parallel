#include "sortlib.h"

#include <omp.h>
#include <stdbool.h>
#include <stdio.h>

static void swap(size_t *a, size_t *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(size_t *list, size_t size) {
    bool swapped;
    for (size_t i = 0; i < size - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < size - 1; j++) {
            if (list[j] > list[j + 1]) {
                swapped = true;
                swap(&list[j], &list[j + 1]);
            }
        }
        if (swapped == false) {
            break;
        }
    }
}

void parallelized_bubble_sort(size_t *list, size_t size, size_t n_threads) {
    if (n_threads > 8) {
        n_threads = 8;
        printf("Using 8 threads!\n");
    }

    omp_set_num_threads(n_threads);
    bool swapped = false;

    printf("Parallelized bubble sort!\n");

    for (size_t k = 0; k < size - 1; k++) {
        swapped = false; // resets at start of each iteration

        if (k % 2 == 0) { // even phase
#pragma omp parallel for
            for (size_t i = 0; i < size / 2; i++) {
                if (list[2 * i] > list[2 * i + 1]) {
                    swap(&list[2 * i], &list[2 * i + 1]);
                    swapped = true;
                }
            }
        } else { // odd phase
#pragma omp parallel for
            for (size_t i = 0; i < size / 2 - 1; i++) {
                if (list[2 * i + 1] > list[2 * i + 2]) {
                    swap(&list[2 * i + 1], &list[2 * i + 2]);
                    swapped = true;
                }
            }
        }
        if (!swapped)
            break;
    }
}
