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
