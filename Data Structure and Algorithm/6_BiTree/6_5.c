void  PreOrder(BiTree root) 
/*先序遍历二叉树, root为指向二叉树根结点的指针*/
{
	if (root!=NULL)
	{
		if (root ->LChild==NULL && root ->RChild==NULL)
			printf("%c  ",root ->data);  /*输出叶子结点*/
		PreOrder(root ->LChild);  /*先序遍历左子树*/
		PreOrder(root ->RChild);  /*先序遍历右子树*/
	}
}