#include <stdio.h>
#include <string.h>
#include "planejar.h"
#define MAX 1000

int main(){
    Voo voos[MAX];
    int numV = 0;
    char operacao[20];
    scanf("%s", operacao);
    while(strcmp(operacao, "planejar") != 0){
        if(strcmp(operacao, "registrar") == 0){
            scanf("%d\n%s%s\n%d/%d/%d\n%lf", &voos[numV].id, voos[numV].aeroO, voos[numV].aeroD, &voos[numV].dataVoo.d, &voos[numV].dataVoo.m, &voos[numV].dataVoo.a, &voos[numV].valor);
            numV++;
        }
        else if(strcmp(operacao, "alterar") == 0){
            int id;
            float valor;
            scanf("%d %f", &id, &valor);
            alterar(voos, numV, id, valor);

        }
        else if(strcmp(operacao, "cancelar") == 0){
            int id;
            scanf("%d", &id);
            cancelar(voos, &numV, id);
        }

        strcpy(operacao, "");
        scanf("%s", operacao);
    }
    Data dataInicio, dataFim;
    char codigo[MAX];
    scanf("%s\n%d/%d/%d %d/%d/%d", codigo, &dataInicio.d, &dataInicio.m, &dataInicio.a, &dataFim.d, &dataFim.m, &dataFim.a);

    //for(int i = 0; i < numV; ++i){
    //    printf("Voo %d\nID: %d\n%s %s\n%d/%d/%d\n%f\n\n", i+1, voos[i].id, voos[i].aeroO, voos[i].aeroD, voos[i].dataVoo.d, voos[i].dataVoo.m, voos[i].dataVoo.a,voos[i].valor);
    //}
    planejar(voos, numV, dataInicio, dataFim, codigo); 
}
