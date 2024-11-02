#include <stdio.h>
#include <stdlib.h>

#include "types.h"
// Faz a alocação da quantidade de arquivos para o ponteiro de filesData;
FileData *allocateFilesData(int files_quantity) {
    FileData *files_data = malloc(files_quantity * sizeof(FileData));

    if (files_data == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para files_data.\n");
        exit(EXIT_FAILURE);
    }

    return files_data;
}

// Lê os arquivos e assim, aloca os numeros dos arquivos para um ponteiro de *file_data.
void readNumbersFromFile(FileData *file_data, char *file_name) {
    int capacity = 50;
    // ============================================================
    //Inicializa o alocamento de memória dos números do arquivo.
    file_data->numbers = malloc(capacity * sizeof(int));
    if (file_data->numbers == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para números do file_data\n");
        exit(EXIT_FAILURE);
    }

    int number;
    int quantity = 0;
    // ============================================================
    //Abre o arquivo para leitura;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Falha ao abrir arquivo: %s.\n", file_name);
        free(file_data->numbers);
        exit(EXIT_FAILURE);
    }

    // ============================================================
    // Lê linha a linha do arquivo, e enquanto não chegar ao fim realoca o vetor para armazenar os dados   
    while (fscanf(file, "%d", &number) == 1) {
        if (quantity == capacity) {
            capacity += 50;
            int *temp = realloc(file_data->numbers, capacity * sizeof(int));
            if (temp == NULL) {
                fprintf(stderr,
                        "Error: Falha ao realocar memória para números do file_data\n");
                free(file_data->numbers);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            file_data->numbers = temp;
        }
        file_data->numbers[quantity] = number;
        quantity++;
    }
    file_data->quantity = quantity;

    fclose(file);
}

//Imprime uma FileData para um arquivo especifícado, caso não exista cria-o
void printOrderedNumbers(char *output_file, FileData *file_data) {
    // *Debugging* 
    // Substitua para ver até onde o processamento da thread vai
    //FILE *file = fopen(output_file, "a+");

    // ============================================================
    // Inicializa o arquivo de saída, caso não exista cria-o  
     FILE *file = fopen(output_file, "w+");
    if (file == NULL) {
        fprintf(stderr, "Error: Falha ao abrir arquivo de saída: %s\n", output_file);
        exit(EXIT_FAILURE);
    }
    // ============================================================
    // Escreve no arquivo de saída o conteudo desejado, do tipo FIleData
    // Imprime a saída do programa
    for (unsigned int i = 0; i < file_data->quantity; i++) {
        fprintf(file, "%d\n", file_data->numbers[i]);
    }
    // ============================================================
    // Debugging 
    //Descomente a linha a baixo para Visualizar até onde é o print, 
    //para ver o processamento da thread acessa thread_manager e descomente também
    // fprintf(file, "---------\n");

    // ============================================================
    // Fecha corretamente o arquivo de saída, e encerra o programa;
    if (fclose(file) != 0) {
        fprintf(stderr, "Error: Falha ao fechar o arquivo de saída: %s\n", output_file);
        exit(EXIT_FAILURE);
    }
}