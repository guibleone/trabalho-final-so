#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

pthread_t *allocateThreadsIds(Arguments *arguments) {
    pthread_t *threads_ids = NULL;

    if ((threads_ids = (pthread_t *)malloc(arguments->threads_quantity *
                                           sizeof(pthread_t))) == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para threads_ids.");
        exit(EXIT_FAILURE);
    }

    return threads_ids;
}