#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função que valida as entradas dos argumentos.
void validateInputs(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr,
                "Error: Uso inválido! Utilize: %s [1,2,4,8] <arquivo1> "
                "<arquivo2> ... "
                "<arquivoN> -o <arquivo de saída>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    if (atoi(argv[1]) != 1 && atoi(argv[1]) != 2 && atoi(argv[1]) != 4 &&
        atoi(argv[1]) != 8) {
        fprintf(stderr, "Error: Quantidade de Threads inválida! Números "
                        "válidos: 1, 2, 4 e 8.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[argc - 2], "–o") & strcmp(argv[argc - 2], "-o")) {
        fprintf(stderr, "Error: Arquivo de saída não especificado!\n");
        exit(EXIT_FAILURE);
    }
}

// Aloca memória dos argumentos de entradas, para um ponteiro;
Arguments *allocateArguments(int argc, char *argv[]) {
    Arguments *arguments = malloc(sizeof(Arguments));
    if (arguments == NULL) {
        fprintf(stderr, "Error: Alocação de memória para Arguments falhou.\n");
        exit(EXIT_FAILURE);
    }

    arguments->threads_quantity = atoi(argv[1]);
    arguments->files_quantity = argc - 4;

    arguments->output_file = malloc(strlen(argv[argc - 1]) + 1);
    if (arguments->output_file == NULL) {
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
        arguments->file_names[i] = malloc(strlen(argv[i + 2]) + 1);
        if (arguments->file_names[i] == NULL) {
            fprintf(stderr, "Error: Alocação de memória para os nomes dos arquivos.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(arguments->file_names[i], argv[i + 2]);
    }

    return arguments;
}

// Libera a memória de muitos arrays já alocados;
void freeMemory(Arguments *arguments, FileData *files_data, pthread_t *threads_ids) {
    for (unsigned int i = 0; i < arguments->files_quantity; i++)
        free(arguments->file_names[i]);
    for (unsigned int i = 0; i < arguments->threads_quantity; i++)
        free(files_data[i].numbers);

    free(files_data);
    free(arguments->output_file);
    free(arguments->file_names);
    free(arguments);
    free(threads_ids);
}

// Dividir os dados dos arquivos em n = T threads.
void splitterData(FileData **files_data, FileData merged_data, int T, int n_data) {
    int ratio = merged_data.quantity / T;
    int rest = merged_data.quantity % T;
    // ============================================================
    // Descomente para Visualizar a distribuição do Vetor
    // printf("Total | razao | resto: %d|%d|%d\n",merged_data.quantity, ratio, rest);

    // ============================================================
    // Aloca mamória para o vetor de distribuição
    int *distribution = calloc(T, sizeof(int));
    if (distribution == NULL) {
        fprintf(stderr, "Error: Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    // ============================================================
    // For para a distribuição do resto da divisão dos arquivos
    // Para uniformizar entre todas as threads
    for (int i = 0; i < T; i++)
        distribution[i] = 0;
    if (rest != 0) {
        for (int i = 0; rest > 0; rest--) {
            distribution[i]++;
            i = (i + 1) % T;
        }
    }
    // ============================================================
    // Aloca a váriavel que será a distribuição uniforme entre todos os números dos
    // arquivos, baseado no número de threads;
    FileData *splitter_data = (FileData *)malloc(T * sizeof(FileData));
    if (splitter_data == NULL) {
        fprintf(stderr, "Error: Falha na alocação de memória para splitter_data.\n");
        free(distribution);
        exit(EXIT_FAILURE);
    }

    // ============================================================
    // Alocação de memoria dos numeros do vetor Splitter data, baseado na uniformidade da
    // quantidade de números
    for (int i = 0; i < T; i++) {
        splitter_data[i].numbers = malloc((ratio + distribution[i]) * sizeof(int));
        if (splitter_data[i].numbers == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for numbers array.\n");
            free(distribution);
            for (int k = 0; k < i; k++)
                free(splitter_data[k].numbers);
            free(splitter_data);
            exit(EXIT_FAILURE);
        }
        splitter_data[i].quantity = ratio + distribution[i];
    }

    // ============================================================
    // Unificação dos arrays para o merged data, para ser dividido em vários vetores do
    // splitter data
    int v = 0;
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < splitter_data[i].quantity; j++) {
            splitter_data[i].numbers[j] = merged_data.numbers[v++];
        }
    }
    free(distribution);

    *files_data = splitter_data;
}

// Juntar os dados de todas os arquivos em um único Array
void mergeData(FileData *files_data, FileData merged_data, int n_data) {
    int k = 0;
    for (int i = 0; i < n_data; i++) {
        for (int j = 0; j < files_data[i].quantity; j++) {
            merged_data.numbers[k] = files_data[i].numbers[j];
            k++;
        }
        free(files_data[i].numbers);
    }
}
// Pego vetor FileData, a fim de junta-los e dividir em números de threads, modificando-o
// para .
void manageData(FileData **files_data, int n_data, int T) {
    int totalQuantity = 0;
    for (int i = 0; i < n_data; i++) {
        totalQuantity += (*files_data)[i].quantity;
    }

    FileData merged_data;
    merged_data.numbers = (int *)malloc(totalQuantity * sizeof(int));
    merged_data.quantity = totalQuantity;
    mergeData((*files_data), merged_data, n_data);
    FileData *split_data = NULL;
    splitterData(&split_data, merged_data, T, n_data);
    free(merged_data.numbers);
    *files_data = split_data;
}