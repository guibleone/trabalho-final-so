# Sistema de Ordenação de Arquivos com Threads
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

Consiste na construção do trabalho final da disciplina de Sistemas Operacionais ministrado na Unicamp. Este projeto é resultado do [enunciado do trabalho](./Assets/Projeto_DisciplinaTT304_2024.2.pdf).

### Objetivo
O objetivo deste programa é exercitar o uso de multithreading para organizar listas de números contidas em arquivos. Utilizamos o algoritmo quicksort em cada thread para ordenar parcialmente os dados, e, ao final, o programa realiza uma ordenação final na thread principal para consolidar o resultado.

### Modo de Funcionamento
<!-- ![Modo de Funcionamento](/Arquitetura%201.png) -->
<img src="./Assets/Arquitetura%201.png" alt="Funcionamento" width="400" height="453">

### Clone o Repositório
```bash
git clone https://github.com/guibleone/trabalho-final-so.git
```

### Modo de Utilização
1. Use o comando `make` para compilar o programa em um único executável.
2. Execute o programa com o comando `./mergesort <n_threads> <arquivo1> <arquivo2> ... <arquivo_n> -o <arquivo_saida>`.

### Teste do Programa
Para testar o funcionamento do programa com arquivos de entrada já configurados, execute o comando abaixo. Isso irá utilizar quatro threads para processar os arquivos de entrada `arq1.dat` e `arq2.dat` na pasta `Inputs`, e salvar o resultado no arquivo `saida.dat`:

```bash
./mergesort 4 ./Inputs/arq1.dat ./Inputs/arq2.dat -o saida.dat
```

#### *Opcional*
3. Execute `./auxPrograms/criador.o` para criar arquivos de teste para o organizador.
4. Execute `./auxPrograms/verificador.o` para verificar se o arquivo de saída está devidamente ordenado.

### Avisos
Este programa foi desenvolvido em ambiente Linux e para sistemas Linux. Não há garantias de funcionamento em Windows nativo; caso necessário, recomenda-se utilizar a WSL (Windows Subsystem for Linux).
