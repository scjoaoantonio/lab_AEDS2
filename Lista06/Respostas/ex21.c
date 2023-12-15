#include <stdio.h>
#include <stdlib.h>

typedef struct ElementoPrioridade {
    int dado, prioridade;
    struct ElementoPrioridade* prox;
} ElementoPrioridade;

typedef struct ElementoPrioridade* FilaPrioridade;

ElementoPrioridade* alocarElemento() {
    return (ElementoPrioridade*)malloc(sizeof(ElementoPrioridade));
}

void liberarElemento(ElementoPrioridade* elemento) {
    free(elemento);
}

FilaPrioridade* criarFilaPrioridade() {
    FilaPrioridade* fp;
    fp = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (fp != NULL)
        *fp = NULL;
    return fp;
}

int estaVazia(FilaPrioridade* fp) {
    if (fp == NULL) return -1;
    return ((*fp) == NULL);
}

int enfileirar(FilaPrioridade* fp, int dado, int prioridade) {
    if (fp == NULL) return 0;
    ElementoPrioridade* novo_elemento = alocarElemento();
    if (novo_elemento == NULL) return 0;

    novo_elemento->dado = dado;
    novo_elemento->prioridade = prioridade;

    if (estaVazia(fp)) {
        novo_elemento->prox = *fp;
        *fp = novo_elemento;
    }
    else {
        ElementoPrioridade* atual, *anterior;
        anterior = NULL;
        atual = *fp; // Início
        while (atual != NULL && atual->prioridade >= novo_elemento->prioridade) {
            anterior = atual;
            atual = atual->prox;
        }
        if (anterior == NULL) {
            novo_elemento->prox = *fp;
            *fp = novo_elemento;
        }
        else {
            novo_elemento->prox = anterior->prox;
            anterior->prox = novo_elemento;
        }
    }
    return 1;
}

int desenfileirar(FilaPrioridade* fp) {
    if (fp == NULL) return 0;
    if (estaVazia(fp)) return 0;
    ElementoPrioridade* aux = *fp;
    *fp = aux->prox;
    liberarElemento(aux);
    return 1;
}

int frente(FilaPrioridade* fp, int* dado) {
    if (fp == NULL) return 0;
    if (estaVazia(fp)) return 0;
    *dado = (*fp)->dado;
    return 1;
}

int tamanhoFila(FilaPrioridade* fp) {
    if (fp == NULL) return -1;
    int tamanho = 0;
    ElementoPrioridade* atual = *fp;
    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }
    return tamanho;
}

void imprimirFila(FilaPrioridade* fp) {
    if (fp == NULL) return;
    if (estaVazia(fp)) {
        printf("Fila está vazia!\n");
        return;
    }
    ElementoPrioridade* atual = *fp;
    while (atual != NULL) {
        printf("[%d, %d] ", atual->prioridade, atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

void destruirFila(FilaPrioridade* fp) {
    if (fp != NULL) {
        ElementoPrioridade* aux;
        while ((*fp) != NULL) {
            aux = *fp;
            *fp = (*fp)->prox;
            liberarElemento(aux);
        }
        free(fp);
    }
}

int main() {
    FilaPrioridade* fp;
    int opcao, dado;

    fp = criarFilaPrioridade();

    do {
        printf("\nMenu:\n");
        printf("1 - Criar Fila\n");
        printf("2 - Enfileirar um item com prioridade\n");
        printf("3 - Obter o início da Fila\n");
        printf("4 - Desenfileirar um item\n");
        printf("5 - Imprimir a Fila\n");
        printf("6 - Mostrar o tamanho da Fila\n");
        printf("7 - Destruir a Fila\n");
        printf("8 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (fp != NULL)
                destruirFila(fp);
            fp = criarFilaPrioridade();
            printf("Fila criada.\n");
            break;
        case 2:
            printf("Informe o elemento a enfileirar: ");
            scanf("%d", &dado);
            int prioridade;
            printf("Informe a prioridade deste elemento: ");
            scanf("%d", &prioridade);
            enfileirar(fp, dado, prioridade);
            break;
        case 3:
            if (frente(fp, &dado))
                printf("Início da Fila: %d\n", dado);
            else
                printf("Fila está vazia.\n");
            break;
        case 4:
            if (desenfileirar(fp))
                printf("Item desenfileirado.\n");
            else
                printf("Fila está vazia.\n");
            break;
        case 5:
            imprimirFila(fp);
            break;
        case 6:
            printf("Tamanho da Fila: %d\n", tamanhoFila(fp));
            break;
        case 7:
            destruirFila(fp);
            printf("Fila destruída.\n");
            break;
        case 8:
            if (fp != NULL) {
                destruirFila(fp);
            }
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 8);

    return 0;
}
