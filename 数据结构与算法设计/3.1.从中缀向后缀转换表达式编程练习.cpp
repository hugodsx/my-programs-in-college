#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXSIZE 50000
typedef struct st{
    char op;
    struct st * next;
} NODE;

void InitStack(NODE* &);//初始化
void Push(NODE* &, char ch);//入栈
void Pop(NODE* &, char &ch);//出栈
void Top(NODE*, char &ch);//返回栈顶元素
bool IsEmpty(NODE*);//判断是否栈空
int isp(char ch);//栈内优先级
int icp(char ch);//栈外优先级

void InitStack(NODE* &s)
{
    s = NULL;
}

void Push(NODE* &s, char ch)
{
    NODE* p = (NODE*)malloc(sizeof(NODE));
    p->next = s, p->op = ch;
    s = p;
}

void Pop(NODE* &s, char &ch)
{
    if(s==NULL)
    {
        return;
    }
    ch = s->op;;
    NODE *p = s;
    s = p->next;
    free(p);
}

void Top(NODE* s, char &ch)
{
    if(s==NULL)
    {
        return;
    }
    ch = s->op;
}

bool IsEmpty(NODE* s)
{
    return s==NULL;
}

int isp(char ch)
{
    switch(ch)
    {
        case '#' : return 0;
        case '(' : return 1;
        case '+' : return 3;
        case '-' : return 3;
        case '*' : return 5;
        case '/' : return 5;
        case '^' : return 7;
        case ')' : return 8;
        default : return -1;
    }
}

int icp(char ch)
{
    switch (ch)
    {
        case '#' : return 0;
        case ')' : return 1;
        case '+' : return 2;
        case '-' : return 2;
        case '*' : return 4;
        case '/' : return 4;
        case '^' : return 7;
        case '(' : return 8;
        default: return -1;
    }
}

int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        char ch = '\0', op = '\0', temp = '\0';
        char *str = (char*)malloc(sizeof(char) * MAXSIZE);
        int i = 0;
        NODE *s;
        scanf("%s",str);
        InitStack(s);
        Push(s, '#');
        for(i = 0 ; str[i] !='\0'; i++)
        {
            if(i >= MAXSIZE)
            {
                //printf("数组越界！\n");
                break;
            }
            if(str[i]>='A'&&str[i]<='Z')
            {
                printf("%c",str[i]);
            }
            else if(str[i]>='a'&&str[i]<='z')
            {
                printf("%c",str[i]);
            }
            else
            {
                Top (s, op);
                ch = str[i];
                while(isp(op)>icp(ch))
                {
                    Pop(s, temp);//输出栈顶
                    printf("%c",temp);
                    Top(s, op);//重新取头元素
                }
                if(isp(op)==icp(ch)&&ch==')')
                {
                    Pop(s, temp);
                }
                else
                {
                    Push(s, ch);
                }
            }
        }
        putchar('\n');
        free(str);
        free(s);
    }
    return 0;
}