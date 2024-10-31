#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "types.h"

// Aloca memória para os dados dos arquivos e coloca e tipifica em FileData para cada arquivo
FileData *allocateFilesData(int files_quantity);

// Le os números do arquivo e preenche a estrutura
void readNumbersFromFile(FileData *file_data, char *file_name);

// Imprime os valores ordenados no arquivo de saída
void printOrderedNumbers(char *output_file, FileData *file_data);

#endif
