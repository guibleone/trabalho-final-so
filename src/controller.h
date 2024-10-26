#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sortNumbers(int *numbers, int count) {
    qsort(numbers, count, sizeof(int), compare);
}
