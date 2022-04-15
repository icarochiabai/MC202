#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG printf("debug\n")
typedef struct No{
    int id; //identidade
    char prof[30]; //string da profissao
    int vacinado; //0 se n vacinado, 1 se vacinado
    int lanterna; //0 se n tem lanterna, 1 se tem lanterna

    struct No * proximo; //quem ta atras na fila
} No;

typedef No * p_no;

p_no criar_lista(){
    return NULL;
}

void zerar_lanternas(p_no fila){
    if(fila != NULL){
        zerar_lanternas(fila->proximo);
        fila->lanterna = 0;
    }
}

p_no adicionar_pessoa_no_inicio(p_no fila, int id, char * prof, char * vac){
    if(fila != NULL){
        zerar_lanternas(fila);
    }
    p_no novo;
    novo = malloc(sizeof(No));
    
    novo->id = id;
    strcpy(novo->prof, prof);
    if(strcmp("vacinado", vac) == 0){
        novo->vacinado = 1;
    } else {
        novo->vacinado = 0;
    }
    novo->proximo = fila;
    novo->lanterna = 1; 
    return novo;
}

p_no adicionar_pessoa_no_fim(p_no fila, int id, char * prof, char * vac){
    if(fila == NULL){
        return adicionar_pessoa_no_inicio(fila, id, prof, vac);
    }
    
    zerar_lanternas(fila);
    p_no atual = fila;
    
    while(atual->proximo != NULL){
        atual = atual->proximo;
    } 
    
    p_no novo;
    novo = malloc(sizeof(No));
    novo->id = id;
    strcpy(novo->prof, prof);
    if(strcmp("vacinado", vac) == 0){
        novo->vacinado = 1;
    } else {
        novo->vacinado = 0;
    }
    atual->proximo = novo;
    novo->proximo = criar_lista();
    novo->lanterna = 1;
    return fila;
}

p_no adicionar_pessoa(p_no fila, int id, char * prof, char * vac){
    if(fila == NULL){
        return adicionar_pessoa_no_inicio(fila, id, prof, vac);
    }
    p_no atual = fila;
    while(atual->lanterna != 1){
        atual = atual->proximo;
    }
    zerar_lanternas(fila);

    p_no novo;
    novo = malloc(sizeof(No));

    novo->id = id;
    strcpy(novo->prof, prof);
    if(strcmp("vacinado", vac) == 0){
        novo->vacinado = 1;
    } else {
        novo->vacinado = 0;
    }
    
    novo->lanterna = 1;

    // bota entre os dois
    novo->proximo = atual->proximo;
    atual->proximo = novo;
    return fila;
}

p_no fiscalizar(p_no fila){
    for(p_no atual = fila; atual != NULL; atual = atual->proximo){
        if(strcmp(atual->prof, "fiscal") == 0 && atual->proximo != NULL){
            while(!atual->proximo->vacinado && atual->proximo != NULL){
                if(atual->proximo->lanterna){
                    atual->lanterna = 1;
                } 
                if(atual->proximo->proximo == NULL){
                    free(atual->proximo);
                    atual->proximo = criar_lista();
                    break;
                }
                p_no aux;
                aux = malloc(sizeof(No));
                aux->proximo = atual->proximo;
                atual->proximo = atual->proximo->proximo;
                
                free(aux->proximo); //libera o que tava nao vacinado
                free(aux); //libera o espaco usado pra armazenar temporariamente o endereco do nao vacinado
            }
        }
    }
    return fila;
}

p_no adicionar(p_no fila, int id, char * prof, char * vac){
    if(strcmp("ex-bbb", prof) == 0 || strcmp("filho-politico", prof) == 0 || strcmp("coach", prof) == 0 || strcmp("herdeiro", prof) == 0 || strcmp("youtuber-financas", prof) == 0){
        fila = adicionar_pessoa_no_inicio(fila, id, prof, vac);
    }
    else if(strcmp("funcionario", prof) == 0){
        fila = adicionar_pessoa_no_fim(fila, id, prof, vac);
    } 
    else{
        fila = adicionar_pessoa(fila, id, prof, vac);
    }
    if(fila != NULL){
        fila = fiscalizar(fila);
    }
    return fila;
}

void imprimir_fila(p_no fila){
    if(fila != NULL){
        char vac[30];
        if(fila->vacinado){
            strcpy(vac, "vacinado");
        } else {
            strcpy(vac, "nao-vacinado");
        }
        printf("%d %s %s\n", fila->id, fila->prof, vac);
        imprimir_fila(fila->proximo);
    }
}

void destruir_fila(p_no fila){
    if(fila != NULL){
        destruir_fila(fila->proximo);
        free(fila);
    }
}

int main(){
    p_no fila;
    fila = criar_lista();
    int id;
    char prof[30];
    char vac[20];
    while(scanf("%d %s %s", &id, prof, vac) != EOF){
        fila = adicionar(fila, id, prof, vac);
    }
    imprimir_fila(fila);
    destruir_fila(fila);
    return 0;
}
