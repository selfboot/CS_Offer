
#include "common.h"
#include "linklist.h"

void  ReverseList(LinkList  L)
{ 
	Node *p,*q;
	p=L->next;
	L->next=NULL;
	while(p!=NULL)
	{ 
		q=p->next;     /*q指针保留p->next得值*/
		p->next=L->next;
		L->next=p;    /*将p结点头插入到单链表L中*/
		p=q;          /*p指向下一个要插入的结点*/
	} 
}

void main()
{
	LinkList l;
	Node *p;
	l=(Node * )malloc(sizeof(Node));
	l->next = NULL;
	printf("用尾插法建立单链表,请输入链表数据,以$结束!\n");
    CreateFromTail(l);
	printf("输入的单链表为:\n");
	p = l->next;
	while(p!=NULL)
	{
		printf("%c\n",p->data);
		p=p->next;
	}
	ReverseList(l);
	printf("逆置后的单链表为:\n");
	p = l->next;
	while(p!=NULL)
	{
		printf("%c\n",p->data);
		p=p->next;
	}
}
