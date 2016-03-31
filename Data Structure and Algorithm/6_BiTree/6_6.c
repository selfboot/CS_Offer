/* LeafCount保存叶子结点的数目的全局变量,调用之前初始化值为0 */
void leaf_a(BiTree root)
{
	if(root!=NULL)
	{
		leaf_a(root->LChild);
		leaf_a(root->RChild);
		if (root ->LChild==NULL && root ->RChild==NULL)
			LeafCount++;
	}
}

int leaf_b(BiTree root)
{
	int LeafCount2;
	if(root==NULL)	
		LeafCount2 =0;
	else 
		if((root->LChild==NULL)&&(root->RChild==NULL))
			LeafCount2 =1;
		else 
			LeafCount2 =leaf_b(root->LChild)+leaf_b(root->RChild);
	/* 叶子数为左右子树的叶子数目之和 */
	return LeafCount2;
}