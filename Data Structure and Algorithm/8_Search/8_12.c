void  ins_mbtree(Mbtree  *mbt,  KeyType  k,  Mbtree q,  int  i)
/* 在m阶B_树t中插入k：如果mbt=NULL，则生成初始根（此时q=NULL,i=0）；否则q指向某个最下层非终端结点，k应插在该结点中q->key[i+1]处，插入后如果q->keynum>m-1，则进行分裂处理*/
{ 
	Mbtree  q1,ap;
	Mbtree new_root;
	int s;
	int finished;
	int x;
	if (*mbt==NULL)
	{ 
		*mbt =(Mbtree)malloc(sizeof(Mbtnode));
		(*mbt)->keynum=1;
		(*mbt)->parent=NULL;
		(*mbt)->key[1]=k;
		(*mbt)->ptr[0]=NULL; 
		(*mbt)->ptr[1]=NULL;
	}
	else  
	{  
		x=k;          /* 将x插到q->key[i+1] 处 */
		ap=NULL;		/* 将ap插到q->ptr[i+1] 处 */
		finished=NULL;
		while (q!=NULL && !finished) 		/* q=NULL 表示已经分裂到根 */
		{ 
			insert(q, i, x, ap);
			if (q->keynum<m) 
				finished=TRUE;  	/* 不再分裂 */
			else
			{
				s=ceil((float)m/2);   /* s=  */
				split(q, &q1);  	/* 分裂 */
				x=q->key[s];	
				ap=q1;
				q=q->parent;
				if (q!=NULL) 
					i=search(q,x);	 /* search( ) 的定义参见B_树查找一节 */
			}
		}
		if (!finished)      /* 表示根结点要分裂，并产生新根 */
		{
			new_root=(Mbtree)malloc(sizeof(Mbtnode));
			new_root->keynum=1;  
			new_root->parent=NULL; 
			new_root->key[1]=x;	
			new_root->ptr[0]=*mbt; 
			new_root->ptr[1]=ap;
			*mbt=new_root;
		}
	}
}