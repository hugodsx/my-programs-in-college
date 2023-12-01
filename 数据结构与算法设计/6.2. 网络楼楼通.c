#include<stdio.h>
#include<string.h>

int a[3000][3], b[3000][3], c[3000][3], f[1001];

int find(int k)
{
    if(f[k] == k)   return k;
    return f[k] = find(f[k]);
}

void QuickSort(int edge[][3], int l, int r)
{
    if(l>=r-1)    return;
    int num = edge[(r-l)/2 + l][2], i;
    int la = 0, lb = 0, lc = 0;
    for(i = l ; i <= r ; i++)
    {
        if(edge[i][2]<num)
        {
            a[la][0] = edge[i][0];
            a[la][1] = edge[i][1];
            a[la++][2] = edge[i][2];
        }  
        else if(edge[i][2]>num)
        {
            c[lc][0] = edge[i][0];
            c[lc][1] = edge[i][1];
            c[lc++][2] = edge[i][2];
        }
        else
        {
            b[lb][0] = edge[i][0];
            b[lb][1] = edge[i][1];
            b[lb++][2] = edge[i][2];
        }
    }
    for(i = 0 ; i < la ; i++)
    {
        edge[i + l][0] = a[i][0];
        edge[i + l][1] = a[i][1];
        edge[i + l][2] = a[i][2];
    }
    for(i = 0 ; i < lb ; i++)
    {
        edge[i + l + la][0] = b[i][0];
        edge[i + l + la][1] = b[i][1];
        edge[i + l + la][2] = b[i][2];
    }
    for(i = 0 ; i < lc ; i++)
    {
        edge[i + l + la + lb][0] = c[i][0];
        edge[i + l + la + lb][1] = c[i][1];
        edge[i + l + la + lb][2] = c[i][2];
    }
    QuickSort(edge, l, l + la - 1);
    QuickSort(edge, l + la + lb, r);
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int i, edge[3000][3];
    for(i = 1 ; i <= N ; i++)
    {
        f[i] = i;
    }
    for(i = 0 ; i < M ; i++)
    {
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);
    }
    QuickSort(edge, 0, M - 1);
    int sum = 0, sum_edge = 0;
    for(i = 0 ; i < M ; i++)
    {
        int num1 = edge[i][0], num2 = edge[i][1];
        if(find(num1) != find(num2))//建立新边
        {
            f[find(num1)] = find(num2);//归并到同一并查集
            //printf("%d  ", edge[i][2]);
            sum += edge[i][2];
            sum_edge++;
        }
        if(sum_edge == N - 1)   break;
    }
    if(sum_edge == N-1) printf("%d\n", sum);
    else printf("-1\n");
    return 0;
}