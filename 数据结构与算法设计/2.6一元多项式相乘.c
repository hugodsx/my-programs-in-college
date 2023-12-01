/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  
  
void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
             sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    if ( flag == 1 )  
             {    x = sign * sum;  
                  sum = 0;  
                  flag = 2;  
          sign = 1;  
             }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
//coefΪϵ����expΪָ��

void multiplication( NODE * h1, NODE * h2, NODE * h3 )
{
    NODE *p1 = h1, *p2 = h2, *p3 = h3, *pp;
    int temp_co = 0, temp_ex = 0, flag = 0;
    while(p1->next!=NULL)//����1����
    {
        p1 = p1->next;
        //���¿�ʼ��h2�ı���
        while(p2->next!=NULL)//����2����
        {
            p2 = p2->next;
            temp_co = p1->coef * p2->coef, temp_ex = p1->exp + p2->exp;//�洢��

            //����Ϊ��h3�Ĳ���
            while(p3->next!=NULL)//��ѯ����3
            {
                if(p3->next->exp > temp_ex &&(p3 == h3 || p3->exp < temp_ex))//���������д���temp_ex���޵��ڵģ������½ڵ�
                {
                    pp = (NODE*)malloc(sizeof(NODE));
                    pp->coef = temp_co, pp->exp = temp_ex;
                    pp->next = p3->next;
                    p3->next = pp;
                    flag = 0;
                    break;
                }

                if(p3->next->exp==temp_ex)//�ҵ����ڵģ��ӽ�ȥ
                {
                    p3->next->coef += temp_co;
                    flag = 1;
                    break;
                }
                
                p3 = p3->next;//ѭ������
            }
            if(p3->next==NULL&&!flag)//flag���Բ�����    
            {
                p3->next = (NODE*)malloc(sizeof(NODE));
                p3 = p3->next;
                p3->coef = temp_co, p3->exp = temp_ex, p3->next = NULL;
            }
            //����Ϊ��h3�Ĳ���
            flag = 0;
        }
        //���Ͻ���h2�ı���
        p2 = h2, p3 = h3;
    }

    p3 = h3;
    while(p3->next!=NULL)//��ʼɾ��h3��ϵ��Ϊ0�Ľڵ�
    {
        if(p3->next->coef==0)
        {
            pp = p3->next;
            p3->next = pp->next;
            free(pp);
        }
        else
        {
            p3 = p3->next;
        }
    }
    if(h3->next==NULL)//h3Ϊ�ձ�ʱ�Ĵ���
    {
        h3->next = (NODE*)malloc(sizeof(NODE));
        h3->next->coef = 0, h3->next->exp = 0, h3->next->next = NULL;
    }
}