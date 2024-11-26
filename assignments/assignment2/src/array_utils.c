#include "array_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RND_BOUND 100

void print_array_cli(const int *list, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%5d", list[i]);
    }
    printf("\n\n");
}

/*
 * fill_array: fills array with random values.
 * NOTE: mutates initial array!
 *
 * @list: pointer to the array of integers.
 * @size: size of the array.
 */
void fill_array(int *list, const size_t size) {
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        list[i] = rand() % MAX_RND_BOUND;
    }
}
