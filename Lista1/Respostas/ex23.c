#include <stdio.h>
#include <stdlib.h>

int somaIntervalo(int maior, int menor) {
    if (maior < menor) {
        return 0;
    } else {
        return maior + somaIntervalo(maior - 1, menor);
    }
}

int main() {
    int maior, menor, resultado;

    printf("Digite o maior número do intervalo: ");
    scanf("%d", &maior);

    printf("Digite o menor número do intervalo: ");
    scanf("%d", &menor);

    if(maior > menor){
        resultado = somaIntervalo(maior, menor);
    }
    else{
        printf("Erro\n");
        return 0;
    }

    printf("A soma do intervalo de %d a %d é: %d\n", maior, menor, resultado);

    return 0;
}
