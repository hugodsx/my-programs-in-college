#include<cstdio>

int N;
char list[100], map[100][100];

int find(char ch){
    for(int i = 0 ; i < N ; i++){
        if(list[i] == ch)   return i;
    }
    return -1;
}

void Input(){
    scanf("%d", &N);
    getchar();
    for(int i = 0 ; i < N ; i++){
        scanf("%c", &list[i]);
        getchar();
    }
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            scanf("%c", &map[i][j]);
            getchar();
        }
    }
}

bool Commutativecal(){
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(i == j) continue;
            if(map[i][j] != map[j][i])
                return false;
        }
    }
    return true;
}

bool Associatecal(){
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            for(int k = 0 ; k < N ; k++){
                if(map[find(map[i][j])][k] != map[i][find(map[j][k])])
                    return false;
            }
        }
    }
    return true;
}

bool Idemponentcal(){
    for(int i = 0 ; i < N ; i++){
        if(map[i][i] != list[i])    return false;
    }
    return true;
}

void Output(bool ans, int type){
    if(type == 1){
        printf("commutative law:");
    }
    if(type == 2){
        printf("associative law:");
    }
    if(type == 3){
        printf("idempotent law:");
    }
    if(ans){
        printf("y\n");
    }
    else{
        printf("n\n");
    }
}

void Identityfind(){
    printf("identity element:");
    int i, j;
    for(i = 0 ; i < N ; i++){
        for(j = 0 ; j < N ; j++){
            if(map[i][j] != list[j])    break;
        }
        if(j == N){
            printf("%c\n", list[i]);
            return;
        }  
    }
    printf("n\n");
}

void Zerofind(){
    printf("zero element:");
    int i, j;
    for(i = 0 ; i < N ; i++){
        for(j = 0 ; j < N ; j++){
            if(map[i][j] != list[i])    break;
        }
        if(j == N){
            printf("%c\n", list[i]);
            return;
        }
    }
    printf("n\n");
}


int main(){
    Input();
    Output(Commutativecal(), 1);
    Output(Associatecal(), 2);
    Output(Idemponentcal(), 3);
    Identityfind();
    Zerofind();
    return 0;
}