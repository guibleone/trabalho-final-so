#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

#include "types.h"

// Valida as entradas do usuário
void validateInputs(int argc, char *argv[]);

// Aloca os dados fornecidos pelo usuário
Arguments *allocateArguments(int argc, char *argv[]);

// Ordena os números de cada arquivo
void sortNumbers(FileData *file_data, int threads_quantity);

// Libera a memória
void freeMemory(Arguments *arguments, FileData *files_data);

#endif