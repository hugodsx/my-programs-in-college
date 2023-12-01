#include<cstdio>
#include<cstring>
#include<cstdlib>

int ans = 0, sum = 0;
void Best(int A[][12], int n, int i, int*& dp, int *max)
{
    int j, k, l;
    if(i == n)
    {
        if(sum > ans)
        {
            ans = sum;
        }
        //memset(dp, -1, sizeof(dp));
    }
    else
    {
        for(j = 0 ; j < n ; ++j)
        {
            for(k = 0 ; k <= i ; ++k)
            {
                if(dp[k] == j)    break;
            }
            if(k == i + 1)
            {
                if(i == n - 1 || sum + A[i][j] + max[i + 1] > ans)
                {
                    dp[i] = j;
                    sum += A[i][j];
                    Best(A, n, i + 1, dp, max);
                    sum -= A[i][j];
                    dp[i] = -1;
                }
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int P[n][n], Q[n][n];
    int i, j;
    for(i = 0 ; i < n ; ++i)
    {
        for(j = 0 ; j < n ; ++j)
        {
            scanf("%d", &P[i][j]);
        }
    }
    for(i = 0 ; i < n ; ++i)
    {
        for(j = 0 ; j < n ; ++j)
        {
            scanf("%d", &Q[i][j]);
        }
    }
    int A[12][12], max[12] = {0};
    for(i = 0 ; i < n ; ++i)
    {
        for(j = 0 ; j < n ; ++j)
        {
            A[i][j] = P[i][j] * Q[j][i];
            if(max[i] < A[i][j])    max[i] = A[i][j];
        }
    }
    for(i = 0 ; i < n - 1 ; ++i)
    {
        for(j = i + 1 ; j < n ; ++j)
        {
            max[i] += max[j];
        }
    }
    int* dp = (int*)malloc(sizeof(int) * 12);
    memset(dp, -1, sizeof(dp));
    Best(A, n, 0, dp, max);
    printf("%d\n", ans);
    return 0;
}