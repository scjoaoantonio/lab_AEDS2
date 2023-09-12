#include <stdio.h>
#include <stdlib.h>

void imprimeCrescente(int n) {
    if(n<=5){
        printf("%d ",n);
        imprimeCrescente(n+1);
    }
}

void imprimeDecrescente(int n) {
    if(n>=1){
        printf("%d ",n);
        imprimeDecrescente(n-1);
    }
}

int main() {
    printf("\nOrdem crescente: ");
    imprimeCrescente(1);

    printf("\nOrdem decrescente: ");
    imprimeDecrescente(5);

    return 0;
}
