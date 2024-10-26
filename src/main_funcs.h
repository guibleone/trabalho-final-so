#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

#include "types.h"

// Valida as entradas do usuário
void validateInputs(int argc, char *argv[]);

// Aloca os dados fornecidos pelo usuário
Arguments *allocateArguments(int argc, char *argv[]);

#endif