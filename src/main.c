#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_controller.h"
#include "main_funcs.h"
#include "thread_manager.h"

int main(int argc, char *argv[]) {

    unsigned int i;

    validateInputs(argc, argv);

    Arguments *arguments = allocateArguments(argc, argv);
    FileData *files_data = allocateFilesData(arguments->files_quantity);

    for (i = 0; i < arguments->files_quantity; i++) {
        readNumbersFromFile(&files_data[i], arguments->file_names[i]);
    }

    for (i = 0; i < arguments->files_quantity; i++) {
        sortNumbers(&files_data[i], arguments->threads_quantity);
    }

    freeMemory(arguments, files_data);
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