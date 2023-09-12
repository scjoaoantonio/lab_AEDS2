#include <stdio.h>
#include <stdlib.h>

void preencherVetor(int vetor[], int tamanho, int i) {
    if (i < tamanho) {
        printf("Digite um numero: ");
        scanf("%d", &vetor[i]);
        preencherVetor(vetor, tamanho, i + 1);
    }
}

void imprimeCrescente(int vetor[], int tamanho, int i) {
    if (i < tamanho) {
        printf("%d ", vetor[i]);
        imprimeCrescente(vetor, tamanho, i + 1);
    }
}

void imprimeDecrescente(int vetor[], int tamanho, int i) {
    if (i >= 0) {
        printf("%d ", vetor[i]);
        imprimeDecrescente(vetor, tamanho, i - 1);
    }
}

int encontrarMaior(int vetor[], int tamanho, int i, int maior) {
    if (i < tamanho) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
        return encontrarMaior(vetor, tamanho, i + 1, maior);
    }
    return maior;
}

int main() {
    int N, maior;

    printf("\nDigite o tamanho do vetor: ");
    scanf("%d", &N);
    int vetor[N]; // Agora o tamanho do vetor é definido após obter N

    preencherVetor(vetor, N, 0);

    printf("\nOrdem crescente: ");
    imprimeCrescente(vetor, N, 0);

    printf("\nOrdem decrescente: ");
    imprimeDecrescente(vetor, N, N - 1);

    maior = encontrarMaior(vetor, N, 0, vetor[0]);
    printf("\nMaior numero do vetor: %d\n", maior);

    return 0;
}
