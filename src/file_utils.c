#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **allocateFileNames(int argc, char *argv[], unsigned int files_quantity) {
    char **file_names = malloc(files_quantity * sizeof(char *));
    if (file_names == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os nomes dos arquivos.\n");
        return NULL;
    }

    for (unsigned int i = 0; i < files_quantity; i++) {
        file_names[i] = malloc(strlen(argv[i + 2]) + 1);
        if (file_names[i] == NULL) {
            perror("Falha ao alocar memória para file_names");
            for (unsigned int j = 0; j < i; j++) {
                free(file_names[j]);
            }
            free(file_names);
            return NULL;
        }
        strcpy(file_names[i], argv[i + 2]);
    }

    return file_names;
}

void freeFileNames(char **file_names, unsigned int files_quantity) {
    for (unsigned int i = 0; i < files_quantity; i++) {
        free(file_names[i]);
    }
    free(file_names);
}

int readNumbersFromFiles(const char *file_name, int **numbers) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int capacity = 100;
    *numbers = malloc(capacity * sizeof(int));
    if (*numbers == NULL) {
        perror("Erro ao alocar memória para numbers");
        fclose(file);
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%d", &(*numbers)[count]) == 1) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            *numbers = realloc(*numbers, capacity * sizeof(int));
            if (*numbers == NULL) {
                perror("Erro ao realocar memória para numbers");
                fclose(file);
                return -1;
            }
        }
    }
    fclose(file);

    return count;
}

void printNumbersOnOutput(char *output_file, int *numbers, int num_count) {
    FILE *file = fopen(output_file, "w+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
}
