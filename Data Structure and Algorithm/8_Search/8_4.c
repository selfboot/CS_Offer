void InsertBST(BSTree *bst, KeyType key)
/*若在二叉排序树中不存在关键字等于key的元素，插入该元素*/
{ 
	BSTree s;
	if (*bst == NULL)/*递归结束条件*/
	{
		s=(BSTree)malloc(sizeof(BSTNode));/*申请新的结点s*/
		s-> key=key;
		s->lchild=NULL; 
		s->rchild=NULL;
		*bst=s;
	}
	else 
		if (key < (*bst)->key)
			InsertBST(&((*bst)->lchild), key);/*将s插入左子树*/
		else 
			if (key > (*bst)->key)
				InsertBST(&((*bst)->rchild), key); /*将s插入右子树*/
}