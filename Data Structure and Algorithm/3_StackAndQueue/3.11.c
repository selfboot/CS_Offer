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
