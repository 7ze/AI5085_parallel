#ifndef SORT_LIB_H_
#define SORT_LIB_H_

#include <stdlib.h>

// bubble sort
void bubble_sort(int *list, size_t size);
void parallelized_bubble_sort(int *list, size_t size, size_t n_threads);

// quick sort
void quick_sort_aux(int *list, size_t size);
void parallelized_quick_sort(int *list, int start, int end);
void parallelized_quick_sort_aux(int *list, size_t size, int n_threads);

#endif // !SORT_LIB_H_
