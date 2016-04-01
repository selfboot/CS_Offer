int Pop(DqStack *S,StackElementType *x,int i)
{
	/* 从i 号堆栈中弹出栈顶元素并送到x中 */
	switch(i)
	{
	case 0:
		if(S->top[0]==-1)
			return(FALSE);
		*x=S->Stack[S->top[0]];
		S->top[0]--;
		break;
	case 1:
		if(S->top[1]==M)  return(FALSE);
		*x=S->Stack[S->top[1]];
		S->top[1]++;
		break;
	default:
		return(FALSE);
	}
	return(TRUE);
}
