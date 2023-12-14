#include<cstdio>
#include<algorithm>
#define MAXSIZE 105

int dp[MAXSIZE][MAXSIZE], n, s[MAXSIZE], Sum[MAXSIZE][MAXSIZE], front[MAXSIZE];

int sum(int a, int b){
    if(b > a){
        return front[b] - front[a] + s[a];
    }
    return (front[n - 1] - (front[a] - front[b] - s[a]));
}

int main(){
    scanf("%d", &n);
    int i, j, k;
    for(i = 0 ; i < n ; i++){
        scanf("%d", &s[i]);
        front[i] = i == 0 ? s[i] : s[i] + front[i - 1];
    }
    if(n == 1){
        printf("%d\n", s[0]);
        printf("%d\n", s[0]);
        return 0;
    }
    for(i = 0 ; i < n ; i++){
        for(j = i ; j < n ; j++){
            if(i != j)
                dp[i][j] = 2147483647;
        }
    }

    for(j = 1 ; j < n ; j++){//最小
        for(i = 0 ; i < n ; i++){
            int temp = sum(i, (i+j)%n);
            Sum[i][(i+j)%n] = temp;
            dp[i][(i+j)%n] = dp[i][i] + dp[(i+1)%n][(i+j)%n] + temp;
            for(int k = i + 1; k < i + j ; k++){
                if(dp[i][(i+j)%n] > (dp[i][k%n] + dp[(k+1)%n][(i+j)%n]) + temp){
                    dp[i][(i+j)%n] = (dp[i][k%n] + dp[(k+1)%n][(i+j)%n]) + temp;
                }
            }
        }
    }
    int ans = dp[0][n-1];
    for(i = 1 ; i < n ; i++){
        if(ans > dp[i][(i+n-1)%n])
            ans = dp[i][(i+n-1)%n];
    }
    printf("%d\n", ans);
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            if(i != j)
                dp[i][j] = -1;
            else
                dp[i][j] = 0;
        }
    }
    for(j = 1 ; j < n ; j++){//最大
        for(i = 0 ; i < n ; i++){
            dp[i][(i+j)%n] = dp[i][i] + dp[(i+1)%n][(i+j)%n] + Sum[i][(i+j)%n];
            for(int k = i + 1; k < i + j ; k++){
                if(dp[i][(i+j)%n] < (dp[i][k%n] + dp[(k+1)%n][(i+j)%n]) + Sum[i][(i+j)%n]){
                    dp[i][(i+j)%n] = (dp[i][k%n] + dp[(k+1)%n][(i+j)%n]) + Sum[i][(i+j)%n];
                }
            }
        }
    }
    ans = dp[0][n-1];
    for(i = 1 ; i < n ; i++){
        if(ans < dp[i][(i+n-1)%n])
            ans = dp[i][(i+n-1)%n];
    }
    printf("%d\n", ans);
    return 0;
}