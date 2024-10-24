#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_funcs.h"

int main(int argc, char *argv[]) {
    if (argc <= 4) {
        fprintf(stderr, "Uso correto: ./mergesort [2,4,8] <arquivo> <arquivo> "
                        "... -o <saida>\n");
        exit(EXIT_FAILURE);
    }

    unsigned int n_threads = atoi(argv[1]);


    // LEITURA DOS NÚMEROS
    int total_numbers;
    int *numbers = getNumbers(argc, argv, &total_numbers);

    int *sorted_numbers = getSortedNumbers(numbers, total_numbers, n_threads);

    printSortedNumbers(sorted_numbers, total_numbers, output_file);

    free(numbers);
    free(sorted_numbers);

    return EXIT_SUCCESS;
}
