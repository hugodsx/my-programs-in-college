#include<cstdio>
#include<cstring>
#define INF 1000000000

int n, e;

void _D(int edge[][30], int begin)
{
    int i, j, k;
    int a[30][30], path[30][30];
    for(i = 0 ; i < n ; i++)
    {
        for(j = 0 ; j < n ; j++)
        {
            a[i][j] = edge[i][j];
            if(i != j && a[i][j] < INF) path[i][j] = i;
            else    path[i][j] = -1;
        }
    }
    for(k = 0 ; k < n ; k++)
    {
        for(i = 0 ; i < n ; i++)
        {
            for(j = 0 ; j < n ; j++)
            {
                if(a[i][j] > a[i][k] + a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    for(i = 0 ; i < n ; i++)
    {
        if(i == begin)  printf("%c:0\n", 'a' + begin);
        else
        {
            printf("%c:%d\n", 'a' + i, a[begin][i]);
        }
    }
}

int main()
{
    char begin;
    scanf("%d,%d,%c", &n, &e, &begin);
    int edge[30][30], e0, i, j;
    char n1, n2;
    for(i = 0 ; i < n ; i++)
    {
        for(j = 0 ; j < n ; j++)
        {
            edge[i][j] = INF;
        }
    }
    for(i = 0 ; i < n ; i++)
    {
        edge[i][i] = 0;
    }
    for(i = 0 ; i < e ; i++)
    {
        getchar();
        scanf("<%c,%c,%d>", &n1, &n2, &e0);
        edge[n1-'a'][n2-'a'] = e0;
    }
    int first = begin - 'a';
    _D(edge, first);
}