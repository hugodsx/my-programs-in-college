#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXSIZE 1000

typedef struct node{
    char data;
    struct node *lchild, *rchild;
}TREE;

void Create(TREE*&, char*, char*, int, int, int, int);
void output(TREE*);

void Create(TREE* &Bit, char* in, char* post, int begin_in, int begin_post, int end_in, int end_post)
{
    if(begin_in <= end_in)
    {    
        Bit = (TREE*)malloc(sizeof(TREE));
        char chpost = post[end_post];
        int i;
        for(i = begin_in ; i < end_in ; ++i)
        {
            if(in[i] == chpost)    break;
        }
        Bit->data = chpost;
        Bit->lchild = NULL;
        Bit->rchild = NULL;
        Create(Bit->lchild, in, post, begin_in, begin_post, i - 1, i - begin_in + begin_post - 1);
        Create(Bit->rchild, in, post, i + 1, begin_post + i - begin_in, end_in, end_post - 1);
    }
}

void output(TREE* Bit)
{
    struct queue
    {
        TREE * data;
        struct queue * link;
    }   *qu;
    qu = (struct queue*)malloc(sizeof(struct queue));
    qu->link = (struct queue*)malloc(sizeof(struct queue));
    qu->link->data = Bit, qu->link->link = NULL;
    struct queue *rear = qu->link;
    struct queue *p = qu->link;
    while(p != NULL)
    {
        putchar(p->data->data);
        if(p->data->lchild != NULL)
        {
            rear->link = (struct queue*)malloc(sizeof(struct queue));
            rear = rear->link;
            rear->data = p->data->lchild, rear->link = NULL;
        }
        if(p->data->rchild != NULL)
        {
            rear->link = (struct queue*)malloc(sizeof(struct queue));
            rear = rear->link;
            rear->data = p->data->rchild, rear->link = NULL;
        }
        qu->link = p->link;
        free(p);
        p = qu->link;
    }
}

int main()
{
    char *in = (char*)malloc(sizeof(char) * MAXSIZE);
    char *post = (char*)malloc(sizeof(char) * MAXSIZE);
    scanf("%s", in);
    scanf("%s", post);
    int begin_in = 0, begin_post = 0, end_in = strlen(in) - 1, end_post = strlen(post) - 1;
    TREE* BiTree;
    Create(BiTree, in, post, begin_in, begin_post, end_in, end_post);
    output(BiTree);
    printf("\n");
    return 0;
}