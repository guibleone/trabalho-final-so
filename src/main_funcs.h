#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

#include "types.h"

// Valida as entradas do usuário
void validateInputs(int argc, char *argv[]);

// Aloca os dados fornecidos pelo usuário
Arguments *allocateArguments(int argc, char *argv[]);

// Libera a memória
void freeMemory(Arguments *arguments, FileData *files_data, pthread_t *threads_ids);

// Manipula o vetor para fazer a distribuição igualmente para as trhreads dos dados
void manageData(FileData **files_data, int n_data, int T);


#endif