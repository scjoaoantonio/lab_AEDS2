#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* esq;
    struct NO* dir;
} NO;

typedef struct NO* ABP;

NO* alocarNO() {
    return (NO*)malloc(sizeof(NO));
}

void liberarNO(NO* q) {
    free(q);
}

ABP* criaABP() {
    ABP* raiz = (ABP*)malloc(sizeof(ABP));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void destroiRec(NO* no) {
    if (no == NULL) return;
    destroiRec(no->esq);
    destroiRec(no->dir);
    liberarNO(no);
    no = NULL;
}

void destroiABP(ABP* raiz) {
    if (raiz != NULL) {
        destroiRec(*raiz);
        free(raiz);
    }
}

int estaVazia(ABP* raiz) {
    if (raiz == NULL) return 1;
    return (*raiz == NULL);
}

int contaNosRec(NO* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contaNosRec(raiz->esq) + contaNosRec(raiz->dir);
}

int contaNos(ABP* raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return contaNosRec(*raiz);
}

int insereRec(NO** raiz, int elem) {
    if (*raiz == NULL) {
        NO* novo = alocarNO();
        if (novo == NULL) return 0;
        novo->info = elem;
        novo->esq = NULL; novo->dir = NULL;
        *raiz = novo;
    } else {
        if ((*raiz)->info == elem) {
            printf("Elemento Existente!\n");
            return 0;
        }
        if (elem < (*raiz)->info)
            return insereRec(&(*raiz)->esq, elem);
        else if (elem > (*raiz)->info)
            return insereRec(&(*raiz)->dir, elem);
    }
    return 1;
}

int insereIte(NO** raiz, int elem) {
    NO* aux = *raiz, *ant = NULL;
    while (aux != NULL) {
        ant = aux;
        if (aux->info == elem) {
            printf("Elemento Existente!\n");
            return 0;
        }
        if (elem < aux->info) aux = aux->esq;
        else aux = aux->dir;
    }
    NO* novo = alocarNO();
    if (novo == NULL) return 0;
    novo->info = elem;
    novo->esq = NULL; novo->dir = NULL;
    if (ant == NULL) {
        *raiz = novo;
    } else {
        if (elem < ant->info) ant->esq = novo;
        else ant->dir = novo;
    }
    return 1;
}

int insereElem(ABP* raiz, int elem) {
    if (raiz == NULL) return 0;
    return insereRec(raiz, elem);
    //return insereIte(raiz, elem);
}

int pesquisaRec(NO** raiz, int elem) {
    if (*raiz == NULL) return 0;
    if ((*raiz)->info == elem) return 1;
    if (elem < (*raiz)->info)
        return pesquisaRec(&(*raiz)->esq, elem);
    else
        return pesquisaRec(&(*raiz)->dir, elem);
}

int pesquisaIte(NO** raiz, int elem) {
    NO* aux = *raiz;
    while (aux != NULL) {
        if (aux->info == elem) return 1;
        if (elem < aux->info)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    return 0;
}

int pesquisa(ABP* raiz, int elem) {
    if (raiz == NULL) return 0;
    if (estaVazia(raiz)) return 0;
    return pesquisaRec(raiz, elem);
    //return pesquisaIte(raiz, elem);
}

NO* removeAtual(NO* atual) {
    NO* no1, *no2;
    // Ambos casos no if(atual->esq == NULL)
    // Caso 1 - NO sem filhos
    // Caso 2.1 - Possui apenas uma subárvore direita
    if (atual->esq == NULL) {
        no2 = atual->dir;
        liberarNO(atual);
        return no2;
    }
    // Caso 3 - Possui as duas subárvores (esq e dir)
    // Estratégia:

    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    liberarNO(atual);
    return no2;
}

int removeIte(NO** raiz, int elem) {
    if (*raiz == NULL) return 0;
    NO* atual = *raiz, *ant = NULL;
    while (atual != NULL) {
        if (elem == atual->info) {
            if (atual == *raiz)
                *raiz = removeAtual(atual);
            else {
                if (ant->dir == atual)
                    ant->dir = removeAtual(atual);
                else
                    ant->esq = removeAtual(atual);
            }
            return 1;
        }
        ant = atual;
        if (elem < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}

int removeElem(ABP* raiz, int elem) {
    if (pesquisa(raiz, elem) == 0) {
        printf("Elemento inexistente!\n");
        return 0;
    }
    //return removeRec(raiz, elem);
    return removeIte(raiz, elem);
}

void em_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        em_ordem(raiz->esq, nivel + 1);
        printf("[%d, %d] ", raiz->info, nivel);
        em_ordem(raiz->dir, nivel + 1);
    }
}

void pre_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        printf("[%d, %d] ", raiz->info, nivel);
        pre_ordem(raiz->esq, nivel + 1);
        pre_ordem(raiz->dir, nivel + 1);
    }
}

void pos_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq, nivel + 1);
        pos_ordem(raiz->dir, nivel + 1);
        printf("[%d, %d] ", raiz->info, nivel);
    }
}

void imprime(ABP* raiz) {
    if (raiz == NULL) return;
    if (estaVazia(raiz)) {
        printf("Arvore Vazia!\n");
        return;
    }
    printf("\nEm Ordem: "); em_ordem(*raiz, 0);
    printf("\nPre Ordem: "); pre_ordem(*raiz, 0);
    printf("\nPos Ordem: "); pos_ordem(*raiz, 0);
    printf("\n");
}

int main() {
    ABP* A;
    A = criaABP();

    int opcao, elemento;
    do {
        printf("\nMenu:\n");
        printf("1 - Criar ABP\n");
        printf("2 - Inserir numero\n");
        printf("3 - Buscar numero\n");
        printf("4 - Remover numero\n");
        printf("5 - Imprimir a ABP em ordem\n");
        printf("6 - Imprimir a ABP em pré-ordem\n");
        printf("7 - Imprimir a ABP em pós-ordem\n");
        printf("8 - Mostrar a quantidade de nós na ABP\n");
        printf("9 - Destruir a ABP\n");
        printf("10 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            destroiABP(A);
            A = criaABP();
            printf("ABP criada.\n");
            break;
        case 2:
            printf("Digite o elemento a ser inserido: ");
            scanf("%d", &elemento);
            insereElem(A, elemento);
            break;
        case 3:
            printf("Digite o elemento a ser buscado: ");
            scanf("%d", &elemento);
            if (pesquisa(A, elemento)) {
                printf("Elemento encontrado na ABP.\n");
            } else {
                printf("Elemento não encontrado na ABP.\n");
            }
            break;
        case 4:
            printf("Digite o elemento a ser removido: ");
            scanf("%d", &elemento);
            if (removeElem(A, elemento)) {
                printf("Elemento removido da ABP.\n");
            } else {
                printf("Elemento não encontrado na ABP ou erro na remoção.\n");
            }
            break;
        case 5:
            printf("Árvore em ordem:\n");
            imprime(A);
            break;
        case 6:
            printf("Árvore em pré-ordem:\n");
            pre_ordem(*A, 0);
            printf("\n");
            break;
        case 7:
            printf("Árvore em pós-ordem:\n");
            pos_ordem(*A, 0);
            printf("\n");
            break;
        case 8:
            printf("Quantidade de nós na ABP: %d\n", contaNos(A));
            break;
        case 9:
            destroiABP(A);
            printf("ABP destruída.\n");
            break;
        case 10:
            destroiABP(A);
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 10);

    return 0;
}
