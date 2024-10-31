#include <stdio.h>
#include <stdlib.h>

int verificarSequenciaCrescente(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return -1;
    }

    int numeroAtual, numeroAnterior;
    if (fscanf(arquivo, "%d", &numeroAnterior) != 1) {
        printf("O arquivo está vazio ou não contém números válidos.\n");
        fclose(arquivo);
        return -1;
    }

    while (fscanf(arquivo, "%d", &numeroAtual) == 1) {
        if (numeroAtual < numeroAnterior) {
            printf("Os números no arquivo %s não estão em sequência crescente.\n", nomeArquivo);
            fclose(arquivo);
            return 0;
        }
        numeroAnterior = numeroAtual;
    }

    printf("Todos os números no arquivo %s estão em sequência crescente.\n", nomeArquivo);
    fclose(arquivo);
    return 1;
}

int main() {
    char nomeArquivo[50];
    
    printf("Digite o endereço do arquivo para verificar: ");
    scanf("%s", nomeArquivo);

    int resultado = verificarSequenciaCrescente(nomeArquivo);
    if (resultado == -1) {
        printf("Não foi possível verificar o arquivo.\n");
    }

    return 0;
}
