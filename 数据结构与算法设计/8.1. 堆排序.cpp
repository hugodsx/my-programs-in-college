#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXSIZE 100010
using namespace std;

int tree[MAXSIZE], N;

bool isleaf(int data)
{
    if(2*data + 1 > MAXSIZE)    return true;//左子树为空，由于层序存储则必为叶子节点
    if(tree[2*data + 1] == -1)  return true;
    return false;
}

void siftdown(int data)//建立大根堆
{
    if(tree[data] != -1  && !isleaf(data))//空节点和叶子节点默认完成下降
    {
        int temp = tree[2*data + 1] > tree[2*data + 2] ? 2*data + 1 : 2*data + 2;
        if(tree[temp] >tree[data])  swap(tree[temp], tree[data]);
        siftdown(2*data + 1);
        siftdown(2*data + 2);
    }
}

int main()
{
    
    scanf("%d", &N);
    for(int i = 0 ; i < N ; i++)
    {
        scanf("%d", &tree[i]);
    }
    for(int i = N ; i < MAXSIZE && i <= 2*(N-1) + 2 ; i++)
    {
        tree[i] = -1;
    }
    for(int i = N - 1 ; i >= 0 ; i--)
    {
        siftdown(i);
    }
    for(int i = 0 ; i < N ; i++)
    {
        printf("%d ", tree[i]);
    }
    putchar('\n');
    swap(tree[0], tree[N-1]);//第一次调整
    tree[N-1] = -1;
    for(int i = N - 2 ; i >= 0 ; i--)
    {
        siftdown(i);2
    }
    for(int i = 0 ; i < N - 1 ; i++)
    {
        printf("%d ", tree[i]);
    }
    putchar('\n');
    swap(tree[0], tree[N-2]);//第二次调整
    tree[N-2] = -1;
    for(int i = N - 3 ; i >= 0 ; i--)
    {
        siftdown(i);
    }
    for(int i = 0 ; i < N - 2 ; i++)
    {
        printf("%d ", tree[i]);
    }
    putchar('\n');
    return 0;
}