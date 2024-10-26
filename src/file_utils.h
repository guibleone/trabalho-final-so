#ifndef FILE_UTILS_H
#define FILE_UTILS_H

char **allocateFileNames(int argc, char *argv[], unsigned int files_quantity);
void freeFileNames(char **file_names, unsigned int files_quantity);
int readNumbersFromFiles(const char *file_name, int **numbers);
void printNumbersOnOutput(char *output_file, int *numbers, int num_count);

#endif
