#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char nome[50];
    int matricula;
    float nota;
};

void avaliarNota(struct Aluno *alunos, int tamanho) {
    struct Aluno *maiorNota = &alunos[0];
    struct Aluno *menorNota = &alunos[0];

    for (int i = 1; i < tamanho; i++) {
        if (alunos[i].nota > maiorNota->nota) {
            maiorNota = &alunos[i];
        }
        if (alunos[i].nota < menorNota->nota) {
            menorNota = &alunos[i];
        }
    }

    printf("Aluno com a maior nota:\n");
    printf("Nome: %s\n", maiorNota->nome);
    printf("Matrícula: %d\n", maiorNota->matricula);
    printf("Nota: %.2f\n", maiorNota->nota);

    printf("\n-\n");

    printf("\nAluno com a menor nota:\n");
    printf("Nome: %s\n", menorNota->nome);
    printf("Matrícula: %d\n", menorNota->matricula);
    printf("Nota: %.2f\n", menorNota->nota);
}

int main() {
    int tamanho = 3;
    struct Aluno alunos[tamanho];

    struct Aluno *ptrAluno = alunos;

    strcpy(ptrAluno->nome, "A");
    ptrAluno->matricula = 1;
    ptrAluno->nota = 10;

    ptrAluno++;

    strcpy(ptrAluno->nome, "B");
    ptrAluno->matricula = 2;
    ptrAluno->nota = 6;

    ptrAluno++;

    strcpy(ptrAluno->nome, "C");
    ptrAluno->matricula = 3;
    ptrAluno->nota = 0;

    avaliarNota(alunos, tamanho);

    return 0;
}
