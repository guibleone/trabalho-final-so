# Sistema de Ordenação de Arquivos com Threads
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

Consiste na construção do trabalho final da disciplina de Sistemas Operacionais ministrado na Unicamp. Este projeto é resultado do [enunciado do trabalho](./Assets/Projeto_DisciplinaTT304_2024.2.pdf).

### Objetivo
O objetivo deste programa é exercitar o uso de multithreading para organizar listas de números contidas em arquivos. Utilizamos o algoritmo quicksort em cada thread para ordenar parcialmente os dados, e, ao final, o programa realiza uma ordenação final na thread principal para consolidar o resultado.

### Modo de Funcionamento
<!-- ![Modo de Funcionamento](/Arquitetura%201.png) -->
<img src="./Assets/Arquitetura%201.png" alt="Funcionamento" width="400" height="453">

Para mais detalhes confira o [Relatório Final](./RelatórioProjetoFinalTT304.pdf) do projeto. 

### Clone o Repositório
```bash
git clone https://github.com/guibleone/trabalho-final-so.git
```

### Modo de Utilização
1. Mova-se para o diretório `cd trabalho-final-so`.
2. Use o comando `make` para compilar o programa em um único executável.
3. Execute o programa com o comando `./mergesort <n_threads> <arquivo1> <arquivo2> ... <arquivo_n> -o <arquivo_saida>`.

### Teste do Programa
Para testar o programa, execute o script testes.sh, que realiza testes com 1, 2, 4 e 8 threads. Ele usa cinco arquivos de entrada predefinidos e exibe os resultados para facilitar a análise do desempenho.

```bash
./testes.sh
```

#### *Opcional*
3. Execute `./auxPrograms/criador.o` para criar arquivos de teste para o organizador.
4. Execute `./auxPrograms/verificador.o` para verificar se o arquivo de saída está devidamente ordenado.

### Avisos
Este programa foi desenvolvido em ambiente Linux e para sistemas Linux. Não há garantias de funcionamento em Windows nativo; caso necessário, recomenda-se utilizar a WSL (Windows Subsystem for Linux).
