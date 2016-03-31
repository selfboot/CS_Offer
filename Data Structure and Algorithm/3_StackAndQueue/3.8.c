int Push(LinkStack top,StackElementType x)  
{
	/* 将数据元素x压入栈top中 */
	LinkStackNode *temp;
	temp=(LinkStackNode *)malloc(sizeof(LinkStackNode));
 	if(temp==NULL)  
		return(FALSE);   /* 申请空间失败 */
	temp->data=x;
	temp->next=top->next;
	top->next=temp;   /* 修改当前栈顶指针 */ 
	return(TRUE);
}
