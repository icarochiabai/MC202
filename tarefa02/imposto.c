#include <stdio.h>      
#define COL 12
#define MAX 1000

float calcularImpostoMensal(float valor){
    // Funcao para calcular o imposto mensal de um valor

    float resultado = 0;

    if(valor > 3743.19){
        resultado += (27.5/100)*(valor - 3743.19);
        valor = 3743.19;
    }
    if(valor > 2995.70){
        resultado += (22.5/100) * (valor - 2995.70);
        valor = 2995.70;
    }
    if(valor > 2246.75){
        resultado += (15.0/100) * (valor - 2246.75);
        valor = 2246.75; 
    }
    if(valor > 1499.15){
        resultado += (7.5/100) * (valor - 1499.15);
        valor = 1499.15;
    }

    return resultado;
} 

float calcularImpostoAnual(float valor){
    // Funcao para calcular o imposto anual de um valor
    float resultado = 0;

    if(valor > 44400.00){
        resultado += (27.5/100)*(valor - 44400.00);
        valor = 44400.00;
    }
    if(valor > 36000.00){
        resultado += (22.5/100) * (valor - 36000.00);
        valor = 36000.00;
    }
    if(valor > 26400.00){
        resultado += (15.0/100) * (valor - 26400.00);
        valor = 26400.00; 
    }
    if(valor > 18000.00){
        resultado += (7.5/100) * (valor - 18000.00);
        valor = 18000.00;
    }

    return resultado;
} 

void completarMatriz(float matriz[][COL + 3], int n){
    // Funcao que formata a matriz, substituindo os valores pelos impostos mensais e tambem calculando e completando o restante da matriz necessaria para ser mostrada na saida
    for(int i = 0; i < n; ++i){
        float valorAnual = 0;
        float valorRetido = 0;
        float valorDevido = 0;
        float valorAjuste;
        for(int j = 0; j < COL; ++j){
            valorAnual += matriz[i][j];

            matriz[i][j] = calcularImpostoMensal(matriz[i][j]);
            valorRetido += matriz[i][j];
        }

        float abatimento;
        scanf("%f", &abatimento);

        valorAnual -= abatimento;
        valorDevido = calcularImpostoAnual(valorAnual);
        valorAjuste = valorDevido - valorRetido;

        matriz[i][COL] = valorRetido;
        matriz[i][COL + 1] = valorDevido;
        matriz[i][COL + 2] = valorAjuste;
    }

}

void printarCabecalho(){
    printf("Jan\tFev\tMar\tAbr\tMai\tJun\tJul\tAgo\tSet\tOut\tNov\tDez\tRetido\tDevido\tAjuste\n"); 
}

void printarMatriz(float matriz[][COL + 3], int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < COL + 3; ++j){
            printf("%.2f\t", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    float tempVal;
    float matriz[MAX][COL + 3];
    scanf("%d", &n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < COL; ++j){
            scanf("%f", &tempVal);
            matriz[i][j] = tempVal;       
        }
    }

    completarMatriz(matriz, n);
    printarCabecalho();
    printarMatriz(matriz, n);


    return 0;
}
