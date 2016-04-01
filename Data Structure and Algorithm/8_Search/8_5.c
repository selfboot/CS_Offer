void  CreateBST(BSTree  *bst)
/*从键盘输入元素的值，创建相应的二叉排序树*/
{ 
	KeyType key;
	*bst=NULL;
	scanf("%d", &key);
	while (key!=ENDKEY)   /*ENDKEY为自定义常量*/
	{
		InsertBST(bst, key);
		scanf("%d", &key);
	}
}