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
        }//初始化
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
                //正
                SumOfEdge[tpoint]++;
                Edge[tpoint][rear[tpoint]] = current;
                rear[tpoint]++;
                //反
            }
        }//树的存储
        int Sum = 0;
        while(Sum < N)
        {
            for(k = 0 ; k < N ; k++)
            {
                if(SumOfEdge[k] == 0)//孤立点
                {
                    Sum++;
                    ans++;
                    SumOfEdge[k] = -1;//-1表示用过了
                }
                if(SumOfEdge[k] == 1)
                {
                    Sum++, ans++;
                    SumOfEdge[k] = -1;//边数为1的节点的删除
                    current = Edge[k][0];//父节点，需要：删除自身，删除与之相邻的节点，与 父节点相邻节点 相邻的节点需 删除父节点相邻节点
                    
                    Sum++;
                    SumOfEdge[current] = -1;//删除父节点自身
                    for(i = 0 ; i < rear[current] ; i++)//删父节点相邻节点，但是度超过1的不能删
                    {
                        if(SumOfEdge[Edge[current][i]] != -1)//与之相邻的节点没有被删除
                        {
                            if(SumOfEdge[Edge[current][i]] == 1)
                            {
                                Sum++, tpoint = Edge[current][i];
                                SumOfEdge[tpoint] = -1;//删除与父节点相邻节点
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