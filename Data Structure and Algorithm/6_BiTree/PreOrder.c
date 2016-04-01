void  PreOrder(BiTree root) 
/*先序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{
	if (root!=NULL)
	{
		Visit(root ->data);  /*访问根结点*/
		PreOrder(root ->LChild);  /*先序遍历左子树*/
		PreOrder(root ->RChild);  /*先序遍历右子树*/
	}
}