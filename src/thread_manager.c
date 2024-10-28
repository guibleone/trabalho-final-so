#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

pthread_t *allocateThreadsIds(int threads_quantity) {
    pthread_t *threads_ids = malloc(threads_quantity * sizeof(pthread_t));

    if (threads_ids == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para threads_ids.\n");
        exit(EXIT_FAILURE);
    }

    return threads_ids;
}
ThreadsData *allocateThreadsData(FileData *file_data, unsigned int thread_id,
                                 char *output_file) {
    ThreadsData *threads_data = (ThreadsData *)malloc(sizeof(ThreadsData));
    if (threads_data == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para Threads Data.\n");
        exit(EXIT_FAILURE);
    }

    threads_data->file_data = file_data;
    threads_data->thread_id = thread_id;
    threads_data->output_file = malloc(strlen(output_file) + 1);
    strcpy(threads_data->output_file, output_file);

    return threads_data;
}

int compareFunction(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void *sortNumbersThread(void *args) {
    FileData *file_data;
    unsigned int thread_id;
    char *output_file;

    file_data = ((ThreadsData *)args)->file_data;
    thread_id = ((ThreadsData *)args)->thread_id;
    output_file = ((ThreadsData *)args)->output_file;

    free(args);

    printf("Thread ID: %d\n", thread_id);
    printf("Quantidade de Números: %d\n", file_data->quantity);
    printf("Arquivo de Saída: %s\n", output_file);

    // Função da biblioteca padrão
    qsort(file_data->numbers, file_data->quantity, sizeof(int), compareFunction);

    printOrderedNumbers(output_file, file_data->numbers);

    pthread_exit(NULL);
}