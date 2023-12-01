#include<cstdio>
#include<cstring>

void copy(int* source, int* stick, int n)
{
    int j = 0;
    for(j = 0 ; j < n ; ++j)
    {
        stick[j] = source[j];
    }
}

void find(int c, int n, int w[], int min[], int& ans, int& sum, int* list, int i, int* temp)
{
    if(i < n)
    {
        int t = temp[i];
        sum += w[i];
        temp[i] = 1;
        if(sum > ans && sum <= c)
        {
            copy(temp, list, n);
            ans = sum;
        }
        if(sum + min[i + 1] <= c)
        {
            find(c, n, w, min, ans, sum, list, i + 1, temp);
        }
        sum -= w[i];
        temp[i] = 0;
        find(c, n, w, min, ans, sum, list, i + 1, temp);
        temp[i] = t;
    }
}

int main()
{
    int c, n;
    scanf("%d%d", &c, &n);
    int w[n], i, min[n];//min存后面所有数中最小的，max存后面所有数中最大的
    for(i = 0 ; i < n ; ++i)
    {
        scanf("%d",&w[i]);
    }
    for(i = n - 1 ; i >= 0 ; --i)
    {
        if(i == n - 1)
        {
            min[i] = w[i];
        }
        else
        {
            min[i] = (w[i] < min[i+1] ? w[i] : min[i+1]);
        }
    }
    int ans = 0, sum = 0, list[100] = {0}, temp[100] = {0};
    find(c, n, w, min, ans, sum, list, 0, temp);
    printf("%d\n", ans);
    for(i = 0 ; i < n ; ++i)
    {
        if(list[i] != 0)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    return 0;
}