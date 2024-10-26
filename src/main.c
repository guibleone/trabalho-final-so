#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "main_funcs.h"
#include "thread_manager.h"

int main(int argc, char *argv[]) {

    validateInputs(argc, argv);

    Arguments *arguments = allocateArguments(argc, argv);
    pthread_t *threads_ids = allocateThreadsIds(arguments);

    

    free(threads_ids);
    free(arguments);
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