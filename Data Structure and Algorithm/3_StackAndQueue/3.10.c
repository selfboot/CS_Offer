int pushi(LinkStack top[M],int i,StackElementType x)
{
	/*将元素x进入第i号链栈*/
	LinkStackNode  *temp;
	temp=(LinkStackNode *)malloc(sizeof(LinkStackNode));
	if(temp==NULL)  return(FALSE);   /* 申请空间失败 */
	temp->data=x;
	temp->next=top[i]->next;
	top[i]->next=temp;   /* 修改当前栈顶指针 */ 
	return(TRUE);
}
