#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 1000

typedef struct word{
    int value[26];
    struct word * next;
}NODE;

int alphacount(char *s, char *alphalist)
{
    memset(alphalist, 0, sizeof(alphalist));
    int length = 0;
    char *p = s, *pa = alphalist;
    for(p = s ; *p != '\0' ; ++p)
    {
        if(isalpha(*p))
        {
            for(pa = alphalist ; *pa != '\0' ; ++pa)
            {
                if(*p == *pa)    break;
            }
            if(*pa == '\0')    {*pa = *p; ++length;}
        }
    }
    return length;
}

void Init(NODE* S0, char* s, char* alphalist, int length)
{
    int i = 0, j = 0, flag = 0, minus = 1;
    NODE* pp = S0;
    for(i = 0 ; s[i] != '\0' ; ++i)
    {
        if(s[i]>='a' && s[i] <= 'z')
        {
            if(!flag)//�µĽ��
            {
                NODE *p = (NODE*)malloc(sizeof(NODE));
                memset(p->value, 0, sizeof(p->value));
                for(j = 0 ; alphalist[j] != '\0' ; ++j)
                {
                    if(alphalist[j] == s[i])
                    {
                        p->value[j] = minus;
                        minus = 1;
                        break;
                    }
                }
                if(alphalist[j] == '\0')    printf("error! -1\n");
                pp->next = p;
                p->next = NULL;
                flag = 1;
            }
            else//����
            {
                for(j = 0 ; alphalist[j] != '\0' ; ++j)
                {
                    if(alphalist[j] == s[i])
                    {
                        if(pp->next->value[j] == 0)   pp->next->value[j] = minus;
                        else//��������ʽ��ֱ�Ӻ��ԣ�ɾ�����еĴ洢�ռ�ͬʱ��s[i]�Ƶ����ʵ�λ��
                        {
                            free(pp->next);
                            pp->next = NULL;
                            while(s[i+1] != '(' && s[i+1] != '\0')    ++i;
                        }
                        minus = 1;
                        break;
                    }
                }
                if(alphalist[j] == '\0')    printf("error! -2\n");
            }
        }
        else if(s[i] == '|')    continue;
        else if(s[i] == '(' || s[i] == ')')    continue;
        else if(s[i] == '&')
        {
            flag = 0;
            pp = pp->next;
        }
        else if(s[i] == '!')    minus = -1;
        else    printf("not checked! -3\n");
    }
}

void connect(NODE* S0, NODE* S1)//S1����S0����
{
    NODE *p = S0;
    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = S1->next;
    S1->next = NULL;
}

void dispel(NODE* S0, NODE* S1, int length)
{
    if(S0->next == NULL || S0->next->next == NULL)
    {
        printf("YES\n");
    }
    else
    {
        NODE *p = S0->next, *pp = S0->next, *ppp = S0->next, *_new, *rear = S1;
        int i, j, k;
        while(p != NULL)
        {
            pp = p->next;//pΪ������ppΪ������
            while(pp != NULL)//�Ƚ϶��߶�Ӧ��ʽ��
            {
                for(i = 0 ; i < length ; ++i)
                {
                    if(pp->value[i] + p->value[i] == 0 && pp->value[i] != 0)//�ҵ���һ����һ���ĸ�ֵ
                    {
                        _new = (NODE*)malloc(sizeof(NODE));
                        memset(_new->value, 0, sizeof(_new->value));
                        _new->next = NULL;
                        break;
                    }
                }
                if(i != length)//�½����µĽڵ�
                {
                    for(j = 0 ; j < length ; ++j)
                    {
                        if(p->value[j] != 0 && pp->value[j] == 0)
                        {
                            _new->value[j] = p->value[j];
                        }
                        else if(p->value[j] == 0 && pp->value[j] != 0)
                        {
                            _new->value[j] = pp->value[j];
                        }
                        else if(p->value[j] != 0 && pp->value[j] != 0)
                        {
                            if(p->value[j] == pp->value[j])
                            {
                                _new->value[j] = p->value[j];
                            }
                            else if(i != j)//�½��Ľڵ�������ʽ
                            {
                                free(_new);
                                _new = NULL;
                                flag = 1;
                                break;
                            }
                        }
                    }
                    if(j == length && i != length)//�½��˽ڵ��ҽڵ���ȷ��ֵ
                    {
                        ppp = S0;
                        while(ppp->next != NULL)//���Ƿ�����ͬ�ڵ�
                        {
                            for(k = 0 ; k < length ; ++k)
                            {
                                if(ppp->next->value[k] != _new->value[k])
                                {
                                    break;//�˳�����Ϊ�в�ͬ
                                }
                            }
                            if(k == length)//����ͬ��
                            {
                                break;
                            }
                            else//������ͬ��
                            {
                                ppp = ppp->next;
                            }
                        }
                        if(ppp->next == NULL)//û�ҵ���ͬ��
                        {
                            rear->next = _new;//��S1�������½ڵ�
                            rear = rear->next;
                            rear->next = NULL;
                        }
                    }
                }
                pp = pp->next;
            }
            p = p->next;
        }
        //����S1���½ڵ�
        p = S1->next;
        if(p == NULL)
        {
            printf("YES\n");
        }
        else
        {
            while(p!=NULL)
            {
                for(i = 0 ; i < length ; ++i)
                {
                    if(p->value[i] != 0)    break;
                }
                if(i != length)    p = p->next;
                else
                {
                    printf("NO\n");
                    S1->next = NULL;
                    break;
                }
            }
        }
    }
}

int main()
{
    char *s = (char*)malloc(sizeof(char) * MAXSIZE);
    char *alphalist = (char*)malloc(sizeof(char) * 26);
    scanf("%s", s);
    int length = alphacount(s, alphalist);
    NODE *S0, *S1;
    S0 = (NODE*)malloc(sizeof(NODE)), S1 = (NODE*)malloc(sizeof(NODE));
    S0->next = NULL, S1->next = NULL;
    memset(S0->value, 0, sizeof(S0->value));
    memset(S1->value, 0, sizeof(S1->value));
    Init(S0, s, alphalist, length);
    do
    {
        connect(S0, S1);
        dispel(S0, S1, length);
    } while (S1->next != NULL);
    
}