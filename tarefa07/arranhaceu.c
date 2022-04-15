#include <stdio.h>
#include <stdlib.h>

#define sim printf("sucesso\n")
#define nao printf("fracasso\n")

void proxima_posicao(int n, int l, int c, int *nl, int *nc){
    if(c + 1 == n + 1) {
        *nl = l + 1;
        *nc = 1;
    } else {
        *nc = c + 1;
        *nl = l;
    }
    return;
}

int visivel(int **m, int n, int l, int c, int v){
    for(int k = 0; k < 4; k++){
        int visiveis = 0;
        if(k == 0){
            int max = m[1][c];
            for(int i = 1; i < l; ++i){
                if(m[i][c] >= max){
                    max = m[i][c];
                    visiveis++;
                }
            }
            if(v > max){
                visiveis++;
            }
            if(visiveis > m[0][c]){
                return 0;
            }
        }
        if(k == 1){
            visiveis++;
            int max = v;
            for(int i = l; i > 0; i--){
                if(m[i][c] >= max){
                    max = m[i][c];
                    visiveis++;
                }
            }
            if(v > max){
                visiveis++;
            }
            if(visiveis > m[n +1][c] && l == n){
                return 0;
            }
        }
        if(k == 2){
            int max = m[l][1];
            for(int i = 1; i < c; ++i){
                if(m[l][i] >= max){
                    max = m[l][i];
                    visiveis++;
                }
            }
            if(v > max){
                visiveis++;
            }
            if(visiveis > m[l][0]){
                return 0;
            }
        }
        if(k == 3){
            visiveis++;
            int max = v;
            for(int i = c; i > 0; i--){
                if(m[l][i] >= max){
                    max = m[l][i];
                    visiveis++;
                }
            }
            if(v > max){
                visiveis++;
            }
            if(visiveis > m[l][n + 1] && c == n){
                return 0;
            }
        }
    }
    return 1;
}

int eh_valido(int **m, int n, int l, int c, int v){
    if(l == 1){
        if(v > n + 1 - m[0][c]){
            return 0;
        }
    }
    if(l == n){
        if(v > n + 1 - m[n+1][c]){
            return 0;
        }
    }
    
    if(c == 1){
        if(v > n + 1 - m[l][0]){
            return 0;
        }
    }
    if(c == n){
        if(v > n + 1 - m[l][n+1]){
            return 0;
        }
    }
    return 1;
}

int pode_inserir(int **m, int n, int l, int c, int v){
    if(l == 1 || l == n || c == 1 || c == n){
        if(!eh_valido(m, n, l, c, v)){
            return 0;
        }
    }
    for(int i = 1; i < n + 1; ++i){
        if(m[l][i] == v){
            return 0;
        }
        if(m[i][c] == v){
            return 0;
        }
    }
    if(!visivel(m, n, l, c, v)){
        return 0;
    }
    return 1;
}

void imprime_resolve(int **m, int n){
    for(int i = 1; i < n + 1; ++i){
        for(int j = 1; j < n + 1; ++j){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    return;
}

int resolve_r(int **m, int n, int l, int c){
    int nl, nc;
    if(l == n + 1){
        return 1;
    }
    proxima_posicao(n, l, c, &nl, &nc);

    for(int v = 1; v <= n; ++v){
        if(pode_inserir(m, n, l, c, v)){
            m[l][c] = v;
            if(resolve_r(m, n, nl, nc)){
                return 1;
            }
        }
    }
    m[l][c] = 0;
    return 0;
}

void resolve(int **m, int n){
    if(resolve_r(m, n, 1, 1)){
        imprime_resolve(m, n);
        return;
    }
}

int main(){
    int n;
    int **m;
    
    scanf("%d", &n);
        
    int l = n + 2;
    int c = n + 2;

    m = malloc(l * sizeof(int *));
    
    for(int i = 0; i < l; ++i){
        m[i] = calloc(c, sizeof(int));    
    }

    for(int i = 0; i < l; ++i){
        for(int j = 0; j < c; ++j){
             scanf("%d", &m[i][j]);
        }
    }

    resolve(m, n);
    for(int i = 0; i < n + 2; ++i){
        free(m[i]);
    }
    free(m);
    return 0;
}
