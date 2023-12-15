#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int *diagonal;
    int *superior;
    int *inferior;
    int tam;
}MFaixa;


void zeraMatriz(MFaixa* mf){
    int i;
    for(i=0; i<mf->tam; i++){
        mf->diagonal[i] = 0;
        if(i < mf->tam -1){
            mf->superior[i] = 0;
            mf->inferior[i] = 0;
        }
    }
}

MFaixa* criaMatriz(int t){
    MFaixa *mf;
    mf = (MFaixa*) malloc (sizeof(MFaixa));
    if(mf != NULL){
        if(t <= 1){
            printf("Dimensao deve ser > 1");
            return NULL;
        }
        mf->tam = t;
        mf->diagonal = (int*) malloc (t*sizeof(int));
        mf->superior = (int*) malloc ((t-1)*sizeof(int));
        mf->inferior = (int*) malloc ((t-1)*sizeof(int));
        if(mf->diagonal == NULL || mf->superior == NULL || mf->inferior == NULL)
          return NULL;
        zeraMatriz(mf);
    }
    return mf;
}

void destroiMatriz(MFaixa* mf){
    if(mf != NULL){
        free(mf->diagonal);
        free(mf->superior);
        free(mf->inferior);
        free(mf);
    }
}

int preencheAleatorio(MFaixa* mf, int ini, int fim){
    if(mf == NULL) return 0;
    srand(time(NULL));
    int i;
    for(i=0; i<mf->tam; i++){
        mf->diagonal[i] = ini + rand() % (fim-ini + 1);
        if(i < mf->tam -1){
            mf->superior[i] = ini + rand() % (fim-ini + 1);
            mf->inferior[i] = ini + rand() % (fim-ini + 1);
        }
    }
    return 1;
}

int insereElem(MFaixa* mf, int elem, int i, int j){
  if(mf == NULL) return 0;
  if(i < 0 || j < 0 || i >= mf->tam || j >= mf->tam){
    printf("Valores invalidos\n");
    return 0;
  }
  if(i == j) mf->diagonal[i] = elem;
  else if(i + 1 == j) mf->superior[i] = elem;
  else if(i == j + 1) mf->inferior[j] = elem;
  else{
    printf("Indices fora da faixa\n");
    return 0;
  }
  return 1;
}

int consultaElem(MFaixa* mf, int i, int j){
  if(mf == NULL) return 0;
  if(i < 0 || j < 0 || i >= mf->tam || j >= mf->tam){
    printf("Valores invalidos\n");
    return 0;
  }
  if(i == j) return mf->diagonal[i];
  else if(i + 1 == j) return mf->superior[i];
  else if(i == j + 1) return mf->inferior[j];
  else return 0;
}

void imprimeFaixaVetores(MFaixa* mf){
  if(mf == NULL) return;
  int i;
  printf("Matriz Faixa, Tamanho: %d x %d:\n", mf->tam, mf->tam);
  printf("Diagonal = [");
  for(i=0; i<mf->tam; i++)
    printf("%d ", mf->diagonal[i]);
  printf("]\n");
  printf("Superior = [");
  for(i=0; i<mf->tam-1; i++)
    printf("%d ", mf->superior[i]);
  printf("]\n");
  printf("Inferior = [");
  for(i=0; i<mf->tam-1; i++)
    printf("%d ", mf->inferior[i]);
  printf("]\n\n");
}

void imprimeFaixa(MFaixa* mf){
  if(mf == NULL) return;
  int i, j;
  imprimeFaixaVetores(mf);
  printf("Matriz Original:\n");
  for(i=0; i<mf->tam; i++){
    for(j=0; j<mf->tam; j++)
      printf("%d\t", consultaElem(mf, i, j));
    printf("\n");
  }
}

int main() {
    int tamanho;
    printf("Digite o tamanho da matriz de faixa: ");
    scanf("%d", &tamanho);

    MFaixa *M = criaMatriz(tamanho);

    int opcao = 0;

    while (opcao != 5) {
        printf("\nMENU:\n");
        printf("1 - Preencher a matriz\n");
        printf("2 - Inserir elemento\n");
        printf("3 - Consultar elemento\n");
        printf("4 - Imprimir matriz\n");
        printf("5 - Sair\n");

        printf("-> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                preencheAleatorio(M, 10, 20);
                printf("Matriz preenchida aleatoriamente.\n");
                break;
            case 2: 
                int elem, i, j;
                printf("Digite o elemento: ");
                scanf("%d", &elem);
                printf("Digite a linha: ");
                scanf("%d", &i);
                printf("Digite a coluna: ");
                scanf("%d", &j);
                if (insereElem(M, elem, i, j))
                    printf("Elemento inserido com sucesso.\n");
                break;
            case 3: 
                printf("Digite a linha: ");
                scanf("%d", &i);
                printf("Digite a coluna: ");
                scanf("%d", &j);
                int valor = consultaElem(M, i, j);
                if (valor != 0)
                    printf("Elemento (%d, %d): %d\n", i, j, valor);
                break;
            case 4: 
                imprimeFaixa(M);
                break;
            case 5:
                printf("................\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    destroiMatriz(M);

    return 0;
}