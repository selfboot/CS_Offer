/*在顺序表L中第i个数据元素之前插入一个元素e。 插入前表长n=L->last+1，
i的合法取值范围是 1≤i≤L->last+2  */
int  InsList(SeqList *L,int i,ElemType e)
{ 
	int k;
	if((i<1) || (i>L->last+2)) /*首先判断插入位置是否合法*/
	{
		printf("插入位置i值不合法");
		return(ERROR);
	}
	if(L->last>= MAXSIZE-1)
	{
		printf("表已满无法插入");
		return(ERROR);
	}
	for(k=L->last;k>=i-1;k--)   /*为插入元素而移动位置*/
		L->elem[k+1]=L->elem[k];
	L->elem[i-1]=e;   /*在C语言数组中，第i个元素的下标为i-1*/
	L->last++;
	return(OK);
}