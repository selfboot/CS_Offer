BSTree  SearchBST(BSTree bst, KeyType key)
/*在根指针bst所指二叉排序树bst上，查找关键字等于key的结点，若查找成功，返回指向该元素结点指针，否则返回空指针*/
{ 
	BSTree q;
	q=bst;
	while(q)
	{
		if (q->key == key) 
			return q;  /*查找成功*/
		if (q->key > key)  
			q=q->lchild;  /*在左子树中查找*/
		else  
			q=q->rchild;  /*在右子树中查找*/
	}
	return NULL; /*查找失败*/
}/*SearchBST*/