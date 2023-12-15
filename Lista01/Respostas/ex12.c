#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 5;

void vetorAleatorio(int *vet, int tamanho) {
    printf("Vetor:\t");
    for (int i = 0; i < tamanho; i++) {
        vet[i] = rand() % 100;
        printf("%d ", vet[i]);
    }
    printf("\n");
}

int retornaMenor(int *vet, int tamanho) {
    int menor = vet[0];
    for (int i = 1; i < tamanho; i++) {
        if (vet[i] < menor) {
            menor = vet[i];
        }
    }
    return menor;
}

int retornaMaior(int *vet, int tamanho) {
    int maior = vet[0];
    for (int i = 1; i < tamanho; i++) {
        if (vet[i] > maior) {
            maior = vet[i];
        }
    }
    return maior;
}

float retornaMedia(int *vet, int tamanho) {
    float soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma = soma + vet[i];
    }
    return soma / tamanho;
}

int main() {
    srand(time(NULL));
    
    int vet[N], vet2[N];

    vetorAleatorio(vet, N);
    vetorAleatorio(vet2, N);

    printf("Maior numero do vetor 1: %d\n", retornaMaior(vet, N));
    printf("Maior numero do vetor 2: %d\n", retornaMaior(vet2, N));
    printf("Menor numero do vetor 1: %d\n", retornaMenor(vet, N));
    printf("Menor numero do vetor 2: %d\n", retornaMenor(vet2, N));
    printf("Media do vetor 1: %.2f\n", retornaMedia(vet, N));
    printf("Media do vetor 2: %.2f\n", retornaMedia(vet2, N));

    return 0;
}
