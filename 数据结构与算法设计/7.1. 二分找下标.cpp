#include<cstdio>
#define MAXSIZE 1000010

int arr[MAXSIZE];

int main()
{
    int n;
    bool flag = false;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(int i = 0 ; i < n ; i++)
    {
        if(i == arr[i])
        {
            printf("%d ", i);
            flag = true;
        }
    }
    if(flag == false)   {printf("No ");}
    putchar('\n');
    return 0;
}