#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int vetor[], int n) {
    int i, j, indiceMax;

    for (i = 0; i < n-1; i++) {
        indiceMax = i;
        for (j = i+1; j < n; j++) {
            if (vetor[j] > vetor[indiceMax]) {
                indiceMax = j;
            }
        }
        trocar(&vetor[indiceMax], &vetor[i]);
    }
}

void insertionSort(int vetor[], int n) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] < chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

void bubbleSort(int vetor[], int n) {
    int i, j;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (vetor[j] < vetor[j+1]) {
                trocar(&vetor[j], &vetor[j+1]);
            }
        }
    }
}

void imprimirVetor(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int vetor[n];

    printf("Digite os %d inteiros:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    selectionSort(vetor, n);
    printf("\nSelection Sort: ");
    imprimirVetor(vetor, n);

    insertionSort(vetor, n);
    printf("\nInsertion Sort: ");
    imprimirVetor(vetor, n);

    bubbleSort(vetor, n);
    printf("\nBubble Sort: ");
    imprimirVetor(vetor, n);

    return 0;
}