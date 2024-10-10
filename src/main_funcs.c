#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "thread_manager.h"

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
  int *sortedNumbers = malloc(total_numbers * sizeof(int));
  if (sortedNumbers == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para sortedNumbers.\n");
    exit(EXIT_FAILURE);
  }

  pthread_t *threadsIds = allocateThreadsIds(n_threads);
  Data *threads_data = malloc(n_threads * sizeof(Data));
  if (threads_data == NULL)
  {
    fprintf(stderr, "Erro ao alocar dados para as threads.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int chunck_size = total_numbers / n_threads;
  unsigned int reminder = total_numbers % n_threads;

  register unsigned int i;
  for (i = 0; i < n_threads; i++)
  {
    threads_data[i].numbers = numbers;
    threads_data[i].start = i * chunck_size;
    threads_data[i].end = (i == n_threads - 1) ? (i + 1) * chunck_size + reminder : (i + 1) * chunck_size;
    pthread_create(&threadsIds[i], NULL, sortThread, (void *)&threads_data[i]);
  }
  for (i = 0; i < n_threads; i++)
    pthread_join(threadsIds[i], NULL);

  mergeSortedChunks(sortedNumbers, threads_data, n_threads, total_numbers);

  free(threadsIds);
  free(threads_data);

  return sortedNumbers;
}
void printSortedNumbers(int *sorted_numbers, unsigned int total_numbers, const char *output_file)
{
  FILE *arq = fopen(output_file, "w");
  if (arq == NULL)
  {
    fprintf(stderr, "Erro ao abir arquivo de saída.\n");
    exit(EXIT_FAILURE);
  }
  for (unsigned int i = 0; i < total_numbers; i++)
    fprintf(arq, "%d\n", sorted_numbers[i]);

  fclose(arq);
}