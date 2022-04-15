#include <stdio.h>
#define MAX 10001

int findPersonIndex(int person, int fila[]){
    for(int i = 0; i < MAX; ++i){
        if(fila[i] == person){
            return i;
        }
    }
    return -1;
}

void conversaram(int fila[], int person1, int person2){
    // Trocar as posicoes dos extremos, se o intervalo for um numero par, vai dar tudo certo porque os individuos serao trocados em duplas.
    // Se o intervalo for um numero impar, vai dar tudo certo pois o numero do meio se adequa na fila ordenada.
    int aux;
    int index1;
    int index2;

    index1 = findPersonIndex(person1, fila);
    index2 = findPersonIndex(person2, fila);
    for(int i = 0; i <= (index2 - index1)/2; ++i){
        aux = fila[index2 - i];
        fila[index2 - i] = fila[index1 + i];
        fila[index1 + i] = aux;
    }
}

void esperou(int fila[], int person1, int person2){
    // Comecando no index da pessoa 1, atribuimos o valor da proxima pessoa e passamos 1, fazemos ate chegar na pessoa 2.
    // Quando chegamos na pessoa 2, atribuimos o seu valor como o da pessoa 1.
    int index1;

    index1 = findPersonIndex(person1, fila);

    while(fila[index1] != person2){
        fila[index1] = fila[index1 + 1];
        ++index1;
    }
    fila[index1] = person1;
}

int main(){
    int fila[MAX];
    int n;
    int m;

    scanf("%d", &n);
    scanf("%d", &m);

    for(int i = 0; i < n; ++i){
        fila[i] = i + 1;
    }

    for(int i = 0; i < m; ++i){
        int op;
        int person1;
        int person2;

        scanf("%d%d%d", &op, &person1, &person2);
        if(op == 1){
            conversaram(fila, person1, person2);
        }
        else if(op == 2){
            esperou(fila, person1, person2);
        }

    }
    for(int i = 0; i < n; ++i){
        printf("%d\n", fila[i]);
    }
}
