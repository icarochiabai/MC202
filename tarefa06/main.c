#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"

#define H 256

int main(){
    int qtdDiamante = 0, qtdOuro = 0, qtdFerro = 0, qtdBlocos, m, n, seed, **altitudes;
    double tempoPorBloco;
    Bloco ***mundo;

    scanf("%d %d\n%d\n%lf", &m, &n, &seed, &tempoPorBloco);
    
    qtdBlocos = m * n * H;
    altitudes = calcularAltitudes(m, n, seed);
    mundo = criarMundo(m, n, altitudes, seed);

    double tempoTotal = explorarMundo(mundo, m, n, altitudes, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    printf("Total de blocos: %d\nTempo total: %lf\nDiamantes: %d\nOuros: %d\nFerros: %d\n", qtdBlocos, tempoTotal, qtdDiamante, qtdOuro, qtdFerro);

    free(altitudes);
    free(mundo);
    return 0;
}
