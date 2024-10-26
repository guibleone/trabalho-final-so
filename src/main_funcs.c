#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread_manager.h"
#include "types.h"

void validateInputs(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr,
                "Error: Uso inválido! Utilize: %s [2,4,8] <arquivo1> "
                "<arquivo2> ... "
                "<arquivoN> -o <arquivo de saída>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    if (atoi(argv[1]) != 2 && atoi(argv[1]) != 4 && atoi(argv[1]) != 8) {
        fprintf(stderr, "Error: Quantidade de Threads inválida! Números "
                        "válidos: 2, 4 e 8.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[argc - 2], "–o") != 0) {
        fprintf(stderr, "Error: Arquivo de saída não especificado!\n");
        exit(EXIT_FAILURE);
    }
}

Arguments *allocateArguments(int argc, char *argv[]) {
    Arguments *arguments = malloc(sizeof(Arguments));
    if (arguments == NULL) {
        fprintf(stderr, "Error: Alocação de memória para Arguments falhou.\n");
        exit(EXIT_FAILURE);
    }

    arguments->threads_quantity = atoi(argv[1]);
    arguments->files_quantity = argc - 4;

    arguments->output_file = malloc(strlen(argv[argc - 1]) + 1);
    if (arguments == NULL) {
        fprintf(stderr, "Error: Alocação de memória para arquivo de saída falhou.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(arguments->output_file, argv[argc - 1]);

    arguments->file_names = malloc(arguments->files_quantity * sizeof(char *));
    if (arguments->file_names == NULL) {
        fprintf(stderr, "Error: Alocação de memória para os nomes dos arquivos.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        arguments->file_names[i] = malloc(strlen(argv[i + 2] + 1));
        if (arguments->file_names[i] == NULL) {
            fprintf(stderr, "Error: Alocação de memória para os nomes dos arquivos.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(arguments->file_names[i], argv[i + 2]);
    }

    return arguments;
}

void sortNumbers(FileData *file_data, int threads_quantity) {
    pthread_t *threads_ids = allocateThreadsIds(threads_quantity);
    unsigned int i;

    for (i = 0; i < threads_quantity; i++)
        if (pthread_create(&threads_ids[i], NULL, sortNumbersThread, (void *)file_data) !=
            0) {
            fprintf(stderr, "Erro: Erro ao criar thread\n");
            exit(EXIT_FAILURE);
        }
    for (i = 0; i < threads_quantity; i++) {
        pthread_join(threads_ids[i], NULL);
    }
}

void freeMemory(Arguments *arguments, FileData *files_data) {
    for (unsigned int i = 0; i < arguments->files_quantity; i++) {
        free(arguments->file_names[i]);
        free(files_data[i].numbers);
    }

    free(files_data);
    free(arguments);
}