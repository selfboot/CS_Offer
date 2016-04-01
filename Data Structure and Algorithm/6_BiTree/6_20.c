void CrtHuffmanCode(HuffmanTree *ht, HuffmanCode *hc, int n)
/*从叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码*/
{
	char *cd;
	int i;
	unsigned int c;
	int start;
	int p;
	hc=(HuffmanCode *)malloc((n+1)*sizeof(char *));  /*分配n个编码的头指针*/
	cd=(char * )malloc(n * sizeof(char ));  /*分配求当前编码的工作空间*/
	cd[n-1]='\0';   /*从右向左逐位存放编码，首先存放编码结束符*/
	for(i=1;i<=n;i++)  /*求n个叶子结点对应的哈夫曼编码*/
	{
		start=n-1;    /*初始化编码起始指针*/
		for(c=i,p=(*ht)[i].parent; p!=0; c=p,p=(*ht)[p].parent) /*从叶子到根结点求编码*/
			if( (*ht)[p].LChild == c) 
				cd[--start]='0';  /*左分支标0*/
			else 
				cd[--start]='1';  /*右分支标1*/
	hc[i]=(char *)malloc((n-start)*sizeof(char));  /*为第i个编码分配空间*/
	strcpy(hc[i],&cd[start]);
	}
	free(cd);
	for(i=1;i<=n;i++)
		printf("%d编码为%s\n",(*ht)[i].weight,hc[i]);
}