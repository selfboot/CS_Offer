void PostOrder(BiTree root)
{
	BiTNode *p,*q;
	BiTNode **s;
	int top=0;
	q=NULL;
	p=root;
	s=(BiTNode**)malloc(sizeof(BiTNode*)*NUM);
	/* NUM为预定义的常数 */
	while(p!=NULL || top!=0)
	{
		while(p!=NULL)
		{
			top++; 
			s[top]=p; 
			p=p->LChild; 
		}  /*遍历左子树*/
		if(top>0) 
		{	
			p=s[top];
			if((p->RChild==NULL) ||(p->RChild==q))	/* 无右孩子，或右孩子已遍历过 */
			{
			    visit(p->data);        /* 访问根结点*/
				q=p;            	/* 保存到q，为下一次已处理结点前驱 */
				top--;
				p=NULL;
			} 
			else	
				p=p->RChild;
		}
	}
	free(s);
}
