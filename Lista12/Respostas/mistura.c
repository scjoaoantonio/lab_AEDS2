#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp; // Número de comparações

// Função de comparação para qsort
int comparacaoInteiros(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void preencheAleatorio(int* v, int n, int ini, int fim) {
    for (int i = 0; i < n; i++) {
        v[i] = ini + rand() % (fim - ini + 1);
    }
}

void imprimeVetor(const int* v, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", v[i]);
    }
    printf("]\n");
}

int buscaSequencial(const int* v, int n, int elem) {
    comp = 0;
    for (int i = 0; i < n; i++) {
        comp++;
        if (v[i] == elem) {
            return i; // Elemento encontrado
        }
    }
    return -1; // Elemento não encontrado
}

int buscaBinariaRecursiva(const int* v, int ini, int fim, int elem) {
    if (ini > fim) {
        return -1;
    }
    int meio = (ini + fim) / 2;
    comp++;
    if (v[meio] == elem) {
        return meio;
    } else if (elem < v[meio]) {
        return buscaBinariaRecursiva(v, ini, meio - 1, elem);
    } else {
        return buscaBinariaRecursiva(v, meio + 1, fim, elem);
    }
}

int buscaBinariaIterativa(const int* v, int ini, int fim, int elem) {
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comp++;
        if (elem == v[meio]) {
            return meio;
        } else if (elem < v[meio]) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    return -1;
}

double medirTempo(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void testeComparativo(int (*algoritmo)(const int*, int, int), const int* v, int n, int elem, const char* nomeAlgoritmo) {
    clock_t inicio, fim;
    comp = 0;

    inicio = clock();
    int indice = algoritmo(v, n, elem);
    fim = clock();

    printf("----- Informacoes %s:\n", nomeAlgoritmo);
    printf("Tempo Execucao:  %f seconds.\n", medirTempo(inicio, fim));
    printf("Comparacoes: %d\n", comp);

    if (indice != -1) {
        printf("O elemento %d foi encontrado na pos %d.\n", elem, indice);
    } else {
        printf("O elemento %d NAO foi encontrado!\n", elem);
    }

    printf("\n");
}

int main() {
    srand(time(NULL));

    int n, elem;
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);

    int* v = (int*)malloc(n * sizeof(int));
    preencheAleatorio(v, n, 1, n);
    printf("Vetor gerado aleatoriamente:\n");
    imprimeVetor(v, n);

    printf("Digite um elemento para busca:\n");
    scanf("%d", &elem);

    // Teste comparativo para Busca Sequencial
    testeComparativo(buscaSequencial, v, n, elem, "Busca Sequencial");

    // Ordenar vetor para Busca Binária
    int* vOrdenado = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        vOrdenado[i] = v[i];
    }
    qsort(vOrdenado, n, sizeof(int), comparacaoInteiros);

    // Teste comparativo para Busca Binária Recursiva
    testeComparativo(buscaBinariaRecursiva, vOrdenado, n, elem, "Busca Binaria Recursiva");

    // Teste comparativo para Busca Binária Iterativa
    testeComparativo(buscaBinariaIterativa, vOrdenado, n, elem, "Busca Binaria Iterativa");

    free(v);
    free(vOrdenado);

    return 0;
}
