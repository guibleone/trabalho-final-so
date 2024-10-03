#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "merge_sort.h"

int main(int argc, char *argv[])
{
  // Garante que o número de entradas é válido
  if (argc <= 4)
  {
    fprintf(stderr, "Uso correto: ./mergesort [2,4,8] <arquivo> <arquivo> ... -o <saida>\n");
    exit(EXIT_FAILURE);
  }

  unsigned int n_threads = atoi(argv[1]);
  if (n_threads != 2 && n_threads != 4 && n_threads != 8)
  {
    fprintf(stderr, "Número de threads deve ser 2, 4 ou 8.\n");
    exit(EXIT_FAILURE);
  }

  const char *output_file = argv[argc - 1];

  // LEITURA DOS NÚMEROS
  unsigned int total_numbers;
  int *numbers = getNumbers(argc, argv, &total_numbers);

  int *sorted_numbers = getSortedNumbers(numbers, total_numbers, n_threads);

  printSortedNumbers(sorted_numbers, total_numbers, output_file);

  free(numbers);
  free(sorted_numbers);

  return EXIT_SUCCESS;
}
