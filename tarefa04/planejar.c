#include <math.h>
#include <stdio.h>          
#include <string.h>
#include "planejar.h"

int compara_data(Data data1, Data data2){
    if(data2.d == data1.d && data2.m == data1.m && data2.a == data1.a){
        return 0;
    }
    else if((data2.a > data1.a) || (data2.a >= data1.a && data2.m > data1.m) || (data2.a >= data1.a && data2.m >= data1.m && data2.d > data1.d)){
        return 1;
    }
    else{
        return -1;
    }
}

int diferenca_data(Data data1, Data data2){
    int dias = 1;
    Data menorData, maiorData;
    int mesesImpares[] = {1, 3, 5, 7, 8, 10, 12};
    int mesesPares[] = {4, 6, 9, 11}; 

    if(compara_data(data1, data2) == 0){
        return 0;
    }
    else if(compara_data(data1, data2) == 1){
        maiorData = data2;
        menorData = data1;    
    }
    else{
        maiorData = data1;
        menorData = data2;
    }
    while(compara_data(menorData, maiorData) != 0){
        dias++;
        menorData.d++;
        for(int i = 0; i < 7; ++i){
            if(menorData.m == mesesImpares[i] && menorData.d%31 == 0){
                menorData.m++;
                menorData.d = 0;
                break;
            }
        }
        for(int i = 0; i < 4; ++i){
            if(menorData.m == mesesPares[i] && menorData.d%30 == 0 && menorData.d != 0){
                menorData.m++;
                menorData.d = 0;
                break;
            }
        }
        if(menorData.m == 2 && menorData.d%28 == 0 && menorData.d != 0){
            menorData.m++;
            menorData.d = 0;
        }
        if(menorData.m%13==0){
            menorData.a++;
            menorData.m = 1;
            menorData.d = 0;
        }
    }                          
    return dias;
}

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor){
    for(int i = 0 ; i < qtd_voos; ++i){
        if(voos[i].id == numero_voo){
            voos[i].valor = novo_valor;
            break;
        }           
    }
}

void cancelar(Voo voos[], int * qtd_voos, int numero_voo){
    for(int i = 0; i < *qtd_voos; ++i){
        if(voos[i].id == numero_voo){
            for(int j = 0; j < *qtd_voos - 1; ++j){
                voos[i+j] = voos[i+j+1];
            } 
            break;
        }
    }
    *qtd_voos -= 1;         // Decrementa a quantidade de numero de voos, dessa forma, se algum novo voo for adicionado, sera 
                            // adicionado no local de memoria onde existe um voo vago. Evitando segmentation fault.
}

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]){
    int melhorIda;
    int melhorVolta;
    double menorIda = INFINITY;
    double menorVolta = INFINITY;

    for(int i = 0; i < qtd_voos; ++i){
        int achou = 0;
        if(strcmp(voos[i].aeroO, codigo_origem) == 0){
            if(voos[i].valor <= menorIda && (compara_data(data_inicio, voos[i].dataVoo) == 1 || compara_data(voos[i].dataVoo, data_inicio) == 0) && compara_data(voos[i].dataVoo, data_fim) == 1){
                for(int j = 0; j < qtd_voos; ++j){
                    if(strcmp(voos[j].aeroD, codigo_origem) == 0 && diferenca_data(voos[i].dataVoo, voos[j].dataVoo) >= 4 && compara_data(voos[i].dataVoo, voos[j].dataVoo) == 1 && (compara_data(voos[j].dataVoo, data_fim) == 1 || compara_data(voos[j].dataVoo, data_fim) == 0)){
                        // Eh um voo elegivel
                        if(voos[j].valor <= menorVolta){
                            achou = 1;
                            menorVolta = voos[j].valor;
                            melhorVolta = voos[j].id;
                        }   
                    }
                }
            if(achou == 1){
                menorIda = voos[i].valor;
                melhorIda = voos[i].id;
                }
            }
        }
    }

    printf("%d\n%d\n", melhorIda, melhorVolta);
}
