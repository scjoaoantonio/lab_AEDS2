#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int raizes(float A, float B, float C, float *X1, float *X2) {

    float delta = (B * B) - (4 * (A * C));

    if (delta > 0) {
        *X1 = (-B + sqrt(delta)) / (2 * A);
        *X2 = (-B - sqrt(delta)) / (2 * A);
        return 2;
    } else if (delta == 0) {
        *X1 = -B / (2 * A);
        return 1;
    } else {
        return 0;
    }
}

int main() {
    float A, B, C, X1, X2;
    int resposta;

    printf("Digite os coeficientes da equacao (A, B e C): \n");
    printf("A: ");
    scanf("%f", &A);
    printf("B: ");
    scanf("%f", &B);
    printf("C: ");
    scanf("%f", &C);

    resposta = raizes(A, B, C, &X1, &X2);

    switch (resposta)
    {
    case 1:
        printf("X1 = %.2f\n", X1);
        break;

    case 2:
        printf("X1 = %.2f\n", X1);
        printf("X2 = %.2f\n", X2);
        break;

    default:
        printf("Sem raizes reais.\n");
        break;
    }

    return 0;
}
