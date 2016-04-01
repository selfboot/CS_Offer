void path(BiTree root, BiTNode *r)
{ 
	BiTNode  *p, *q;
	int i, find=0, top=0;
	BiTNode *s[NUM];
	q = NULL;   /* 用q保存刚遍历过的结点 */
	p = root;
	while ( (p != NULL || top != 0) && !find )
	{
		while ( p != NULL )
		{ 
			top++; 
			s[top] = p;
			p = p->LChild; 
		}                /* 遍历左子树 */
		if (top > 0)
		{  
			p=s[top];       /* 根结点 */
			if ( p->RChild == NULL || p->RChild == q )
			{ 
				if(p == r)   /*找到r所指结点，则显示从根结点到r所指结点之间的路径*/
				{
					for(i=1;i<=top;i++) 
						printf("%c  ",s[i]->data);
					find=1;
				}
				else
				{
					q = p;        /* 用q保存刚遍历过的结点 */
					top--;
					p = NULL;    /* 跳过前面左遍历，继续退栈 */
				}
			}
			else
				p = p->RChild;     /* 遍历右子树 */
		}
	}  
}