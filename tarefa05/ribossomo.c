#include <stdio.h>
#include <stdlib.h>

#define MAX 13

struct s_base{
    char tipo;
    char traducao;
    int qtd;
};

typedef struct s_base base;


int main(){
    char dna[MAX];
    char rna[MAX];
    base dicionario[MAX];
    int n;
    char *seqDna, *seqRna;

    int l1 = 0;
    int c1;
    while((c1 = getchar()) != '\n'){
        dna[l1] = c1;
        l1++;
    }

    int l2 = 0;
    int c2;
    while((c2 = getchar()) != '\n'){
        rna[l2] = c2;
        l2++;
    }

    for(int i = 0; i < MAX; ++i){
        dicionario[i].tipo = dna[i];
        dicionario[i].traducao = rna[i];
        dicionario[i].qtd = -1;
    }
    
    scanf("%d\n", &n);
    seqDna = calloc(n, sizeof(char));
    seqRna = calloc(n, sizeof(char));
    
    for(int i = 0; i < n; ++i){
        scanf("%c", &seqDna[i]);     
    }
    
    printf("ID:");
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < MAX; ++j){
            if(seqDna[i] == dicionario[j].tipo){
                dicionario[j].qtd++;
                seqRna[i] = dicionario[j].traducao;
                printf("\t%d", dicionario[j].qtd);
            }
        }
    }
    
    printf("\nDNA:");
    for(int i = 0; i < n; ++i){
        printf("\t%c", seqDna[i]);
    }
    printf("\n"); 
    for(int i = 0; i < n; ++i){
        printf("\t|");
    }

    printf("\nRNA:");
    for(int i = 0; i < n; ++i){
        printf("\t%c", seqRna[i]);
    }
    printf("\n");

    free(seqDna);
    free(seqRna);

    return 0;
}
