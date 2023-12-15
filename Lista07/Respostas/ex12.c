#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int **dados;
    int lin, col;
} Matriz;

void zeraMatriz(Matriz *mat) {
    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            mat->dados[i][j] = 0;
}

Matriz *criaMatriz(int l, int c) {
    Matriz *mat;
    mat = (Matriz *)malloc(sizeof(Matriz));
    if (mat != NULL) {
        if (l <= 0 || c <= 0) {
            printf("Valores inválidos\n");
            return NULL;
        }
        int i;
        mat->lin = l;
        mat->col = c;
        mat->dados = (int **)malloc(l * sizeof(int *));
        for (i = 0; i < l; i++)
            mat->dados[i] = (int *)malloc(c * sizeof(int));
        zeraMatriz(mat);
    }
    return mat;
}

void destroiMatriz(Matriz *mat) {
    if (mat != NULL) {
        int i;
        for (i = 0; i < mat->lin; i++)
            free(mat->dados[i]);
        free(mat->dados);
        free(mat);
    }
}

int preencheAleatorio(Matriz *mat, int ini, int fim) {
    if (mat == NULL)
        return 0;
    srand(time(NULL));
    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            mat->dados[i][j] = ini + rand() % (fim - ini + 1);
    return 1;
}

int insereElem(Matriz *mat, int elem, int l, int c) {
    if (mat == NULL)
        return 0;
    if (l < 0 || c < 0 || l >= mat->lin || c >= mat->col) {
        printf("Valores inválidos\n");
        return 0;
    }
    mat->dados[l][c] = elem;
    return 1;
}

int consultaElem(Matriz *mat, int *p, int l, int c) {
    if (mat == NULL)
        return 0;
    if (l < 0 || c < 0 || l >= mat->lin || c >= mat->col) {
        printf("Valores inválidos\n");
        return 0;
    }
    *p = mat->dados[l][c];
    return 1;
}

void imprime(Matriz *mat) {
    if (mat == NULL)
        return;
    int i, j;
    printf("Matriz %d x %d:\n", mat->lin, mat->col);
    for (i = 0; i < mat->lin; i++) {
        for (j = 0; j < mat->col; j++)
            printf("%d ", mat->dados[i][j]);
        printf("\n");
    }
    printf("\n");
}

int e_matrizQuadrada(Matriz *mat) {
    if (mat == NULL)
        return 0;
    return (mat->lin == mat->col);
}

Matriz *criaTriangularSup(Matriz *mat) {
    if (mat == NULL)
        return NULL;
    if (!e_matrizQuadrada(mat)) {
        printf("Nao eh matriz quadrada!\n");
        return NULL;
    }
    int i, j;
    Matriz *ts = criaMatriz(mat->lin, mat->col);
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            if (i <= j)
                ts->dados[i][j] = mat->dados[i][j];
    return ts;
}

Matriz *criaTriangularInf(Matriz *mat) {
    if (mat == NULL)
        return NULL;
    if (!e_matrizQuadrada(mat)) {
        printf("Nao eh matriz quadrada\n");
        return NULL;
    }
    int i, j;
    Matriz *ti = criaMatriz(mat->lin, mat->col);
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            if (i >= j)
                ti->dados[i][j] = mat->dados[i][j];
    return ti;
}

Matriz *criaDiagonal(Matriz *mat) {
    if (mat == NULL)
        return NULL;
    if (!e_matrizQuadrada(mat)) {
        printf("Não eh matriz quadrada!\n");
        return NULL;
    }
    int i, j;
    Matriz *d = criaMatriz(mat->lin, mat->col);
    for (i = 0; i < mat->lin; i++)
        d->dados[i][i] = mat->dados[i][i];
    return d;
}

int e_Simetrica(Matriz *mat) {
    if (mat == NULL)
        return 0;
    if (!e_matrizQuadrada(mat)) {
        printf("Nao eh matriz quadrada!\n");
        return 0;
    }
    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = i + 1; j < mat->col; j++)
            if (mat->dados[i][j] != mat->dados[j][i])
                return 0;
    return 1;
}

Matriz *criaTransposta(Matriz *mat) {
    if (mat == NULL)
        return NULL;
    Matriz *t = criaMatriz(mat->col, mat->lin);
    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            t->dados[j][i] = mat->dados[i][j];
    return t;
}

int main() {
    Matriz *M;
    M = criaMatriz(2, 2);
    preencheAleatorio(M, 1, 10);
    imprime(M);

    Matriz *A;
    A = criaMatriz(3, 3);
    preencheAleatorio(A, 1, 10);
    imprime(A);

    if (e_Simetrica(A))
        printf("Matriz simetrica\n");
    else
        printf("Nao eh matriz simetrica\n");

    Matriz *TS, *TI;
    TS = criaTriangularSup(A);
    TI = criaTriangularInf(A);

    printf("Triangular Superior:\n");
    imprime(TS);
    printf("Triangular Inferior:\n");
    imprime(TI);

    Matriz *T;
    T = criaTransposta(A);
    printf("Transposta:\n");
    imprime(T);

    destroiMatriz(M);
    destroiMatriz(A);
    destroiMatriz(TS);
    destroiMatriz(TI);
    destroiMatriz(T);

    return 0;
}
