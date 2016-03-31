int GetTop(SeqStack *S, StackElementType *x)
{  
	/* 将栈S的栈顶元素弹出，放到x所指的存储空间中，但栈顶指针保持不变 */
	if(S->top==-1)  /*栈为空*/
		return(FALSE);
	else
	{
		*x = S->elem[S->top];
		return(TRUE);
	}	
}
