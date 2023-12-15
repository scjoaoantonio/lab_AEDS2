#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Funcionario {
    char nome[50];
    double salario;
    int anoContratacao;
} Funcionario;

typedef struct NO {
    Funcionario info;
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
    if (no == NULL)
        return;
    destroiRec(no->esq);
    destroiRec(no->dir);
    liberarNO(no);
}

void destroiABP(ABP* raiz) {
    if (raiz != NULL) {
        destroiRec(*raiz);
        free(raiz);
    }
}

int estaVazia(ABP* raiz) {
    if (raiz == NULL)
        return 1;
    return (*raiz == NULL);
}

NO* insereRec(NO* no, Funcionario func) {
    if (no == NULL) {
        NO* novo = alocarNO();
        if (novo == NULL)
            return NULL;
        novo->info = func;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (func.salario < no->info.salario)
        no->esq = insereRec(no->esq, func);
    else if (func.salario > no->info.salario)
        no->dir = insereRec(no->dir, func);

    return no;
}

void insereElem(ABP* raiz, Funcionario func) {
    if (raiz == NULL)
        return;
    *raiz = insereRec(*raiz, func);
}

NO* buscaFuncionario(NO* raiz, double salario) {
    if (raiz == NULL || raiz->info.salario == salario)
        return raiz;

    if (salario < raiz->info.salario)
        return buscaFuncionario(raiz->esq, salario);

    return buscaFuncionario(raiz->dir, salario);
}

void buscaFuncionarioPrint(NO* raiz, double salario) {
    NO* resultado = buscaFuncionario(raiz, salario);
    if (resultado != NULL) {
        printf("Nome: %s\n", resultado->info.nome);
        printf("Salario: %.2f\n", resultado->info.salario);
        printf("Ano de Contratacao: %d\n", resultado->info.anoContratacao);
    } else {
        printf("Funcionario nao encontrado.\n");
    }
}

NO* removeRec(NO* raiz, double salario) {
    if (raiz == NULL)
        return raiz;

    if (salario < raiz->info.salario)
        raiz->esq = removeRec(raiz->esq, salario);
    else if (salario > raiz->info.salario)
        raiz->dir = removeRec(raiz->dir, salario);
    else {
        if (raiz->esq == NULL) {
            NO* temp = raiz->dir;
            liberarNO(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NO* temp = raiz->esq;
            liberarNO(raiz);
            return temp;
        }

        NO* temp = raiz->dir;
        while (temp->esq != NULL)
            temp = temp->esq;

        raiz->info = temp->info;
        raiz->dir = removeRec(raiz->dir, temp->info.salario);
    }

    return raiz;
}

void removeElem(ABP* raiz, double salario) {
    if (raiz == NULL || *raiz == NULL)
        return;
    *raiz = removeRec(*raiz, salario);
}

void em_ordem(NO* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("Nome: %s, Salario: %.2f, Ano de Contratacao: %d\n", raiz->info.nome, raiz->info.salario, raiz->info.anoContratacao);
        em_ordem(raiz->dir);
    }
}

void imprime(ABP* raiz) {
    if (raiz == NULL)
        return;
    if (estaVazia(raiz)) {
        printf("Arvore Vazia!\n");
        return;
    }
    printf("\nEm Ordem:\n");
    em_ordem(*raiz);
    printf("\n");
}

int main() {
    ABP* A;
    A = criaABP();
    int opcao;
    double salario;
    Funcionario func;

    do {
        printf("\nMenu:\n");
        printf("1 - Inserir Funcionario\n");
        printf("2 - Buscar Funcionario por Salario\n");
        printf("3 - Remover Funcionario por Salario\n");
        printf("4 - Imprimir Arvore em Ordem\n");
        printf("5 - Sair\n");
        printf("Escolha a opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome: ");
                scanf("%s", func.nome);
                printf("Salario: ");
                scanf("%lf", &func.salario);
                printf("Ano de Contratacao: ");
                scanf("%d", &func.anoContratacao);
                insereElem(A, func);
                break;

            case 2:
                printf("Digite o salario para buscar: ");
                scanf("%lf", &salario);
                buscaFuncionarioPrint(*A, salario);
                break;

            case 3:
                printf("Digite o salario para remover: ");
                scanf("%lf", &salario);
                removeElem(A, salario);
                break;

            case 4:
                imprime(A);
                break;

            case 5:
                destroiABP(A);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}
