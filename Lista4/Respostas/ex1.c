#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} ListaSequencialEstatica;

void inicializarLista(ListaSequencialEstatica *lista) {
    lista->size = 0;
}

// 1.2
int procura(ListaSequencialEstatica *lista, int x) {
    for (int i = 0; i < lista->size; i++) {
        if (lista->data[i] == x) {
            return i;
        }
    }
    return -1; // Elemento não encontrado
}

// 1.3
void insersao(ListaSequencialEstatica *lista, int x) {
    if (lista->size == MAX_SIZE) {
        printf("Erro: Lista está cheia.\n");
        return;
    }

    int i;
    for (i = 0; i < lista->size; i++) {
        if (x < lista->data[i]) {
            break;
        }
    }

    // Deslocar elementos maiores para a direita para abrir espaço para o novo elemento
    for (int j = lista->size; j > i; j--) {
        lista->data[j] = lista->data[j - 1];
    }

    // Inserir o novo elemento na posição correta
    lista->data[i] = x;
    lista->size++;
}

// 1.4
void removerElemento(ListaSequencialEstatica *lista, int x) {
    int indice = procura(lista, x);
    if (indice != -1) {
        // Deslocar elementos à esquerda para preencher o espaço do elemento removido
        for (int i = indice; i < lista->size - 1; i++) {
            lista->data[i] = lista->data[i + 1];
        }
        lista->size--;
    }
}

int main() {
    ListaSequencialEstatica lista;
    inicializarLista(&lista);

    insersao(&lista, 1);
    insersao(&lista, 2);
    insersao(&lista, 3);
    insersao(&lista, 4);

    printf("Elemento 1 encontrado no índice: %d\n", procura(&lista, 1));

    printf("Nova lista: ");
    for (int i = 0; i < lista.size; i++) {
        printf("%d ", lista.data[i]);
    }
    printf("\n");

    removerElemento(&lista, 1);
    printf("Nova lista após remoção: ");
    for (int i = 0; i < lista.size; i++) {
        printf("%d ", lista.data[i]);
    }
    printf("\n");

    return 0;
}
