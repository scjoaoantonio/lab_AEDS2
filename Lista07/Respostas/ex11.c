#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 3

typedef struct {
    int dados[MAX][MAX];
    int lin, col;
} Matriz;

Matriz* criaMatriz(int l, int c);
void destroiMatriz(Matriz* mat);
int preencheAleatorio(Matriz* mat, int ini, int fim);
void imprime(Matriz* mat);
Matriz* somaMatrizes(Matriz* mat1, Matriz* mat2);
Matriz* subtraiMatrizes(Matriz* mat1, Matriz* mat2);
Matriz* multiplicaMatrizes(Matriz* mat1, Matriz* mat2);

int main() {
    Matriz *M1, *M2, *soma, *subtracao, *multiplicacao;

    M1 = criaMatriz(MAX, MAX);
    preencheAleatorio(M1, 0, 10);

    M2 = criaMatriz(MAX, MAX);
    preencheAleatorio(M2, 0, 10);

    printf("Matriz 1:\n");
    imprime(M1);

    printf("Matriz 2:\n");
    imprime(M2);

    soma = somaMatrizes(M1, M2);
    if (soma != NULL) {
        printf("Soma das Matrizes:\n");
        imprime(soma);
        destroiMatriz(soma);
    } else {
        printf("Operação de soma inválida, matrizes incompatíveis!\n");
    }

    subtracao = subtraiMatrizes(M1, M2);
    if (subtracao != NULL) {
        printf("Subtração das Matrizes:\n");
        imprime(subtracao);
        destroiMatriz(subtracao);
    } else {
        printf("Operação de subtração inválida, matrizes incompatíveis!\n");
    }

    multiplicacao = multiplicaMatrizes(M1, M2);
    if (multiplicacao != NULL) {
        printf("Multiplicação das Matrizes:\n");
        imprime(multiplicacao);
        destroiMatriz(multiplicacao);
    } else {
        printf("Operação de multiplicação inválida, dimensões incompatíveis!\n");
    }

    destroiMatriz(M1);
    destroiMatriz(M2);

    return 0;
}

void zeraMatriz(Matriz* mat) {
    for (int i = 0; i < mat->lin; i++)
        for (int j = 0; j < mat->col; j++)
            mat->dados[i][j] = 0;
}

Matriz* criaMatriz(int l, int c) {
    Matriz* mat = (Matriz*)malloc(sizeof(Matriz));
    if (mat == NULL) {
        printf("Erro ao alocar matriz!\n");
        return NULL;
    }
    if (l <= 0 || c <= 0 || l > MAX || c > MAX) {
        printf("Valores inválidos, matriz não criada!\n");
        free(mat);
        return NULL;
    }
    mat->lin = l;
    mat->col = c;
    zeraMatriz(mat);
    return mat;
}

void destroiMatriz(Matriz* mat) {
    if (mat != NULL)
        free(mat);
}

int preencheAleatorio(Matriz* mat, int ini, int fim) {
    if (mat == NULL) return 0;
    srand(time(NULL));
    for (int i = 0; i < mat->lin; i++)
        for (int j = 0; j < mat->col; j++)
            mat->dados[i][j] = ini + rand() % (fim - ini + 1);
    return 1;
}

void imprime(Matriz* mat) {
    if (mat == NULL) return;
    printf("Matriz %d x %d:\n", mat->lin, mat->col);
    for (int i = 0; i < mat->lin; i++) {
        for (int j = 0; j < mat->col; j++)
            printf("\t%d", mat->dados[i][j]);
        printf("\n");
    }
}

Matriz* somaMatrizes(Matriz* mat1, Matriz* mat2) {
    if (mat1 == NULL || mat2 == NULL || mat1->lin != mat2->lin || mat1->col != mat2->col) {
        return NULL;
    }

    Matriz* result = criaMatriz(mat1->lin, mat1->col);
    for (int i = 0; i < mat1->lin; i++) {
        for (int j = 0; j < mat1->col; j++) {
            result->dados[i][j] = mat1->dados[i][j] + mat2->dados[i][j];
        }
    }

    return result;
}

Matriz* subtraiMatrizes(Matriz* mat1, Matriz* mat2) {
    if (mat1 == NULL || mat2 == NULL || mat1->lin != mat2->lin || mat1->col != mat2->col) {
        return NULL;
    }

    Matriz* result = criaMatriz(mat1->lin, mat1->col);
    for (int i = 0; i < mat1->lin; i++) {
        for (int j = 0; j < mat1->col; j++) {
            result->dados[i][j] = mat1->dados[i][j] - mat2->dados[i][j];
        }
    }

    return result;
}

Matriz* multiplicaMatrizes(Matriz* mat1, Matriz* mat2) {
    if (mat1 == NULL || mat2 == NULL || mat1->col != mat2->lin) {
        return NULL;
    }

    Matriz* result = criaMatriz(mat1->lin, mat2->col);
    for (int i = 0; i < mat1->lin; i++) {
        for (int j = 0; j < mat2->col; j++) {
            result->dados[i][j] = 0;
            for (int k = 0; k < mat1->col; k++) {
                result->dados[i][j] += mat1->dados[i][k] * mat2->dados[k][j];
            }
        }
    }

    return result;
}
