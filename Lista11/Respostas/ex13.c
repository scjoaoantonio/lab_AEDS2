#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct SortingStats {
    int comparisons;
    int movements;
};

int partition(int arr[], int low, int high, struct SortingStats *stats) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        stats->comparisons++;
        if (arr[j] > pivot) {
            i++;
            stats->movements++;
            swap(&arr[i], &arr[j]);
        }
    }
    stats->movements++;
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, struct SortingStats *stats) {
    if (low < high) {
        int pi = partition(arr, low, high, stats);
        quickSort(arr, low, pi - 1, stats);
        quickSort(arr, pi + 1, high, stats);
    }
}

void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

double measureTime(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void testSortingAlgorithm(void (*sortFunction)(int[], int, int, struct SortingStats *), int arr[], int size, const char *algorithmName) {
    struct SortingStats stats = {0, 0};
    int *tempArr = (int *)malloc(size * sizeof(int));
    copyArray(arr, tempArr, size);

    clock_t start = clock();
    sortFunction(tempArr, 0, size - 1, &stats);
    clock_t end = clock();

    printf("%s:\n", algorithmName);
    printf("Tempo de execução: %f segundos\n", measureTime(start, end));
    printf("Número de comparações: %d\n", stats.comparisons);
    printf("Número de movimentações: %d\n", stats.movements);

    free(tempArr);
}

int main() {
    FILE *file = fopen("./ordenacao/100-contrario.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    testSortingAlgorithm(quickSort, arr, n, "QuickSort");

    free(arr);

    return 0;
}
