// #include<iostream>
// typedef struct node{
//     int data;
//     struct node *lchild, *rchild;
// }TREE;

// void Swap(int &a, int &b)
// {
//     a ^= b;
//     b ^= a;
//     a ^= b;
// }

// void Init(TREE* &tr)
// {
//     tr = nullptr;
// }

// void siftup(TREE* &tr, int x)
// {
//     if(tr == nullptr)
//     {
//         tr = new TREE();
//         tr->data = x, tr->lchild = nullptr, tr->rchild = nullptr;
//         return;
//     }
//     if(tr->data > x)//????
//     {
//         siftup(tr->lchild, x);
//     }
//     if(tr->data <= x)
//     {
//         siftup(tr->rchild, x);
//     }
// }

// int find(TREE *tr, int num, int &used)
// {
//     if(tr == nullptr)//???????????
//     {
//         return -1;
//     }
//     int ans = find(tr->lchild, num, used);
//     if(ans != -1)   return ans;//????????
//     used++;
//     if(used == num)  return tr->data;
//     return find(tr->rchild, num, used);
// }

// int main()
// {
//     int n = 0, x, y, used = 0, ans = 0;
//     char ch;
//     TREE *Bit;
//     Init(Bit);
//     while(std::cin >> x >> ch >> y)
//     {
//         siftup(Bit, y);
//         n++;
//     }
//     std::cout << find(Bit, (n-1)/2 + 1, used) << std::endl;
//     return 0;
// }

#include<iostream> 
#define MAXSIZE 2000010 
 
using namespace std; 
 
int arr[MAXSIZE], n = 0; 
int temp[MAXSIZE]; 
 
void Swap(int &a, int &b) 
{ 
    a ^= b; 
    b ^= a; 
    a ^= b; 
} 
 
int Median(int need, int l, int r) 
{ 
    int m = (l + r) / 2; 
    if(arr[l] < arr[r]) 
    { 
        Swap(arr[l], arr[r]); 
    } 
    if(arr[l] < arr[m]) 
    { 
        Swap(arr[l], arr[m]); 
    } 
    if(arr[m] < arr[r]) 
    { 
        Swap(arr[m], arr[r]); 
    } 
    int len = l - r; 
    if(need > l + len / 3 && need < l + 2 * len / 3) 
    { 
        Swap(arr[l], arr[m]); 
    } 
    else if(need > l + 2 * len / 3) 
    { 
        Swap(arr[l], arr[r]); 
    } 
    return arr[l]; 
} 
 
int find(int need, int l, int r) 
{ 
    int pivot = Median(need, l, r); 
    int i = l, j = r; 
    for(int k = l + 1 ; k <= r ; k++) 
    { 
        if(arr[k] < pivot) 
        { 
            temp[i++] = arr[k]; 
        } 
        else 
        { 
            temp[j--] = arr[k]; 
        } 
    } 
    if(j != i)  printf("error\n"); 
    else 
    { 
        temp[i] = pivot; 
        if(i == need)    return pivot; 
        else 
        { 
            if(i > need)//?????? 
            { 
                for(int k = l ; k < i ; k++) 
                { 
                    arr[k] = temp[k]; 
                } 
                return find(need, l, i - 1); 
            } 
            else//?????? 
            { 
                for(int k = r ; k > i ; k--) 
                { 
                    arr[k] = temp[k]; 
                } 
                return find (need, i + 1, r); 
            } 
        } 
    } 
    return -1; 
} 
 
int main() 
{ 
    char ch; 
    int x, y; 
    while(cin >> x >> ch >> y) 
    { 
        arr[n++] = y; 
    } 
    cout << find((n-1)/2, 0, n - 1) << endl; 
    return 0; 
} 