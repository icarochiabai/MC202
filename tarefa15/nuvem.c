#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50
#define MAX 3191

typedef struct Item{
    char palavra[MAX_CHAR];
    int frequencia;
} item;

typedef struct No{
	char palavra[MAX_CHAR];
	struct No * proximo;
} No;

typedef No * p_no;

typedef struct Palavra{
	char palavra[MAX_CHAR];
	int frequencia;
} palavra;

typedef struct {
	p_no vetor[MAX];
	int tamanho;
} Hash;

typedef Hash * p_hash;

p_hash criarHash(){
	p_hash h = malloc(sizeof(Hash));
	h->tamanho = 0;
	return h;
}

int hash(char palavra[MAX_CHAR]){
	int n = 0;
	for(int i = 0; i < strlen(palavra); i++)
		n = (256 * n + palavra[i]) % MAX;
	return n;	
}

void inserir(p_hash v, char palavra[MAX_CHAR]){
	
}

int main(){
	return 0;
}

