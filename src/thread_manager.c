#include <bits/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

// Aloca a memória para os ThreadsID
pthread_t *allocateThreadsIds(int threads_quantity) {
    pthread_t *threads_ids = malloc(threads_quantity * sizeof(pthread_t));

    if (threads_ids == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para threads_ids.\n");
        exit(EXIT_FAILURE);
    }

    return threads_ids;
}

// Aloca memória para os dados que serão processado pelas Threads
ThreadsData *allocateThreadsData(FileData *file_data, unsigned int thread_id, char *output_file) {
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

// Função de comparação para o quicksort
int compareFunction(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

// Função para ordenar os números com base no quicksort que será executada por uma thread;
void *sortNumbersThread(void *args) {
    ThreadsData *threads_data = (ThreadsData *)args;
    ThreadsOutputData *threadOutput = (ThreadsOutputData *) malloc(sizeof(ThreadsOutputData));
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    FileData *file_data = threads_data->file_data;
    FileData *ordered_numbers = malloc(sizeof(FileData));

    qsort(file_data->numbers, file_data->quantity, sizeof(int), compareFunction);

    ordered_numbers->numbers = file_data->numbers;
    ordered_numbers->quantity = file_data->quantity;
    threadOutput->outputFileData = ordered_numbers;
    clock_gettime(CLOCK_MONOTONIC, &fim);
    threadOutput->tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    free(threads_data->output_file);
    free(threads_data);
    //Descomente para ver até onde essa thread vai e va ao no file controller e descomente tambem;
    // printOrderedNumbers("teste.txt", ordered_numbers);
    pthread_exit((void *)threadOutput);
}