int Push(SeqStack *S,StackElementType x)
{
	if(S->top==(Stack_Size-1))  
		return(FALSE);  /*Õ»ÒÑÂú*/
	S->top++;
	S->elem[S->top]=x;
	return(TRUE);
}
