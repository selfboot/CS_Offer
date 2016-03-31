#define  M  10   /*M个链栈*/
#define TRUE 1
#define FALSE 0

typedef struct node
{
	StackElementType data;
	struct node *next;
}LinkStackNode,  *LinkStack;
LinkStack  top[M];

/*第i号栈的进栈操作*/
int  pushi(LinkStack top[M],int i,StackElementType x)
{
	/*将元素x进入第i号链栈*/
	LinkStackNode  *temp;
	temp=(LinkStackNode * )malloc(sizeof(LinkStackNode));
	if(temp==NULL)  
		return(FALSE);   /* 申请空间失败 */
	temp->data=x;
	temp->next=top[i]->next;
	top[i]->next=temp;   /* 修改当前栈顶指针 */ 
	return(TRUE);
}

/*第i号栈元素的出栈操作*/
int Pop(LinkStack top[M],int i,StackElementType *x)
{  
	/* 将栈top的栈顶元素弹出，放到x所指的存储空间中 */
	LinkStackNode *temp;
	temp=top[i]->next;
	if(temp==NULL)  /*第i号栈为空栈*/
		return(FALSE);
	top[i]->next=temp->next;
	*x=temp->data;
	free(temp);   /* 释放存储空间 */
	return(TRUE);
}
