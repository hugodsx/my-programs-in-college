#include<cstdio>
#include<cstdlib>
#define MAXSIZE 1000
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
} Tree;

void Create(Tree*, char*, int&);
void output(Tree*, int&);
void change(Tree*);
void pre(Tree*);
void in(Tree*);
void post(Tree*);
int count(Tree*);

void Create(Tree *BiT, char *s, int& i)
{
    if(BiT != NULL)
    {
        char ch = s[i++];
        if(ch != '#')
        {
            BiT->data = ch;
            BiT->lchild = (Tree*)malloc(sizeof(Tree));
            BiT->rchild = (Tree*)malloc(sizeof(Tree));
            Create(BiT->lchild, s, i);
            Create(BiT->rchild, s, i);
        }
        else
        {
            BiT->data = '#';
            BiT->lchild = NULL;
            BiT->rchild = NULL;
        }
    }
}

void output(Tree *BiT, int& j)
{
    
    if(BiT->data != '#')
    {
        int i = 0;
        while(i < j)
        {
            printf("   ");
            ++i;
        }
        i = 0;
        while(i < j)
        {
            putchar(' ');
            ++i;
        }
        printf("%c\n", BiT->data);
        ++j;
        output(BiT->lchild, j);
        output(BiT->rchild, j);
        --j;
    }
}

void change(Tree* BiT)
{
    Tree *p;
    if(BiT->data != '#')
    {
        change(BiT->lchild);
        change(BiT->rchild);
        p = BiT->lchild;
        BiT->lchild = BiT->rchild;
        BiT->rchild = p;
    }
}

void pre(Tree *BiT)
{
    if(BiT->data != '#')
    {
        printf("%c", BiT->data);
        pre(BiT->lchild);
        pre(BiT->rchild);
    }
}

void in(Tree *BiT)
{
    if(BiT->data != '#')
    {
        in(BiT->lchild);
        printf("%c", BiT->data);
        in(BiT->rchild);
    }
}

void post(Tree *BiT)
{
    if(BiT->data != '#')
    {
        post(BiT->lchild);
        post(BiT->rchild);
        printf("%c", BiT->data);
    }
}

int count(Tree *BiT)
{
    if(BiT->lchild->data == '#' && BiT->rchild->data == '#')
    {
        return 1;
    }
    else
    {
        return (BiT->lchild->data == '#' ? 0 : count(BiT->lchild)) + (BiT->rchild->data == '#' ? 0 : count(BiT->rchild));
    }
}

int main()
{
    char *str = (char*)malloc(sizeof(char) * MAXSIZE);
    int i = 0, j = 0;
    scanf("%s", str);
    Tree *BiTree = (Tree*)malloc(sizeof(Tree)), *p;
    Create(BiTree, str, i);
    printf("BiTree\n");
    output(BiTree, j);
    printf("pre_sequence  : ");
    pre(BiTree);
    putchar('\n');
    printf("in_sequence   : ");
    in(BiTree);
    putchar('\n');
    printf("post_sequence : ");
    post(BiTree);
    putchar('\n');
    printf("Number of leaf: %d\n", count(BiTree));
    change(BiTree);
    printf("BiTree swapped\n");
    j = 0;
    output(BiTree, j);
    printf("pre_sequence  : ");
    pre(BiTree);
    putchar('\n');
    printf("in_sequence   : ");
    in(BiTree);
    putchar('\n');
    printf("post_sequence : ");
    post(BiTree);
    putchar('\n');
    return 0;
}
