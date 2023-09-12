#include <stdio.h>
#include <stdlib.h>

int contadorNegativos(float *vet, int N) {
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (*(vet + i) < 0) {
            count++;
        }
    }

    return count;
}

int main() {
    int N, numNegativos;
    float VET[N];

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        printf("Digite o numero %d do vetor:\n", i+1);    
        scanf("%f", &VET[i]);
    }

    numNegativos = contadorNegativos(VET, N);
    printf("Números negativos: %d\n", numNegativos);
    return 0;
}
