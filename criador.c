#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criarArquivoComNumerosAleatorios(int id, int quantidade) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "arq%d.dat", id);  // Nomeia os arquivos como "arquivo_1.txt", "arquivo_2.txt", etc.

    FILE *arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo em modo de escrita
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        int numeroAleatorio = rand() % 10001;  // Gera um número aleatório entre 0 e 10.000
        fprintf(arquivo, "%d\n", numeroAleatorio);
    }

    fclose(arquivo);  // Fecha o arquivo
    printf("Arquivo %s criado com %d números.\n", nomeArquivo, quantidade);
}

int main() {
    int numArquivos, quantidadeNumeros;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("Quantos arquivos deseja criar? ");
    scanf("%d", &numArquivos);

    printf("Quantos números (mínimo de 1000) por arquivo? ");
    scanf("%d", &quantidadeNumeros);

    // Garante que o número mínimo de números por arquivo seja 1000
    if (quantidadeNumeros < 1000) {
        printf("A quantidade mínima de números por arquivo é 1000. Ajustando para 1000.\n");
        quantidadeNumeros = 1000;
    }

    // Cria os arquivos
    for (int i = 1; i <= numArquivos; i++) {
        criarArquivoComNumerosAleatorios(i, quantidadeNumeros);
    }

    printf("Todos os arquivos foram criados com sucesso.\n");

    return 0;
}
