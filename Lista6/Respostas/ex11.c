#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int qtd, ini, fim;
    int dados[MAX];
} Deque;

Deque *criarDeque() {
    Deque *deque;
    deque = (Deque *)malloc(sizeof(Deque));
    if (deque != NULL) {
        deque->qtd = deque->ini = deque->fim = 0;
    }
    return deque;
}

void destruirDeque(Deque *deque) {
    if (deque != NULL)
        free(deque);
}

int tamanhoDoDeque(Deque *deque) {
    if (deque == NULL)
        return -1;
    return deque->qtd;
}

int estaCheio(Deque *deque) {
    if (deque == NULL)
        return -1;
    return (deque->qtd == MAX);
}

int estaVazio(Deque *deque) {
    if (deque == NULL)
        return -1;
    return (deque->qtd == 0);
}

int inserirNoInicio(Deque *deque, int elem) {
    if (deque == NULL)
        return 0;
    if (estaCheio(deque))
        return 0;
    deque->ini = (deque->ini - 1 < 0 ? MAX - 1 : deque->ini - 1);
    deque->dados[deque->ini] = elem;
    deque->qtd++;
    return 1;
}

int inserirNoFim(Deque *deque, int elem) {
    if (deque == NULL)
        return 0;
    if (estaCheio(deque))
        return 0;
    deque->dados[deque->fim] = elem;
    deque->fim = (deque->fim + 1) % MAX;
    deque->qtd++;
    return 1;
}

int removerDoInicio(Deque *deque) {
    if (deque == NULL)
        return 0;
    if (estaVazio(deque))
        return 0;
    deque->ini = (deque->ini + 1) % MAX;
    deque->qtd--;
    return 1;
}

int removerDoFim(Deque *deque) {
    if (deque == NULL)
        return 0;
    if (estaVazio(deque))
        return 0;
    deque->fim = (deque->fim - 1 < 0 ? MAX - 1 : deque->fim - 1);
    deque->qtd--;
    return 1;
}

int obterInicio(Deque *deque, int *elem) {
    if (deque == NULL)
        return 0;
    if (estaVazio(deque))
        return 0;
    *elem = deque->dados[deque->ini];
    return 1;
}

int obterFim(Deque *deque, int *elem) {
    if (deque == NULL)
        return 0;
    if (estaVazio(deque))
        return 0;
    int i = (deque->fim - 1 < 0 ? MAX - 1 : deque->fim - 1);
    *elem = deque->dados[i];
    return 1;
}

void imprimirDeque(Deque *deque) {
    if (deque == NULL)
        return;
    if (estaVazio(deque)) {
        printf("Deque Vazio!\n");
        return;
    }
    int i = deque->ini;
    printf("Elementos: \n");
    do {
        printf("%d ", deque->dados[i]);
        i = (i + 1) % MAX;
    } while (i != deque->fim);
    printf("\n");
}

int main() {
    Deque *deque;
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