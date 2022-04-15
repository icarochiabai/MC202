#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"

int **calcularAltitudes(int m, int n, int seed){
    int **matriz;

    matriz = malloc(m * sizeof(int *));
    for(int i = 0; i < m; ++i){
        matriz[i] = malloc(n * sizeof(int));
    }
    
    for(int x = 0; x < m; ++x){
        for(int z = 0; z < n; ++z){
            matriz[x][z] = (seed * (202 + x + z) + 12345 + x + z) % 256;
        }
    }
    return matriz;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed){
    Bloco ***mundo;

    mundo = malloc(m * sizeof(int **)); // Aloca para os valores de x
    for(int x = 0; x < m; ++x){
        mundo[x] = malloc(n * sizeof(int *)); // Aloca para os valores de z pra cada x
        for(int z = 0; z < n; ++z){
            mundo[x][z] = malloc(256 * sizeof(Bloco)); // Aloca para a lista de alturas total
            for(int y = 0; y < 256; ++y){
                if(y > altitudes[x][z]){
                    mundo[x][z][y].valor = 21;
                }
                else {
                    mundo[x][z][y].valor = (seed * (202 + x + y + z) + x + y + z) % 33; 
                }      
            }
        }
    }
    return mundo;
}

double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos){
    for(int x = 0; x < m; ++x){
        for(int z = 0; z < n; ++z){
            for(int y = 0; y < 256; ++y){
                if(mundo[x][z][y].valor >= 21 && mundo[x][z][y].valor <= 32){
                    *qtdBlocos -= 1; // Se for um bloco vazio / agua / lava, decrementamos a contagem total de blocos
                }
                else if(mundo[x][z][y].valor == 0){
                    *qtdDiamante += 1;
                }
                else if(mundo[x][z][y].valor == 1 || mundo[x][z][y].valor == 2){
                    *qtdOuro += 1;
                }
                else if(mundo[x][z][y].valor >= 3 && mundo[x][z][y].valor <= 5){
                    *qtdFerro += 1;
                }
            }
        }
    }
    return (*qtdBlocos) * tempoPorBloco;
}

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

    printf("Total de Blocos: %d\nTempo total: %.2fs\nDiamantes: %d\nOuros: %d\nFerros: %d\n", qtdBlocos, tempoTotal, qtdDiamante, qtdOuro, qtdFerro);

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            free(mundo[i][j]);
        }
        free(mundo[i]);
        free(altitudes[i]);
    }

    free(mundo);
    free(altitudes);
    return 0;
}
