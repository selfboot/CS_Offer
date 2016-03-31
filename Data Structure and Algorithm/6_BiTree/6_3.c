void  PostOrder(BiTree root)  
/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
{
	if(root!=NULL)
	{
		PostOrder(root ->LChild); /*后序遍历左子树*/
		PostOrder(root ->RChild); /*后序遍历右子树*/
		Visit(root ->data);       /*访问根结点*/
	}
}