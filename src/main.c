#include "controller.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Verificar uso correto do sistema
    if (argc < 6 || strcmp(argv[argc - 2], "-o") != 0) {
        fprintf(stderr,
                "Uso: %s <número de threads> <arquivo1> <arquivo2> ... "
                "<arquivoN> -o <arquivo de saída>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    // Alocar dados fornecidos
    char *output_file = argv[argc - 1];
    int threads_quantity = atoi(argv[1]);
    unsigned int files_quantity = argc - 4;

    // Alocar nome dos arquivos
    char **file_names = allocateFileNames(argc, argv, files_quantity);
    if (file_names == NULL) {
        return EXIT_FAILURE;
    }

    // Ler números do primeiro arquivo
    int *numbers = NULL;
    int num_count = readNumbersFromFiles(file_names[0], &numbers);
    if (num_count == -1) {
        freeFileNames(file_names, files_quantity);
        return EXIT_FAILURE;
    }

    // Ordenar números
    sortNumbers(numbers, num_count);

    // Imprimir números ordenados
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Liberação de memória
    free(numbers);
    freeFileNames(file_names, files_quantity);

    return EXIT_SUCCESS;
}
