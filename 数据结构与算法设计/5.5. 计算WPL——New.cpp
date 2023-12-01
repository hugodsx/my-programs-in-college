#include<cstdio>
#include<cstdlib>
#define leaf 500
#define total 999
#define MAX 2147483647
typedef struct 
{
    int weight;
    int parent, lchild, rchild;
}HTNODE;
typedef struct 
{
    HTNODE element[total];
    int num, root;
}HFTREE;
void CreateHFTree(HFTREE&, int*, int);
int WPL(HFTREE, int, int);

void CreateHFTree(HFTREE& HF, int* fr, int n)
{
    int i, k, s1, s2, min1, min2;
    for(i = 0 ; i < n ; ++i)
    {
        HF.element[i].weight = fr[i];
    }
    for(i = 0 ; i < leaf ; ++i)
    {
        HF.element[i].parent = -1, HF.element[i].rchild = -1, HF.element[i].lchild = -1;
    }
    for(i = n ; i < 2*n-1 ; ++i)
    {
        min1 = MAX, min2 = MAX;
        s1 = 0, s2 = 0;
        for(k = 0 ; k < i ; ++k)
        {
            if(HF.element[k].parent == -1)
            {
                if(HF.element[k].weight < min1)
                {
                    min2 = min1;
                    min1 = HF.element[k].weight;
                    s2 = s1;
                    s1 = k;
                }
                else if(HF.element[k].weight < min2)
                {
                    min2 = HF.element[k].weight;
                    s2 = k;
                }
            }
        }
        HF.element[s1].parent = i, HF.element[s2].parent = i;
        HF.element[i].lchild = s1, HF.element[i].rchild = s2;
        HF.element[i].weight = HF.element[s1].weight + HF.element[s2].weight;
    }
    HF.num = n, HF.root = 2*n - 2;
}

int WPL(HFTREE HF, int root, int i)
{
    if(HF.element[root].lchild == -1 && HF.element[root].rchild == -1)
    {
        return HF.element[root].weight * i;
    }
    else
    {
        int i1 = WPL(HF, HF.element[root].lchild, i + 1);
        int i2 = WPL(HF, HF.element[root].rchild, i + 1);
        return i1 + i2;
    }
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int* fr = (int*)malloc(sizeof(int) * n);
    for(i = 0 ; i < n ; ++i)
    {
        scanf("%d", &fr[i]);
    }
    HFTREE HfTree;
    CreateHFTree(HfTree, fr, n);
    printf("WPL=%d\n", WPL(HfTree, HfTree.root, 0));
    return 0;
}

