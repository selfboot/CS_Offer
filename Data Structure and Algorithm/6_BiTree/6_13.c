void  Inthread(BiTree root)
/* 对root所指的二叉树进行中序线索化，其中pre始终指向刚访问过的结点，其初值为NULL*/
{
	if (root!=NULL)
	{ 
		Inthread(root->LChild);  /* 线索化左子树 */
		if (root->LChild==NULL)
		{
			root->Ltag=1; 
			root->LChild=pre;  /*置前驱线索 */
		}
		if (pre!=NULL&& pre->RChild==NULL)  /* 置后继线索 */
		{
			pre->RChild=root;
			pre->Rtag=1;
		}
	pre=root;
	Inthread(root->RChild);  /*线索化右子树*/
	}
}	