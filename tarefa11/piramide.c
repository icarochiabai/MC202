#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 20

typedef struct No { // No para implementação da árvore
    char nome[MAX_CHAR];
    float valor;

    int nivel;
    struct No *esquerda, *direita, *pai;
} No;

typedef No * p_no;

p_no criarArvore(){
    return NULL;
}

p_no buscarNome(p_no raiz, char nome[MAX_CHAR]){
    if(raiz == NULL || strcmp(raiz->nome, nome) == 0){
        return raiz;
    }
    p_no esq = buscarNome(raiz->esquerda, nome);
    if(esq != NULL){
        return esq;
    }
    return buscarNome(raiz->direita, nome);
}

void adicionarBonificacao_r(p_no raiz, float fator, int caso){
    if(fator <= 0){
        return;
    }
    if(raiz != NULL && fator > 0 && caso == 0){
        raiz->valor += fator/100 * raiz->esquerda->valor;
        raiz->valor += fator/100 * raiz->direita->valor;

        raiz->esquerda->valor *= (1 - fator/100);
        raiz->direita->valor *= (1 - fator/100);        
    }
    else if(raiz != NULL && fator > 0 && caso != 0){
        if(caso == -1){
            raiz->valor += fator/100 * raiz->esquerda->valor;
            raiz->esquerda->valor *= (1 - fator/100);
        }
        else if(caso == 1){
            raiz->valor += fator/100 * raiz->direita->valor;
            raiz->direita->valor *= (1 - fator/100);
        }
    }
    
    if(raiz->pai != NULL){
        if(strcmp(raiz->nome, raiz->pai->esquerda->nome) == 0){ //se for o filho da esquerda, o caso é -1
            adicionarBonificacao_r(raiz->pai, --fator, -1);
        } else {
            adicionarBonificacao_r(raiz->pai, --fator, 1); // se for o filho da direita, o caso é 1
        }
    }
}

void adicionarBonificacao(p_no raiz){
    adicionarBonificacao_r(raiz, 6, 0);
}

int altura(p_no raiz){
    int h_esq, h_dir;
    if(raiz == NULL){
        return 0;
    }
    h_esq = altura(raiz->esquerda);
    h_dir = altura(raiz->direita);

    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

p_no adicionarElemento_r(p_no raiz, char nome_recrutador[MAX_CHAR], char nome_recrutado[MAX_CHAR], float valor, int nivel){
    if(raiz == NULL){   
        p_no novo = malloc(sizeof(No));
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->pai = NULL;
        novo->nivel = nivel;

        strcpy(novo->nome, nome_recrutado);
        novo->valor = valor;
        return novo;
    }
    p_no pai = buscarNome(raiz, nome_recrutador);

    if(pai->esquerda == NULL){
        pai->esquerda = adicionarElemento_r(pai->esquerda, nome_recrutador, nome_recrutado, valor, pai->nivel + 1);
        pai->esquerda->pai = pai;

        if(pai->valor - 0.1 * pai->esquerda->valor >= 0){
            pai->valor -= 0.1 * pai->esquerda->valor;
            pai->esquerda->valor *= 1.1;
        } else {
            pai->esquerda->valor += pai->valor;
            pai->valor = 0;
        }
    }
    else if(pai->direita == NULL){
        pai->direita = adicionarElemento_r(pai->direita, nome_recrutador, nome_recrutado, valor, pai->nivel + 1);
        pai->direita->pai = pai;

        if(pai->valor - 0.1 * pai->direita->valor >= 0){
            pai->valor -= 0.1 * pai->direita->valor;
            pai->direita->valor *= 1.1;
        } else {
            pai->direita->valor += pai->valor;
            pai->valor = 0;
        }

        adicionarBonificacao(pai);
    }
    return raiz;
}

p_no adicionarElemento(p_no raiz, char nome_recrutador[MAX_CHAR], char nome_recrutado[MAX_CHAR], float valor){
    return adicionarElemento_r(raiz, nome_recrutador, nome_recrutado, valor, 1);
}

void imprimirNivel(p_no raiz, int nivel){
    if(raiz != NULL && raiz->nivel <= nivel){
        if(raiz->nivel == nivel){
            printf(" [%s %.2f]", raiz->nome, raiz->valor);
        }
        imprimirNivel(raiz->esquerda, nivel);
        imprimirNivel(raiz->direita, nivel);
    }
}

void imprimirNiveis(p_no raiz, int nivel){
    printf("Nivel %d:", nivel);
    imprimirNivel(raiz, nivel);
    printf("\n");
}

void destruirArvore(p_no raiz){
    if(raiz != NULL){
        destruirArvore(raiz->esquerda);
        destruirArvore(raiz->direita);
        free(raiz);
    }
}

int main(){
    p_no arvore = criarArvore();  

    char nome_recrutador[MAX_CHAR];
    char nome_recrutado[MAX_CHAR];
    float valor;

    scanf("%*s %s %f", nome_recrutador, &valor);
    arvore = adicionarElemento(arvore, nome_recrutador, nome_recrutador, valor);
    imprimirNiveis(arvore, 1);

    while(scanf("%s %*s %s %f", nome_recrutador, nome_recrutado, &valor) != EOF){
        printf("\n");
        arvore = adicionarElemento(arvore, nome_recrutador, nome_recrutado, valor);
        for(int i = 0; i < altura(arvore); i++){
            imprimirNiveis(arvore, i+1);
        }
    }    
    destruirArvore(arvore);
}