#include <stdio.h>
#include <stdlib.h>

#include "types.h"

FileData *allocateFilesData(int files_quantity) {
    FileData *files_data = malloc(files_quantity * sizeof(FileData));

    if (files_data == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para files_data.\n");
        exit(EXIT_FAILURE);
    }

    return files_data;
}

void readNumbersFromFile(FileData *file_data, char *file_name) {
    int capacity = 50;

    file_data->numbers = malloc(capacity * sizeof(int));
    if (file_data->numbers == NULL) {
        fprintf(stderr, "Error: Falha ao alocar memória para números do file_data\n");
        exit(EXIT_FAILURE);
    }

    int number;
    int quantity = 0;

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Falha ao abrir arquivo: %s.\n", file_name);
        free(file_data->numbers);
        exit(EXIT_FAILURE);
    }

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

void printOrderedNumbers(char *output_file, int *numbers) {
    FILE *file = fopen(output_file, "w+");
    if (file == NULL) {
        fprintf(stderr, "Error: Falha ao abrir arquivo de saída: %s\n", output_file);
        free(numbers);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}