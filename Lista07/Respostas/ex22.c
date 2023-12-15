#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int **dados;
    int lin, col;
}Matriz;

typedef struct {
    int *A;
    int *IA;
    int *JA;
    int lin, col, QNN, QI;
} MEsparsaCSR;

void zeraMatriz(Matriz* mat){
    int i, j;
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            mat->dados[i][j] = 0; 
}

Matriz* criaMatriz(int l, int c){
    Matriz* mat;
    mat = (Matriz*) malloc (sizeof(Matriz));
    if(mat != NULL){
        if(l <= 0 || c <= 0){
            printf("Valores invalidos\n");
            return NULL;
        }
        int i;        
        mat->lin = l;
        mat->col = c;
        mat->dados = (int**) malloc (l*sizeof(int*));
        for(i=0; i<l; i++)
            mat->dados[i] = (int*) malloc (c*sizeof(int));
        zeraMatriz(mat);
    }
    return mat;
}

void destroiMatriz(Matriz* mat){
    if(mat != NULL){
        int i;
        for(i=0; i<mat->lin; i++)
            free(mat->dados[i]);
        free(mat->dados);
        free(mat);
    }
}

int preencheAleatorio(Matriz* mat, int ini, int fim){
    if(mat == NULL) return 0;
    srand(time(NULL));
    int i, j;
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            mat->dados[i][j] = ini + rand() % (fim-ini + 1); 
    return 1;
}

int insereElem(Matriz* mat, int elem, int l, int c){
    if(mat == NULL) return 0;
    if(l < 0 || c < 0 || l >= mat->lin || c >= mat->col){
        printf("Valores invalidos\n");
        return 0;
    }
    mat->dados[l][c] = elem;
    return 1;
}

int consultaElem(Matriz* mat, int *p, int l, int c){
    if(mat == NULL) return 0;
    if(l < 0 || c < 0 || l >= mat->lin || c >= mat->col){
        printf("Valores invalidos\n");
        return 0;
    }
    *p = mat->dados[l][c];
    return 1;
}

void imprime(Matriz* mat){
    if(mat == NULL) return;
    int i, j;
    printf("Matriz %d x %d:\n", mat->lin, mat->col);
    for(i=0; i<mat->lin; i++){
        for(j=0; j<mat->col; j++)
            printf("%d ", mat->dados[i][j]);
        printf("\n");
    }
    printf("\n");
}


int e_matrizQuadrada(Matriz *mat){
    if(mat == NULL) return 0;
    return (mat->lin == mat->col);
}

Matriz* criaTriangularSup(Matriz* mat){
    if(mat == NULL) return NULL;
    if(!e_matrizQuadrada(mat)){
        printf("A matriz nao eh quadrada\n");
        return NULL;
    } 
    int i, j;
    Matriz* ts = criaMatriz(mat->lin, mat->col);
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            if(i <= j)
                ts->dados[i][j] = mat->dados[i][j];
    return ts;
}

Matriz* criaTriangularInf(Matriz* mat){
    if(mat == NULL) return NULL;
    if(!e_matrizQuadrada(mat)){
        printf("A matriz nao eh quadrada\n");
        return NULL;
    } 
    int i, j;
    Matriz* ti = criaMatriz(mat->lin, mat->col);
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            if(i >= j)
                ti->dados[i][j] = mat->dados[i][j];
    return ti;
}

Matriz* criaDiagonal(Matriz* mat){
    if(mat == NULL) return NULL;
    if(!e_matrizQuadrada(mat)){
        printf("A matriz nao eh quadrada\n");
        return NULL;
    } 
    int i, j;
    Matriz* d = criaMatriz(mat->lin, mat->col);
    for(i=0; i<mat->lin; i++)
        d->dados[i][i] = mat->dados[i][i];
    return d;
}

int e_Simetrica(Matriz* mat){
    if(mat == NULL) return 0;
    if(!e_matrizQuadrada(mat)){
        printf("A matriz nao eh quadrada\n");
        return 0;
    }
    int i, j;
    for(i=0; i<mat->lin; i++)
        for(j=i+1; j<mat->col; j++)
            if(mat->dados[i][j] != mat->dados[j][i])
                return 0;
    return 1;
}

