void inorder(BiTree root);
{
   int top=0; p=bt;
   L1: if (p!=NULL)       /* 遍历左子树 */       
   { 
     top=top+2;    
     if(top>m) return;       /*栈满溢出处理*/
     s[top-1]=p;            /* 本层参数进栈 */    
     s[top]=L2;             /* 返回地址进栈 */
     p=p->LChild;           /* 给下层参数赋值 */
     goto L1;               /* 转向开始 */
   L2:  Visit(p->data);     /* 访问根 */
     top=top+2;
     if(top>m) return;       /*栈满溢出处理*/;
     s[top-1]=p;            /* 遍历右子树 */
     s[top]=L3;
     p=p->RChild;
     goto L1;
   }
   L3: if(top!=0)      
  { 
    addr=s[top];
    p=s[top-1];            /* 取出返回地址 */
    top=top-2;             /* 退出本层参数 */
    goto addr;
  }
}
/*算法a*/

void inorder(BiTree root)   /* 中序遍历二叉树，root为二叉树的根结点 */
{
	int top=0; 
	BiTree p;
	BiTree s[Stack_Size];
	int m;
	m = Stack_Size-1;
	p = root;
	do
	{
		while(p!=NULL)
		{ 
			if (top>m) return;
			top=top+1;  
			s[top]=p;
			p=p->LChild;
		};  /* 遍历左子树 */
		if(top!=0)
		{ 
			p=s[top];
			top=top-1;
			Visit(p->data);  /* 访问根结点 */
			p=p->RChild;  /* 遍历右子树 */
		}   
	}
	while(p!=NULL || top!=0);
}
           /*算法b*/


void  InOrder(BiTree root) /* 中序遍历二叉树的非递归算法 */
{
	SeqStack S;
	BiTree p;
	InitStack (&S);
	p=root;
	while(p!=NULL || !IsEmpty(&S))
	{ 
		if (p!=NULL)  /* 根指针进栈，遍历左子树 */
		{
			Push(&S,p);
			p=p->LChild;
		}
		else
		{  /*根指针退栈，访问根结点，遍历右子树*/
			Pop(&S,&p); 
			Visit(p->data);  
			p=p->RChild;
		}
	}
}
            /*算法c*/