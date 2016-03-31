int  DelList(SeqList *L,int i,ElemType *e)
/*在顺序表L中删除第i个数据元素，并用指针参数e返回其值。i的合法取值为1≤i≤L.last+1 */    
{ 
	int k;
	if((i<1)||(i>L->last+1))   
	{ 
		printf("删除位置不合法!");
		return(ERROR);
	}
	*e = L->elem[i-1];  /* 将删除的元素存放到e所指向的变量中*/
	for(k=i; i<=L->last; k++)
	    L->elem[k-1] = L->elem[k];  /*将后面的元素依次前移*/
	L->last--;
	return(OK);
}