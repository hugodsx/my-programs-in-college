#include<cstdio>
#include<cstdlib>

typedef struct node
{
    int tag;
    int ref;
    union
    {
        char ch;//tag = 0,ԭ�ӱ�
        struct node *hlink;//tag = 1,��ͷָ��
    } info;
    struct node *tlink;
} NODE;

void CreateGList(int&, char *, NODE *&);
void printGList(NODE *);
NODE* GetHead(NODE *);
NODE* GetTail(NODE *);
void DestroyGList(NODE *&);

void CreateGList(int& i, char *s, NODE *& g)//g���ݵĿ�����hlinkҲ������ָ���β��tlink,��ʼ���ܱ���G
{
    char ch = s[i++];
    if(ch != '\0')
    {
        if(ch == '(')//��ʼ������ͷ�ڵ�
        {
            if(s[i] == ')')    {g = NULL; ++i;}//�ձ�
            else
            {
                g = (NODE*)malloc(sizeof(NODE));
                g->ref = 0, g->tag = 1;
                CreateGList(i, s, g->info.hlink);
                CreateGList(i, s, g->tlink);
            }
        }
        else if(ch == ')')
            g = NULL;
        else if(ch == ',')//�б�β�ڵ�
        {
            g = (NODE*)malloc(sizeof(NODE));
            g->ref = 0, g->tag = 1;
            CreateGList(i, s, g->info.hlink);//g�ı�β��ͷ�ڵ㽨��
            CreateGList(i, s, g->tlink);//g�ı�β�ı�β�ڵ㽨��
        }
        else
        {
            g = (NODE*)malloc(sizeof(NODE));
            g->tag = 0, g->ref = 0;
            g->info.ch = ch;
        }   
    }
}

void printGList(NODE *g)
{
    if(g)//�ǿ�
    {    if(g->tag == 1)//��ͷ���
        {
            if(g->info.hlink ==NULL || g->info.hlink->tag == 1)
                putchar('(');//˵����ͷ���ӱ��������
            printGList(g->info.hlink);//�����ͷ
            if(g->info.hlink ==NULL || g->info.hlink->tag == 1)  
                putchar(')');
            if(g->tlink)//�б�β
            {
                putchar(',');
                printGList(g->tlink);
            }
        }
        else//ԭ�ӽ��
        {
            putchar(g->info.ch);
        }
    }
}

NODE* GetHead(NODE* g)
{
    NODE *q = (NODE*)malloc(sizeof(NODE));
    q->tag = g->tag, q->info = g->info, q->ref = g->ref;
    q->tlink = NULL;
    if(q->tag == 1)
        q = q->info.hlink;
    return q;
}

NODE* GetTail(NODE* g)
{
    return g->tlink;
}

void DestroGList(NODE*& g)
{
    if(g)
    {
        if(g->tag == 0)    {free(g);g = NULL;}
        else
        {
            NODE *h = g->info.hlink, *t = g->tlink;
            DestroGList(h);
            if(t)
                DestroGList(t);
            free(g);
            g = NULL;
        }
    }
}

int main()
{
    char *s = (char*)malloc(sizeof(char) * 1000);
    scanf("%s", s);
    int i = 0, form = 0;
    NODE *G, *p;
    CreateGList(i, s, G);
    do
    {
        if(form == 1)//ȡ��ͷ��ɾ��β
        {
            printf("destroy tail\n");
            p = GetTail(G);
            G = GetHead(G);
            DestroGList(p);
            printf("free list node\n");
        }
        else if(form == 2)
        {
            printf("free head node\n");
            p = GetHead(G);
            G = GetTail(G);
            DestroGList(p);
            printf("free list node\n");
        }
        printf("generic list: ");
        if(G == NULL || G->tag != 0)    putchar('(');
        printGList(G);
        if(G == NULL || G->tag != 0)    putchar(')');
        printf("\n");
        if(G && G->tag != 0)    scanf("%d", &form);
    }while(G && G->tag != 0);//G�ǿ��ҷ�ԭ�ӽ��
    return 0;
}
