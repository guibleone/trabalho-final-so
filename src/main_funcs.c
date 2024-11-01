#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"

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
    if (atoi(argv[1]) != 1 && atoi(argv[1]) != 2 && atoi(argv[1]) != 4 && atoi(argv[1]) != 8) {
        fprintf(stderr, "Error: Quantidade de Threads inválida! Números "
                        "válidos: 2, 4 e 8.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[argc - 2], "–o") & strcmp(argv[argc - 2], "-o")) {
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
void splitterData (FileData **files_data, FileData mergedData, int T, int nData) {
    int ratio = mergedData.quantity / T;
    int rest = mergedData.quantity % T;
    // Descomente para Visualizar a distribuição do Vetor
    printf("Total | razao | resto: %d|%d|%d\n",mergedData.quantity, ratio, rest);

    int *distribution = calloc(T, sizeof(int));
    if (distribution == NULL){
        fprintf(stderr, "Error: Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < T; i++)
        distribution[i] = 0;
    if (rest != 0){
        for (int i = 0; rest > 0; rest--) {
            distribution[i]++;
            i = (i + 1) % T;
        }   
    } 

    FileData * splitter_data = (FileData *) malloc(T * sizeof(FileData));
    if (splitter_data == NULL) {
        fprintf(stderr, "Error: Falha na alocação de memória para splitter_data.\n");
        free(distribution);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < T; i++) {
        splitter_data[i].numbers = malloc((ratio + distribution[i]) * sizeof(int));
        if (splitter_data[i].numbers == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for numbers array.\n");
            free(distribution); 
            for (int k = 0; k < i; k++) free(splitter_data[k].numbers); 
            free(splitter_data);
            exit(EXIT_FAILURE);

        }
        splitter_data[i].quantity = ratio + distribution[i]; 
    }


    int v = 0;
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < splitter_data[i].quantity; j++) {
            splitter_data[i].numbers[j] = mergedData.numbers[v++];
        }
    }
    free(distribution);

    *files_data = splitter_data;
}

// Juntar os dados de todas os arquivos em um único Array
void mergeData (FileData *files_data, FileData mergedData, int nData) {
    int k = 0;
    for (int i = 0; i < nData; i++) {
        for (int j = 0; j < files_data[i].quantity; j++) {
            mergedData.numbers[k] = files_data[i].numbers[j];
            k++;
        }       
        free(files_data[i].numbers); 
    }
}

void manageData (FileData **files_data, int nData, int T) { 
    int totalQuantity = 0;
    for (int i = 0; i < nData; i++){
        totalQuantity += (*files_data)[i].quantity;
    }

    FileData mergedData;
    mergedData.numbers = (int *)  malloc(totalQuantity * sizeof(int));
    mergedData.quantity = totalQuantity;
    mergeData((*files_data), mergedData, nData);
    FileData *split_data = NULL;
    splitterData(&split_data, mergedData, T, nData);
    free(mergedData.numbers);
    *files_data = split_data;
}