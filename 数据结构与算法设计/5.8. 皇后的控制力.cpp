#include<cstdio>
#include<cstring>
#include <cstdlib>

int check(int i, int j, int chess[], int M)//δ�����Ʒ���0
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

int func(int N, int M, int chess[])//�ж��Ƿ�ȫ������
{
    int i = 0, j = 0, i1, j1;
    for(i = 0 ; i < N ; i++)
    {
        for(j = 0 ; j < N ; j++)
        {
            if(!check(i, j, chess, M))   return 0;//�ҵ�һ��δ�����Ƶ�λ��
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
        int k, l, i1, i2;//k�洢��ηŵĻʺ������У�l�洢������
        for(k = j + 1 ; k < N - (M - (i + 1)) - 1 ; ++k)//����һ�����ӷŵ��е���һ�У�����ʣ�µ��и��ܷ���ʣ�µ�����
        {
            for(l = 0 ; l < N ; ++l)//ÿ��ö��
            {
                i1 = 0;
                while(i1 < i - 1)//�����Ѿ��Ź�������
                {
                    if(*(chess + i1 + 10) == l)   break;//�����غ�
                    if(chess[i1] + chess[i1 + 10] == k + l || chess[i1] - chess[i1 + 10] == k - l)  break;
                    i1++;
                }
                if(i1 == i - 1)//�ж��Ƿ�����δ�غϹ�
                {
                    chess[i - 1] = k, chess[i - 1 + 10] = l;//��
                    Put(ans, N, M, chess, i, k);//��һ���ʺ�ķ���
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