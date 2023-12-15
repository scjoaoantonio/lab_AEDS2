#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    NO* topo;
} Pilha;

Pilha* criaPilha() {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha != NULL) {
        pilha->qtd = 0;
        pilha->topo = NULL;
    }
    return pilha;
}

void destroiPilha(Pilha* pilha) {
    if (pilha != NULL) {
        while (pilha->topo != NULL) {
            NO* aux = pilha->topo;
            pilha->topo = pilha->topo->prox;
            free(aux);
        }
        free(pilha);
    }
}

int estaVazia(Pilha* pilha) {
    return (pilha == NULL || pilha->qtd == 0);
}

int tamanhoPilha(Pilha* pilha) {
    if (pilha == NULL) {
        return -1;
    }
    return pilha->qtd;
}

int empilhar(Pilha* pilha, int elemento) {
    if (pilha == NULL) {
        return 0;
    }
    NO* novo = (NO*)malloc(sizeof(NO));
    if (novo == NULL) {
        return 0;
    }
    novo->info = elemento;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->qtd++;
    return 1;
}

int desempilhar(Pilha* pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }
    NO* aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    pilha->qtd--;
    return 1;
}

int verTopo(Pilha* pilha, int* p) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }
    *p = pilha->topo->info;
    return 1;
}

void imprime(Pilha* pilha) {
    if (pilha == NULL || pilha->qtd == 0) {
        printf("Pilha Vazia!\n");
        return;
    }
    NO* atual = pilha->topo;
    printf("Elementos: \n");
    while (atual != NULL) {
        printf("%d ", atual->info);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    Pilha* pilha = NULL;
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
