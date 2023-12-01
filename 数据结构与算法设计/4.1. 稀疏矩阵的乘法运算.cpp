#include<cstdio>

int main()
{
    int row1, col1, sum1, row2, col2, sum2;
    scanf("%d%d%d", &row1, &col1, &sum1);
    int triplegroup1[sum1][3];
    int i = 0, j = 0, k = 0, l = 0;
    for(i = 0 ; i < sum1 ; ++i)
    {
        scanf("%d%d%d", &triplegroup1[i][0], &triplegroup1[i][1], &triplegroup1[i][2]);
    }

    scanf("%d%d%d", &row2, &col2, &sum2);
    int triplegroup2[sum2][3];
    for(i = 0 ; i < sum2 ; ++i)
    {
        scanf("%d%d%d", &triplegroup2[i][0], &triplegroup2[i][1], &triplegroup2[i][2]);
    }
    printf("%d\n", row1);
    printf("%d\n", col2);
    int sum = 0, temp = 0;
    //矩阵1的每行*矩阵2的每列
    for(i = 0 ; i < row1 ; ++i)//矩阵1中的每一行
    {
        for(l = 0 ; l < col2 ; ++l)//矩阵2中的每一列；进行矩阵1 i行和矩阵2 l行相乘
        {
            temp = 0;//计算一次前计数清零
            for(j = 0 ; j < sum1 ; ++j)//在矩阵1中找i行的元素
            {
                if(triplegroup1[j][0] > i + 1)    break;//行数递增，遇到更大行数的直接退出
                if(triplegroup1[j][0] == i + 1)//矩阵1中找到了i行的某个元素，去矩阵2中找有没有对应的可以与之相乘的元素
                {
                    for(k = 0 ; k < sum2 ; ++k)//矩阵2中查找
                    {
                        if(triplegroup2[k][0] > triplegroup1[j][1])    break;//同上退出条件
                        if(triplegroup2[k][1] == l + 1 && triplegroup2[k][0] == triplegroup1[j][1])//是否有l列元素且该元素的行数与矩阵1中刚查找到的那个元素的列数相同
                        {
                            temp += triplegroup1[j][2] * triplegroup2[k][2];//两元素相乘
                            break;//temp存储了这一行计算时的中间结果
                        }
                    }
                }
            }
            if(temp != 0)    ++sum;//temp不为0，说明本次计算有结果，总数加1
        }
    }
    printf("%d\n", sum);
    if(sum==0)    return 0;
    for(i = 0 ; i < row1 ; ++i)//矩阵1中的每一行
    {
        for(l = 0 ; l < col2 ; ++l)//矩阵2中的每一列；进行矩阵1 i行和矩阵2 l行相乘
        {
            temp = 0;//计算一次前计数清零
            for(j = 0 ; j < sum1 ; ++j)//在矩阵1中找i行的元素
            {
                if(triplegroup1[j][0] > i + 1)    break;//行数递增，遇到更大行数的直接退出
                if(triplegroup1[j][0] == i + 1)//矩阵1中找到了i行的某个元素，去矩阵2中找有没有对应的可以与之相乘的元素
                {
                    for(k = 0 ; k < sum2 ; ++k)//矩阵2中查找
                    {
                        if(triplegroup2[k][0] > triplegroup1[j][1])    break;//同上退出条件
                        if(triplegroup2[k][1] == l + 1 && triplegroup2[k][0] == triplegroup1[j][1])//是否有l列元素且该元素的行数与矩阵1中刚查找到的那个元素的列数相同
                        {
                            temp += triplegroup1[j][2] * triplegroup2[k][2];//两元素相乘
                            break;//temp存储了这一行计算时的中间结果
                        }
                    }
                }
            }
            if(temp != 0)
            {
                printf("%d,%d,%d\n", i + 1, l + 1, temp);
            }
        }
    }
    return 0;
}