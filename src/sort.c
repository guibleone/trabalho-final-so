void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], unsigned int low, unsigned int high) {
    int pivot = array[high];

      int i = low; 

    for (int j = low + 1; j <= high; j++) { 
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i], &array[high]); 

    return i;
}

void quickSort(int array[], unsigned int low, unsigned int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}