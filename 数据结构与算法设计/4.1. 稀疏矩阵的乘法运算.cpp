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
    //����1��ÿ��*����2��ÿ��
    for(i = 0 ; i < row1 ; ++i)//����1�е�ÿһ��
    {
        for(l = 0 ; l < col2 ; ++l)//����2�е�ÿһ�У����о���1 i�к;���2 l�����
        {
            temp = 0;//����һ��ǰ��������
            for(j = 0 ; j < sum1 ; ++j)//�ھ���1����i�е�Ԫ��
            {
                if(triplegroup1[j][0] > i + 1)    break;//������������������������ֱ���˳�
                if(triplegroup1[j][0] == i + 1)//����1���ҵ���i�е�ĳ��Ԫ�أ�ȥ����2������û�ж�Ӧ�Ŀ�����֮��˵�Ԫ��
                {
                    for(k = 0 ; k < sum2 ; ++k)//����2�в���
                    {
                        if(triplegroup2[k][0] > triplegroup1[j][1])    break;//ͬ���˳�����
                        if(triplegroup2[k][1] == l + 1 && triplegroup2[k][0] == triplegroup1[j][1])//�Ƿ���l��Ԫ���Ҹ�Ԫ�ص����������1�иղ��ҵ����Ǹ�Ԫ�ص�������ͬ
                        {
                            temp += triplegroup1[j][2] * triplegroup2[k][2];//��Ԫ�����
                            break;//temp�洢����һ�м���ʱ���м���
                        }
                    }
                }
            }
            if(temp != 0)    ++sum;//temp��Ϊ0��˵�����μ����н����������1
        }
    }
    printf("%d\n", sum);
    if(sum==0)    return 0;
    for(i = 0 ; i < row1 ; ++i)//����1�е�ÿһ��
    {
        for(l = 0 ; l < col2 ; ++l)//����2�е�ÿһ�У����о���1 i�к;���2 l�����
        {
            temp = 0;//����һ��ǰ��������
            for(j = 0 ; j < sum1 ; ++j)//�ھ���1����i�е�Ԫ��
            {
                if(triplegroup1[j][0] > i + 1)    break;//������������������������ֱ���˳�
                if(triplegroup1[j][0] == i + 1)//����1���ҵ���i�е�ĳ��Ԫ�أ�ȥ����2������û�ж�Ӧ�Ŀ�����֮��˵�Ԫ��
                {
                    for(k = 0 ; k < sum2 ; ++k)//����2�в���
                    {
                        if(triplegroup2[k][0] > triplegroup1[j][1])    break;//ͬ���˳�����
                        if(triplegroup2[k][1] == l + 1 && triplegroup2[k][0] == triplegroup1[j][1])//�Ƿ���l��Ԫ���Ҹ�Ԫ�ص����������1�иղ��ҵ����Ǹ�Ԫ�ص�������ͬ
                        {
                            temp += triplegroup1[j][2] * triplegroup2[k][2];//��Ԫ�����
                            break;//temp�洢����һ�м���ʱ���м���
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