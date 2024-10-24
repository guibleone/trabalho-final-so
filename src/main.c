#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 6 || strcmp(argv[argc - 2], "-o") != 0) {
        fprintf(stderr,
                "Uso: %s <número de threads> <arquivo1> <arquivo2> ... "
                "<arquivoN> -o <arquivo de saída>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    char *output_file = argv[argc - 1];
    int threads_quantity = atoi(argv[1]);
    unsigned int files_quantity = argc - 4;

    char **file_names = malloc(files_quantity * sizeof(char *));
    if (file_names == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os nomes dos arquivos.\n");
        return EXIT_FAILURE;
    }

    for (unsigned int i = 0; i < files_quantity; i++) {
        file_names[i] = malloc(strlen(argv[i + 2]) + 1);
        if (file_names[i] == NULL) {
            perror("Falha ao alocar memória para file_names");
            for (unsigned int j = 0; j < i; j++) {
                free(file_names[j]);
            }
            free(file_names);
            return EXIT_FAILURE;
        }
        strcpy(file_names[i], argv[i + 2]);
    }

    printf("Arquivo de saída: %s\n", output_file);
    printf("Quantidade de threads: %d\n", threads_quantity);
    printf("Quantidade de arquivos: %u\n", files_quantity);
    for (unsigned int i = 0; i < files_quantity; i++) {
        printf("Arquivo %d: %s\n", i + 1, file_names[i]);
        free(file_names[i]); // Libera memória
    }
    free(file_names); // Libera a memória do array
    return EXIT_SUCCESS;
}