Matriz* criaTransposta(Matriz* mat){
    if(mat == NULL) return NULL;
    Matriz* t = criaMatriz(mat->col, mat->lin);
    int i, j;
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            t->dados[j][i] = mat->dados[i][j];
    return t;
}

MEsparsaCSR* criaMatrizEsparsa(int l, int c, int qnn){
    MEsparsaCSR *ms;
    ms = (MEsparsaCSR*) malloc (sizeof(MEsparsaCSR));
    if(ms != NULL){
        if(l <= 0 || c <= 0 || qnn < 0){
            printf("Valores invalidos\n");
            return NULL;
        }
        ms->lin = l; ms->col = c;
        ms->QI = 0; ms->QNN = qnn;
        ms->A = ms->IA = ms->JA = NULL;
        if(qnn != 0){
            ms->A = (int*) malloc (qnn*sizeof(int));
            ms->JA = (int*) malloc (qnn*sizeof(int));
            if(ms->A == NULL || ms->JA == NULL) return NULL;
        }
        ms->IA = (int*) malloc ((ms->lin+1)*sizeof(int));
        if(ms->IA == NULL) return NULL;
        int i; for(i=0; i<l+1; i++) ms->IA[i] = 0;
    }
    return ms;
}

int* meuRealloc(int* v, int tam){
    int* aux = (int*) malloc ((tam+1)*sizeof(int));
    if(aux != NULL){
        if(v != NULL){
            int i;
            for(i=0; i<tam; i++)
                aux[i] = v[i];
            free(v);
        }
    }
    return aux;
}

void imprimeEsparsaVetores(MEsparsaCSR* ms){
  if(ms == NULL) return;
  int i, j;
  printf("Matriz Esparsa, Tamanho: %d x %d:\n", ms->lin, ms->col);
  printf("%d elementos nao nulos.\n", ms->QNN);
  printf("A = [");
  for(i=0; i<ms->QNN; i++)
    printf("%d ", ms->A[i]);
  printf("]\n");
  printf("IA = [");
  for(i=0; i<ms->lin+1; i++)
    printf("%d ", ms->IA[i]);
  printf("]\n");
  printf("JA = [");
  for(i=0; i<ms->QNN; i++)
    printf("%d ", ms->JA[i]);
  printf("]\n\n");
}

int insereElemEsparsa(MEsparsaCSR *ms, int elem, int i, int j) {
    if(ms == NULL) return 0;
    if(i < 0 || j < 0 || i >= ms->lin || j >= ms->col){
        printf("Valores invalidos\n");
        return 0;
    }
    int k;
    int index = -1;
    int ini = ms->IA[i]; int fim = ms->IA[i+1];
    // Encontre a posição correta para inserir o valor
    for(k = ini; k<fim; k++)
        if (ms->JA[k] >= j) {
            index = k;
            break;
        }

    if (index == -1) {
        if(ms->QI == ms->QNN){
            ms->A = meuRealloc(ms->A, ms->QNN);
            ms->JA = meuRealloc(ms->JA, ms->QNN);
            ms->QNN++;
        }
        
        for(k = ms->QNN-1; k>=fim; k--){
            ms->A[k] = ms->A[k-1];
            ms->JA[k] = ms->JA[k-1];
        }
        ms->A[fim] = elem;
        ms->JA[fim] = j;
        ms->QI++;

        for (int k = i+1; k<=ms->lin; k++)
            ms->IA[k]++;
    } else { 
        ms->A[index] = elem;
    }
    imprimeEsparsaVetores(ms);
    return 1;
}

int removeElemEsparsa(MEsparsaCSR *ms, int i, int j) {
    if(ms == NULL) return 0;
    if(i < 0 || j < 0 || i >= ms->lin || j >= ms->col){
        printf("Valores invalidos\n");
        return 0;
    }

    int k;
    int index = -1;
    int ini = ms->IA[i]; int fim = ms->IA[i+1];
    
    for(k = ini; k<fim; k++)
        if (ms->JA[k] == j) {
            index = k;
            break;
        }

    if (index != -1) {
        
        for (k = index; k < ms->QNN - 1; k++) {
            ms->A[k] = ms->A[k+1];
            ms->JA[k] = ms->JA[k+1];
        }
        ms->QNN--;
        ms->QI--;

        for (int k = i+1; k<=ms->lin; k++)
            ms->IA[k]--;
    }else{
        printf("Elemento nao existente\n"); return 0;
    }
    imprimeEsparsaVetores(ms);
    return 1;
}


