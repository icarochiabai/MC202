#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 20

typedef struct No_Produto{
    char nome[MAX_CHAR];
    float valor;

    struct No_Produto * esquerda;
    struct No_Produto * direita;
} No_Produto;

typedef No_Produto * p_nop;

typedef struct No {
    int codigo;

    p_nop arvore; // Cada nó possui uma árvore (para ordenar os produtos), além do filho esquerdo e direito
    struct No * esquerda; // Logo, acho que é uma árvore binária de árvores binárias
    struct No * direita;
} No;

typedef No * p_no;

p_nop criar_subarvore(){
    return NULL;
}

p_nop inserir_elemento_subarvore(p_nop no, char nome[MAX_CHAR], float valor){
    if(no == NULL){
        p_nop novo = malloc(sizeof(No_Produto));
        strcpy(novo->nome, nome);
        novo->valor = valor;
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if(strcmp(nome, no->nome) < 0){
        no->esquerda = inserir_elemento_subarvore(no->esquerda, nome, valor);
    }
    if(strcmp(nome, no->nome) > 0){
        no->direita = inserir_elemento_subarvore(no->direita, nome, valor);
    }
    return no;
}

p_no criar_arvore(){
    return NULL;
}


p_no inserir_elemento(p_no no, char nome[MAX_CHAR], int codigo, float valor){
    if(no == NULL){
        p_no novo = malloc(sizeof(No));
        novo->arvore = NULL;
        novo->arvore = inserir_elemento_subarvore(novo->arvore, nome, valor);
        novo->codigo = codigo;
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if(codigo < no->codigo){
        no->esquerda = inserir_elemento(no->esquerda, nome, codigo, valor);
    }
    if(codigo > no->codigo){
        no->direita = inserir_elemento(no->direita, nome, codigo, valor);
    }
    if(codigo == no->codigo){
        no->arvore = inserir_elemento_subarvore(no->arvore, nome, valor);
    }
    return no;
}

void imprimir_subarvore(p_nop no, int codigo, float faixa){
    if(no != NULL){
        imprimir_subarvore(no->esquerda, codigo, faixa);
        if(no->valor <= 1.1 * faixa){
            printf("%s %d %.2f\n", no->nome, codigo, no->valor);
        }
        imprimir_subarvore(no->direita, codigo, faixa);
    }
}

int tem_abaixo(p_nop no, float faixa){
    if(no != NULL){
        if(no->valor <= 1.1 * faixa){
            return 1;
        }
        else{
            return (tem_abaixo(no->esquerda, faixa) > tem_abaixo(no->direita, faixa) ? tem_abaixo(no->esquerda, faixa) : tem_abaixo(no->direita, faixa));
        }
    }
    return 0;
}

void imprimir_arvore(p_no no, int codigo, float faixa){
    if(no != NULL){
        if(codigo > no->codigo){
            imprimir_arvore(no->direita, codigo, faixa);
            return;
        }
        if(codigo < no->codigo){
            imprimir_arvore(no->esquerda, codigo, faixa);
            return;
        }
        else {
            printf("OFERTAS para %d:\n", codigo);
            if(tem_abaixo(no->arvore, faixa)){
                imprimir_subarvore(no->arvore, no->codigo, faixa);
            } else {
                printf("nenhuma boa oferta foi encontrada");
            }
            printf("\n");
            return;
        }
    }
    else {
        printf("OFERTAS para %d:\n", codigo);
        printf("nenhuma boa oferta foi encontrada\n");
        return;
    }
}

void destruir_subarvore(p_nop no){
    if(no != NULL){
        destruir_subarvore(no->esquerda);
        destruir_subarvore(no->direita);
        free(no);
    }
}

void destruir_arvore(p_no no){
    if(no != NULL){
        destruir_subarvore(no->arvore);
        destruir_arvore(no->esquerda);
        destruir_arvore(no->direita);
        free(no);
    }
}

int main(){
    int n, m;
    scanf("%d", &n);

    char nome[MAX_CHAR];
    int codigo;
    float valor;
    
    p_no arvore = criar_arvore();
    for(int i = 0; i < n; i++){
        scanf("%s %d %f", nome, &codigo, &valor);
        arvore = inserir_elemento(arvore, nome, codigo, valor);
    }
    
    float faixa;
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%d %f", &codigo, &faixa);
        imprimir_arvore(arvore, codigo, faixa);
    }

    destruir_arvore(arvore);

    return 0;
}