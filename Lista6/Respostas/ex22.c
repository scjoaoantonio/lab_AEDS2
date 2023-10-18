#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct ElementoPrioridade {
    int dado, prioridade;
} ElementoPrioridade;

typedef struct {
    int tamanho;
    ElementoPrioridade elementos[MAX];
} FilaPrioridade;

FilaPrioridade* criarFilaPrioridade() {
    FilaPrioridade* fp;
    fp = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (fp != NULL)
        fp->tamanho = 0;
    return fp;
}

void destruirFilaPrioridade(FilaPrioridade* fp) {
    if (fp != NULL)
        free(fp);
}

int tamanhoFila(FilaPrioridade* fp) {
    if (fp == NULL) return -1;
    return fp->tamanho;
}

int estaCheia(FilaPrioridade* fp) {
    if (fp == NULL) return -1;
    return (fp->tamanho == MAX);
}

int estaVazia(FilaPrioridade* fp) {
    if (fp == NULL) return -1;
    return (fp->tamanho == 0);
}

void trocarElementos(ElementoPrioridade* a, ElementoPrioridade* b) {
    ElementoPrioridade temp;
    temp.dado = a->dado;
    temp.prioridade = a->prioridade;
    a->dado = b->dado;
    a->prioridade = b->prioridade;
    b->dado = temp.dado;
    b->prioridade = temp.prioridade;
}

void ajustarHeapInserir(FilaPrioridade* fp, int filho) {
    int pai = (filho - 1) / 2;
    int prioridadePai = fp->elementos[pai].prioridade;
    int prioridadeFilho = fp->elementos[filho].prioridade;
    while (filho > 0 && prioridadePai < prioridadeFilho) {
        trocarElementos(&fp->elementos[filho], &fp->elementos[pai]);
        filho = pai;
        pai = (pai - 1) / 2;
        prioridadePai = fp->elementos[pai].prioridade;
        prioridadeFilho = fp->elementos[filho].prioridade;
    }
}

int enfileirar(FilaPrioridade* fp, int dado, int prioridade) {
    if (fp == NULL) return 0;
    if (estaCheia(fp)) return 0;
    fp->elementos[fp->tamanho].dado = dado;
    fp->elementos[fp->tamanho].prioridade = prioridade;
    ajustarHeapInserir(fp, fp->tamanho);
    fp->tamanho++;
    return 1;
}

void ajustarHeapRemover(FilaPrioridade* fp, int pai) {
    int filho = 2 * pai + 1;
    while (filho < fp->tamanho) {
        if (filho < fp->tamanho - 1 && fp->elementos[filho].prioridade < fp->elementos[filho + 1].prioridade)
            filho++;
        if (fp->elementos[pai].prioridade > fp->elementos[filho].prioridade)
            break;
        trocarElementos(&fp->elementos[pai], &fp->elementos[filho]);
        pai = filho;
        filho = 2 * pai + 1;
    }
}

int desenfileirar(FilaPrioridade* fp) {
    if (fp == NULL) return 0;
    if (estaVazia(fp)) return 0;
    fp->tamanho--;
    fp->elementos[0].dado = fp->elementos[fp->tamanho].dado;
    fp->elementos[0].prioridade = fp->elementos[fp->tamanho].prioridade;
    ajustarHeapRemover(fp, 0);
    return 1;
}

int frente(FilaPrioridade* fp, int* dado, int* prioridade) {
    if (fp == NULL) return 0;
    if (estaVazia(fp)) return 0;
    *dado = fp->elementos[0].dado;
    *prioridade = fp->elementos[0].prioridade;
    return 1;
}

void imprimirFila(FilaPrioridade* fp) {
    if (fp == NULL) return;
    if (estaVazia(fp)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Elementos:\n");
    for (int i = 0; i < fp->tamanho; i++) {
        printf("[%d, %d] (%d) -- ", fp->elementos[i].prioridade, fp->elementos[i].dado, i);
    }
    printf("\n");
}

int main() {
    FilaPrioridade* fp;
    int opcao, dado, prioridade;

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
                destruirFilaPrioridade(fp);
            fp = criarFilaPrioridade();
            printf("Fila criada.\n");
            break;
        case 2:
            printf("Informe o elemento a enfileirar: ");
            scanf("%d", &dado);
            printf("Informe a prioridade deste elemento: ");
            scanf("%d", &prioridade);
            enfileirar(fp, dado, prioridade);
            break;
        case 3:
            if (frente(fp, &dado, &prioridade))
                printf("Início da Fila: [%d, %d]\n", prioridade, dado);
            else
                printf("Fila vazia.\n");
            break;
        case 4:
            if (desenfileirar(fp))
                printf("Item desenfileirado.\n");
            else
                printf("Fila vazia.\n");
            break;
        case 5:
            imprimirFila(fp);
            break;
        case 6:
            printf("Tamanho da Fila: %d\n", tamanhoFila(fp));
            break;
        case 7:
            destruirFilaPrioridade(fp);
            printf("Fila destruída.\n");
            break;
        case 8:
            if (fp != NULL) {
                destruirFilaPrioridade(fp);
            }
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 8);

    return 0;
}
