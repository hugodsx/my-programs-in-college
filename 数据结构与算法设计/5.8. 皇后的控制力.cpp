#include<cstdio>
#include<cstring>
#include <cstdlib>

int check(int i, int j, int chess[], int M)//未被控制返回0
{
    int k;
    for(k = 0 ; k < M ; k++)
    {
        if(i == chess[k])   return 1;
        if(j == chess[k + 10])  return 1;
        if(chess[k] + chess[k + 10] == i + j)   return 1;
        if(chess[k] - chess[k + 10] == i - j)   return 1;
    }
    return 0;
}

int func(int N, int M, int chess[])//判定是否全部控制
{
    int i = 0, j = 0, i1, j1;
    for(i = 0 ; i < N ; i++)
    {
        for(j = 0 ; j < N ; j++)
        {
            if(!check(i, j, chess, M))   return 0;//找到一个未被控制的位置
        }
    }
    return 1;
}

void Put(int& ans, int N, int M, int chess[], int i, int j)
{
    if(i == M)
    {
        ans += func(N, M, chess);
    }
    else
    {
        ++i;
        int k, l, i1, i2;//k存储这次放的皇后所在行，l存储所在列
        for(k = j + 1 ; k < N - (M - (i + 1)) - 1 ; ++k)//从上一个棋子放的行的下一行，到还剩下的行刚能放完剩下的棋子
        {
            for(l = 0 ; l < N ; ++l)//每列枚举
            {
                i1 = 0;
                while(i1 < i - 1)//对于已经放过的棋子
                {
                    if(*(chess + i1 + 10) == l)   break;//列数重合
                    if(chess[i1] + chess[i1 + 10] == k + l || chess[i1] - chess[i1 + 10] == k - l)  break;
                    i1++;
                }
                if(i1 == i - 1)//判断是否列数未重合过
                {
                    chess[i - 1] = k, chess[i - 1 + 10] = l;//放
                    Put(ans, N, M, chess, i, k);//下一个皇后的放置
                }
            }
        }
    }
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int chess[22];
    memset(chess, -1, sizeof(chess));
    int ans = 0, i = 0 , j = -1;
    Put(ans, N, M, chess, i, j);
    printf("%d\n", ans);
    return 0;
}