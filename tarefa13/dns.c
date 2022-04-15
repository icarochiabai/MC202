#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

enum Cor {VERMELHO, PRETO};

typedef struct Dominio {
    char nome[MAX_CHAR];
    char ip[MAX_CHAR];
} Dominio;

typedef struct No {
    char ip[MAX_CHAR];

    int repeticao;
    enum Cor cor;

    struct No * esquerda;
    struct No * direita;
} No;

typedef No * p_no;

p_no criarArvore(){
    return NULL;
}

int ehVermelho(p_no no){
    if(no == NULL){
        return 0; //os nulos sao pretos
    }
    return no->cor == VERMELHO;
}

int ehPreto(p_no no){
    if(no == NULL){
        return 1; // os nulos sao pretos
    }
    return no->cor == PRETO;
}

p_no rotaciona_para_esquerda(p_no no){
    p_no novo = no->direita;
    no->direita = novo->esquerda;
    novo->esquerda = no;
    novo->cor = no->cor;
    no->cor = VERMELHO;
    return novo;
}

p_no rotaciona_para_direita(p_no no){
    p_no novo = no->esquerda;
    no->esquerda = novo->direita;
    novo->direita = no;
    novo->cor = no->cor;
    no->cor = VERMELHO;
    return novo;
}

void sobe_vermelho(p_no no){
    no->cor = VERMELHO;
    no->esquerda->cor = no->direita->cor = PRETO;
}

p_no adicionar_elemento_r(p_no no, char ip[MAX_CHAR] ){
    if(no == NULL){
        p_no elemento;
        elemento = malloc(sizeof(No));
        elemento->esquerda = elemento->direita = NULL;
        elemento->repeticao = 1;
        strcpy(elemento->ip, ip);
        elemento->cor = VERMELHO;
        return elemento;
    }
    
    int valor = strcmp(no->ip, ip);

    if(valor < 0){
        no->direita = adicionar_elemento_r(no->direita, ip);
    }
    else if(valor > 0) {
        no->esquerda = adicionar_elemento_r(no->esquerda, ip);
    }
    else {
        no->repeticao++;
    }

    if(ehVermelho(no->direita) && ehPreto(no->esquerda)){
        no = rotaciona_para_esquerda(no);
    }
    if(ehVermelho(no->esquerda) && ehVermelho(no->esquerda->esquerda)){
        no = rotaciona_para_direita(no);
    }
    if(ehVermelho(no->esquerda) && ehVermelho(no->direita)){
        sobe_vermelho(no);
    }

    return no;
}

p_no adicionar_elemento(p_no no, char string[MAX_CHAR]){
    no = adicionar_elemento_r(no, string);
    no->cor = PRETO;
    return no;
}

void imprimir_arvore(p_no no){    
    if(no != NULL){
        imprimir_arvore(no->esquerda);
        printf("Palavra: '%s' - Frequencia: %d\n", no->ip, no->repeticao);
        imprimir_arvore(no->direita);
    }
}

int frequencia(p_no no, char ip[MAX_CHAR]){
    if(no != NULL){
        int valor = strcmp(ip, no->ip);

        if(valor < 0){
            return frequencia(no->esquerda, ip);
        }
        if(valor > 0){
            return frequencia(no->direita, ip);
        }
        if(valor == 0){
            return no->repeticao;
        }
        return 0;
    }
    return 0;
}

int main(){
    p_no ips = criarArvore();

    int u, n;
    scanf("%d\n%d", &u, &n);
    Dominio * dominios = malloc(n * sizeof(Dominio));
    for(int i = 0; i < n; i++){
        char dominio[MAX_CHAR];
        char ip[MAX_CHAR];

        scanf("%s %s", dominio, ip);
        strcpy(dominios[i].nome, dominio);
        strcpy(dominios[i].ip, ip);
    }

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        char nome[MAX_CHAR];
        char ip[MAX_CHAR];

        scanf("%*s %s %*s %s", nome, ip);

        for(int j = 0; j < n; j++){
            if(strcmp(dominios[j].nome, nome) == 0){
                ips = adicionar_elemento(ips, ip);
                if(frequencia(ips, ip) > u){
                    printf("FORBIDDEN %s FROM %s\n", nome, ip);
                }
                else{
                    printf("ACCEPTED %s FROM %s RESPOND %s\n", nome, ip, dominios[j].ip);
                }
                break;
            } else {
                if(j == n-1){
                    printf("NOTFOUND %s FROM %s\n", nome, ip);
                }
            }
        }
    }
    
    return 0;
}