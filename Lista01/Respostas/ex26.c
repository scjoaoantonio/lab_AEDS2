#include <stdio.h>
#include <stdlib.h>

void torresDeHanoi(int n, char inicio, char fim, char aux) {
    if (n == 1) {
        printf("O disco 1 vai de %c para %c\n", inicio, fim);
        return;
    }

    torresDeHanoi(n - 1, inicio, aux, fim);
    printf("O disco %d vai de %c para %c\n", n, inicio, fim);
    torresDeHanoi(n - 1, aux, fim, inicio);
}

int main() {
    int n;

    printf("Digite o número de discos: ");
    scanf("%d", &n);
    printf("Passos para resolver o problema das Torres de Hanoi com %d discos:\n", n);
    torresDeHanoi(n, 'A', 'C', 'B');

    return 0;
}
