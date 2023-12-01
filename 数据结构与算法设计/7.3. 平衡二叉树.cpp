#include<cstdio>
#include<cstdlib>
#include<algorithm>
typedef struct tree
{
    char data;
    int height;
    struct tree *lchild, *rchild;
}AVLNode;

int calHeight(AVLNode * &anode)
{
    if(anode == nullptr)    return 0;
    return (calHeight(anode->lchild) > calHeight(anode->rchild) ? calHeight(anode->lchild) : calHeight(anode->rchild)) + 1;
}
AVLNode * RightRotation(AVLNode * &anode)//RR
{
    AVLNode *p = anode, *q = anode->lchild;
    p->lchild = q->rchild;
    q->rchild = p;
    return q;
}
AVLNode * LeftRotation(AVLNode * &anode)//LL
{
    AVLNode *p = anode, *q = anode->rchild;
    p->rchild = q->lchild;
    q->lchild = p;
    return q;
}
AVLNode * Insert(AVLNode * &anode, char input)
{
    if(anode == nullptr)
    {
        anode = (AVLNode*)malloc(sizeof(AVLNode));
        anode->data = input, anode->lchild = nullptr, anode->rchild = nullptr, anode->height = 1;
        return anode;
    }
    else
    {
        if(anode->data > input)
        {
            Insert(anode->lchild, input);
            //printf("%d ", calHeight(anode->lchild) - calHeight(anode->rchild));
            if(calHeight(anode->lchild) - calHeight(anode->rchild) > 1)//²»Æ½ºâ
            {
                if(input < anode->lchild->data)//LL
                {
                    anode = RightRotation(anode);
                }
                else//LR
                {
                    anode->lchild = LeftRotation(anode->lchild);
                    anode = RightRotation(anode);
                }
            }
            return anode;
        }
        else
        {
            Insert(anode->rchild, input);
            //printf("%d ", calHeight(anode->rchild) - calHeight(anode->lchild));
            if(calHeight(anode->rchild) - calHeight(anode->lchild) > 1)
            {
                if(input > anode->rchild->data)//RR
                {
                    anode = LeftRotation(anode);
                }
                else//RL
                {
                    anode->rchild = RightRotation(anode->rchild);
                    anode = LeftRotation(anode);
                }
            }
            return anode;
        }
    }
}
void Preorder(AVLNode * anode)
{
    if(anode)
    {
        printf("%c", anode->data);
        Preorder(anode->lchild);
        Preorder(anode->rchild);
    }
}
void Inorder(AVLNode * anode)
{
    if(anode)
    {
        Inorder(anode->lchild);
        printf("%c", anode->data);
        Inorder(anode->rchild);
    }
}
void Postorder(AVLNode * anode)
{
    if(anode)
    {
        Postorder(anode->lchild);
        Postorder(anode->rchild);
        printf("%c", anode->data);
    }
}
void OutPut(AVLNode * anode, int height)
{
    if(anode)
    {
        OutPut(anode->rchild, height + 1);
        for(size_t i = 0 ; i < height ; i++)
            printf("    ");
        printf("%c\n", anode->data);
        OutPut(anode->lchild, height + 1);
    }
}
AVLNode *atree;

int main()
{
    atree = nullptr;
    char input;
    while(true)
    {
        scanf("%c", &input);
        if(input == '\n') break;
        atree = Insert(atree, input);
    }
    printf("Preorder: ");
    Preorder(atree);
    printf("\n");
    printf("Inorder: ");
    Inorder(atree);
    printf("\n");
    printf("Postorder: ");
    Postorder(atree);
    printf("\n");
    printf("Tree:\n");
    OutPut(atree, 0);
    return 0;
}