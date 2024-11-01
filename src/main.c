#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "file_controller.h"
#include "main_funcs.h"
#include "thread_manager.h"
#include "types.h"

int main(int argc, char *argv[]) {
    validateInputs(argc, argv);

    Arguments *arguments = allocateArguments(argc, argv);
    FileData *files_data = allocateFilesData(arguments->files_quantity);
    FileData *teste = files_data;  
    pthread_t *threads_ids = allocateThreadsIds(arguments->threads_quantity);

    FileData ordered_data = {0, NULL};

    // Lê números dos arquivos e os armazena em files_data
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        readNumbersFromFile(&files_data[i], arguments->file_names[i]);
    }

    // União dos vetores de arquivos e divisão do ventor em N 
    manageData(&files_data, arguments->files_quantity, arguments->threads_quantity);
    //Inicio do Timer;
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    // Criação das threads para ordenar os números
    for (unsigned int i = 0; i < arguments->threads_quantity; i++) {
        unsigned int thread_id = i;
            ThreadsData *threads_data = allocateThreadsData(&files_data[i], thread_id, arguments->output_file);
        if (pthread_create(&threads_ids[thread_id], NULL, sortNumbersThread,
                           (void *)threads_data) != 0) {
            fprintf(stderr, "Erro: Erro ao criar thread\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // Recebendo e imprimindo resultados das threads
    void *thread_result;
    for (unsigned int i = 0; i < arguments->threads_quantity; i++) {
        unsigned int thread_id = i;
        pthread_join(threads_ids[thread_id], &thread_result);
        ThreadsOutputData *threadOutput = (ThreadsOutputData *)thread_result;
        printf("Tempo de execução do Thread %d: %f segundos.\n",i,threadOutput->tempoExecucao);
        FileData *result_data = threadOutput->outputFileData;
        int thread_quantity = result_data->quantity;
        int *thread_numbers = result_data->numbers;

        // Aloca ou realoca memória para os números ordenados
        ordered_data.numbers =
            realloc(ordered_data.numbers, (ordered_data.quantity + thread_quantity) * sizeof(int));
        if (ordered_data.numbers == NULL) {
            fprintf(stderr, "Erro: Erro ao realocar memória\n");
            exit(EXIT_FAILURE); 
        }
        for (int j = 0; j < thread_quantity; j++) {
            ordered_data.numbers[ordered_data.quantity++] = thread_numbers[j];
        }
        free(threadOutput->outputFileData);
        free(threadOutput);
    }

    qsort(ordered_data.numbers, ordered_data.quantity, sizeof(int), compareFunction);

    //Fim do Timer
    clock_gettime(CLOCK_MONOTONIC, &fim);
    float tempoExecucaoTotal = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo total de execução: %f segundos.\n", tempoExecucaoTotal);

    printOrderedNumbers(arguments->output_file, &ordered_data);

    free(teste->numbers);
    // for (int i = 0; arguments->files_quantity; i++)
        // free(&teste[i]);
    free(ordered_data.numbers);
    freeMemory(arguments, files_data, threads_ids);
    return 0;
}
