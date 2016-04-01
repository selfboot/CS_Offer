void CrtHuffmanTree(HuffmanTree *ht , int *w, int n)
{ /* w存放已知的n个权值，构造哈夫曼树ht */
	int m,i;
	int s1,s2;
	m=2*n-1;
	*ht=(HuffmanTree)malloc((m+1)*sizeof(HTNode));  /*0号单元未使用*/
	for(i=1;i<=n;i++) 
	{/*1-n号放叶子结点，初始化*/
		(*ht)[i].weight = w[i];
		(*ht)[i].LChild = 0;
		(*ht)[i].parent = 0;
		(*ht)[i].RChild = 0;
	}		
	for(i=n+1;i<=m;i++)
	{
		(*ht)[i].weight = 0;
		(*ht)[i].LChild = 0;
		(*ht)[i].parent = 0;
		(*ht)[i].RChild = 0;
	}    /*非叶子结点初始化*/
/*	------------初始化完毕！对应算法步骤1---------*/
	
	for(i=n+1;i<=m;i++)    /*创建非叶子结点,建哈夫曼树*/
	{  /*在(*ht)[1]~(*ht)[i-1]的范围内选择两个parent为0且weight最小的结点，其序号分别赋值给s1、s2返回*/
		select(ht,i-1,&s1,&s2);
		(*ht)[s1].parent=i;
		(*ht)[s2].parent=i;
		(*ht)[i].LChild=s1;
		(*ht)[i].RChild=s2;
		(*ht)[i].weight=(*ht)[s1].weight+(*ht)[s2].weight;
	} 
}/*哈夫曼树建立完毕*/