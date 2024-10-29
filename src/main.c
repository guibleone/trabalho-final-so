#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_controller.h"
#include "main_funcs.h"
#include "thread_manager.h"

int main(int argc, char *argv[]) {
    validateInputs(argc, argv);

    Arguments *arguments = allocateArguments(argc, argv);
    FileData *files_data = allocateFilesData(arguments->files_quantity);
    pthread_t *threads_ids = allocateThreadsIds(arguments->threads_quantity);

    FileData ordered_data = {0, NULL};

    // Lê números dos arquivos e os armazena em files_data
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        readNumbersFromFile(&files_data[i], arguments->file_names[i]);
    }

    // Criação das threads para ordenar os números
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        unsigned int thread_id = i % arguments->threads_quantity;
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
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        unsigned int thread_id = i % arguments->threads_quantity;
        pthread_join(threads_ids[thread_id], &thread_result);

        FileData *result_data = (FileData *)thread_result;
        int thread_quantity = result_data->quantity;
        int *thread_numbers = result_data->numbers;

        // Aloca ou realoca memória para os números ordenados
        ordered_data.numbers =
            realloc(ordered_data.numbers, (ordered_data.quantity + thread_quantity) * sizeof(int));
        for (int j = 0; j < thread_quantity; j++) {
            ordered_data.numbers[ordered_data.quantity++] = thread_numbers[j];
        }
    }

    qsort(ordered_data.numbers, ordered_data.quantity, sizeof(int), compareFunction);

    printOrderedNumbers(arguments->output_file, &ordered_data);

    freeMemory(arguments, files_data, threads_ids);
    return 0;
}
