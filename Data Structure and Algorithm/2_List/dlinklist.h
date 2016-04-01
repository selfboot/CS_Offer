
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK   1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef char ElemType;

typedef struct DNode
{
	ElemType data;
	struct DNode *prior, *next;
}DNode,	*DoubleList;

void CreateList(DoubleList L)
/*通过键盘输入表中元素值，利用尾插法建单链表,并返回该单链表头指针L*/
{ 
	DNode *r, *s;
	char c;
	int   flag =1; /*设置一个标志，初值为1，当输入"$"时，flag为0，建表结束*/
	L->next=L;
	L->prior=L;
	r=L;              
	while(flag)         
	{
		c=getchar();
		if(c!='$')
		{
			s=(DNode*)malloc(sizeof(DNode));
			s->data=c;
			r->next=s;
			s->prior=r;
			r=s;
		}
		else
		{
			flag=0;
			r->next=L;   
			L->prior=r;
		}
	}   /*while*/
} 
