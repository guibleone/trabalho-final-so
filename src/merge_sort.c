#include <stdlib.h>
#include <stdio.h>

int *getNumbers(int argc, char *argv[], int *total_numbers)
{
  int *numbers = malloc(sizeof(int) * 100);
  if (numbers == NULL)
  {
    fprintf(stderr, "Erro ao alocar a memória.\n");
    exit(EXIT_FAILURE);
  }

  *total_numbers = 0;

  unsigned int n_files = argc - 4;

  for (unsigned int i = 2; i < n_files + 2; i++)
  {
    FILE *arq = fopen(argv[i], "r");
    if (arq == NULL)
    {
      fprintf(stderr, "Erro ao abirir arquivo %s.\n", argv[i]);
      free(numbers);
      exit(EXIT_FAILURE);
    }

    int num;
    while (fscanf(arq, "%d", &num) != EOF)
    {
      if (*total_numbers % 100 == 0)
      {
        numbers = realloc(numbers, (*total_numbers + 100) * sizeof(int));
        if (numbers == NULL)
        {
          fprintf(stderr, "Erro ao realocar memória para os números.\n");
          exit(EXIT_FAILURE);
        }
      }
      numbers[*total_numbers] = num;
      (*total_numbers)++;
    }
    fclose(arq);
  }

  return numbers;
}

int *getSortedNumbers(int *numbers, unsigned int total_numbers, int n_threads)
{
  int *sortedNumbers = malloc(sizeof(int));
  return sortedNumbers;
}
void printSortedNumbers(int *sorted_numbers, unsigned int total_numbers, const char *output_file)
{
}