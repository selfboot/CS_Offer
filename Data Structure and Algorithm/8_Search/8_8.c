BSTNode  * DelBST(BSTree t, KeyType  k) /*在二叉排序树t中删去关键字为k的结点*/
{
	BSTNode  *p, *f,*s ,*q;
	p=t; 
	f=NULL;
	while(p)  /*查找关键字为k的待删结点p*/
	{ 
		if(p->key==k )  break;  /*找到则跳出循环*/
		f=p;   /*f指向p结点的双亲结点*/
		if(p->key>k)  
			p=p->lchild;
		else 
			p=p->rchild;
	} 
	if(p==NULL)  return t;  /*若找不到，返回原来的二叉排序树*/
	if(p->lchild==NULL)  /*p无左子树*/
	{ 
		if(f==NULL) 
			t=p->rchild;  /*p是原二叉排序树的根*/
		else 
			if(f->lchild==p)  /*p是f的左孩子*/
				f->lchild=p->rchild ;  /*将p的右子树链到f的左链上*/
			else  /*p是f的右孩子*/
				f->rchild=p->rchild ;  /*将p的右子树链到f的右链上*/
			free(p);  /*释放被删除的结点p*/
	}
	else  /*p有左子树*/
	{ 
		q=p; 
		s=p->lchild;
		while(s->rchild)  /*在p的左子树中查找最右下结点*/
		{
			q=s; 
			s=s->rchild;
		}
		if(q==p) 
			q->lchild=s->lchild ;  /*将s的左子树链到q上*/
		else 
			q->rchild=s->lchild;
		p->key=s->key;  /*将s的值赋给p*/
		free(s);
	}
	return t;
}  /*DelBST*/