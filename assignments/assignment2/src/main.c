#include "array_utils.h"
#include "sortlib.h"

#include <getopt.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    BUBBLE_SORT,
    QUICK_SORT,
    MERGE_SORT,
    UNKOWN_ALGORITHM,
} algorithm;

typedef struct {
    algorithm algo;
    int n_threads;
    size_t array_size;
} Config;

const size_t DEFAULT_ARRAY_SIZE = 1000000;

void usage_info(char *binary_name);
algorithm parse_algorithm(const char *algorithm);
void sort(const Config *config, const char *algo);

int main(int argc, char **argv) {
    static struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {"threads", required_argument, NULL, 't'},
        {"arraysize", required_argument, NULL, 'n'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    int opt;
    char *algo, *endptr;
    bool invalid_array_size = false;
    Config config = {
        .algo = UNKOWN_ALGORITHM,
        .n_threads = 0,
        .array_size = DEFAULT_ARRAY_SIZE,
    };

    while ((opt = getopt_long(argc, argv, "a:t:n:h", long_options, NULL)) !=
           -1) {
        switch (opt) {
        case 'a':
            algo = optarg;
            config.algo = parse_algorithm(algo);
            break;

        case 't':
            config.n_threads = atoi(optarg);
            break;

        case 'n':
            config.array_size = strtoul(optarg, &endptr, 10);
            invalid_array_size = *endptr != '\0' ? true : false;
            break;

        case 'h':
            usage_info(argv[0]);
            return EXIT_SUCCESS;
        }
    }

    if (config.n_threads == 0 || config.algo == UNKOWN_ALGORITHM ||
        invalid_array_size) {
        usage_info(argv[0]);
        return EXIT_FAILURE;
    }

    sort(&config, algo);

    return EXIT_SUCCESS;
}

void usage_info(char *binary_name) {
    printf("Usage: %s [OPTIONS]..\n", binary_name);
    printf("  -a, --algorithm   [bubble/quick/merge]            Select which "
           "sorting algorithm to use (required)\n");
    printf("  -t, --threads     [1-8]                           Select the "
           "number of threads to use (required)\n");
    printf("  -n, --arraysize   [size]                          Choose the "
           "size of array (optional)\n");
    printf("  -h, --help                                        Display "
           "this help message\n");
}

algorithm parse_algorithm(const char *algorithm) {
    if (strcmp(algorithm, "bubble") == 0)
        return BUBBLE_SORT;
    else if (strcmp(algorithm, "quick") == 0)
        return QUICK_SORT;
    else if (strcmp(algorithm, "merge") == 0)
        return MERGE_SORT;
    else
        return UNKOWN_ALGORITHM;
}

void sort(const Config *config, const char *algo) {
    printf("The array size: %zu\n", config->array_size);
    printf("The number of threads: %d\n", config->n_threads);
    printf("The algorithm to use: %s sort algorithm\n", algo);

    double start_time = omp_get_wtime();

    srand(time(NULL));
    int *list = (int *)malloc(config->array_size * sizeof(size_t));

    fill_array(list, config->array_size);
    printf("\nFilled the array with random values!\n");
    /* print_array_cli(list, ARRAY_SIZE); */

    switch (config->algo) {

    case BUBBLE_SORT:
        printf("Using Bubble Sort!\n");
        if (config->n_threads == 1)
            bubble_sort(list, config->array_size);
        else
            parallelized_bubble_sort(list, config->array_size,
                                     config->n_threads);
        break;

    case QUICK_SORT:
        printf("Using Quick Sort!\n");
        if (config->n_threads == 1)
            quick_sort_aux(list, config->array_size);
        else
            parallelized_quick_sort_aux(list, config->array_size,
                                        config->n_threads);
        break;

    case MERGE_SORT:
        printf("Using Merge Sort!\n");
        break;

    default:
        printf("Unknown sorting algorithm! Please try again.\n");
        break;
    }

    printf("\nFinished Sorting!\n");
    free(list);
    /* print_array_cli(list, ARRAY_SIZE); */

    double end_time = omp_get_wtime();
    printf("COMPUTATION TIME: %.10f seconds\n", end_time - start_time);
}
