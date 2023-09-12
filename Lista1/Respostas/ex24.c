#include <stdio.h>
#include <stdlib.h>

int multiplicacao(int M, int N) {
    if (N == 0) {
        return 0;
    } else {
        return M + multiplicacao(M, N - 1);
    }
}

int main() {
    int M, N, resultado;

    printf("Digite o primeiro número (M): ");
    scanf("%d", &M);

    printf("Digite o segundo número (N): ");
    scanf("%d", &N);

    if (M >= 0 && N >= 0) {
        resultado = multiplicacao(M, N);
        printf("%d x %d = %d\n", M, N, resultado);
    } else {
        printf("Erro");
        return 0;
    }

    return 0;
}
