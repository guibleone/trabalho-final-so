# trabalho-final-so
Este projeto é resultado do [Enunciado do trabalho](./Assets/Projeto_DisciplinaTT304_2024.2.pdf)

### Objetivo 
Este programa tem como objetivo exercitar o uso de multithreding, a fim de organizar uma listas de números de arquivos, utilizando de algorimos de quicksort em cada thread, e depois retorna a organização pelas threads e ordena-as novamente na thread principal.

### Modo de Funcionamento
<!-- ![Modo de Funcionamento](/Arquitetura%201.png) -->
<img src="./Assets/Arquitetura%201.png" alt="HowWorks" width="400" height="453">

### Modo de utilização
1. Utilize do `make` para copilar o programa em um só arquivo
2. Execute com `./mergesort <threads> <arquivos> -o <arquivosaida>`
- *Opcional*
    3. a Execute o `./criador.o` para criar arquivos de teste para o Organizador.
    4. b Execute o `./verificador.o` para verificar se o arquivo de saída esta devidamente organizado.

### Avisos
Esse programa foi desenvolvido em sistemas linux para sistemas linux, não há certeza de funcionar em Windows Puro, caso deseje tente com a WSL.