MEsparsaCSR* transformarEmCSR(Matriz* mat){
    MEsparsaCSR *ms = criaMatrizEsparsa(mat->lin, mat->col, 0);
    if(ms != NULL){
        if(mat == NULL){
            printf("Matriz de entrada inexistente!\n");
            return NULL;
        }

        int i, j;
        for(i=0; i<mat->lin; i++)
            for(j=0; j<mat->col; j++)
                if(mat->dados[i][j] != 0)
                    insereElemEsparsa(ms, mat->dados[i][j], i, j);
    }
    return ms;
}

int consultaElemEsparsa(MEsparsaCSR* ms, int i, int j){
  if(ms == NULL) return 0;
  if(i < 0 || j < 0 || i >= ms->lin || j >= ms->col){
    printf("Valores invalidos\n");
    return 0;
  }
  int k;
  for(k = ms->IA[i]; k<ms->IA[i+1]; k++)
    if(ms->JA[k] == j) return ms->A[k];
  return 0;
}

void imprimeEsparsa(MEsparsaCSR* ms){
  if(ms == NULL) return;
  int i, j;
  imprimeEsparsaVetores(ms);
  printf("Matriz Original:\n");
  for(i=0; i<ms->lin; i++){
    for(j=0; j<ms->col; j++)
      printf("%d\t", consultaElemEsparsa(ms, i, j));
    printf("\n");
  }
}

void destroiMatrizEsparsa(MEsparsaCSR* ms){
    if(ms != NULL){
        free(ms->A);
        free(ms->IA);
        free(ms->JA);
        free(ms);
    }
}


int main() {
    Matriz *M = criaMatriz(4, 6);
    insereElem(M, 10, 0, 0);
    insereElem(M, 20, 0, 1);
    insereElem(M, 30, 1, 1);
    insereElem(M, 4, 1, 3);
    insereElem(M, 50, 2, 2);
    insereElem(M, 60, 2, 3);
    insereElem(M, 70, 2, 4);
    insereElem(M, 80, 3, 5);

    MEsparsaCSR *MS;
    MS = transformarEmCSR(M);

    MEsparsaCSR *MS2;
    MS2 = criaMatrizEsparsa(4, 6, 0);

    int opcao = 0;

    while (opcao != 7) {
        printf("\nMENU\n");
        printf("1 - Imprimir matriz original\n");
        printf("2 - Imprimir matriz esparsa CSR\n");
        printf("3 - Inserir elemento na matriz esparsa CSR\n");
        printf("4 - Remover elemento da matriz esparsa CSR\n");
        printf("5 - Consultar elemento da matriz esparsa CSR\n");
        printf("6 - Inserir elementos na matriz esparsa CSR manualmente\n");
        printf("7 - Sair\n");

        printf("-> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprime(M);
                break;
            case 2: 
                imprimeEsparsa(MS);
                break;
            case 3:
                int elem, l, c;
                printf("Digite o elemento: ");
                scanf("%d", &elem);
                printf("Digite a linha: ");
                scanf("%d", &l);
                printf("Digite a coluna: ");
                scanf("%d", &c);
                insereElemEsparsa(MS2, elem, l, c);
                break;
            case 4:
                printf("Digite a linha: ");
                scanf("%d", &l);
                printf("Digite a coluna: ");
                scanf("%d", &c);
                removeElemEsparsa(MS2, l, c);
                break;
            case 5:
                printf("Digite a linha: ");
                scanf("%d", &l);
                printf("Digite a coluna: ");
                scanf("%d", &c);
                int valor = consultaElemEsparsa(MS2, l, c);
                if (valor != 0)
                    printf("Elemento (%d, %d): %d\n", l, c, valor);
                break;
            case 6:
                for (l = 0; l < MS2->lin; l++) {
                    for (c = 0; c < MS2->col; c++) {
                        printf("Digite o elemento (%d, %d): ", l, c);
                        scanf("%d", &elem);
                        insereElemEsparsa(MS2, elem, l, c);
                    }
                }
                break;
            case 7: // Sair
                printf("..........\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    destroiMatriz(M);
    destroiMatrizEsparsa(MS);
    destroiMatrizEsparsa(MS2);

    return 0;
}