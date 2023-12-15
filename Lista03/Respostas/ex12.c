#include <stdio.h>
#include <stdlib.h>


typedef struct {
    float lado;
} Cubo;

Cubo *criar(float lado) {
    Cubo *cubo = malloc(sizeof(Cubo));
    cubo->lado = lado;
    return cubo;
}

void excluir(Cubo *cubo) {
    free(cubo);
}

float calcLado(const Cubo *cubo) {
    return cubo->lado;
}

float calcArea(const Cubo *cubo) {
    return 6 * cubo->lado * cubo->lado;
}

float calcVolume(const Cubo *cubo) {
    return cubo->lado * cubo->lado * cubo->lado;
}

int main() {
    Cubo *cubo = criar(2.0);

    printf("Medidas do cubo: \n");
    printf("Tamanho do lado: %.2f\n", calcLado(cubo));
    printf("Área: %.2f\n", calcArea(cubo));
    printf("Volume: %.2f\n", calcVolume(cubo));

    excluir(cubo);

    return 0;
}