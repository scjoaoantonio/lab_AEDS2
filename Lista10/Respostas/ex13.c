#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int vetor[], int n, long long *comparacoes, long long *movimentacoes) {
    int i, j, indiceMin;

    for (i = 0; i < n-1; i++) {
        indiceMin = i;
        for (j = i+1; j < n; j++) {
            (*comparacoes)++;
            if (vetor[j] < vetor[indiceMin]) {
                indiceMin = j;
            }
        }
        trocar(&vetor[indiceMin], &vetor[i]);
        (*movimentacoes)++;
    }
}

void insertionSort(int vetor[], int n, long long *comparacoes, long long *movimentacoes) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > chave) {
            (*comparacoes)++;
            vetor[j + 1] = vetor[j];
            j = j - 1;
            (*movimentacoes)++;
        }
        vetor[j + 1] = chave;
        (*movimentacoes)++;
    }
}

void bubbleSort(int vetor[], int n, long long *comparacoes, long long *movimentacoes) {
    int i, j;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            (*comparacoes)++;
            if (vetor[j] > vetor[j+1]) {
                trocar(&vetor[j], &vetor[j+1]);
                (*movimentacoes)++;
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

void lerArquivo(char *nomeArquivo, int **vetor, int *tamanho) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("ERRO");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d", tamanho);

    *vetor = (int *)malloc(*tamanho * sizeof(int));

    for (int i = 0; i < *tamanho; i++) {
        fscanf(arquivo, "%d", &(*vetor)[i]);
    }

    fclose(arquivo);
}

int main() {
    char nomeArquivo[] = "./inputs/10000-contrario.txt";  // Nome do arquivo de entrada
    int *vetor, tamanho;
    long long comparacoes, movimentacoes;
    clock_t inicio, fim;

    lerArquivo(nomeArquivo, &vetor, &tamanho);

    comparacoes = movimentacoes = 0;
    inicio = clock();
    selectionSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();
    printf("\nSelectionSort: %lld comparacoes, %lld movimentacoes, Tempo: %lf segundos\n",
           comparacoes, movimentacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    comparacoes = movimentacoes = 0;
    inicio = clock();
    insertionSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();
    printf("\nInsertionSort: %lld comparacoes, %lld movimentacoes, Tempo: %lf segundos\n",
           comparacoes, movimentacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    comparacoes = movimentacoes = 0;
    inicio = clock();
    bubbleSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();
    printf("\nBubbleSort: %lld comparacoes, %lld movimentacoes, Tempo: %lf segundos\n",
           comparacoes, movimentacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    free(vetor);

    return 0;
}
