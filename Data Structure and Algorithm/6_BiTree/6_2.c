void  InOrder(BiTree root)  
/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{
	if (root!=NULL)
	{
		InOrder(root ->LChild);   /*中序遍历左子树*/
		Visit(root ->data);        /*访问根结点*/
		InOrder(root ->RChild);   /*中序遍历右子树*/
	}
}