BSTree  SearchBST(BSTree bst, KeyType key)
/ *在根指针bst所指二叉排序树中，递归查找某关键字等于key的元素，若查找成功，返回指向该元素结点指针，否则返回空指针* /
{ 
	if (!bst) 
		return NULL;
	else 
		if (bst->key == key)
			return bst;/ *查找成功* /
		else
			if (bst->key > key)
				return SearchBST(bst->lchild, key);/ *在左子树继续查找* /
			else 
				return SearchBST(bst->rchild, key);/ *在右子树继续查找* /
}