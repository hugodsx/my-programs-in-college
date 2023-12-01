#include<cstdio>
#include<cmath>

int MT[13][13], str[200], n;

void Get()
{
    int a;
    n = 0;
    while(scanf("%d",&a)!=EOF)
    {
        str[n++] = a;
    }
    n = (int)sqrt(n);
    int i, j, k = 0;
    for(i = 1 ; i <= n ; i++)
    {
        for(j = 1 ; j <= n ; j++)
        {
            MT[i][j] = str[k++];
        }
    }
}

void Warshall()
{
    int k, i, j;
    for(k = 1 ; k <= n ; k++)
    {
        for(i = 1 ; i <= n ; i++)
        {
            for(j = 1 ; j <= n ; j++)
            {
                if(MT[i][j] != 1)
                {
                    MT[i][j] = (MT[i][k] == 1 && MT[k][j] == 1);
                }
            }
        }
    }
}

void Output()
{
    int i, j;
    for(i = 1 ; i <=n ; i++)
    {
        for(j = 1 ; j <= n ; j++)
        {
            printf("%d", MT[i][j]);
            if(j == n)  printf("\n");
            else  printf(" ");
        }
    }
}

int main()
{
    Get();
    Warshall();
    Output();
    return 0;
}