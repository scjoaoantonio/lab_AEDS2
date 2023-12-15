#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* proximo;
    struct Nodo* anterior;
} Nodo;

typedef struct ListaDuplamenteEncadeada {
    Nodo* cabeca;
    Nodo* cauda;
} ListaDuplamenteEncadeada;

// 3.1 Reimplementação do TAD de Lista Duplamente Encadeada
void inicializarLista(ListaDuplamenteEncadeada* lista) {
    lista->cabeca = NULL;
    lista->cauda = NULL;
}

void insercaoNoFinal(ListaDuplamenteEncadeada* lista, int valor) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    novoNodo->valor = valor;
    novoNodo->proximo = NULL;
    novoNodo->anterior = lista->cauda;

    if (lista->cabeca == NULL) {
        lista->cabeca = novoNodo;
    } else {
        lista->cauda->proximo = novoNodo;
    }

    lista->cauda = novoNodo;
}

void imprimirLista(ListaDuplamenteEncadeada* lista) {
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// 3.2 Tamanho da lista
int tamanhoLista(ListaDuplamenteEncadeada* lista) {
    int tamanho = 0;
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

// 3.3 Inserção ordenada na lista
void insercaoOrdenada(ListaDuplamenteEncadeada* lista, int valor) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    novoNodo->valor = valor;
    novoNodo->proximo = NULL;
    novoNodo->anterior = NULL;

    Nodo* atual = lista->cabeca;
    Nodo* anterior = NULL;

    while (atual != NULL && valor >= atual->valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) {
        novoNodo->proximo = lista->cabeca;
        lista->cabeca->anterior = novoNodo;
        lista->cabeca = novoNodo;
    } else {
        novoNodo->proximo = atual;
        novoNodo->anterior = anterior;
        anterior->proximo = novoNodo;

        if (atual != NULL) {
            atual->anterior = novoNodo;
        }
    }
}

// 3.4 Remoção da primeira ocorrência de um elemento
void removerElemento(ListaDuplamenteEncadeada* lista, int valor) {
    Nodo* atual = lista->cabeca;
    while (atual != NULL && atual->valor != valor) {
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (atual == lista->cabeca) {
            lista->cabeca = atual->proximo;
            if (lista->cabeca != NULL) {
                lista->cabeca->anterior = NULL;
            }
        } else {
            atual->anterior->proximo = atual->proximo;
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
        }

        free(atual);
    }
}

void liberarLista(ListaDuplamenteEncadeada* lista) {
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        Nodo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
    lista->cauda = NULL;
}

int main() {
    ListaDuplamenteEncadeada lista;
    inicializarLista(&lista);

    // 3.1 Inserção de 3 elementos a partir de uma lista vazia (no fim/no início)
    insercaoNoFinal(&lista, 1);
    insercaoNoFinal(&lista, 2);
    insercaoNoFinal(&lista, 3);

    printf("Elementos da lista (esquerda para a direita): ");
    imprimirLista(&lista);

    // 3.2 Tamanho da lista
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));

    // 3.3 Inserção ordenada
    insercaoOrdenada(&lista, 0);
    insercaoOrdenada(&lista, 4);

    printf("Elementos da lista após inserção ordenada: ");
    imprimirLista(&lista);

    // 3.4 Remoção da primeira ocorrência de um elemento
    removerElemento(&lista, 2);

    printf("Elementos da lista após remoção do elemento 2: ");
    imprimirLista(&lista);

    liberarLista(&lista);

    return 0;
}
