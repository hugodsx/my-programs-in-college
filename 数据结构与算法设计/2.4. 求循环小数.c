/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
void output( NODE *, int );  
void change( int, int, NODE * );  
  
void output( NODE * head, int kk )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<kk )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");  
}
  
int main()  
{   int n, m,k;  
    NODE * head;  
  
    scanf("%d%d%d", &n, &m, &k);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head,k );  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  

change( int n, int m, NODE * head ) 
{
    int flag = 1, len = 1, temp = 10;
    NODE * p = head;
    typedef struct memory{
        int data;
        int no;
        struct memory * next;
    }MEM;
    MEM mem[10], *q;//mem[i]存储了n%10的顺序数
    for(int j = 0 ; j < 10 ; j++)
    {
        (mem[j]).data = -1, (mem[j]).no = 0,(mem[j]).next = NULL;
    }

    while(n&&flag)//！flag表示找到了循环节
    {
        temp = n;//排查n是否已经出现
        q = &(mem[temp%10]);//q
        while(q->next!=NULL)//找寻是否出现过相同的除数
        {
            if(q->next->data==temp)//出现过
            {
                NODE * pp = head;//去找其位置
                for(int i = 1 ; i <= q->next->no ; ++i)
                {
                    pp = pp->next;
                    if(pp==NULL)
                    {
                        printf("pp为空\n");
                        exit(-1);
                    }    
                }
                p->next = pp;
                flag = 0;
                break;
            }
            q = q->next;
        }
        if(flag&&q->next==NULL)//其表明未出现过，则要将他放入链表中
        {
            q->next = (MEM*)malloc(sizeof(MEM));
            q = q->next;
            q->data = n, q->no = len, q->next = NULL;
            ++len;
            p->next = (NODE*)malloc(sizeof(NODE));
            p = p->next;
            n *= 10;
            p->data = n/m, p->next = NULL;
            n %= m;
        }
    }
}