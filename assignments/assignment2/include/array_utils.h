#ifndef ARRAY_UTILS_H_
#define ARRAY_UTILS_H_

#include <stdlib.h>

/**
 * print_array_cli: prints array to cli.
 *
 * @list: pointer to the array of integers.
 * @size: size of the array.
 */
void print_array_cli(const int *list, const size_t size);

/**
 * fill_array: fills array with random values.
 * NOTE: mutates initial array!
 *
 * @list: pointer to the array of integers.
 * @size: size of the array.
 */
void fill_array(int *list, const size_t size);

#endif // !ARRAY_UTILS_H_
