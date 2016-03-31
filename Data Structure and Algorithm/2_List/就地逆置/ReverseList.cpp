
#include <stdio.h>
#include <stdlib.h>

#define ElemType char
typedef struct Node    /*结点类型定义*/ 
{ 
	ElemType data;
	struct Node  * next;
}Node, *LinkList;  /* LinkList为结构指针类型*/


LinkList CreateFromTail()
/*通过键盘输入表中元素值，利用尾插法建单链表,并返回该单链表头指针L*/
{ 
	LinkList L;
	Node *r, *s;
	char c;
	int   flag =1; /*设置一个标志，初值为1，当输入"$"时，flag为0，建表结束*/
	L=(Node * )malloc(sizeof(Node));     
	L->next=NULL;	 		/*为头结点分配存储空间，建立空的单链表L*/
	r=L;                /*r指针动态指向链表的当前表尾，以便于做尾插入，其初值指向头结点*/
	while(flag)         /*循环输入表中元素值，将建立新结点s插入表尾*/
	{
		c=getchar();
		if(c!='$')
		{
			s=(Node*)malloc(sizeof(Node));
			s->data=c;
			r->next=s;
			r=s;
		}
		else
		{
			flag=0;
			r->next=NULL;   /*将最后一个结点的next链域置为空，表示链表的结束*/
		}
	}  
	return L;
} 

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
	printf("用尾插法建立单链表,请输入链表数据,以$结束!\n");
    l = CreateFromTail();
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
