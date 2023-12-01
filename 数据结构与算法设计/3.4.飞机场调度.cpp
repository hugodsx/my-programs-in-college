#include<stdio.h>
#include<stdlib.h>
typedef struct plane{
    int num;
    int WaitTime;
    struct plane * link;
} QUEUE;//飞机队列

typedef struct runway{
    int num;//飞机编号
    char type;//此时跑道占用是用于降落还是起飞
    int busytime;//跑道繁忙时间
    int usedtime;//跑道本次占用时间
}ARRAY;

void Push(QUEUE *PLANE, int num, int WaitTime)
{
    QUEUE * p = PLANE;
    while(p->link!=NULL)    p = p->link;
    p->link = (QUEUE*)malloc(sizeof(QUEUE));
    p->link->num = num, p->link->WaitTime = WaitTime, p->link->link = NULL;
}

void Pop(QUEUE *PLANE)
{
    QUEUE * p = PLANE;
    QUEUE *pp = p->link;
    p->link = pp->link;
    free(pp);
}

int IsEmpty(QUEUE *PLANE)
{
    return PLANE->link == NULL;
}
//降落优先于起飞
int main()
{
    int N, LandTime, TakeofTime, CurrentTime = 0, LandWaitTime = 0, TakeofWaitTime = 0, numLand = 0, numTakeof = 0, sumLand = 0, sumTakeof = 0;
    int i, flag = 1;
    scanf("%d %d %d", &N, &LandTime, &TakeofTime);
    QUEUE *LandQueue = (QUEUE*)malloc(sizeof(QUEUE)), *TakeofQueue = (QUEUE*)malloc(sizeof(QUEUE));
    LandQueue->num = -1, LandQueue->link = NULL, TakeofQueue->num = -1, TakeofQueue->link = NULL;
    ARRAY Runway[N];
    for(i = 0 ; i < N ; ++i)
    {
        Runway[i].busytime = 0;
        Runway[i].num = 0;
        Runway[i].type = '*';
        Runway[i].usedtime = 0;
    }
    while(numLand >= 0 || numTakeof >= 0 || !IsEmpty(LandQueue) || !IsEmpty(TakeofQueue) || flag)
    {
        flag = 0;
        printf("Current Time: %4d\n", CurrentTime++);//现在时间的输出
        for(i = 0 ; i < N ; ++i)
        {
            if(Runway[i].type == 'L' && Runway[i].usedtime == LandTime)
            {
                printf("runway %02d is free\n", i + 1);
                Runway[i].num = 0, Runway[i].type = '*', Runway[i].usedtime = 0;
            }
            if(Runway[i].type == 'T' && Runway[i].usedtime == TakeofTime)
            {
                printf("runway %02d is free\n", i + 1);
                Runway[i].num = 0, Runway[i].type = '*', Runway[i].usedtime = 0;
            }
        }
        if(numLand >= 0 && numTakeof >= 0)//输入要起飞和降落的飞机数
        {
            scanf("%d %d", &numLand, &numTakeof);
        }
        for(i = 1 ; i <= numLand ; ++i)//要降落的飞机入等待队列
        {
            ++sumLand;
            Push(LandQueue, 5000 + sumLand, 0);
        }
        for(i = 1 ; i <= numTakeof ; ++i)//要起飞的飞机入等待队列
        {
            ++sumTakeof;
            Push(TakeofQueue, sumTakeof, 0);
        }
        for(i = 0 ; i < N ; ++i)//搜索跑道数组
        {
            //所有时间相关的增加都是以本次CurrentTime是否繁忙为基准，繁忙则++
            if(Runway[i].num == 0)//跑道空闲
            {
                if(!IsEmpty(LandQueue))//降落队列非空
                {
                    flag = 1;
                    Runway[i].num = LandQueue->link->num;
                    LandWaitTime += LandQueue->link->WaitTime;
                    Pop(LandQueue);
                    Runway[i].type = 'L';
                    ++Runway[i].usedtime;
                    ++Runway[i].busytime;
                    printf("airplane %04d is ready to land on runway %02d\n", Runway[i].num, i + 1);
                }
                else if(!IsEmpty(TakeofQueue))
                {
                    flag = 1;
                    Runway[i].num = TakeofQueue->link->num;
                    TakeofWaitTime += TakeofQueue->link->WaitTime;
                    Pop(TakeofQueue);
                    Runway[i].type = 'T';
                    ++Runway[i].usedtime;
                    ++Runway[i].busytime;
                    printf("airplane %04d is ready to takeoff on runway %02d\n", Runway[i].num, i + 1);
                }
                else    continue;//没有新的请求
            }
            else//跑道不空闲，可能会有繁忙到空闲的转变
            {
                flag = 1;
                ++Runway[i].busytime;
                ++Runway[i].usedtime;
            }
        }
        QUEUE *p = LandQueue->link;
        while(p!=NULL)
        {
            ++p->WaitTime;
            p = p->link;
        }
        p = TakeofQueue->link;
        while(p!=NULL)
        {
            ++p->WaitTime;
            p = p->link;
        }
    }

    printf("simulation finished\n");
    printf("simulation time: %4d\n", --CurrentTime);
    printf("average waiting time of landing: %4.1f\n", (float)LandWaitTime / sumLand);
    printf("average waiting time of takeoff: %4.1f\n", (float)TakeofWaitTime / sumTakeof);
    float sumbusytime = 0;
    for(i = 0 ; i < N ; ++i)
    {
        printf("runway %02d busy time: %4d\n", i + 1, Runway[i].busytime);
        sumbusytime += Runway[i].busytime;
    }
    printf("runway average busy time percentage: %4.1f%\n", sumbusytime * 100 / N / CurrentTime);
}