#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **tabela;
    int tam, qtd;
} Hash;

Hash *criaHash(int t) {
    Hash *h;
    h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL) {
        h->tam = t;
        h->qtd = 0;
        h->tabela = (int **)malloc(t * sizeof(int *));
        if (h->tabela == NULL)
            return NULL;
        int i;
        for (i = 0; i < t; i++)
            h->tabela[i] = NULL;
    }
    return h;
}

void destroiHash(Hash *h) {
    if (h != NULL) {
        int i;
        for (i = 0; i < h->tam; i++)
            if (h->tabela[i] != NULL)
                free(h->tabela[i]);
        free(h->tabela);
        free(h);
    }
}

int chaveDivisao(int chave, int tam) {
    return (chave & 0x7FFFFFFF) % tam;
}

int chaveMultiplicacao(int chave, int tam) {
    float A = 0.6180339887; // constante: 0 < A < 1
    float val = chave * A;
    val = val - (int)val;
    return (int)(tam * val);
}

int chaveDobra(int chave, int tam) {
    int pos, n_bits = 30;

    int p = 1;
    int r = p << n_bits;
    while ((chave & r) != r)
    {
        n_bits--;
        r = p << n_bits;
    }

    n_bits++;
    pos = chave;
    while (pos > tam)
    {
        int metade_bits = n_bits / 2;
        int parte1 = pos >> metade_bits;
        parte1 = parte1 << metade_bits;
        int parte2 = pos ^ parte1;
        parte1 = pos >> metade_bits;
        pos = parte1 ^ parte2;
        n_bits = n_bits / 2;
    }
    return pos;
}

int insereHash_semTratar(Hash *h, int elem, int (*funcaoHash)(int, int)) {
    if (h == NULL)
        return 0;
    int pos = funcaoHash(elem, h->tam);

    if (h->tabela[pos] == NULL) {
        int *novo = (int *)malloc(sizeof(int));
        if (novo == NULL)
            return 0;
        *novo = elem;
        h->tabela[pos] = novo;
        h->qtd++;
    }
    else
    {
        // Tratamento de colisões (substituição)
        *(h->tabela[pos]) = elem;
    }
    return 1;
}

int buscaHash_semTratar(Hash *h, int elem, int (*funcaoHash)(int, int), int *p) {
    if (h == NULL)
        return 0;
    int pos = funcaoHash(elem, h->tam);
    if (h->tabela[pos] == NULL)
        return 0;
    if (*(h->tabela[pos]) == elem)
    {
        *p = *(h->tabela[pos]);
        return 1;
    }
    return 0;
}

void imprimeHash(Hash *h) {
    if (h == NULL)
        return;
    int i;
    for (i = 0; i < h->tam; i++)
    {
        printf("%d: ", i);
        if (h->tabela[i] == NULL)
            printf("NULL\n");
        else
            printf("%d\n", *(h->tabela[i]));
    }
}

int main()
{
    Hash *h_divisao = criaHash(31);
    Hash *h_multiplicacao = criaHash(31);
    Hash *h_dobra = criaHash(31);

    int elem, busca;

    printf("Digite um elemento para inserir nas Tabelas Hash:\n");
    scanf("%d", &elem);

    insereHash_semTratar(h_divisao, elem, chaveDivisao);
    insereHash_semTratar(h_multiplicacao, elem, chaveMultiplicacao);
    insereHash_semTratar(h_dobra, elem, chaveDobra);

    printf("Elemento %d inserido nas Tabelas Hash.\n", elem);

    printf("Digite um elemento para buscar nas Tabelas Hash:\n");
    scanf("%d", &elem);

    if (!buscaHash_semTratar(h_divisao, elem, chaveDivisao, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Divisao.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Divisao.\n", busca);

    if (!buscaHash_semTratar(h_multiplicacao, elem, chaveMultiplicacao, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Multiplicacao.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Multiplicacao.\n", busca);

    if (!buscaHash_semTratar(h_dobra, elem, chaveDobra, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Dobra.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Dobra.\n", busca);

    printf("\n--- Tabela Hash Divisao ---\n");
    imprimeHash(h_divisao);
    printf("\n--- Tabela Hash Multiplicacao ---\n");
    imprimeHash(h_multiplicacao);
    printf("\n--- Tabela Hash Dobra ---\n");
    imprimeHash(h_dobra);

    destroiHash(h_divisao);
    destroiHash(h_multiplicacao);
    destroiHash(h_dobra);

    return 0;
}
