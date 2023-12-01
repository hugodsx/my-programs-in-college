#include<cstdio>
#include<cstdlib>

typedef struct node
{
    int tag;
    int ref;
    union
    {
        char ch;//tag = 0,原子表
        struct node *hlink;//tag = 1,表头指针
    } info;
    struct node *tlink;
} NODE;

void CreateGList(int&, char *, NODE *&);
void printGList(NODE *);
NODE* GetHead(NODE *);
NODE* GetTail(NODE *);
void DestroyGList(NODE *&);

void CreateGList(int& i, char *s, NODE *& g)//g传递的可以是hlink也可以是指向表尾的tlink,初始是总表名G
{
    char ch = s[i++];
    if(ch != '\0')
    {
        if(ch == '(')//开始建立表头节点
        {
            if(s[i] == ')')    {g = NULL; ++i;}//空表
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
        else if(ch == ',')//有表尾节点
        {
            g = (NODE*)malloc(sizeof(NODE));
            g->ref = 0, g->tag = 1;
            CreateGList(i, s, g->info.hlink);//g的表尾的头节点建立
            CreateGList(i, s, g->tlink);//g的表尾的表尾节点建立
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
    if(g)//非空
    {    if(g->tag == 1)//表头结点
        {
            if(g->info.hlink ==NULL || g->info.hlink->tag == 1)
                putchar('(');//说明表头有子表，输出括号
            printGList(g->info.hlink);//输出表头
            if(g->info.hlink ==NULL || g->info.hlink->tag == 1)  
                putchar(')');
            if(g->tlink)//有表尾
            {
                putchar(',');
                printGList(g->tlink);
            }
        }
        else//原子结点
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
        if(form == 1)//取表头，删表尾
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
    }while(G && G->tag != 0);//G非空且非原子结点
    return 0;
}
