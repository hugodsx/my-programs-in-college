#include<iostream>
#include<algorithm>
#define MAXSIZE 100
int n, a[MAXSIZE][MAXSIZE], dp[MAXSIZE][MAXSIZE];
using namespace std;

int Max(int row, int col)
{
    if(col == 0)//三角形某行最左列
        return dp[row-1][col] + a[row][col];
    if(col == row)//三角形某行最右列
        return dp[row-1][col-1] + a[row][col];
    return max(dp[row-1][col-1], dp[row-1][col]) + a[row][col];
}

int main()
{
    cin >> n;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j <= i ; j++)
        {
            cin >> a[i][j];
        }
    }
    dp[0][0] = a[0][0];
    for(int i = 1 ; i < n ; i++)
    {
        for(int j = 0 ; j <= i ; j++)
        {
            dp[i][j] = Max(i, j);
        }
    }
    int ans = 0;
    for(int i = 0 ; i < n ; i++)
    {
        ans = max(ans, dp[n-1][i]);
    }
    printf("%d\n", ans);
    return 0;
}