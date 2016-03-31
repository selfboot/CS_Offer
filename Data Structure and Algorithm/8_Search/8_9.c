void  ins_AVLtree(AVLTree  *avlt ,  KeyType  K)
/*在平衡二叉树中插入元素k，使之成为一棵新的平衡二叉排序树*/
{
	AVLTNode *S;
	AVLTNode *A,*FA,*p,*fp,*B,*C;
	S=(AVLTree)malloc(sizeof(AVLTNode));
	S->key=K; 
	S->lchild=S->rchild=NULL;
	S->bf=0;
	if (*avlt==NULL)  
		*avlt=S;
	else 
	{ 
	/* 首先查找S的插入位置fp，同时记录距S的插入位置最近且
		平衡因子不等于0（等于-1或1）的结点A，A为可能的失衡结点*/
		A=*avlt;  FA=NULL;
		p=*avlt;  fp=NULL;
		while  (p!=NULL)
		{ 
			if (p->bf!=0) 
			{
				A=p; FA =fp;
			}
			fp=p;
			if  (K < p->key)  
				p=p->lchild;
			else  
				p=p->rchild;
		}
		/* 插入S*/
		if (K < fp->key) 
			fp->lchild=S;
		else
			fp->rchild=S;
		/* 确定结点B，并修改A的平衡因子 */
		if (K < A->key)
		{
			B=A->lchild;
			A->bf=A->bf+1;
		}
		else
		{
			B=A->rchild;
			A->bf=A->bf-1;
		}
		/* 修改B到S路径上各结点的平衡因子（原值均为0）*/
		p=B;
		while (p!=S)
		{
			if  (K < p->key)
			{
				p->bf=1;
				p=p->lchild;
			}
			else
			{
				p->bf=-1;
				p=p->rchild;
			}
			/* 判断失衡类型并做相应处理 */
			if  (A->bf==2 && B->bf==1)       /* LL型 */
			{
				B=A->lchild;
				A->lchild=B->rchild;
				B->rchild=A;
				A->bf=0;
				B->bf=0;
				if (FA==NULL) 
					*avlt=B;
				else 
					if (A==FA->lchild) 
						FA->lchild=B;
					else 
						FA->rchild=B;
			}
			else
				if (A->bf==2 && B->bf==-1)       /* LR型 */
				{
					B=A->lchild;
					C=B->rchild;
					B->rchild=C->lchild;
					A->lchild=C->rchild;
					C->lchild=B;
					C->rchild=A;
					if (S->key < C->key)
					{ 
						A->bf=-1;
						B->bf=0;
						C->bf=0;
					}
					else 
						if (S->key >C->key)
						{
							A->bf=0;
							B->bf=1;
							C->bf=0;
						}
						else
						{ 
							A->bf=0;
							B->bf=0;
						}
						if  (FA==NULL) 
							*avlt=C;
						else 
							if (A==FA->lchild) 
								FA->lchild=C;
							else 
								FA->rchild=C;
				}
				else 
					if  (A->bf==-2 && B->bf==1)       /* RL型 */
					{
						B=A->rchild;
						C=B->lchild;
						B->lchild=C->rchild;
						A->rchild=C->lchild;
						C->lchild=A;
						C->rchild=B;
						if (S->key <C->key) 
						{ 
							A->bf=0;
							B->bf=-1;
							C->bf=0;
						}
						else 
							if (S->key >C->key)
							{
								A->bf=1;
								B->bf=0;
								C->bf=0;
							}
							else 
							{ 
								A->bf=0;
								B->bf=0;
							}
							if (FA==NULL)  
								*avlt=C;
							else
								if (A==FA->lchild) 
									FA->lchild=C;
								else  
									FA->rchild=C;
					}
					else 
						if (A->bf==-2 && B->bf==-1)       /* RR型 */
						{
							B=A->rchild;
							A->rchild=B->lchild;
							B->lchild=A;
							A->bf=0;
							B->bf=0;
							if (FA==NULL) 
								*avlt=B;
							else
								if (A==FA->lchild)
									FA->lchild=B;
								else 
									FA->rchild=B;
						}
				}
		}
}
