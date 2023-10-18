#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
    struct NO* ant;
} NO;

typedef struct {
    int qtd;
    struct NO* ini;
    struct NO* fim;
} Deque;

NO* alocarNO() {
    return (NO*)malloc(sizeof(NO));
}

void liberarNO(NO* q) {
    free(q);
}

Deque* criarDeque() {
    Deque* dq;
    dq = (Deque*)malloc(sizeof(Deque));
    if (dq != NULL) {
        dq->qtd = 0;
        dq->ini = NULL;
        dq->fim = NULL;
    }
    return dq;
}

void destruirDeque(Deque* dq) {
    if (dq != NULL) {
        NO* aux;
        while (dq->ini != NULL) {
            aux = dq->ini;
            dq->ini = dq->ini->prox;
            liberarNO(aux);
        }
        free(dq);
    }
}

int tamanhoDeque(Deque* dq) {
    if (dq == NULL)
        return -1;
    return dq->qtd;
}

int estaVazio(Deque* dq) {
    if (dq == NULL)
        return -1;
    return (dq->qtd == 0);
}

int inserirNoInicio(Deque* dq, int elem) {
    if (dq == NULL) return 0;
    NO* novo = alocarNO();
    if (novo == NULL) return 0;
    novo->info = elem;
    novo->ant = NULL;
    if (estaVazio(dq)) {
        novo->prox = NULL;
        dq->fim = novo;
    }
    else {
        dq->ini->ant = novo;
        novo->prox = dq->ini;
    }
    dq->ini = novo;
    dq->qtd++;
    return 1;
}

int inserirNoFim(Deque* dq, int elem) {
    if (dq == NULL) return 0;
    NO* novo = alocarNO();
    if (novo == NULL) return 0;
    novo->info = elem;
    novo->prox = NULL;
    if (estaVazio(dq)) {
        novo->ant = NULL;
        dq->ini = novo;
    }
    else {
        dq->fim->prox = novo;
        novo->ant = dq->fim;
    }
    dq->fim = novo;
    dq->qtd++;
    return 1;
}

int removerDoInicio(Deque* dq) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    NO* aux = dq->ini;
    if (dq->ini == dq->fim) {
        dq->ini = dq->fim = NULL;
    }
    else {
        dq->ini = dq->ini->prox;
        dq->ini->ant = NULL;
    }
    liberarNO(aux);
    dq->qtd--;
    return 1;
}

int removerDoFim(Deque* dq) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    NO* aux = dq->fim;
    if (dq->ini == dq->fim) {
        dq->ini = dq->fim = NULL;
    }
    else {
        dq->fim = dq->fim->ant;
        dq->fim->prox = NULL;
    }
    liberarNO(aux);
    dq->qtd--;
    return 1;
}

int obterInicio(Deque* dq, int* elem) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    *elem = dq->ini->info;
    return 1;
}

int obterFim(Deque* dq, int* elem) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    *elem = dq->fim->info;
    return 1;
}

void imprimirDeque(Deque* dq) {
    if (dq == NULL) return;
    if (estaVazio(dq)) {
        printf("Deque Vazio!\n");
        return;
    }
    NO* aux = dq->ini;
    printf("Elementos:\n");
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    Deque* deque;
    int opcao, elem;

    deque = criarDeque();

    do {
        printf("\nMenu:\n");
        printf("1 - Criar Deque\n");
        printf("2 - Inserir um item no fim\n");
        printf("3 - Inserir um item no início\n");
        printf("4 - Ver o início do Deque\n");
        printf("5 - Ver o fim do Deque\n");
        printf("6 - Remover um item do fim\n");
        printf("7 - Remover um item do início\n");
        printf("8 - Imprimir o Deque\n");
        printf("9 - Destruir o Deque\n");
        printf("10 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (deque != NULL)
                destruirDeque(deque);
            deque = criarDeque();
            printf("Deque criado.\n");
            break;
        case 2:
            printf("Digite o elemento a ser inserido no fim: ");
            scanf("%d", &elem);
            inserirNoFim(deque, elem);
            break;
        case 3:
            printf("Digite o elemento a ser inserido no início: ");
            scanf("%d", &elem);
            inserirNoInicio(deque, elem);
            break;
        case 4:
            if (obterInicio(deque, &elem))
                printf("Início do Deque: %d\n", elem);
            else
                printf("Deque vazio.\n");
            break;
        case 5:
            if (obterFim(deque, &elem))
                printf("Fim do Deque: %d\n", elem);
            else
                printf("Deque vazio.\n");
            break;
        case 6:
            if (removerDoFim(deque))
                printf("Item removido do fim.\n");
            else
                printf("Deque vazio.\n");
            break;
        case 7:
            if (removerDoInicio(deque))
                printf("Item removido do início.\n");
            else
                printf("Deque vazio.\n");
            break;
        case 8:
            imprimirDeque(deque);
            break;
        case 9:
            if (deque != NULL) {
                destruirDeque(deque);
                printf("Deque destruído.\n");
            }
            break;
        case 10:
            if (deque != NULL) {
                destruirDeque(deque);
            }
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 10);

    return 0;
}
