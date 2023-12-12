#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp;

int* copiaVetor(const int* v, int n) {
    int* v2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        v2[i] = v[i];
    }
    return v2;
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

void preencheAleatorio(int* v, int n, int ini, int fim) {
    for (int i = 0; i < n; i++) {
        v[i] = ini + rand() % (fim - ini + 1);
    }
}

void troca(int* a, int* b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int buscaSequencial(const int* v, int n, int elem) {
    for (int i = 0; i < n; i++) {
        comp++;
        if (v[i] == elem) {
            return i; 
        }
    }
    return -1; 
}

int particao(int* v, int ini, int fim) {
    int i = ini, j = fim;
    int pivo = v[(ini + fim) / 2];
    while (1) {
        while (v[i] > pivo) {
            i++;
        } 
        while (v[j] < pivo) {
            j--;
        }

        if (i < j) {
            troca(&v[i], &v[j]); 
            i++;
            j--;
        } else {
            return j; 
        }
    }
}

void QuickSort(int* v, int ini, int fim) {
    if (ini < fim) {
        int q = particao(v, ini, fim);
        QuickSort(v, ini, q);
        QuickSort(v, q + 1, fim);
    }
}

int rec_buscaBinariaDesc(const int* v, int ini, int fim, int elem) {
    if (ini > fim)
        return -1;
    int meio = (ini + fim) / 2;
    comp++;
    if (v[meio] == elem)
        return meio;
    else if (elem > v[meio])
        return rec_buscaBinariaDesc(v, ini, meio - 1, elem);
    else
        return rec_buscaBinariaDesc(v, meio + 1, fim, elem);
}

int it_buscaBinariaDesc(const int* v, int ini, int fim, int elem) {
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comp++;
        if (elem == v[meio])
            return meio;
        else if (elem > v[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

int main() {

    srand(time(NULL));
    comp = 0;
    clock_t t;

    int* v;
    int n, x;
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);
    v = (int*)malloc(n * sizeof(int));

    preencheAleatorio(v, n, 1, n);
    QuickSort(v, 0, n - 1);

    printf("Digite um elemento para busca:\n");
    scanf("%d", &x);

    int ind;

    t = clock();
    ind = buscaSequencial(v, n, x);
    t = clock() - t;
    printf("Tempo Execucao:  %f\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento %d foi encontrado na pos %d.\n", x, ind);
    else
        printf("O elemento %d NAO foi encontrado!\n", x);

    comp = 0;
    t = clock();
    ind = rec_buscaBinariaDesc(v, 0, n - 1, x);
    t = clock() - t;
    printf("Tempo:  %f.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento %d foi encontrado na pos %d.\n", x, ind);
    else
        printf("O elemento %d NAO foi encontrado!\n", x);

    comp = 0;
    t = clock();
    ind = it_buscaBinariaDesc(v, 0, n - 1, x);
    t = clock() - t;
    printf("Tempo:  %f\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    free(v);
    return 0;
}
