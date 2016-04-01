int Pop(SeqStack *S,StackElementType *x)
{  
	/* 将栈S的栈顶元素弹出，放到x所指的存储空间中 */
	if(S->top= =-1)  /*栈为空*/
		return(FALSE);
	else
	{
		*x=S->elem[S->top];
		S->top--;    /* 修改栈顶指针 */
  		return(TRUE);
	}
}
