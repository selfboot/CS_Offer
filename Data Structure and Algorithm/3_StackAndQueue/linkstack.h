#define TRUE 1
#define FALSE 0

typedef struct node
{
	StackElementType data;
	struct node *next;
}LinkStackNode;

typedef LinkStackNode *LinkStack;

/*进栈操作。*/
int Push(LinkStack top, StackElementType x)/* 将数据元素x压入栈top中 */ 
{
	LinkStackNode *temp;
	temp=(LinkStackNode *)malloc(sizeof(LinkStackNode));
 	if(temp==NULL)  
 		return(FALSE);   /* 申请空间失败 */
	temp->data=x;
	temp->next=top->next;
	top->next=temp;   /* 修改当前栈顶指针 */ 
	return(TRUE);
}

/*出栈操作。*/
int Pop(LinkStack top, StackElementType *x)
{  
	/* 将栈top的栈顶元素弹出，放到x所指的存储空间中 */
	LinkStackNode * temp;
	temp=top->next;
	if(temp==NULL)  /*栈为空*/
		return(FALSE);
	top->next=temp->next;
	*x=temp->data;
	free(temp);   /* 释放存储空间 */
	return(TRUE);
}

