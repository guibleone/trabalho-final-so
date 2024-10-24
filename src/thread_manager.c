#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 999999

#include "sort.h"
#include "thread_manager.h"

pthread_t *allocateThreadsIds(unsigned int n_threads) {
    if (n_threads != 2 && n_threads != 4 && n_threads != 8) {
        fprintf(stderr, "Número de threads deve ser 2, 4 ou 8.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t *threadsIds = malloc(n_threads * sizeof(pthread_t));
    if (threadsIds == NULL) {
        fprintf(stderr, "Erro ao alocar IDS da threads.\n");
        exit(EXIT_FAILURE);
    }

    return threadsIds;
}

void *sortThread(void *args) {
    Data *data = (Data *)args;
    int *numbers = data->numbers;
    unsigned int start = data->start;
    unsigned int end = data->end;

    quickSort(numbers, start, end);

    pthread_exit(NULL);
}

void mergeSortedChunks(int *sortedNumbers, Data *threads_data, int n_threads,
                       unsigned int total_numbers) {
    unsigned int *indices = malloc(n_threads * sizeof(unsigned int));
    if (indices == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os índices.\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < n_threads; i++)
        indices[i] = threads_data[i].start;

    for (unsigned int k = 0; k < total_numbers; k++) {
        int min_value = INT_MAX;
        int min_index = -1;

        for (unsigned int i = 0; i < n_threads; i++) {
            if (indices[i] < threads_data[i].end) {
                if (threads_data[i].numbers[indices[i]] < min_value) {
                    min_value = threads_data[i].numbers[indices[i]];
                    min_index = i;
                }
            }
        }
        sortedNumbers[k] = min_value;
        indices[min_index]++;
        
        if (min_index != -1) { 
            sortedNumbers[k] = min_value;
            indices[min_index]++;
        }
    }

    free(indices);
}
