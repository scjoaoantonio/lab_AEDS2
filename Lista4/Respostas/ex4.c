#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct NO* Lista;

Lista criaLista() {
    Lista li;
    li = (Lista)malloc(sizeof(NO));
    if (li != NULL) {
        li->prox = li; // A lista aponta para ela mesma inicialmente
    }
    return li;
}

int listaVazia(Lista li) {
    if (li == NULL) return 1;
    if (li->prox == li) return 1; // True - Vazia!
    return 0; // False - tem elemento!
}

NO* alocarNO() {
    return (NO*)malloc(sizeof(NO));
}

void liberarNO(NO* q) {
    free(q);
}

int insereFim(Lista li, int elem) {
    if (li == NULL) return 0;
    NO* novo = alocarNO();
    if (novo == NULL) return 0;
    novo->info = elem;
    novo->prox = li->prox;
    li->prox = novo;
    return 1;
}

void imprimeLista(Lista li) {
    if (li == NULL) return;
    if (listaVazia(li)) {
        printf("Lista Vazia!\n");
        return;
    }
    printf("Elementos:\n");
    NO* aux = li->prox;
    do {
        printf("%d ", aux->info);
        aux = aux->prox;
    } while (aux != li->prox);
    printf("\n");
}

void destroiLista(Lista li) {
    if (li != NULL) {
        NO* aux = li->prox;
        while (aux != li) {
            NO* prox = aux->prox;
            liberarNO(aux);
            aux = prox;
        }
        free(li);
    }
}

// 4.1 Tamanho da lista
int tamanhoLista(Lista li) {
    if (li == NULL) return 0;
    if (listaVazia(li)) return 0;
    int tamanho = 0;
    NO* aux = li->prox;
    do {
        tamanho++;
        aux = aux->prox;
    } while (aux != li->prox);
    return tamanho;
}

// 4.2 Procura por um elemento na lista
int procura(Lista li, int x) {
    if (li == NULL || listaVazia(li)) return 0;
    NO* aux = li->prox;
    do {
        if (aux->info == x) return 1;
        aux = aux->prox;
    } while (aux != li->prox);
    return 0;
}

int main() {
    Lista L;
    L = criaLista();

    insereFim(L, 10);
    insereFim(L, 20);
    insereFim(L, 30);

    printf("Elementos da lista: ");
    imprimeLista(L);

    printf("Tamanho da lista: %d\n", tamanhoLista(L));

    int elemento = 20;
    if (procura(L, elemento)) {
        printf("Elemento %d encontrado na lista.\n", elemento);
    } else {
        printf("Elemento %d não encontrado na lista.\n", elemento);
    }

    destroiLista(L);

    return 0;
}
