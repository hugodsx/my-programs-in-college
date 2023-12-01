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

void InitStack(NODE* &);//��ʼ��
void Push(NODE* &, char, int);//��ջ
int Pop(NODE* &, char &, int &);//��ջ
int Top(NODE*, char &, int &);//����ջ��Ԫ��
bool IsEmpty(NODE*);//�ж��Ƿ�ջ��
int isp(char);//ջ�����ȼ�
int icp(char);//ջ�����ȼ�
bool is_op(char*, char*);//�ж��Ƿ�Ϊ�����
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

bool is_op(char *p, char *str)//Ĭ����ʽ��ȷ��������ж����Ƿ�Ϊ�����
{
    if(*p!='-')    return true;
    //p����λ��һ���Ǹ���
    if(p==str)   return false;
    char *ptest = p;
    while(ptest!=str)
    {
        --ptest;
        if(*ptest>='0'&&*ptest<='9')    return true;//ǰһλ�����֣�Ϊ�����
        if(*ptest!='('&&*ptest!=')')    return false;//ǰһλ�ǳ���������������������Ϊ����
    }
    return false;//ǰ��ȫ�����ţ����Ǹ���
}
//����Ժ����ж�Ҳ�а�����������������������������߸��ţ�Ҳ��������������������

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
            if(*p>'9'||*p<'0')//���ڷ���
            {
                count_op = (*p=='('||*p==')' ? 0 : 1);
                //���ж��Ƿ���Ч����ǰ�����ж�
                char *ptest = p + 1;
                for(; !isdigit(*ptest) && *ptest != '\0' ; ptest++)//���������ֻ����ַ���ĩβ��ʱ�����ѭ��
                {
                    if(*ptest=='('||*ptest==')'||*ptest=='#')    continue;//����ֱ���������������ŵ���Կ���������Ƿ�ջ��ʵ��
                    ++count_op;
                    if(count_op>=3)//������������
                    {
                        printf("error.\n");
                        flag = 0;
                        break;
                    }
                    if(is_op(p, str)==is_op(ptest, str)&&*p!='('&&*p!=')')//��������������ͬ
                    {
                        printf("error.\n");
                        flag = 0;
                        break;
                    }
                }
                if(!flag)   break;//����Ļ��˳�
                
                if(is_op(p, str))//����������
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
                    while(flag&&isp(op)>icp(ch))//�ڲ����ȼ��ߣ�Ҫ���
                    {
                        if(!Pop(s, op, temp_num))//ȡ�����ջ��
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        if(!Pop(n, temp_ch, num1))//ȡ����ջ��
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        if(!Pop(n, temp_ch, num2))//ȡ����ջ��
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        switch (op)//�ж������
                        {
                        case '+' : Push(n, temp_ch, num2 + num1); break;
                        case '-' : Push(n, temp_ch, num2 - num1); break;
                        case '*' : Push(n, temp_ch, num2 * num1); break;
                        case '/' :
                            if(num1==0)//����Ϊ0
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
                else//�Ǹ���
                {
                    g = 1;//�´ζ�����ʱ��g�����ǲ��Ǹ���
                }
            }
            else//��������
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