#include<cstdio>
#include<cstdlib>

int Pow(int, int);
void count(int, int, long int&);

void count(int n, int m, long int& ans)
{
    n -= m;
    if(n > 1)
    {
        int h = 2;
        while(n > Pow(2, h) - 2)    ++h;
        ans += Pow(2, h-2);
        n -= (Pow(2, h-1) - 1) - (h - 1 - 1);
        count(n, h - 2, ans);
    }
    else if(n == 1)
    {
        ans += 1;
        --n;
    }
}

int Pow(int a, int n)
{
    int ans = 1;
    int i;
    for(i = 1 ; i <= n ; ++i)
    {
        ans *= a;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n ,m;
        scanf("%d%d", &n, &m);
        long int ans = 0;
        if(m <= 30 && n >= Pow(2, m + 1) - 1)
        {
            ans = Pow(2, m) ;
            n = 0;
        }
        else
        {
            while(n > 0)
            {
                n -= m;
                if(n > 1)
                {
                    int h = 2;
                    while(n > Pow(2, h) - 2)    ++h;
                    ans += Pow(2, h-2);
                    n -= (Pow(2, h-1) - 1) - (h - 1 - 1);
                    m = h - 2;
                }
                else if(n == 1)
                {
                ans += 1;
                --n;
                }
            }
            
        }
        printf("%d\n", ans);
    }
    return 0;
}