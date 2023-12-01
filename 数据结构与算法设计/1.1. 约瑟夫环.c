#include<stdio.h>
#include<stdlib.h>
struct student{
	int num;
	struct student * next;
};

typedef struct student NODE;
typedef struct student * PNODE;

int main()
{
	int n, m, k;
	scanf("%d,%d,%d",&n,&k,&m);
	if(n<1||m<1||k<1){
		printf("n,m,k must bigger than 0.\n");
		return 1;
	}
	if(k>n){
		printf("k should not bigger than n.\n");
		return 2;
	}
	
	PNODE head, p, q;
	head = (PNODE)malloc(sizeof(NODE));
	head->num = -1, head->next = NULL;
	int i;
	
	q = head;
	for(i=1;i<=n;i++){
		p = (PNODE)malloc(sizeof(NODE));
		p->num = i, p->next = NULL;
		q->next = p;
		q = q->next;
	}
	
	p = head;
	for(i=1;i<k;i++){
		p = p->next;
	}
	int len = 1;
	
	while(head->next!=NULL){
		for(i=1;i<=m;i++){
			if(p->next!=NULL){
				p = p->next;
			}
			else{
				p = head->next;
			}
		}
		printf("%d",p->num);
		q = head;
		while(q->next!=p){//存储p前一个节点 
			q = q->next;
		}
		q->next = p->next;//删除报数为m的节点 
		free(p);
		p = NULL;
		
		if(head->next==NULL||len==10){//所有的都输出了 
			putchar('\n');
			len = 1;
		}
		else{//没有输出完 
			printf(" ");
			len++;
		}
		
		p = q; 
	}
	return 0;
}
