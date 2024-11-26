#include "sortlib.h"
#include <omp.h>
#include <stdio.h>

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(int *list, int start, int end) {
    int pivot = list[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (list[j] < pivot) {
            i += 1;
            swap(&list[i], &list[j]);
        }
    }
    i += 1;
    swap(&list[i], &list[end]);
    return i;
}

void quick_sort(int *list, int start, int end) {
    if (end <= start)
        return;
    int pivot = partition(list, start, end);
    quick_sort(list, start, pivot - 1);
    quick_sort(list, pivot + 1, end);
}

void quick_sort_aux(int *list, size_t size) { quick_sort(list, 0, size - 1); }

void parallelized_quick_sort(int *list, int start, int end) {
    if (end <= start)
        return;
    int pivot = partition(list, start, end);
#pragma omp task shared(list)
    parallelized_quick_sort(list, start, pivot - 1);
#pragma omp task shared(list)
    parallelized_quick_sort(list, pivot + 1, end);
}

void parallelized_quick_sort_aux(int *list, size_t size, int n_threads) {
    omp_set_num_threads(n_threads);
    printf("Parallelized quick sort!\n");
#pragma omp parallel
    {
#pragma omp single
        parallelized_quick_sort(list, 0, size - 1);
    }
}
