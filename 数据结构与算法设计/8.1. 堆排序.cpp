#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXSIZE 100010
using namespace std;

int tree[MAXSIZE], N;

bool isleaf(int data)
{
    if(2*data + 1 > MAXSIZE)    return true;//������Ϊ�գ����ڲ���洢���ΪҶ�ӽڵ�
    if(tree[2*data + 1] == -1)  return true;
    return false;
}

void siftdown(int data)//���������
{
    if(tree[data] != -1  && !isleaf(data))//�սڵ��Ҷ�ӽڵ�Ĭ������½�
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
    swap(tree[0], tree[N-1]);//��һ�ε���
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
    swap(tree[0], tree[N-2]);//�ڶ��ε���
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