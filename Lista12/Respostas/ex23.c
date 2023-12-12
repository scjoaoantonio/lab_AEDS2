#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

typedef struct
{
    No **tabela;
    int tam;
} Hash;

Hash *criaHash(int t)
{
    Hash *h;
    h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL)
    {
        h->tam = t;
        h->tabela = (No **)malloc(t * sizeof(No *));
        if (h->tabela == NULL)
            return NULL;
        int i;
        for (i = 0; i < t; i++)
            h->tabela[i] = NULL;
    }
    return h;
}

void destroiLista(No *lista)
{
    while (lista != NULL)
    {
        No *aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

void destroiHash(Hash *h)
{
    if (h != NULL)
    {
        int i;
        for (i = 0; i < h->tam; i++)
            destroiLista(h->tabela[i]);
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

int insereHash_Encadeado(Hash *h, int elem)
{
    if (h == NULL)
        return 0;
    int pos = chaveMultiplicacao(elem, h->tam);

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
        return 0;

    novo->valor = elem;
    novo->prox = h->tabela[pos];
    h->tabela[pos] = novo;

    return 1;
}

int buscaHash_Encadeado(Hash *h, int elem)
{
    if (h == NULL)
        return 0;
    int pos = chaveMultiplicacao(elem, h->tam);

    No *atual = h->tabela[pos];
    while (atual != NULL)
    {
        if (atual->valor == elem)
            return 1;
        atual = atual->prox;
    }

    return 0;
}

void imprimeHash(Hash *h)
{
    if (h == NULL)
        return;
    int i;
    for (i = 0; i < h->tam; i++)
    {
        printf("%d: ", i);
        No *atual = h->tabela[i];
        while (atual != NULL)
        {
            printf("%d -> ", atual->valor);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

int main()
{
    Hash *h = criaHash(31);

    int elem;

    printf("Digite um elemento para inserir na Tabela Hash:\n");
    scanf("%d", &elem);

    insereHash_Encadeado(h, elem);

    printf("Elemento %d inserido na Tabela Hash.\n", elem);

    printf("Digite um elemento para buscar na Tabela Hash:\n");
    scanf("%d", &elem);

    if (buscaHash_Encadeado(h, elem))
        printf("Elemento %d encontrado na Tabela Hash.\n", elem);
    else
        printf("Elemento %d NAO encontrado na Tabela Hash.\n", elem);

    printf("\n--- Tabela Hash ---\n");
    imprimeHash(h);

    destroiHash(h);

    return 0;
}
