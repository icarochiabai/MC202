#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("debug\n")

typedef struct No{
    int altura;

    struct No * proximo;
    struct No * anterior;
} No;

typedef No * p_no;

p_no criar_lista_circular(){
    p_no head = malloc(sizeof(No));

    head->proximo = head;
    head->anterior = head;
    return head;
}

p_no adicionar_elemento(p_no lista, int valor){
    p_no novo = malloc(sizeof(No));
    novo->altura = valor;

    novo->proximo = lista->proximo;
    novo->anterior = lista;
    lista->proximo->anterior = novo;
    lista->proximo = novo;

    return novo; //me faz adicionar no final, depois de adicionar basta andar 1 posicao e chegamos na cabeca da lista.
}

p_no adicionar_no(p_no lista, p_no no){
    no->proximo = lista->proximo;
    no->anterior = lista;
    lista->proximo->anterior = no;
    lista->proximo = no;

    return lista;
}

void imprimir_lista_circular_r(p_no lista, p_no cabeca){
    if(lista->proximo != cabeca){
        printf("%d ", lista->proximo->altura);
        imprimir_lista_circular_r(lista->proximo, cabeca);
    }
}

void imprimir_lista_circular(p_no lista){
    imprimir_lista_circular_r(lista, lista);
    printf("\n");
}

p_no remover_elemento(p_no lista){
    lista->proximo = lista->proximo->proximo;
    free(lista->proximo->anterior);
    lista->proximo->anterior = lista;
    return lista;
}

int ordenar(p_no lista){
    p_no head = lista;
    int ordenada = 1;
    
    for(p_no no = lista->proximo; no->proximo != head; no = no->proximo){
        if(no->proximo->altura < no->altura){
            int aux = no->proximo->altura;
            no->proximo->altura = no->altura;
            no->altura = aux;

            ordenada = 0;
        }
    }
    return ordenada;
}

void ordenar_lista(p_no lista){
    int ordenada = 0;
    while(!ordenada){
        ordenada = ordenar(lista);
    }
}

void destruir_lista_circular(p_no lista){
    while(lista->proximo != lista){
        lista = remover_elemento(lista);
    }
    free(lista);
}

p_no jogar_dados(p_no head, p_no equipe, int sentido, int m){
    p_no atual;
    atual = head->proximo; //primeiro jogador (depois da cabeca da lista)

    if(sentido == -1){ //sentido anti-horario
        for(int i = 1; i < m; ++i){ //vai pro anterior
            atual = atual->anterior;
            if(atual == head){ //descontar se ele passou pela cabeca
                --i;
            }
        }
        if(atual == head){ //se parar na cabeca, vai mais 1 pra tras
            atual = atual->anterior;
        }
    }
    else if(sentido == 1){
        for(int i = 1; i < m; ++i){
            atual = atual->proximo;
            if(atual == head){
                --i;
            }
        }
        if(atual == head){
            atual = atual->proximo;
        }
    }
    
    p_no aux;
    atual->anterior->proximo = atual->proximo; //liga o anterior do escolhido ao proximo do escolhido
    aux = atual->anterior; //no auxiliar para armazenar a posicao do anterior ao escolhido
    equipe = adicionar_no(equipe, atual); //religamos o escolhido para sua devida lista circular da sua equipe
    aux->proximo->anterior = aux;  //usamos o no auxiliar para ligar o o proximo do escolhido ao anterior do escolhido


    return equipe;
}

int main(){
    p_no lista_circular = criar_lista_circular();
    p_no equipe1 = criar_lista_circular();
    p_no equipe2 = criar_lista_circular();
    int n, altura, m;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &altura);
        lista_circular = adicionar_elemento(lista_circular, altura);
    }
    lista_circular = lista_circular->proximo; //anda 1 posicao para chegar na cabeca da lista.
    for(int i = 0; i < n; ++i){
        scanf("%d", &m);
        if(i % 2 == 0){
            equipe1 = jogar_dados(lista_circular, equipe1, -1, m);
        } else {
            equipe2 = jogar_dados(lista_circular, equipe2, 1, m);
        }
    }

    ordenar_lista(equipe1);
    ordenar_lista(equipe2);

    imprimir_lista_circular(equipe1);
    imprimir_lista_circular(equipe2);

    destruir_lista_circular(lista_circular);
    destruir_lista_circular(equipe1);
    destruir_lista_circular(equipe2);
    return 0;
}
