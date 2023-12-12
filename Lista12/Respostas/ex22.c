#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int **tabela;
    int tam, qtd;
} Hash;

Hash *criaHash(int t)
{
    Hash *h;
    h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL)
    {
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

void destroiHash(Hash *h)
{
    if (h != NULL)
    {
        int i;
        for (i = 0; i < h->tam; i++)
            if (h->tabela[i] != NULL)
                free(h->tabela[i]);
        free(h->tabela);
        free(h);
    }
}

int chaveMultiplicacao(int chave, int tam)
{
    float A = 0.6180339887;
    float val = chave * A;
    val = val - (int)val;
    return (int)(tam * val);
}

int insereHash_EnderAberto(Hash *h, int elem, int (*funcaoSondagem)(int, int, int))
{
    if (h == NULL)
        return 0;
    int i, pos, newPos;
    pos = chaveMultiplicacao(elem, h->tam);
    for (i = 0; i < h->tam; i++)
    {
        newPos = funcaoSondagem(pos, i, h->tam);
        if (h->tabela[newPos] == NULL)
        {
            int *novo = (int *)malloc(sizeof(int));
            if (novo == NULL)
                return 0;
            *novo = elem;
            h->tabela[newPos] = novo;
            h->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash_EnderAberto(Hash *h, int elem, int (*funcaoSondagem)(int, int, int), int *p)
{
    if (h == NULL)
        return 0;
    int i, pos, newPos;
    pos = chaveMultiplicacao(elem, h->tam);
    for (i = 0; i < h->tam; i++)
    {
        newPos = funcaoSondagem(pos, i, h->tam);
        if (h->tabela[newPos] == NULL)
            return 0;
        if (*(h->tabela[newPos]) == elem)
        {
            *p = *(h->tabela[newPos]);
            return 1;
        }
    }
    return 0;
}

int sondagemLinear(int pos, int i, int tam)
{
    return (pos + i) % tam;
}

int sondagemQuadratica(int pos, int i, int tam)
{
    pos = pos + i * i;
    return pos % tam;
}

int sondagemDuploHash(int pos, int i, int tam)
{
    int H2 = chaveMultiplicacao(i + 1, tam - 1) + 1;
    return (pos + i * H2) % tam;
}

void imprimeHash(Hash *h)
{
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
    Hash *h_linear = criaHash(31);
    Hash *h_quadratica = criaHash(31);
    Hash *h_duplo = criaHash(31);

    int elem, busca;

    printf("Digite um elemento para inserir nas Tabelas Hash:\n");
    scanf("%d", &elem);

    insereHash_EnderAberto(h_linear, elem, sondagemLinear);
    insereHash_EnderAberto(h_quadratica, elem, sondagemQuadratica);
    insereHash_EnderAberto(h_duplo, elem, sondagemDuploHash);

    printf("Elemento %d inserido nas Tabelas Hash.\n", elem);

    printf("Digite um elemento para buscar nas Tabelas Hash:\n");
    scanf("%d", &elem);

    if (!buscaHash_EnderAberto(h_linear, elem, sondagemLinear, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Linear.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Linear.\n", busca);

    if (!buscaHash_EnderAberto(h_quadratica, elem, sondagemQuadratica, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Quadratica.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Quadratica.\n", busca);

    if (!buscaHash_EnderAberto(h_duplo, elem, sondagemDuploHash, &busca))
        printf("Elemento NAO encontrado na Tabela Hash Duplo.\n");
    else
        printf("Elemento %d encontrado na Tabela Hash Duplo.\n", busca);

    printf("\n--- Tabela Hash Linear ---\n");
    imprimeHash(h_linear);
    printf("\n--- Tabela Hash Quadratica ---\n");
    imprimeHash(h_quadratica);
    printf("\n--- Tabela Hash Duplo ---\n");
    imprimeHash(h_duplo);

    destroiHash(h_linear);
    destroiHash(h_quadratica);
    destroiHash(h_duplo);

    return 0;
}
