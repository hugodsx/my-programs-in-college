#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MaxSize 1000

typedef struct node{
    int num;
    struct node * link;
}ENODE;

typedef struct point{
    char data;
    ENODE * link;
}EDGE;

typedef struct Graph
{
    int num;
    EDGE E[MaxSize];
}MAP;

void CreateLink(MAP& G, int num1, int num2)
{
    ENODE* New = (ENODE*)malloc(sizeof(ENODE));
    ENODE* p = G.E[num1].link;
    while(p!=NULL && p->num != num2)    p = p->link;
    if(!p)
    {
        New->num = num2, New->link = NULL;
        New->link = G.E[num1].link;
        G.E[num1].link = New;
    }
}

void OutPut(EDGE E)
{
    ENODE *p = E.link;
    while(p!=NULL)
    {
        printf(" %d", p->num);
        p = p->link;
    }
    putchar('\n');
}

void BFS(MAP G)//i是当前顶点编号，j是输出顺序号
{
    int checked[G.num], i;
    memset(checked, 0, sizeof(checked));
    int sequence[G.num];
    int front = 0, rear = 0;
    for(i = 0 ; i < G.num ; i++)
    {
        if(checked[i] == 0)//没有搜索过这一个点
        {
            printf("%c", G.E[i].data);
            checked[i] = 1;
            sequence[rear++] = i;
            while(front < rear)
            {
                ENODE *p = G.E[sequence[front++]].link;
                while(p!=NULL)
                {
                    if(!checked[p->num])
                    {
                        printf("%c", G.E[p->num].data);
                        checked[p->num] = 1;
                        sequence[rear++] = p->num;
                    }
                    p = p->link;
                }
            }
        }   
    }
    putchar('\n');
}

int main()
{
    char ch = '#';
    MAP G;
    G.num = 0;
    while(ch != '*')
    {
        scanf("%c", &ch);
        if(ch == '*')   break;
        if(ch >= 'a' && ch <= 'z')
        {
            G.E[G.num].data = ch;
            G.E[G.num++].link = NULL;
        }
    }
    int num1 = 0, num2 = 0;
    while(true)
    {
        scanf("%d,%d", &num1, &num2);
        if(num1 == -1 && num2 == -1)    break;
        else
        {
            CreateLink(G, num1, num2);
            CreateLink(G, num2, num1);
        }
    }
    printf("the ALGraph is\n");
    int i;
    for(i = 0 ; i < G.num ; i++)
    {
        printf("%c", G.E[i].data);
        OutPut(G.E[i]);
    }
    printf("the Breadth-First-Seacrh list:");
    BFS(G);
    return 0;
}
