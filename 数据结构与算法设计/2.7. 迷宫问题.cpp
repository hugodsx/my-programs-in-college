#include<cstdio>
#include<cstdlib>

typedef struct Node{
    int x, y;
    struct Node * next;
} NODE;

void InitStack(NODE*&);
void Push(NODE*&, int, int);
void Pop(NODE*&, int*, int*);
void GetTop(NODE*&, int*, int*);
int StackEmpty(NODE*&);
void output(NODE*&);

void InitStack(NODE * &s)//初始化
{
    s = NULL;
}
void Push(NODE * &s, int x, int y)//入栈
{
    NODE * p = (NODE*)malloc(sizeof(NODE));
    p->x = x, p->y = y, p->next = s;
    s = p;
}
void Pop(NODE * &s, int * x, int * y)
{
    if(s==NULL)
    {
        printf("栈为空，出栈失败！\n");
        return;
    }
    *x = s->x, *y = s->y;
    NODE * p = s;
    s = p->next;
    free(p);
}
void GetTop(NODE * &s , int * x , int * y)
{
    if(s==NULL)
    {
        printf("栈为空，无法获得栈顶值！\n");
        return;
    }
    *x = s->x, *y = s->y;
}
int StackEmpty(NODE * &s)
{
    return (s==NULL);
}
void output(NODE * &s)//s为倒序插入，需正序输出
{
    NODE *head = NULL, *p;
    int tx, ty;
    while(!StackEmpty(s))
    {
        Pop(s, &tx, &ty);
        p = (NODE*)malloc(sizeof(NODE));
        p->x = tx, p->y = ty, p->next = head;
        head = p;
    }
    while(!StackEmpty(head))
    {
        Pop(head, &ty, &tx);
        printf("<%d,%d> ",tx+1, ty+1);
    }
    putchar('\n');
}

int main()
{
    int row, col;
    scanf("%d%d",&row,&col);
    int a[row][col], m[row][col], i, j;
    for(i = 0 ; i < row ; i++)
    {
        for(j = 0 ; j < col ; j++)
        {
            scanf("%d",&a[i][j]);
            m[i][j] = a[i][j];
        }
    }
    if(a[row-1][col-1]||a[0][0])
    {
        printf("There is no solution!\n");
        return 0;
    }//起点或者终点为障碍物，一定无解，直接结束

    NODE * s;
    InitStack(s);
    Push(s, 0, 0);//从起点开始出发
    while(!StackEmpty(s))//栈非空
    {
        int temp_x = -1, temp_y = -1;
        GetTop(s, &temp_x, &temp_y);//取栈顶值

        if(temp_x==col-1&&temp_y==row-1)//取出的值为终点值
        {
            output(s);
            return 1;
        }

        if(temp_y<row-1&&!m[temp_y+1][temp_x])//下侧是否可取
        {
            Push(s, temp_x, temp_y+1);
            m[temp_y][temp_x] = 2;
        }
        else if(temp_x<col-1&&!m[temp_y][temp_x+1])//右侧是否可取
        {
            Push(s, temp_x+1, temp_y);
            m[temp_y][temp_x] = 2;
        }
        else if(temp_y>0&&!m[temp_y-1][temp_x])//上侧是否可取
        {
            Push(s, temp_x, temp_y-1);
            m[temp_y][temp_x] = 2;
        }
        else if(temp_x>0&&!m[temp_y][temp_x-1])//左侧是否可取
        {
            Push(s, temp_x-1, temp_y);
            m[temp_y][temp_x] = 2;
        }
        else//上下左右均不可取，往回走
        {
            Pop(s, &temp_x, &temp_y);//将栈顶弹出
            m[temp_y][temp_x] = 1;//记录走过的错路
        }
    }
    return 0;
}