#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pacote {
    int id, prioridade, incremento;    
} Pacote;

typedef struct {
    Pacote * pacotes;
    int n, tamanho;
} FP;

typedef FP * p_fp;

#define PAI(i) ( (i-1)/2 )

#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)

void troca(Pacote * p1, Pacote * p2){
    Pacote paux = *p1;
    *p1 = *p2;
    *p2 = paux;
}

p_fp criar_filaprio(int tamanho){
    p_fp fprio = malloc(sizeof(FP));
    fprio->pacotes = malloc(tamanho * sizeof(Pacote));
    fprio->n = 0;
    fprio->tamanho = tamanho;

    return fprio;
}

void sobe_no_heap(p_fp fprio, int n){
    if(n > 0 && fprio->pacotes[PAI(n)].prioridade < fprio->pacotes[n].prioridade){
        troca(&fprio->pacotes[n], &fprio->pacotes[PAI(n)]);
        sobe_no_heap(fprio, PAI(n));
    }
}

void desce_no_heap(p_fp fprio, int n){
    int maior_pacote;
    if(F_ESQ(n) < fprio->n){
        maior_pacote = F_ESQ(n);
        if(F_DIR(n) < fprio->n && fprio->pacotes[F_ESQ(n)].prioridade < fprio->pacotes[F_DIR(n)].prioridade){
            maior_pacote = F_DIR(n);
        }
        if(fprio->pacotes[n].prioridade < fprio->pacotes[maior_pacote].prioridade){
            troca(&fprio->pacotes[n], &fprio->pacotes[maior_pacote]);
            desce_no_heap(fprio, maior_pacote);
        }
    }
}

void adicionar_pacote(p_fp fprio, Pacote p){
    fprio->pacotes[fprio->n] = p;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

Pacote extrair_maximo(p_fp fprio){
    Pacote maior_pacote = fprio->pacotes[0];
    troca(&fprio->pacotes[0], &fprio->pacotes[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return maior_pacote;
}

void heapfy(p_fp fprio, int k){
    for(int i = k; i > 0; i--){
        if(fprio->n > 0){
            Pacote p;
            p = extrair_maximo(fprio);
            printf("%d\t%d\t%d\n", p.id, p.prioridade, p.incremento);
        }
    }
}

void ordenar(p_fp fprio, int k){
    int maior_pacote;
    if(F_ESQ(k) < fprio->n){
        maior_pacote = F_ESQ(k);
        if(fprio->pacotes[F_ESQ(k)].prioridade > maior_pacote){
            maior_pacote = F_ESQ(k);
        }
        if(F_DIR(k) < fprio->n && fprio->pacotes[F_DIR(k)].prioridade > fprio->pacotes[F_ESQ(k)].prioridade){
            maior_pacote = F_DIR(k);
        }
        if(fprio->pacotes[k].prioridade < fprio->pacotes[maior_pacote].prioridade){
            troca(&fprio->pacotes[k], &fprio->pacotes[maior_pacote]);
        }
        ordenar(fprio, F_ESQ(k));
        if(F_DIR(k) < fprio->n){
            ordenar(fprio, F_DIR(k));
        }
    } 
}

void destruir_filaprio(p_fp fprio){
    free(fprio->pacotes);
    free(fprio);
}

int main(){
    int k, m;
    scanf("%d %d", &k, &m);

    p_fp fprio = criar_filaprio(m);

    int id, prioridade, incremento, tick;
    tick = 1;

    while(scanf("%d %d %d", &id, &prioridade, &incremento) != EOF){
        if(id == 0 && prioridade == 0 && incremento == 0){
            printf("TICK %d\n", tick);
            heapfy(fprio, k);
            for(int i = 0; i < fprio->n; i++){
                fprio->pacotes[i].prioridade += fprio->pacotes[i].incremento;
            }
            ordenar(fprio, 0);
            printf("\n");
            tick++;
        }
        else{
            if(fprio->n < fprio->tamanho){
                Pacote p;
                p.id = id;
                p.prioridade = prioridade;
                p.incremento = incremento;
            
                adicionar_pacote(fprio, p);
            }
        }
    }

    destruir_filaprio(fprio);

    return 0;
}