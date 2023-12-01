 #include<cstdio>
 #include<cstdlib>

typedef struct tree
{
    int data;
    int stage;
    struct tree * lchild;
    struct tree * rchild;
}Bitree;

Bitree * Tree;
int n;

void Create(Bitree *& tr, int stage)
{
    if(tr == NULL)
    {
        tr = (Bitree*)malloc(sizeof(Bitree));
        tr->data = n, tr->stage = stage, tr->lchild = NULL, tr->rchild = NULL;
    }
    else
    {
        if(n < tr->data)
        {
            Create(tr->lchild, stage + 1);
        }
        else
        {
            Create(tr->rchild, stage + 1);
        }
    }
}

void MidOrder(Bitree * tr)
{
    if(tr != NULL)
    {
        MidOrder(tr->lchild);
        for(int i = 0 ; i < tr->stage ; i++)
        {
            printf("    ");
        }
        printf("%d\n", tr->data);
        MidOrder(tr->rchild);
    }
}

void Output(Bitree * tr)
{
    if(tr != NULL)
    {
        Output(tr->lchild);
        printf(" %d", tr->data);
        Output(tr->rchild);
    }
}

int main()
{
    Tree = NULL;
    while(true)
    {
        scanf("%d", &n);
        if(n == 0)  break;
        Create(Tree, 0);
    }
    MidOrder(Tree);
    printf("\n");
    Output(Tree);
    putchar('\n');
    return 0;
}
