#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
    int topo;
    int dados[MAX];
}Pilha;


Pilha* criaPilha(){
    Pilha* pi;
    pi = (Pilha*) malloc (sizeof(Pilha));
    if(pi != NULL){
        pi->topo = 0;
    }
    return pi;
}

void destroiPilha(Pilha *pi){
    if(pi != NULL)
        free(pi);
}

int tamanhoPilha(Pilha *pi){
    if(pi == NULL)
        return -1;
    return pi->topo;
}

int estaCheia(Pilha *pi){
    if(pi == NULL)
        return -1;
    return (pi->topo == MAX);
}

int estaVazia(Pilha *pi){
    if(pi == NULL)
        return -1;
    return (pi->topo == 0);
}


int empilhar(Pilha* pi, int elem){
    if(pi == NULL) return 0;
    if(estaCheia(pi)) return 0;
    pi->dados[pi->topo] = elem;
    pi->topo++;
    return 1;
}

int desempilhar(Pilha* pi){
    if(pi == NULL) return 0;
    if(estaVazia(pi)) return 0;
    pi->topo--;
    return 1;
}

int verTopo(Pilha* pi, int* p){
  if(pi == NULL) return 0;
  if(estaVazia(pi)) return 0;
  *p = pi->dados[pi->topo-1];
  return 1;
}

void imprime(Pilha* pi){
  if(pi == NULL) return;
  if(estaVazia(pi)){
    printf("Pilha Vazia!\n");
    return;
  }
  printf("Elementos: \n");
  int i;
  for(i=pi->topo-1; i>=0; i--)
    printf("%d ", pi->dados[i]);
  printf("\n");
}

int main() {
    Pilha *pilha = NULL;
    int opcao, elemento, topo;

    do {
        printf("\nMenu:\n");
        printf("1 - Criar pilha\n");
        printf("2 - Empilhar um item\n");
        printf("3 - Ver o topo da pilha\n");
        printf("4 - Desempilhar um item\n");
        printf("5 - Imprimir a pilha\n");
        printf("6 - Destruir a pilha\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (pilha == NULL) {
                    pilha = criaPilha();
                    printf("Pilha criada com sucesso.\n");
                } else {
                    printf("A pilha já foi criada.\n");
                }
                break;

            case 2:
                if (pilha != NULL) {
                    printf("Digite o elemento a ser empilhado: ");
                    scanf("%d", &elemento);
                    if (empilhar(pilha, elemento)) {
                        printf("Elemento empilhado com sucesso.\n");
                    } else {
                        printf("Erro ao empilhar o elemento.\n");
                    }
                } else {
                    printf("A pilha não foi criada ainda.\n");
                }
                break;

            case 3:
                if (pilha != NULL) {
                    if (verTopo(pilha, &topo)) {
                        printf("O topo da pilha é: %d\n", topo);
                    } else {
                        printf("A pilha está vazia.\n");
                    }
                } else {
                    printf("A pilha não foi criada ainda.\n");
                }
                break;

            case 4:
                if (pilha != NULL) {
                    if (desempilhar(pilha)) {
                        printf("Elemento desempilhado com sucesso.\n");
                    } else {
                        printf("A pilha está vazia.\n");
                    }
                } else {
                    printf("A pilha não foi criada ainda.\n");
                }
                break;

            case 5:
                if (pilha != NULL) {
                    imprime(pilha);
                } else {
                    printf("A pilha não foi criada ainda.\n");
                }
                break;

            case 6:
                if (pilha != NULL) {
                    destroiPilha(pilha);
                    pilha = NULL;
                    printf("Pilha destruída com sucesso.\n");
                } else {
                    printf("A pilha não foi criada ainda.\n");
                }
                break;

            case 7:
                printf("Saindo do programa.\n");
                if (pilha != NULL) {
                    destroiPilha(pilha);
                }
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
