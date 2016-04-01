void CreateBiTree(BiTree *bt)
{
      char ch; 
      ch = getchar();
      if(ch=='.') *bt=NULL;
      else 
	{
		*bt=(BiTree)malloc(sizeof(BiTNode)); //生成一个新结点
                           (*bt)->data=ch;
                           CreateBiTree(&((*bt)->LChild)); //生成左子树
                           CreateBiTree(&((*bt)->RChild)); //生成右子树
	}
}