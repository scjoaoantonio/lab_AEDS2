#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ContaBancaria {
    int numeroConta;
    double saldo;
    char nome[100];
};

void criarConta(struct ContaBancaria *c, int numero, char *nome) {
    c->numeroConta = numero;
    c->saldo = 0.0;
    strcpy(c->nome, nome);
}

void depositar(struct ContaBancaria *c, double valor) {
    if (valor > 0) {
        c->saldo += valor;
        printf("Depositado: %.2lf.\n", valor);
    } else {
        printf("Valor de depósito inválido.\n");
    }
}

void sacar(struct ContaBancaria *c, double valor) {
    if (valor > 0 && valor <= c->saldo) {
        c->saldo -= valor;
        printf("Sacado: %.2lf.\n", valor);
    } else {
        printf("Saldo insuficiente ou valor inválido.\n");
    }
}

double consultarSaldo(struct ContaBancaria *c) {
    return c->saldo;
}

void imprimirInfo(struct ContaBancaria *c) {
    printf("Número da Conta: %d\n", c->numeroConta);
    printf("nome da Conta: %s\n", c->nome);
    printf("Saldo Atual: %.2lf\n", c->saldo);
}

void menu(struct ContaBancaria *c) {
    int opcao;
    double valor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Consultar Saldo\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser depositado: ");
                scanf("%lf", &valor);
                depositar(c, valor);
                break;
            case 2:
                printf("Digite o valor pra sacar: ");
                scanf("%lf", &valor);
                sacar(c, valor);
                break;
            case 3:
                printf("Saldo atual: %.2lf\n", consultarSaldo(c));
                break;
            case 4:
                printf("...\n");
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

int main() {
    struct ContaBancaria minhaConta;

    criarConta(&minhaConta, 61, "João Antônio");

    menu(&minhaConta);

    return 0;
}

