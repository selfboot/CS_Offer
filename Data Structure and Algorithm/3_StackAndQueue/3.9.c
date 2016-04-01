int Pop(LinkStack top,StackElementType *x)
{  
	/* 将栈top的栈顶元素弹出，放到x所指的存储空间中 */
	LinkStackNode *temp;
	temp=top->next;
	if(temp==NULL)  /*栈为空*/
		return(FALSE);
	top->next=temp->next;
	*x=temp->data;
	free(temp);   /* 释放存储空间 */
	return(TRUE);
}
