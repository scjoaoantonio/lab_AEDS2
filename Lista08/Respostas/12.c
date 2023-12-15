#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    char nome[100];
    int matricula;
    double nota;
} Aluno;

typedef struct NO {
    Aluno info;
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

int comparaAlunos(Aluno aluno1, Aluno aluno2) {
    return strcmp(aluno1.nome, aluno2.nome);
}

int insereRec(NO** raiz, Aluno aluno) {
    if (*raiz == NULL) {
        NO* novo = alocarNO();
        if (novo == NULL) return 0;
        novo->info = aluno;
        novo->esq = NULL; novo->dir = NULL;
        *raiz = novo;
    }
    else {
        int comp = comparaAlunos(aluno, (*raiz)->info);
        if (comp == 0) {
            printf("Aluno já existe!\n");
            return 0;
        }
        if (comp < 0)
            return insereRec(&(*raiz)->esq, aluno);
        else
            return insereRec(&(*raiz)->dir, aluno);
    }
    return 1;
}

int insereElem(ABP* raiz, char nome[], int matricula, double nota) {
    if (raiz == NULL) return 0;

    Aluno novoAluno;
    strcpy(novoAluno.nome, nome);
    novoAluno.matricula = matricula;
    novoAluno.nota = nota;

    return insereRec(raiz, novoAluno);
}

Aluno buscaRec(NO* raiz, char nome[]) {
    Aluno alunoNulo;
    alunoNulo.matricula = -1;
    if (raiz == NULL) return alunoNulo;
    int comp = strcmp(raiz->info.nome, nome);
    if (comp == 0)
        return raiz->info;
    if (comp < 0)
        return buscaRec(raiz->esq, nome);
    else
        return buscaRec(raiz->dir, nome);
}

Aluno buscaAluno(ABP* raiz, char nome[]) {
    Aluno alunoNulo;
    alunoNulo.matricula = -1;
    if (raiz == NULL) return alunoNulo;
    return buscaRec(*raiz, nome);
}

int removeRec(NO** raiz, char nome[]) {
    if (*raiz == NULL) return 0;
    int comp = strcmp(nome, (*raiz)->info.nome);
    if (comp == 0) {
        NO* aux;
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            liberarNO(*raiz);
            *raiz = NULL;
        }
        else if ((*raiz)->esq == NULL) {
            aux = *raiz;
            *raiz = (*raiz)->dir;
            liberarNO(aux);
        }
        else if ((*raiz)->dir == NULL) {
            aux = *raiz;
            *raiz = (*raiz)->esq;
            liberarNO(aux);
        }
        else {
            NO* filho = (*raiz)->esq;
            while (filho->dir != NULL)
                filho = filho->dir;
            (*raiz)->info = filho->info;
            return removeRec(&(*raiz)->esq, nome);
        }
        return 1;
    }
    else if (comp < 0)
        return removeRec(&(*raiz)->esq, nome);
    else
        return removeRec(&(*raiz)->dir, nome);
}

int removeElem(ABP* raiz, char nome[]) {
    if (buscaAluno(raiz, nome).matricula == -1) {
        printf("Aluno inexistente!\n");
        return 0;
    }
    return removeRec(raiz, nome);
}

void em_ordem(NO* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("Nome: %s, Matricula: %d, Nota: %.2lf\n", raiz->info.nome, raiz->info.matricula, raiz->info.nota);
        em_ordem(raiz->dir);
    }
}

void imprime(ABP* raiz) {
    if (raiz == NULL) return;
    if (estaVazia(raiz)) {
        printf("Árvore Vazia!\n");
        return;
    }
    printf("\nAlunos:\n");
    em_ordem(*raiz);
}

int main() {
    ABP* arvore = criaABP();

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Criar ABP\n");
        printf("2 - Inserir aluno\n");
        printf("3 - Buscar aluno\n");
        printf("4 - Remover aluno\n");
        printf("5 - Imprimir a ABP\n");
        printf("6 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            destroiABP(arvore);
            arvore = criaABP();
            printf("ABP criada.\n");
            break;
        case 2: {
            char nome[100];
            int matricula;
            double nota;

            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]s", nome);
            printf("Digite a matrícula: ");
            scanf("%d", &matricula);
            printf("Digite a nota: ");
            scanf("%lf", &nota);

            if (insereElem(arvore, nome, matricula, nota)) {
                printf("Aluno inserido com sucesso.\n");
            }
            break;
        }

        case 3: {
            char nome[100];
            printf("Digite o nome do aluno que deseja buscar: ");
            scanf(" %[^\n]s", nome);

            Aluno alunoBuscado = buscaAluno(arvore, nome);
            if (alunoBuscado.matricula == -1) {
                printf("Aluno não encontrado.\n");
            }
            else {
                printf("Aluno encontrado:\n");
                printf("Nome: %s, Matrícula: %d, Nota: %.2lf\n", alunoBuscado.nome, alunoBuscado.matricula, alunoBuscado.nota);
            }
            break;
        }
        case 4: {
            char nome[100];
            printf("Digite o nome do aluno que deseja remover: ");
            scanf(" %[^\n]s", nome);

            if (removeElem(arvore, nome)) {
                printf("Aluno removido com sucesso.\n");
            }
            break;
        }
        case 5:
            imprime(arvore);
            break;
        case 6:
            destroiABP(arvore);
            printf("Programa encerrado.\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
