#include<iostream>
#include<stack>
#include<cctype>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int PriorityofOperator(char, int);
int isp(char);
int icp(char);
void evalRPN(char*, char*);
int calculate(char*, char*, int*, int);
void print(int*, int*, int, int);
int PriorityofOperator(char ch, int type)
{
    if(type == 1)
        return isp(ch);
    if(type == 2)
        return icp(ch);
    printf("error.-1\n");
    return 0;
}

int isp(char ch)//ջ�����ȼ���(�ܵͣ�)�ܸߣ�ʵ����Ч��;ջ������ͬ������ջ��
{
    switch(ch)
    {
        case '#' : return 0;
        case '(' : return 1;
        case '+' : return 3;
        case '-' : return 5;
        case '|' : return 7;
        case '&' : return 9;
        case '!' : return 11;
        case ')' : return 13;
        default : printf("error.-2\n"); return -1;
    }
}

int icp(char ch)
{
        switch(ch)
    {
        case '#' : return 0;
        case ')' : return 1;
        case '+' : return 2;
        case '-' : return 4;
        case '|' : return 6;
        case '&' : return 8;
        case '!' : return 10;
        case '(' : return 13;
        default : printf("error.-3\n"); return -1;
    }
}

void evalRPN(char* cal, char* alpha)
{
    char str[1000] = {0};
    cin >> str;
    int length_str = strlen(str);
    str[length_str] = '#';
    stack<char> op;
    op.push('#');//�ڱ����
    int i = 0, j = 0, length_alpha = 0, leng_cal = 0;
    for(i = 0 ; str[i] != '\0' ; ++i)
    {
        if(str[i]>='a'&&str[i]<='z')
        {
            for(j = 0 ; j < length_alpha ; ++j)
            {
                if(alpha[j] == str[i])
                    break;//����ͬ��ĸ���˳�
            }
            if(j == length_alpha)//û�ҵ���ͬ��ĸ
            {
                alpha[length_alpha++] = str[i];
            }
            cal[leng_cal++] = str[i];
        }
        else
        {
            while(PriorityofOperator(op.top(), 1) > PriorityofOperator(str[i], 2))//ջ�����ȼ����ߣ�Ҫ���
            {
                cal[leng_cal++] = op.top();//�����������
                op.pop();//���������
            }
            if(PriorityofOperator(op.top(), 1) < PriorityofOperator(str[i], 2))//���ջ�����ȼ��ϵͣ�Ҫ��str[i]��ջ
                op.push(str[i]);
            else//�������ȼ���ͬ��ֻ�����������Ż����ڱ��ڵ㣬ɾ��ջ��Ԫ��
                op.pop();
        }
    }
}

int calculate(char* cal, char* alpha, int* List, int length)//����ֵΪ����ʽֵ
{
    stack<int> s;
    int i, j;
    for(i = 0 ; i < strlen(cal) ; ++i)
    {
        if(cal[i]>='a'&&cal[i]<='z')//���ʽ����������ĸ���滻Ϊ����
        {
            for(j = 0 ; j < strlen(alpha) ; ++j)
            {
                if(cal[i] == alpha[j])
                {
                    s.push(List[j]);
                    break;
                }
            }
        }
        else//�������
        {
            if(cal[i] == '!')//�����������������
            {
                if(s.empty())
                {
                    printf("error.-6\n");
                    continue;
                }
                int num1 = s.top();
                s.pop();
                s.push(!num1);
            }
            else
            {
                if(s.empty())
                {
                    printf("error.-7\n");
                    continue;
                }
                int num2 = s.top();
                s.pop();
                if(s.empty())
                {
                    printf("error.-8\n");
                    continue;
                }
                int num1 = s.top();
                s.pop();
                switch(cal[i])//���о�������
                {
                    case '|' :
                        if(num1 || num2)
                            s.push(1);
                        else
                            s.push(0);
                        break;
                    case '&' :
                        if(num1 && num2)
                            s.push(1);
                        else
                            s.push(0);
                        break;
                    case '-' ://�����ͷ
                        if(num1 == 1 && num2 == 0)
                            s.push(0);
                        else
                            s.push(1);
                        break;
                    case '+' :
                        if(num1 == num2)
                            s.push(1);
                        else
                            s.push(0);
                        break;
                    default : printf("error.-4\n");
                }
            }
        }
    }
    if(s.empty())
    {
        printf("error.-5\n");
        return -1;
    }
    return s.top();
}

void Print(int* m, int* M, int length_m, int length_M)
{
    int i;
    if(length_m == 0)
    {
        cout << "0 ";
    }
    //cout << M << endl;
    for(i = 0 ; i < length_m; ++i)
    {
        cout << 'm' << m[i] << ' ' ;
        if(length_m > 1 && i != length_m - 1)
            cout << "�� ";
    }
    cout << "; ";
    if(length_M == 0)
    {
        cout << "1" << endl;
        return;
    }
    for(i = 0 ; i < length_M ; ++i)
    {
        cout << 'M' << M[i];
        if(i != length_M - 1)
            cout << ' ';
        if(length_M > 1 && i != length_M - 1)
            cout << "�� ";
    }
    cout << endl;
}

int main()
{
    int N = 10;
    //while(N--)
    //{
    char cal[1000] = {0};
    char alpha[1000] = {0};
    evalRPN(cal, alpha);
    //cout << cal << endl;���������沨��ʽ�洢����ʽ����alpha����洢�����б���
    int SumofVal = strlen(alpha);
    int TrueValueList[SumofVal];//��ֵ��
    memset(TrueValueList, 0, sizeof(TrueValueList));
    int M[1000] = {0}, m[1000] = {0};
    int i, j, length_m = 0, length_M = 0;
    for(i = 0 ; i < pow(2, (float)SumofVal) ; i++)
    {
        if(i)   ++TrueValueList[SumofVal - 1];
        for(j = SumofVal - 1 ; j > 0 ; --j)
        {
            if(TrueValueList[j] >= 2)
            {
                TrueValueList[j] = 0;
                ++TrueValueList[j-1];
            }
            else
                break;
        }//����������
        int value = calculate(cal, alpha, TrueValueList, SumofVal);
        if(value == 1)//���渳ֵ����С�����ȡ��ʽ��m
            m[length_m++] = i;
        else if(value == 0)//�ɼٸ�ֵ�����������ȡ��ʽ��M
            M[length_M++] = i;
        else
            break;
    }
    if(i == pow(2, (float)SumofVal))//ǰ�涼��ȷ�������
    {
        Print(m, M, length_m, length_M);
    }
    else
    {
        cout << "error : value = -1" << endl;
    }
    //}
    return 0;
}