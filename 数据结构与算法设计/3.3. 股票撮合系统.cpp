#include<cstdio>
#include<cstdlib>

typedef struct node{
    int orderid;//ί�б��
    int stockid;//��Ʊ��
    float price;//�۸�
    int quantity;//����
    char type;//��/������
    struct node * link;
} NODE;

NODE *B, *S;

int QueueEmpty(NODE *);
void print(NODE *, int);
int search(NODE *, int);

int QueueEmpty(NODE * q)
{
    return q->link == NULL;
}

void print(NODE * q, int stock)
{
    NODE * p = q->link;
    while(p != NULL)
    {
        if(p->stockid == stock)
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, p->type);
        p = p->link;
    }
}

int search(NODE *q, int order)
{
    NODE *p = q, *pp = q->link;
    while(pp != NULL)
    {
        if(pp->orderid == order)
        {
            printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", pp->orderid, pp->stockid, pp->price, pp->quantity, pp->type);
            p->link = pp->link == NULL ? NULL : pp->link;
            free(pp);
            return 1;
        }
        else
        {
            p = p->link;
            pp = pp->link;
        }
    }
    return 0;
}

int main()
{
    int form = 0, len = 0;
    B = (NODE*)malloc(sizeof(NODE));
    S = (NODE*)malloc(sizeof(NODE));
    B->link = NULL, S->link = NULL;
    int order, stock, quantity;
    float price;
    char type;
    int _order = 0, _quantity = 0;
    float _price = 0;
    while(true)
    {
        scanf("%d", &form);
        if(form == 0)   break;
        if(form == 1)//ί������
        {
            scanf("%d %f %d %c", &stock, &price, &quantity, &type);
            order = ++len;
            printf("orderid: %04d\n", order);//���ί�б��
            if(type == 's')//��������
            {
                NODE *p = B, *pp = B->link;
                while(pp != NULL)//��ί�в�Ϊ�գ���ί��û�н�����
                {
                    if(pp->price < price)    break;
                    if(pp->stockid != stock)
                    {
                        p = p->link;
                        pp = pp->link;
                        continue;
                    }
                    else//ͬһֻ��Ʊ��ί�м۸������ί�м۸�
                    {
                        if(pp->quantity == quantity)//��ͬ
                        {
                            _order = pp->orderid, _quantity = pp->quantity, _price = pp->price;
                            p->link = pp->link;
                            free(pp);
                            pp = p->link;
                            quantity = 0;
                            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", price / 2 + _price / 2 , _quantity, order, _order);
                            break;
                        }
                        else if(pp->quantity <= quantity)//��ί��û��ȫ�����ף���ί�е�Ҫ��������������
                        {
                            _order = pp->orderid, _quantity = pp->quantity, _price = pp->price;
                            p->link = pp->link;
                            free(pp);
                            pp = p->link;
                            quantity -= _quantity;
                            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", price / 2 + _price / 2 , _quantity, order, _order);
                            continue;
                        }
                        else//��ί��ȫ�����ף���������
                        {
                            pp->quantity -= quantity;
                            _order = pp->orderid, _price = pp->price;
                            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", price / 2 + _price / 2, quantity, order, _order);
                            quantity = 0;
                            break;
                        }
                    }
                }
                if(quantity != 0)//��ί��û������
                {
                    NODE * add = (NODE*)malloc(sizeof(NODE));
                    add->orderid = order, add->price = price, add->quantity = quantity, add->stockid = stock, add->type = type, add->link = NULL;
                    if(QueueEmpty(S))
                    {                 
                        add->link = S->link;
                        S->link = add;
                    }
                    else
                    {
                        NODE * p = S, *pp = S->link;
                        while(pp != NULL && pp->price <= price)//�ͼ�����������ǰ��
                        {
                            p = p->link;
                            pp = pp->link;
                        }
                        add->link = pp == NULL ? NULL : pp;
                        p->link = add;
                    }
                }
            }
            if(type == 'b')//������
            {
                NODE * p = S, *pp = S->link;
                while(pp != NULL)//��ί��û�н�����
                {
                    if(pp->price > price)   break;
                    if(pp->stockid != stock)
                    {
                        p = p->link;
                        pp = pp->link;
                        continue;
                    }
                    else//ͬһ֧��Ʊ��ί�м۸�С����ί�м۸�
                    {
                        if(pp->quantity == quantity)
                        {
                            _order = pp->orderid, _quantity = pp->quantity, _price = pp->price;
                            p->link = pp->link;
                            free(pp);
                            pp = p->link;
                            quantity = 0;
                            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", price / 2 + _price / 2, _quantity, order, _order);
                            break;
                        }
                        else if(pp->quantity <= quantity)//��ί��û��ȫ�����ף���ί�е�Ҫ��������������
                        {
                            _order = pp->orderid, _quantity = pp->quantity, _price = pp->price;
                            p->link = pp->link;
                            free(pp);
                            pp = p->link;
                            quantity -= _quantity;
                            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", price / 2 + _price / 2, _quantity, order, _order);
                            continue;
                        }
                        else//��ί��ȫ�����ף���������
                        {
                            pp->quantity -= quantity;
                            _order = pp->orderid, _price = pp->price;
                            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", price / 2 + _price / 2, quantity, order, _order);
                            quantity = 0;
                            break;
                        }
                    }
                }
                if(quantity != 0)//��ί��û�б�����
                {
                    NODE * add = (NODE*)malloc(sizeof(NODE));
                    add->orderid = order, add->price = price, add->quantity = quantity, add->stockid = stock, add->type = type, add->link = NULL;
                    if(QueueEmpty(B))
                    {
                        add->link = B->link;
                        B->link = add;
                    }
                    else
                    {
                        NODE *p = B, *pp = B->link;
                        while(pp != NULL && pp->price >= price)//�߼�����������ǰ��
                        {
                            p = p->link;
                            pp = pp->link;
                        }//����λ��Ϊp��pp֮��
                        add->link = pp == NULL ? NULL : pp;
                        p->link = add;
                    }
                }
            }
        }
        else if(form == 2)//ί�в�ѯ
        {
            scanf("%d",&stock);
            printf("buy orders:\n");
            print(B, stock);
            printf("sell orders:\n");
            print(S, stock);
        }
        else if(form == 3)//ί��ɾ��
        {
            scanf("%d",&order);
            int status = 0;
            status = search(B, order);
            if(status == 0)
                status = search(S, order);
            if(status == 0)
                printf("not found\n");
        }
    }
    return 0;
}