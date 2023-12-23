#include<cstdio>
#include<cstring>

int Rank(int Z, int a){
    int ans = 0, list[Z], init = a;
    memset(list, 0, sizeof(list));
    while(list[a] == 0){
        ans++, list[a] = 1;
        a += init;
        a %= Z;
    }
    return ans;
}

int main(){
    int Z, a;
    scanf("%d£¬%d", &Z, &a);
    printf("%d\n", Rank(Z, a));
    return 0;
}