#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

vector<char> list;
queue<char> Max;
queue<char> Min;
int map[20][20], n;

void search(int& num, char& ch, int type)
{
    if(type == 1)//知道ch找num
    {
        int i;
        for(i = 0 ; i < list.size() ; i++)
        {
            if(list[i] == ch)
            {
                num = i;
                break;
            }
        }
    }
    if(type == 2)
    {
        ch = list[num];
    }
}

void input()
{
    char ch;
    while(true)
    {
        scanf("%c", &ch);
        if(ch == '\n')  break;
        if(ch == ',')   continue;
        if(ch >= 'a' && ch <= 'z')
        {
            list.push_back(ch);
        }
    }
    memset(map, 0, sizeof(map));
    while(true)
    {
        scanf("%c", &ch);
        if(ch == '\n')  break;
        if(ch == ',' || ch == '>')   continue;
        if(ch == '<')
        {
            char ch1, ch2;
            scanf("%c,%c", &ch1, &ch2);
            int num1 = 0, num2 = 0;
            search(num1, ch1, 1);
            search(num2, ch2, 1);
            map[num1][num2] = 1;
        }
    }
}

void find()//col有非0不能极小，row有非0不能极大
{
    int i, j;
    for(i = 0 ; i < n ; i++)//找极小
    {
        for(j = 0 ; j < n ; j++)
        {
            if(j != i && map[j][i] != 0)    break;
        }
        if(j == n)
        {
            char ch;
            search(i, ch, 2);
            Min.push(ch);
        }
    }
    for(i = 0 ; i < n ; i++)
    {
        for(j = 0 ; j < n ; j++)
        {
            if(j != i && map[i][j] != 0)    break;
        }
        if(j == n)
        {
            char ch;
            search(i, ch, 2);
            Max.push(ch);
        }
    }
}

void output(queue<char> vec)
{
    while(!vec.empty())
    {
        printf("%c", vec.front());
        vec.pop();
        if(!vec.empty())    putchar(',');
    }
    putchar('\n');
}

int main()
{
    input();
    n = list.size();
    find();
    output(Min);
    output(Max);
    return 0;
}