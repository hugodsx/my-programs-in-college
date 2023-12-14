#include<iostream>
#include<cstring>
#define MAXSIZE 201
using namespace std;

int a[MAXSIZE][MAXSIZE], n, dp[MAXSIZE][MAXSIZE];

int main(){
    cin >> n;
    for(int i = 0 ; i < n - 1 ; i++){
        for(int j = i + 1 ; j < n ; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(i != j)
                dp[i][j] = 2147483647;
        }
    }
    
    for(int i = 0 ; i < n - 1; i++){
        for(int j = i + 1 ; j < n ; j++){
            for(int k = i ; k < j ; k++){
                if(dp[i][j] > dp[i][k] + a[k][j])   dp[i][j] = dp[i][k] + a[k][j];
            }
        }
    }
    printf("%d\n", dp[0][n-1]);
    return 0;
}