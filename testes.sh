#!/bin/bash

# Definir o arquivo de saída
output_file="saida.dat"

# Definir os arquivos de entrada em um array
input_files=(./Inputs/arq1.dat ./Inputs/arq2.dat ./Inputs/arq3.dat ./Inputs/arq4.dat ./Inputs/arq5.dat)

# Concatenar todos os arquivos de entrada em uma única string
input_files_str="${input_files[@]}"

# Loop para executar o programa com diferentes números de threads
for threads in 1 2 4 8; do
    echo "Executando com $threads threads..."
    ./mergesort "$threads" $input_files_str -o "$output_file"
    echo "Execução com $threads threads concluída."
done
