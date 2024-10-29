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

    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        readNumbersFromFile(&files_data[i], arguments->file_names[i]);
    }
    
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

    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        unsigned int thread_id = i % arguments->threads_quantity;
        pthread_join(threads_ids[thread_id], NULL);
    }

    freeMemory(arguments, files_data, threads_ids);
    return 0;
}

/*
    printf("%s\n", arguments->output_file);
    printf("%d\n", arguments->files_quantity);
    printf("%d\n", arguments->threads_quantity);
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        printf("%s ", arguments->file_names[i]);
    }
*/

/*
    for (i = 0; i < arguments->files_quantity; i++) {
         printf("Quantidade de Números: %d\n", files_data[i].quantity);
        for (int j = 0; j < files_data[i].quantity; j++) {
            printf("%d ", files_data[i].numbers[j]);
        }

        printf("\n");
    }
*/