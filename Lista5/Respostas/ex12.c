#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    NO* ini;
    NO* fim;
} Fila;

Fila* criaFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->qtd = 0;
        fila->ini = fila->fim = NULL;
    }
    return fila;
}

void destroiFila(Fila* fila) {
    if (fila != NULL) {
        while (fila->ini != NULL) {
            NO* aux = fila->ini;
            fila->ini = fila->ini->prox;
            free(aux);
        }
        free(fila);
    }
}

int estaVazia(Fila* fila) {
    return (fila == NULL || fila->qtd == 0);
}

int tamanhoFila(Fila* fila) {
    if (fila == NULL) {
        return -1;
    }
    return fila->qtd;
}

int enfileirar(Fila* fila, int elemento) {
    if (fila == NULL) {
        return 0;
    }
    NO* novo = (NO*)malloc(sizeof(NO));
    if (novo == NULL) {
        return 0;
    }
    novo->info = elemento;
    novo->prox = NULL;
    if (fila->fim == NULL) {
        fila->ini = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->qtd++;
    return 1;
}

int desenfileirar(Fila* fila) {
    if (fila == NULL || fila->ini == NULL) {
        return 0;
    }
    NO* aux = fila->ini;
    fila->ini = fila->ini->prox;
    free(aux);
    fila->qtd--;
    if (fila->ini == NULL) {
        fila->fim = NULL;
    }
    return 1;
}

int verInicio(Fila* fila, int* p) {
    if (fila == NULL || fila->ini == NULL) {
        return 0;
    }
    *p = fila->ini->info;
    return 1;
}

void imprime(Fila* fila) {
    if (fila == NULL || fila->qtd == 0) {
        printf("Fila Vazia!\n");
        return;
    }
    NO* atual = fila->ini;
    printf("Elementos: \n");
    while (atual != NULL) {
        printf("%d ", atual->info);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    Fila* fila = NULL;
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
