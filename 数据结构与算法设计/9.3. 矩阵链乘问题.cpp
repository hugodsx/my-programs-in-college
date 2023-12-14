#include<cstdio>
#define MAXSIZE 110

int m[MAXSIZE][MAXSIZE], s[MAXSIZE][MAXSIZE], p[MAXSIZE], n;

void output(int i, int j){
    if(i == j){
        printf("A%d", i);
        return;
    }
    else{
        printf("(");
        output(i, s[i][j]);
        output(s[i][j] + 1, j);
        printf(")");
        return;
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 0 ; i <= n ; i++){
        scanf("%d", &p[i]);
    }
    if(n == 1){
        printf("0\n");
        printf("(A1)\n");
        return 0;
    }
    
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            if(i != j){
                m[i][j] = 2147483647;
            }
            if(i == j - 1){
                m[i][j] = p[i - 1] * p[i] * p[i + 1];
                s[i][j] = i;
            }
        }
    }

    for(int j = 2 ; j <= n ; j++){
        for(int i = j - 1 ; i >= 1 ; i--){
            for(int k = i; k < j ; k++){
                if(m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]){
                    m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    s[i][j] = k;
                }
            }
        }
    }

    printf("%d\n", m[1][n]);
    output(1, n);
    printf("\n");
    return 0;
}