#define TRUE 1
#define FALSE 0
#define Stack_Size 50

#define StackElementType char

/*顺序栈*/

typedef struct
{
	StackElementType elem[Stack_Size]; /*用来存放栈中元素的一维数组*/
	int top;          		/*用来存放栈顶元素的下标，top为-1表示空栈*/
}SeqStack;


/*初始化*/
void InitStack(SeqStack *S)
{
	/*构造一个空栈S*/
  	S->top = -1;
}

/*判栈空*/
int IsEmpty(SeqStack *S) /*判断栈S为空栈时返回值为真，反之为假*/
{
	return(S->top==-1?TRUE:FALSE);
}

/*判栈满*/
int IsFull(SeqStack *S)	/*判断栈S为满栈时返回值为真，反之为假*/
{
	return(S->top==Stack_Size-1?TRUE:FALSE);
}

int Push(SeqStack *S,StackElementType x)
{
	if(S->top==Stack_Size-1)  
		return(FALSE);  /*栈已满*/
	S->top++;
	S->elem[S->top] = x;
	return(TRUE);
}

int Pop(SeqStack *S,StackElementType *x)
{  
	/* 将栈S的栈顶元素弹出，放到x所指的存储空间中 */
	if(S->top == -1)  /*栈为空*/
		return(FALSE);
	else
	{
  		*x = S->elem[S->top];
		S->top--;    /* 修改栈顶指针 */
  		return(TRUE);
	}
}

/*取栈顶元素。*/
int GetTop(SeqStack *S,StackElementType *x)
{  
	/* 将栈S的栈顶元素弹出，放到x所指的存储空间中，但栈顶指针保持不变 */
	if(S->top == -1)  /*栈为空*/
		return(FALSE);
	else
	{
  		*x = S->elem[S->top];
  		return(TRUE);
	}	
}

/*进行匹配*/
int Match(char ch,char str)
{		
	if(ch=='(' && str==')')
	{
		return TRUE;
	}
	else if(ch=='[' && str==']')
	{
		return TRUE;
	}
	else if(ch=='{' && str=='}')
	{
		return TRUE;
	}
	else 
		return FALSE;
}