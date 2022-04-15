#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        char nome[30];
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }
}
