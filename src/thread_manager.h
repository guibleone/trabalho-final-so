#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "types.h"
#include <pthread.h>

// Aloca memória para os ids das threads.
pthread_t *allocateThreadsIds(int threads_quantity);

// Aloca memória para os dados transitados entre as threads
ThreadsData *allocateThreadsData(FileData *file_data, unsigned int thread_id,
                                 char *output_file);

// Ordena os números de um arquivo
void *sortNumbersThread(void *args);

#endif