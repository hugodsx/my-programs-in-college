#include<cstdio>
#define MAXSIZE 200

int n, map[MAXSIZE][MAXSIZE], vertex[MAXSIZE], begin;

void Input(){
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d", &map[i][j]);
        }
    }
}

bool DFS(int i, int length){
    if(vertex[i] != 0){
        if(i != begin)  return true;
        return length%2 == 0;
    }
    vertex[i] = 1;
    for(int j = 0 ; j < n ; j++){
        if(i == j)  continue;
        if(map[i][j] != 0){
            map[i][j]--;
            if(DFS(j, length + 1) == false) return false;
            vertex[j] = 0;
            map[i][j]++;
            vertex[begin] = 1;
        }
    }
    return true;
}

bool find(){
    for(int i = 0 ; i < n ; i++){
        if(map[i][i] != 0)  return false;
    }
    for(int i = 0 ; i < n ; i++){
        begin = i;
        if(DFS(i, 0) == false) return false;
    }
    return true;
}

void Output(){
    if(find())  printf("yes\n");
    else printf("no\n");
}

int main(){
    Input();
    Output();
    return 0;
}