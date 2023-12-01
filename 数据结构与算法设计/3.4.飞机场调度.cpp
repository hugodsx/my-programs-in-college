#include<stdio.h>
#include<stdlib.h>
typedef struct plane{
    int num;
    int WaitTime;
    struct plane * link;
} QUEUE;//�ɻ�����

typedef struct runway{
    int num;//�ɻ����
    char type;//��ʱ�ܵ�ռ�������ڽ��仹�����
    int busytime;//�ܵ���æʱ��
    int usedtime;//�ܵ�����ռ��ʱ��
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
//�������������
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
        printf("Current Time: %4d\n", CurrentTime++);//����ʱ������
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
        if(numLand >= 0 && numTakeof >= 0)//����Ҫ��ɺͽ���ķɻ���
        {
            scanf("%d %d", &numLand, &numTakeof);
        }
        for(i = 1 ; i <= numLand ; ++i)//Ҫ����ķɻ���ȴ�����
        {
            ++sumLand;
            Push(LandQueue, 5000 + sumLand, 0);
        }
        for(i = 1 ; i <= numTakeof ; ++i)//Ҫ��ɵķɻ���ȴ�����
        {
            ++sumTakeof;
            Push(TakeofQueue, sumTakeof, 0);
        }
        for(i = 0 ; i < N ; ++i)//�����ܵ�����
        {
            //����ʱ����ص����Ӷ����Ա���CurrentTime�Ƿ�æΪ��׼����æ��++
            if(Runway[i].num == 0)//�ܵ�����
            {
                if(!IsEmpty(LandQueue))//������зǿ�
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
                else    continue;//û���µ�����
            }
            else//�ܵ������У����ܻ��з�æ�����е�ת��
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