#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "types.h"
#include <pthread.h>

// Aloca memória para os ids das threads.
pthread_t *allocateThreadsIds(Arguments *arguments);

#endif