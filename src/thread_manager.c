#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

pthread_t *allocateThreadsIds(int threads_quantity) {
    pthread_t *threads_ids = malloc(threads_quantity * sizeof(pthread_t));

    if (threads_ids == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para threads_ids.\n");
        exit(EXIT_FAILURE);
    }

    return threads_ids;
}

int compareFunction(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void *sortNumbersThread(void *args) {
    pthread_t thread_id = pthread_self();
    printf("%d \n", 1);
    printf("Thread #%ld\n", thread_id);

    FileData *file_data = (FileData *)args;

    qsort(file_data->numbers, file_data->quantity, sizeof(int), compareFunction);

    pthread_exit(NULL);
}