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
void Output(NODE*);
int Degree(NODE*);
int Count(NODE*, int);

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
void Output(NODE* G, int h)
{
    if(G)
    {
        if(G->tag == 1)
        {
            Output(G->info.hlink, h + 1);
            Output(G->tlink, h);
        }
        else
        {
            for(int i = 1 ; i < h ; ++i)
            {
                printf("    ");
            }
            printf("%c\n", G->info.ch);
        }
    }
}

int Degree(NODE* G)
{
    if(G)
    {
        int i = 0;
        if(G->tag == 1)
        {
            if(G->info.hlink->tag == 0)
            {
                NODE* p = G->tlink;
                while(p != NULL)
                {
                    ++i;
                    p = p->tlink;
                }
            }
            else
            {
                i = 0;
            }
            int i1 = Degree(G->tlink);
            int i2 = Degree(G->info.hlink);
            if(i < i1)    i = i1;
            if(i < i2)    i = i2;
            return i;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Count(NODE* G, int num)
{
    int ans = 0;
    if(G)
    {
        int i = 0;
        if(G->tag == 1)
        {
            if(G->info.hlink->tag == 0)
            {
                NODE* p = G->tlink;
                while(p != NULL)
                {
                    ++i;
                    p = p->tlink;
                }
            }
            else
            {
                i = -1;
            }
            if(i == num)    ++ans;
            int i1 = Count(G->tlink, num);
            int i2 = Count(G->info.hlink, num);
            ans += i1 + i2;
            return ans;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int main()
{
    char *s = (char*)malloc(sizeof(char) * 1000);
    scanf("%s", s);
    int i = 0;
    NODE *G;
    CreateGList(i, s, G);
    Output(G, 0);
    printf("Degree of tree: %d\n", Degree(G));
    for(i = 0 ; i <= Degree(G) ; ++i)
    {
        printf("Number of nodes of degree %d: %d\n", i, Count(G, i));
    }
    return 0;
}