#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    char nome[100];
    double valor;
    int quantidade;
};

struct ListaProdutos {
    struct Produto produtos[100];
    int totalProdutos;
};

void criarLista(struct ListaProdutos *c) {
    c->totalProdutos = 0;
}

void adicionarProduto(struct ListaProdutos *c, char *nome, double valor, int quantidade) {
    if (c->totalProdutos < 100) {
        struct Produto novoProduto;
        strcpy(novoProduto.nome, nome);
        novoProduto.valor = valor;
        novoProduto.quantidade = quantidade;
        c->produtos[c->totalProdutos] = novoProduto;
        c->totalProdutos++;
        printf("Produto adicionado.\n");
    } else {
        printf("Não é possível adicionar mais produtos.\n");
    }
}

int verificarEstoque(struct ListaProdutos *c, char *nome) {
    for (int i = 0; i < c->totalProdutos; i++) {
        if (strcmp(c->produtos[i].nome, nome) == 0) {
            return c->produtos[i].quantidade;
        }
    }
    return -1;
}

void imprimirLista(struct ListaProdutos *c) {
    printf("\nCatálogo de Produtos:\n");
    for (int i = 0; i < c->totalProdutos; i++) {
        printf("Nome: %s Preço: %.2lf Quantidade: %d\n",
               c->produtos[i].nome, c->produtos[i].valor, c->produtos[i].quantidade);
    }
}

void exibirMenu(struct ListaProdutos *c) {
    int opcao;
    char nome[100];
    double valor;
    int quantidade;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Verificar Estoque\n");
        printf("3. Imprimir Catálogo\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                scanf("%s", nome);
                printf("Digite o preço do produto: ");
                scanf("%lf", &valor);
                printf("Digite a quantidade em estoque: ");
                scanf("%d", &quantidade);
                adicionarProduto(c, nome, valor, quantidade);
                break;
            case 2:
                printf("Digite o nome do produto: ");
                scanf("%s", nome);
                int estoque = verificarEstoque(c, nome);
                if (estoque >= 0) {
                    printf("Quantidade em estoque de %s: %d\n", nome, estoque);
                } else {
                    printf("Produto não encontrado no catálogo.\n");
                }
                break;
            case 3:
                imprimirLista(c);
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
    struct ListaProdutos Lista;

    criarLista(&Lista);

    exibirMenu(&Lista);

    return 0;
}


