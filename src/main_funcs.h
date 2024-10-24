#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

int *getNumbers(int argc, char *argv[], int *total_numbers);
int *getSortedNumbers(int *numbers, unsigned int total_numbers, int n_threads);
void printSortedNumbers(int *sorted_numbers, unsigned int total_numbers,
                        const char *output_file);

#endif