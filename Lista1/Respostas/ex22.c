#include <stdio.h>
#include <stdlib.h>

void imprimeDecrescente(char vetor[], int tamanho) {
    if(tamanho>=0){
        printf("%c ",vetor[tamanho]);
        imprimeDecrescente(vetor,tamanho-1);
    }
}

int main() {
    char vetor[] = {'A','B','C','D'};
    int i, count=0;

    for(i=0;vetor[i]!='\0';i++){
        count++;
    }

    printf("\nElementos do vetor em ordem decrescente: ");
    imprimeDecrescente(vetor,count);

    return 0;
}
