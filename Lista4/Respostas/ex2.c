#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* proximo;
} Nodo;

typedef struct ListaEncadeada {
    Nodo* cabeca;
} ListaEncadeada;

// 2.1 Reimplementação do TAD de Lista Simplesmente Encadeada
void inicializarLista(ListaEncadeada* lista) {
    lista->cabeca = NULL;
}

void insercaoNoFinal(ListaEncadeada* lista, int valor) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    novoNodo->valor = valor;
    novoNodo->proximo = NULL;

    if (lista->cabeca == NULL) {
        lista->cabeca = novoNodo;
    } else {
        Nodo* atual = lista->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNodo;
    }
}

// 2.3 Inserção ordenada na lista
void insercaoOrdenada(ListaEncadeada* lista, int valor) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    novoNodo->valor = valor;
    novoNodo->proximo = NULL;

    if (lista->cabeca == NULL || valor < lista->cabeca->valor) {
        novoNodo->proximo = lista->cabeca;
        lista->cabeca = novoNodo;
    } else {
        Nodo* atual = lista->cabeca;
        while (atual->proximo != NULL && valor >= atual->proximo->valor) {
            atual = atual->proximo;
        }
        novoNodo->proximo = atual->proximo;
        atual->proximo = novoNodo;
    }
}

void imprimirLista(ListaEncadeada* lista) {
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// 2.2 Tamanho da lista
int tamanhoLista(ListaEncadeada* lista) {
    int tamanho = 0;
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

// 2.4 Remoção da primeira ocorrência de um elemento na lista
void removerElemento(ListaEncadeada* lista, int valor) {
    Nodo* atual = lista->cabeca;
    Nodo* anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            lista->cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    }
}

void liberarLista(ListaEncadeada* lista) {
    Nodo* atual = lista->cabeca;
    while (atual != NULL) {
        Nodo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
}

int main() {
    ListaEncadeada lista;
    inicializarLista(&lista);

    // 2.1 Inserção de 3 elementos a partir de uma lista vazia (no fim/no início)
    insercaoNoFinal(&lista, 1);
    insercaoNoFinal(&lista, 2);
    insercaoNoFinal(&lista, 3);

    printf("Elementos da lista: ");
    imprimirLista(&lista);

    // 2.2 Tamanho da lista
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));

    // 2.3 Inserção ordenada
    insercaoOrdenada(&lista, 0);
    insercaoOrdenada(&lista, 4);

    printf("Elementos da lista após inserção ordenada: ");
    imprimirLista(&lista);

    // 2.4 Remoção da primeira ocorrência de um elemento
    removerElemento(&lista, 2);

    printf("Elementos da lista após remoção do elemento 2: ");
    imprimirLista(&lista);

    // Liberar a lista
    liberarLista(&lista);

    return 0;
}
