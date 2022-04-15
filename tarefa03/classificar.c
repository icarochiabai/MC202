#include <stdio.h>
#include <string.h>

#define MAX 200
#define MAXNAME 30
#define DEBUG printf("Debug\n")

void ordenarLista(char lista[][MAXNAME], int n){
    int organizado = 0;
    while(organizado == 0){
        organizado = 1;
        for(int i = 0; i < n-1; ++i){
            if(strcmp(lista[i], lista[i+1]) > 0){
                organizado = 0;

                char aux[MAXNAME];
                strcpy(aux, lista[i]);
                strcpy(lista[i], lista[i+1]);
                strcpy(lista[i+1], aux);
            }
        }
    }
}

void ordenarLista2(char lista[][MAXNAME], int n){
    int organizado = 0;
    while(organizado == 0){
        organizado = 1;
        for(int i = 0; i < n-1; ++i){
            char sobrenome1[MAXNAME] = "";
            char sobrenome2[MAXNAME] = "";
            int tamanhonome1;
            int tamanhonome2;

            for(int j = 0; j < MAXNAME; ++j){
                if(lista[i][j] == '_'){
                    tamanhonome1 = j + 1;
                }   
                if(lista[i + 1][j] == '_'){
                    tamanhonome2 = j + 1;
                }
            }
            for(int j = 0; j < strlen(lista[i]) - tamanhonome1; ++j){
                sobrenome1[j] = lista[i][tamanhonome1 + j];
            }
            for(int j = 0; j < strlen(lista[i+1]) - tamanhonome2; ++j){
                sobrenome2[j] = lista[i+1][tamanhonome2 + j];
            }
            if(strcmp(sobrenome1, sobrenome2) > 0){
                organizado = 0;

                char aux[MAXNAME];
                strcpy(aux, lista[i]);
                strcpy(lista[i], lista[i+1]);
                strcpy(lista[i+1], aux);
            }
        }
    }
}


int main(){
    char nomes[MAX][MAXNAME];
    char nomesProcessados[MAX][MAXNAME];
    int n;
    char operacao[30];

    scanf("%d", &n);
    scanf("%s", operacao);

    for(int i = 0; i < n; ++i){
        scanf("%s", nomes[i]);
    }

    if(strcmp(operacao, "homonimos") == 0){
        int numeroDeHomonimos = 0;

        for(int i = 0; i < n; ++i){
            int counter = -1;
            char primeiroNome[MAXNAME] = "";

            // Pegamos o primeiro nome da primeira pessoa
            for(int j = 0; j < MAXNAME; ++j){
                if(nomes[i][j] != '_'){
                    primeiroNome[j] = nomes[i][j];
                } else {
                    break;
                }
            }
            // Pegamos o primeiro nome da segunda pessoa
            for(int j = 0; j < n; ++j){
                char segundoNome[MAXNAME] = "";

                for(int k = 0; k < MAXNAME; ++k){
                    if(nomes[j][k] != '_'){
                        segundoNome[k] = nomes[j][k];
                    } else {
                        break;
                    }
                }
                // Se os dois nomes forem iguais, acrescentamos 1 ao contador
                if(strcmp(primeiroNome, segundoNome) == 0){
                    counter++;
                }

            }
            // Se o contador for maior (caso tenha mais que 2 pessoas com o mesmo nome) ou igual 1, adicionamos o nome da pessoa ao vetor de nome processados e aumentamos em 1 o numero de homonimos ocorridos.
            if(counter >= 1){
                strcpy(nomesProcessados[numeroDeHomonimos], nomes[i]);
                numeroDeHomonimos++;
            }
        }

        ordenarLista(nomesProcessados, numeroDeHomonimos);
        for(int i = 0; i < numeroDeHomonimos; ++i){
            printf("%s\n", nomesProcessados[i]);
        }

    }
    else if(strcmp(operacao, "parentes") == 0){
        int numeroDeParentes = 0;
        
        for(int i = 0; i < n; ++i){
            char sobrenome1[MAXNAME] = "";
            int counter = -1;
            int tamanhoNome1;
            
            for(int j = 0; j < MAXNAME; ++j){
                if(nomes[i][j] == '_'){
                    tamanhoNome1 = j + 1;
                    break;
                }
            }
            for(int j = 0; j < strlen(nomes[i]) - tamanhoNome1; j++){
                sobrenome1[j] = nomes[i][tamanhoNome1 + j];
            }
            for(int j = 0; j < n; ++j){
                char sobrenome2[MAXNAME] = "";
                int tamanhoNome2;

                for(int k = 0; k < MAXNAME; ++k){
                    if(nomes[j][k] == '_'){
                        tamanhoNome2 = k+1;
                        break;
                    }
                }
                for(int k = 0; k < strlen(nomes[j]) - tamanhoNome2; ++k){
                    sobrenome2[k] = nomes[j][tamanhoNome2 + k];
                }
                if(strcmp(sobrenome1, sobrenome2) == 0){
                    counter++;
                }
                }
                
            if(counter >= 1){
                strcpy(nomesProcessados[numeroDeParentes], nomes[i]);
                numeroDeParentes++;
            }
        }
        ordenarLista(nomesProcessados, numeroDeParentes);
        ordenarLista2(nomesProcessados, numeroDeParentes);
        for(int i = 0; i < numeroDeParentes; ++i){
            printf("%s\n", nomesProcessados[i]);
        }
    }
}
