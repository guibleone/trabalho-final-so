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
    // Posteriormente o endereço será trocado, então é necessário salvar o endereço para
    // desalocar no final;
    FileData *files_data_address = files_data;
    pthread_t *threads_ids = allocateThreadsIds(arguments->threads_quantity);

    FileData ordered_data = {0, NULL};

    // Lê números dos arquivos e os armazena em files_data
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        readNumbersFromFile(&files_data[i], arguments->file_names[i]);
    }

    // União dos vetores de arquivos e divisão do ventor em N
    manageData(&files_data, arguments->files_quantity, arguments->threads_quantity);
    // Inicio do Timer;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Criação das threads para ordenar os números
    for (unsigned int i = 0; i < arguments->threads_quantity; i++) {
        unsigned int thread_id = i;
        ThreadsData *threads_data =
            allocateThreadsData(&files_data[i], thread_id, arguments->output_file);
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

        // Conversão da resposta do threads para uma váriavel tipada
        ThreadsOutputData *thread_output = (ThreadsOutputData *)thread_result;
        printf("Tempo de execução do Thread %d: %f segundos.\n", i,
               thread_output->execution_time);
        FileData *result_data = thread_output->output_file_data;
        int thread_quantity = result_data->quantity;
        int *thread_numbers = result_data->numbers;

        // Aloca ou realoca memória para os números ordenados
        ordered_data.numbers =
            realloc(ordered_data.numbers,
                    (ordered_data.quantity + thread_quantity) * sizeof(int));
        if (ordered_data.numbers == NULL) {
            fprintf(stderr, "Erro: Erro ao realocar memória\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < thread_quantity; j++) {
            ordered_data.numbers[ordered_data.quantity++] = thread_numbers[j];
        }
        free(thread_output->output_file_data);
        free(thread_output);
    }

    // Ordena com base
    qsort(ordered_data.numbers, ordered_data.quantity, sizeof(int), compareFunction);

    // Fim do Timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    float total_execution_time =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Tempo total de execução: %f segundos.\n", total_execution_time);

    printOrderedNumbers(arguments->output_file, &ordered_data);

    free(files_data_address);
    free(ordered_data.numbers);
    freeMemory(arguments, files_data, threads_ids);
    return 0;
}
