#ifndef TYPES_H
#define TYPES_H

// Dados fornecidos pelo usuário
typedef struct {
    int threads_quantity;
    int files_quantity;
    char **file_names;
    char *output_file;
} Arguments;

#endif