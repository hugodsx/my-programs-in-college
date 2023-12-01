#include<cstdio>
#include<cstring>
#define MAXSIZE 1501

int Edge[MAXSIZE][MAXSIZE], SumOfEdge[MAXSIZE], N, rear[MAXSIZE], ans;

int main()
{
    int i, j, k;
    while((scanf("%d", &N)) != EOF)
    {
        ans = 0;
        if(N == 1)  {printf("1\n"); continue;}
        for(i = 0 ; i < N ; i++)
        {
            rear[i] = 0;
            SumOfEdge[i] = 0;
            for(j = 0 ; j < N ; j++)
            {
                Edge[i][j] = -1;
            }
        }//��ʼ��
        int current, tedge, tpoint;
        for(i = 0 ; i < N ; i++)
        {
            scanf("%d:(%d)", &current, &tedge);
            SumOfEdge[current] += tedge;
            for(j = 0 ; j < tedge ; j++)
            {
                scanf("%d", &tpoint);
                Edge[current][rear[current]] = tpoint;
                rear[current]++;
                //��
                SumOfEdge[tpoint]++;
                Edge[tpoint][rear[tpoint]] = current;
                rear[tpoint]++;
                //��
            }
        }//���Ĵ洢
        int Sum = 0;
        while(Sum < N)
        {
            for(k = 0 ; k < N ; k++)
            {
                if(SumOfEdge[k] == 0)//������
                {
                    Sum++;
                    ans++;
                    SumOfEdge[k] = -1;//-1��ʾ�ù���
                }
                if(SumOfEdge[k] == 1)
                {
                    Sum++, ans++;
                    SumOfEdge[k] = -1;//����Ϊ1�Ľڵ��ɾ��
                    current = Edge[k][0];//���ڵ㣬��Ҫ��ɾ������ɾ����֮���ڵĽڵ㣬�� ���ڵ����ڽڵ� ���ڵĽڵ��� ɾ�����ڵ����ڽڵ�
                    
                    Sum++;
                    SumOfEdge[current] = -1;//ɾ�����ڵ�����
                    for(i = 0 ; i < rear[current] ; i++)//ɾ���ڵ����ڽڵ㣬���Ƕȳ���1�Ĳ���ɾ
                    {
                        if(SumOfEdge[Edge[current][i]] != -1)//��֮���ڵĽڵ�û�б�ɾ��
                        {
                            if(SumOfEdge[Edge[current][i]] == 1)
                            {
                                Sum++, tpoint = Edge[current][i];
                                SumOfEdge[tpoint] = -1;//ɾ���븸�ڵ����ڽڵ�
                            }
                            else
                            {
                                SumOfEdge[Edge[current][i]]--;
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}