#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

typedef struct
{
  int *numbers;
  unsigned int start;
  unsigned int end;
} Data;

pthread_t *allocateThreadsIds(unsigned int n_threads);
void *sortThread(void *args);
void mergeSortedChunks(int *sortedNumbers, Data *threads_data, int n_threads, unsigned int total_numbers);

#endif