#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<cstring>
#define MAXSIZE 50000
#define INF 2147483647

typedef struct st{
    char op;
    int data;
    struct st * next;
} NODE;

void InitStack(NODE* &);//初始化
void Push(NODE* &, char, int);//入栈
int Pop(NODE* &, char &, int &);//出栈
int Top(NODE*, char &, int &);//返回栈顶元素
bool IsEmpty(NODE*);//判断是否栈空
int isp(char);//栈内优先级
int icp(char);//栈外优先级
bool is_op(char*, char*);//判断是否为运算符
void InitStack(NODE* &s)
{
    s = NULL;
}

void Push(NODE* &s, char ch, int num)
{
    NODE* p = (NODE*)malloc(sizeof(NODE));
    p->next = s, p->op = ch, p->data = num;
    s = p;
}

int Pop(NODE* &s, char &ch, int &num)
{
    if(s==NULL)
    {
        return 0;
    }
    ch = s->op, num = s->data;
    NODE *p = s;
    s = p->next;
    free(p);
    return 1;
}

int Top(NODE* s, char &ch, int &num)
{
    if(s==NULL)
    {
        return 0 ;
    }
    ch = s->op, num = s->data;
    return 1;
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
        case '%' : return 5;
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
        case '%' : return 4;
        case '^' : return 7;
        case '(' : return 8;
        default: return -1;
    }
}

bool is_op(char *p, char *str)//默认算式正确情况进行判定其是否为运算符
{
    if(*p!='-')    return true;
    //p是首位，一定是负号
    if(p==str)   return false;
    char *ptest = p;
    while(ptest!=str)
    {
        --ptest;
        if(*ptest>='0'&&*ptest<='9')    return true;//前一位是数字，为运算符
        if(*ptest!='('&&*ptest!=')')    return false;//前一位是除了括号以外的运算符，其为负号
    }
    return false;//前面全是括号，则是负号
}
//这个对后面判定也有帮助，不能连续出现两个运算符或者负号，也不能连续出现三个符号

int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        NODE *s, *n;
        InitStack(s);
        Push(s, '#', INF);
        InitStack(n);
        char *str = (char*)malloc(sizeof(char) * MAXSIZE);
        scanf("%s",str);
        int len = strlen(str);
        str[len] = '#', str[len+1] = '\0';
        char ch = 0, op = 0, num = 0, *p = str, temp_ch;
        int flag = 1, count_op = 0, temp_num = INF, num1 = INF, num2 = INF, g = 0;
        for( ; *p != '\0' && flag; ++p)
        {
            if(*p>'9'||*p<'0')//对于符号
            {
                count_op = (*p=='('||*p==')' ? 0 : 1);
                //先判定是否有效，从前往后判定
                char *ptest = p + 1;
                for(; !isdigit(*ptest) && *ptest != '\0' ; ptest++)//在遇到数字或者字符串末尾的时候结束循环
                {
                    if(*ptest=='('||*ptest==')'||*ptest=='#')    continue;//括号直接跳过，关于括号的配对可以用最后是否栈空实现
                    ++count_op;
                    if(count_op>=3)//三个连续符号
                    {
                        printf("error.\n");
                        flag = 0;
                        break;
                    }
                    if(is_op(p, str)==is_op(ptest, str)&&*p!='('&&*p!=')')//两个符号类型相同
                    {
                        printf("error.\n");
                        flag = 0;
                        break;
                    }
                }
                if(!flag)   break;//错误的话退出
                
                if(is_op(p, str))//如果是运算符
                {
                    if(*p!='('&&*p!=')'&&p!=str&&*p!='#')
                    {
                        char *ptest = p - 1;
                        if(*ptest=='(')
                        {
                            printf("error.\n");
                            flag = 0;
                        }
                        while(flag&&ptest!=str&&(*ptest=='('||*ptest==')'))
                        {
                            --*ptest;
                        }
                        if(*ptest=='+'||*ptest=='-'||*ptest=='*'||*ptest=='/'||*ptest=='^')
                        {
                            if(flag)    printf("error.\n");
                            flag = 0;
                        }
                    }
                    Top(s, op, temp_num);
                    ch = *p;
                    while(flag&&isp(op)>icp(ch))//内部优先级高，要输出
                    {
                        if(!Pop(s, op, temp_num))//取运算符栈顶
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        if(!Pop(n, temp_ch, num1))//取数字栈顶
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        if(!Pop(n, temp_ch, num2))//取数字栈顶
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        switch (op)//判断运算符
                        {
                        case '+' : Push(n, temp_ch, num2 + num1); break;
                        case '-' : Push(n, temp_ch, num2 - num1); break;
                        case '*' : Push(n, temp_ch, num2 * num1); break;
                        case '/' :
                            if(num1==0)//除数为0
                            {   
                                printf("Divide 0.\n");
                                flag = 0;
                            }
                            else
                            {
                                Push(n, temp_ch, num2 / num1);
                            }
                            break;
                        case '%' :
                            Push(n, temp_ch, num2 % num1); break;
                        case '^' :
                        if(num1 < 0)
                        {
                            printf("error.\n");
                            flag = 0;
                        }
                        else
                        {
                            Push(n, temp_ch, pow((double)num2, (double)num1));
                        }
                        break;
                        default: printf("error.\n"); flag = 0;
                        }
                        Top(s, op, temp_num);
                    }
                    if(!flag)   break;
                    if(isp(op)==icp(ch)&&(ch==')'||ch=='#'))
                    {
                        Pop(s, temp_ch, temp_num);
                    }
                    else
                    {
                        Push(s, ch, INF);
                    }
                }
                else//是负号
                {
                    g = 1;//下次读数的时候，g代表是不是负数
                }
            }
            else//对于数字
            {
                char *ptest = p;
                temp_num = 0;
                while(*ptest>='0'&&*ptest<='9')
                {
                    temp_num *= 10;
                    temp_num += *ptest - '0';
                    ++ptest;
                }
                p = ptest - 1;
                if(g)
                {
                    temp_num = 0 - temp_num;
                    g = 0;
                }
                Push(n, '\0', temp_num);
            }
        }
        if(flag)
        {
            if(Pop(n, temp_ch, temp_num)==0)
            {
                printf("error.\n");
            }  
            else if(!IsEmpty(n)||!IsEmpty(s))
            {
                printf("error.\n");
            }
            else
            {
                printf("%d\n",temp_num);
            }
        }
        free(str);
        free(s);
        free(n);
    }
    return 0;
}