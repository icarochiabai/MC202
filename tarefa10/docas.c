#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 20
#define debug printf("DEBUG\n")

typedef struct No {
    char produto[MAX_CHAR];
    
    struct No * proximo;
} No;

typedef No * p_no;

void destruir_lista(p_no no){
    if(no != NULL){
        destruir_lista(no->proximo);
        free(no);
    }
}

void imprimir_lista(p_no no){
    if(no != NULL){
        printf("%s\n", no->produto);
        imprimir_lista(no->proximo);
    }
}
// Coisas da pilha
typedef struct Pilha {
    p_no topo;

    int capacidade;
    int quantidade;
} Pilha;

typedef Pilha * p_pilha;

p_pilha criar_pilha(int capacidade){
    p_pilha nova = malloc(sizeof(Pilha));
    nova->topo = NULL;
    nova->capacidade = capacidade;
    nova->quantidade = 0;
    return nova;
}

void empilhar(p_pilha pilha, char produto[MAX_CHAR]){
    if(pilha->quantidade < pilha->capacidade){
        p_no novo = malloc(sizeof(No));
        strcpy(novo->produto, produto);
        novo->proximo = pilha->topo;
        pilha->topo = novo;
        pilha->quantidade++;
    }
}

const char * desempilhar(p_pilha pilha){
    if(pilha->topo != NULL){
        char * produto = malloc(sizeof(char) * MAX_CHAR);
        strcpy(produto, pilha->topo->produto);
        pilha->quantidade--;
        pilha->topo = pilha->topo->proximo;
        return produto;
    } else {
        return "error";
    }
}

void destruir_pilha(p_pilha pilha){
    if(pilha->topo != NULL){
        destruir_lista(pilha->topo);
    }
    free(pilha);
}

// Navios
typedef struct Navio {
    char nome[20];
    char objetivo[20];
    char produto[20];

    int quantidade;
    int capacidade;
} navio;

typedef navio * p_navio;

// Código funcional
int carregar(navio * navio, p_pilha * docas, int n_docas){
    int qtd = 0;
    if(navio->quantidade < navio->capacidade){
        for(int i = 0; i < n_docas; i++){
            if(docas[i]->topo != NULL){
                if(strcmp(docas[i]->topo->produto, navio->produto) == 0){ // se o produto no topo da pilha for igual ao produto que o navio carrega
                    while(strcmp(docas[i]->topo->produto, navio->produto) == 0 && navio->capacidade > navio->quantidade){ // enquanto o produto do topo for o produto que o navio carrega e o navio tem espaço
                        navio->quantidade = navio->quantidade + 1;
                        desempilhar(docas[i]);
                        qtd++;
                        if(docas[i]->topo == NULL){
                            break;
                        }
                    }
                    printf("%s carrega %s doca: %d conteineres: %d\n", navio->nome, navio->produto, i, qtd);
                    return 1;
                }    
            }
        }
    }
    return 0;
}

int descarregar(navio * navio, p_pilha * docas, int n_docas){
    int qtd = 0;
    if(navio->quantidade > 0){
        for(int i = 0; i < n_docas; i++){
            if(docas[i]->capacidade != docas[i]->quantidade){
                int vezes = docas[i]->capacidade - docas[i]->quantidade;
                for(int j = 0; j < vezes; j++){ //adiciona o maximo de produto possivel
                    if(navio->quantidade != 0){
                        navio->quantidade = navio->quantidade - 1;
                        empilhar(docas[i], navio->produto);
                        qtd++;
                    }
                }
                printf("%s descarrega %s doca: %d conteineres: %d\n", navio->nome, navio->produto, i, qtd);
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    
    int n_docas, capacidade, n;
    scanf("%d\n%d\n%d", &n_docas, &capacidade, &n);

    p_pilha * docas = malloc(sizeof(p_pilha) * n_docas);
    for(int i = 0; i < n_docas; i++){
        p_pilha pilha = criar_pilha(capacidade);
        docas[i] = pilha;
    }

    p_navio navios = malloc(sizeof(navio) * n);
    for(int i = 0; i < n; i++){
        navio novo;
        char nome[20], objetivo[20], produto[20];
        int quantidade;

        scanf("%s %s %s %d", nome, objetivo, produto, &quantidade);
        strcpy(novo.nome, nome);
        strcpy(novo.objetivo, objetivo);
        strcpy(novo.produto, produto);
        novo.capacidade = quantidade;
        if(strcmp(objetivo, "carrega") == 0){
            novo.quantidade = 0;
        }
        else if(strcmp(objetivo, "descarrega") == 0){
            novo.quantidade = quantidade;
        }
        navios[i] = novo;
    }

    int running = 1;
    while(running){
        int ini1 = 0;
        int ini2 = 0;
        for(int i = 0; i < n; i++){
            if(strcmp(navios[i].objetivo, "carrega") == 0){
                int x = carregar(&navios[i], docas, n_docas);
                if(x == 1){
                    ini1 = 1;
                }
                //printf("%s tem %d containeres e pode ter ate %d\n", navios[i].nome, navios[i].quantidade, navios[i].capacidade);
            }
            else if(strcmp(navios[i].objetivo, "descarrega") == 0){
                int y = descarregar(&navios[i], docas, n_docas);
                if(y == 1){
                    ini2 = 1;
                }
                //printf("%s tem %d containeres e pode ter ate %d\n", navios[i].nome, navios[i].quantidade, navios[i].capacidade);
            }
        }
        if(ini1 == 0 && ini2 == 0){
            break;
        }
    }
    int qtd_concluida = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(navios[i].objetivo, "carrega") == 0){
            if(navios[i].quantidade == navios[i].capacidade){
                qtd_concluida++;
            }
        }
        else if(strcmp(navios[i].objetivo, "descarrega") == 0 ){
            if(navios[i].quantidade == 0){
                qtd_concluida++;
            }
        }
    }
    
    if(qtd_concluida != n){
        printf("ALERTA: impossivel esvaziar fila, restam %d navios.\n", n - qtd_concluida);
    }

    free(navios);
    for(int i = 0; i < n_docas; i++){
        destruir_pilha(docas[i]);
    }
    free(docas);
}