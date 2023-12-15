#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elementos;
    int tamanho;
} Inteiros;

Inteiros criarConjuntoVazio() {
    Inteiros conjunto;
    conjunto.elementos = NULL;
    conjunto.tamanho = 0;
    return conjunto;
}

void inserirElementoNoConjunto(Inteiros *conjunto, int elemento) {
    conjunto->tamanho++;
    conjunto->elementos = (int *)realloc(conjunto->elementos, conjunto->tamanho * sizeof(int));
    conjunto->elementos[conjunto->tamanho - 1] = elemento;
}

void removerElementoDoConjunto(Inteiros *conjunto, int elemento) {
    int i;
    int *novoVetor = NULL;
    int novoTamanho = 0;
    for (i = 0; i < conjunto->tamanho; i++) {
        if (conjunto->elementos[i] != elemento) {
            novoTamanho++;
            novoVetor = (int *)realloc(novoVetor, novoTamanho * sizeof(int));
            novoVetor[novoTamanho - 1] = conjunto->elementos[i];
        }
    }

    free(conjunto->elementos);
    conjunto->elementos = novoVetor;
    conjunto->tamanho = novoTamanho;
}

int pertenceAoConjunto(const Inteiros *conjunto, int numero) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        if (conjunto->elementos[i] == numero) {
            return 1;
        }
    }
    return 0;
}

int obterMenorValorNoConjunto(const Inteiros *conjunto) {
    int menor = conjunto->elementos[0];
    for (int i = 1; i < conjunto->tamanho; i++) {
        if (conjunto->elementos[i] < menor) {
            menor = conjunto->elementos[i];
        }
    }
    return menor;
}

int obterMaiorValorNoConjunto(const Inteiros *conjunto) {
    int maior = conjunto->elementos[0];
    for (int i = 1; i < conjunto->tamanho; i++) {
        if (conjunto->elementos[i] > maior) {
            maior = conjunto->elementos[i];
        }
    }
    return maior;
}

int conjuntosSaoIguais(const Inteiros *conjunto1, const Inteiros *conjunto2) {
    if (conjunto1->tamanho != conjunto2->tamanho) {
        return 0;
    }

    for (int i = 0; i < conjunto1->tamanho; i++) {
        if (!pertenceAoConjunto(conjunto2, conjunto1->elementos[i])) {
            return 0;
        }
    }
    return 1;
}

int obterTamanhoDoConjunto(const Inteiros *conjunto) {
    return conjunto->tamanho;
}

int conjuntoEhVazio(const Inteiros *conjunto) {
    return (conjunto->tamanho == 0);
}

void liberarConjunto(Inteiros *conjunto) {
    free(conjunto->elementos);
    conjunto->elementos = NULL;
    conjunto->tamanho = 0;
}

int main() {
    Inteiros conjunto1 = criarConjuntoVazio();
    Inteiros conjunto2 = criarConjuntoVazio();

    inserirElementoNoConjunto(&conjunto1, 154);
    inserirElementoNoConjunto(&conjunto1, 852);
    inserirElementoNoConjunto(&conjunto1, 30);

    inserirElementoNoConjunto(&conjunto2, 72);
    inserirElementoNoConjunto(&conjunto2, 13);
    inserirElementoNoConjunto(&conjunto2, 40);

    printf("Conjunto 1:\n");
    for (int i = 0; i < conjunto1.tamanho; i++) {
        printf("%d ", conjunto1.elementos[i]);
    }
    printf("\n");

    printf("Conjunto 2:\n");
    for (int i = 0; i < conjunto2.tamanho; i++) {
        printf("%d ", conjunto2.elementos[i]);
    }
    printf("\n");

    int numero = 2;
    if (pertenceAoConjunto(&conjunto1, numero)) {
        printf("%d pertence ao Conjunto 1\n", numero);
    } else {
        printf("%d NÃO pertence ao Conjunto 1\n", numero);
    }

    printf("Menor valor do Conjunto 2: %d\n", obterMenorValorNoConjunto(&conjunto2));
    printf("Maior valor do Conjunto 2: %d\n", obterMaiorValorNoConjunto(&conjunto2));

    if (conjuntosSaoIguais(&conjunto1, &conjunto2)) {
        printf("Conjunto 1 e Conjunto 2 são iguais.\n");
    } else {
        printf("Conjunto 1 e Conjunto 2 não são iguais.\n");
    }

    printf("Tamanho do Conjunto 1: %d\n", obterTamanhoDoConjunto(&conjunto1));
    printf("Tamanho do Conjunto 2: %d\n", obterTamanhoDoConjunto(&conjunto2));

    if (conjuntoEhVazio(&conjunto1)) {
        printf("Conjunto 1 está vazio.\n");
    } else {
        printf("Conjunto 1 não está vazio.\n");
    }

    liberarConjunto(&conjunto1);
    liberarConjunto(&conjunto2);

    return 0;
}
