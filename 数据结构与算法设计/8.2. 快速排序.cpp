#include<cstdio>
#define MAXSIZE 100
#define swap Swap
using namespace std;

int list[MAXSIZE], n = 0;
int Median[MAXSIZE], idx = 0;

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Input()
{
    char ch = '#';
    int flag = 1;
    ch = getchar();
    while(ch != '#')
    {
        if(ch == '-')   flag = -1;
        if(ch >= '0' && ch <= '9')
        {
            list[n] *= 10;
            list[n] += ch - '0';
        }
        if(ch == '\n')
        {
            list[n] *= flag;
            n++, flag = 1;
        }
        ch = getchar();
    }
}

int median(int l, int r)
{
    int m = (l + r)/2;
    if (list[l] > list[m])
        swap(list[l], list[m]);
    if (list[l] > list[r])
        swap(list[l], list[r]);
    if (list[m] > list[r])
        swap(list[m], list[r]);
    swap(list[l], list[m]);
    return list[l];
}

void InsertSort(int l, int r) {
    int i, j, temp;
    for(i = l + 1; i <= r; i++) {
        j = i;
        temp = list[i];
        while(j > l && list[j - 1] > temp) {
            list[j] = list[j - 1];
            j--;
        }
        list[j] = temp;
    }
}

void QuickSort(int l, int r)
{
    if(l < r)
    {
        if(r - l + 1 <= 5)
        {
            InsertSort(l, r);
        }
        else
        {
            int pivot = median(l, r);
            Median[idx++] = pivot;
            int i = l + 1, j = r;
            while(i < j)
            {
                while(i < j && list[i] < pivot) i++;
                while(i < j && list[j] > pivot) j--;
                if(i < j)
                {
                    swap(list[i], list[j]);
                    i++, j--;
                }   
            }
            if(list[i] <= list[l])
            {
                list[l] = list[i];
                list[i] = pivot;
            }
            else
            {
                swap(list[l], list[--i]);
            }
            QuickSort(l, i - 1);
            QuickSort(i + 1, r);
        }
    }
}

int main()
{
    n = 0, idx = 0;
    Input();
    QuickSort(0, n - 1);
    printf("After Sorting:\n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("%d ", list[i]);
    }
    putchar('\n');
    printf("Median3 Value:\n");
    if(idx == 0)
    {
        printf("none\n");
    }
    else
    {
        for(int i = 0 ; i < idx ; i++)
        {
            printf("%d ", Median[i]);
        }
        printf("\n");
    }
    return 0;
}