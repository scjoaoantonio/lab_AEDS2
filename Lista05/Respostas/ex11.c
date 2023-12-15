#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef struct{
    int qtd, ini, fim;
    int dados[MAX];
}Fila;


Fila* criaFila(){
    Fila* fi;
    fi = (Fila*) malloc (sizeof(Fila));
    if(fi != NULL){
        fi->qtd = fi->ini = fi->fim = 0;
    }
    return fi;
}

void destroiFila(Fila *fi){
    if(fi != NULL)
        free(fi);
}

int tamanhoFila(Fila *fi){
    if(fi == NULL)
        return -1;
    return fi->qtd;
}

int estaCheia(Fila *fi){
    if(fi == NULL)
        return -1;
    return (fi->qtd == MAX);
}

int estaVazia(Fila *fi){
    if(fi == NULL)
        return -1;
    return (fi->qtd == 0);
}


int enfileirar(Fila* fi, int elem){
    if(fi == NULL) return 0;
    if(estaCheia(fi)) return 0;
    fi->dados[fi->fim] = elem;
    fi->fim = (fi->fim+1) % MAX;
    fi->qtd++;
    return 1;
}

int desenfileirar(Fila* fi){
    if(fi == NULL) return 0;
    if(estaVazia(fi)) return 0;
    fi->ini = (fi->ini+1) % MAX;
    fi->qtd--;
    return 1;
}

int verInicio(Fila* fi, int* p){
  if(fi == NULL) return 0;
  if(estaVazia(fi)) return 0;
  *p = fi->dados[fi->ini];
  return 1;
}

void imprime(Fila* fi){
  if(fi == NULL) return;
  if(estaVazia(fi)){
    printf("Fila Vazia!\n");
    return;
  }
  int i = fi->ini;
  printf("Elementos: \n");
  do{
    printf("%d ", fi->dados[i]);
    i = (i + 1) % MAX;
  }while(i != fi->fim);
  //Usar do..while garante a impressao de todos elementos
  //mesmo com a fila cheia
  printf("\n");
}

int main() {
    Fila *fila = NULL;
    int opcao, elemento, inicio;

    do {
        printf("\nMenu:\n");
        printf("1 - Criar fila\n");
        printf("2 - Enfileirar um item\n");
        printf("3 - Ver o início da fila\n");
        printf("4 - Desenfileirar um item\n");
        printf("5 - Imprimir a fila\n");
        printf("6 - Destruir a fila\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (fila == NULL) {
                    fila = criaFila();
                    printf("Fila criada com sucesso.\n");
                } else {
                    printf("A fila já foi criada.\n");
                }
                break;

            case 2:
                if (fila != NULL) {
                    printf("Digite o elemento a ser enfileirado: ");
                    scanf("%d", &elemento);
                    if (enfileirar(fila, elemento)) {
                        printf("Elemento enfileirado com sucesso.\n");
                    } else {
                        printf("Erro ao enfileirar o elemento.\n");
                    }
                } else {
                    printf("A fila não foi criada ainda.\n");
                }
                break;

            case 3:
                if (fila != NULL) {
                    if (verInicio(fila, &inicio)) {
                        printf("O início da fila é: %d\n", inicio);
                    } else {
                        printf("A fila está vazia.\n");
                    }
                } else {
                    printf("A fila não foi criada ainda.\n");
                }
                break;

            case 4:
                if (fila != NULL) {
                    if (desenfileirar(fila)) {
                        printf("Elemento desenfileirado com sucesso.\n");
                    } else {
                        printf("A fila está vazia.\n");
                    }
                } else {
                    printf("A fila não foi criada ainda.\n");
                }
                break;

            case 5:
                if (fila != NULL) {
                    imprime(fila);
                } else {
                    printf("A fila não foi criada ainda.\n");
                }
                break;

            case 6:
                if (fila != NULL) {
                    destroiFila(fila);
                    fila = NULL;
                    printf("Fila destruída com sucesso.\n");
                } else {
                    printf("A fila não foi criada ainda.\n");
                }
                break;

            case 7:
                printf("Saindo do programa.\n");
                if (fila != NULL) {
                    destroiFila(fila);
                }
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
