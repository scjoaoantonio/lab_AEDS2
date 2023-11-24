#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa {
    char nome[50];
    int idade;
};

void trocar(struct Pessoa *a, struct Pessoa *b) {
    struct Pessoa temp = *a;
    *a = *b;
    *b = temp;
}

int compararPessoa(const void *a, const void *b) {
    struct Pessoa *p1 = (struct Pessoa *)a;
    struct Pessoa *p2 = (struct Pessoa *)b;

    int comparacaoNome = strcmp(p1->nome, p2->nome);

    if (comparacaoNome != 0) {
        return comparacaoNome;
    } else {
        return p1->idade - p2->idade;
    }
}

void selectionSort(struct Pessoa vetor[], int n, int crescente) {
    int i, j, indiceExtremo;

    for (i = 0; i < n-1; i++) {
        indiceExtremo = i;
        for (j = i+1; j < n; j++) {
            int comparacao = compararPessoa(&vetor[j], &vetor[indiceExtremo]);

            if ((crescente && comparacao < 0) || (!crescente && comparacao > 0)) {
                indiceExtremo = j;
            }
        }
        trocar(&vetor[indiceExtremo], &vetor[i]);
    }
}

void insertionSort(struct Pessoa vetor[], int n, int crescente) {
    int i, j;
    struct Pessoa chave;

    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0) {
            int comparacao = compararPessoa(&vetor[j], &chave);

            if ((crescente && comparacao <= 0) || (!crescente && comparacao >= 0)) {
                break;
            }

            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

void imprimirVetor(struct Pessoa vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s, %d\n", vetor[i].nome, vetor[i].idade);
    }
    printf("\n");
}

int main() {
    struct Pessoa pessoas[] = {
        {"Pessoa 1", 25},
        {"Pessoa 2", 30},
        {"Pessoa 3", 20},
        {"Pessoa 4", 35},
        {"Pessoa 5", 25}
    };

    int tamanho = sizeof(pessoas) / sizeof(pessoas[0]);

    qsort(pessoas, tamanho, sizeof(struct Pessoa), compararPessoa);
    printf("Ordenação crescente:\n");
    imprimirVetor(pessoas, tamanho);

    qsort(pessoas, tamanho, sizeof(struct Pessoa), compararPessoa);
    printf("Ordenação decrescente:\n");
    imprimirVetor(pessoas, tamanho);

    selectionSort(pessoas, tamanho, 1);
    printf("Ordenação crescente (Selection Sort):\n");
    imprimirVetor(pessoas, tamanho);

    selectionSort(pessoas, tamanho, 0);
    printf("Ordenação decrescente (Selection Sort):\n");
    imprimirVetor(pessoas, tamanho);

    insertionSort(pessoas, tamanho, 1);
    printf("Ordenação crescente (Insertion Sort):\n");
    imprimirVetor(pessoas, tamanho);

    insertionSort(pessoas, tamanho, 0);
    printf("Ordenação decrescente (Insertion Sort):\n");
    imprimirVetor(pessoas, tamanho);

    return 0;
}