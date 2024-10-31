#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

// Dados fornecidos pelo usuário
typedef struct {
    int threads_quantity;
    int files_quantity;
    char **file_names;
    char *output_file;
} Arguments;

// Dados para cada arquivo
typedef struct {
    int quantity;
    int *numbers;
} FileData;

typedef struct {
    FileData *outputFileData;
    double tempoExecucao;
} ThreadsOutputData;

// Dados enviados para as threads
typedef struct {
    FileData *file_data;
    unsigned int thread_id;
    char *output_file;
} ThreadsData;

#endif