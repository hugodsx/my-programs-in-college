#include<cstdio>
#define MAXSIZE 101

int n, map[MAXSIZE][MAXSIZE];
bool vertex[MAXSIZE];

void Input(){
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d", &map[i][j]);
        }
    }
}

// void DFS(int begin, int end, int& flag1, int& flag2){
//     if(begin == end)    return;
//     vertex[begin] = 1;
//     for(int i = 0 ; i < n ; i++){
//         if(i == begin)  continue;
//         if(vertex[i] == 1)  continue;
//         if(map[begin][end] == 1)    return;
//         if(map[])
//     }
// }

int justify(){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            for(int k = 0 ; k < n ; k++){
                if(map[i][j] == 0){
                    if(map[i][k] == 1 && map[k][j] == 1){
                        map[i][j] = 1;
                    }
                }
            }
        }
    }
    int flag = 1;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(i == j)  continue;
            if(map[i][j] == 0){
                if(map[j][i] == 0)  return 3;
                flag = 2;
            }
        }
    }
    return flag;
}

void Output(){
    int ans = justify();
    if(ans == 1){
        printf("A\n");
    }
    if(ans == 2){
        printf("B\n");
    }
    if(ans == 3){
        printf("C\n");
    }
}

int main(){
    Input();
    Output();
    return 0;
}