void   sift(RecordType  r[],  int k, int m)
/* 假设ｒ[k..m]是以ｒ[k]为根的完全二叉树，且分别以ｒ[2k]和ｒ[2k+1]为根的左、右子树为大根堆，调整r[k]，使整个序列r[k..m]满足堆的性质 */
{
	RecordType t;
	int i,j;
	int x;
	int finished;
	t= r[k];          /* 暂存"根"记录r[k] */ 
	x=r[k].key;
	i=k;
	j=2*i;
	finished=FALSE;
		while( j<=m && !finished  ) 
		{     
		if (j<m  && r[j].key< r[j+1].key ) 
		j=j+1;  /* 若存在右子树，且右子树根的关键字大，则沿右分支"筛选" */
		if ( x>= r[j].key)
			finished=TRUE;            /*  筛选完毕  */ 
		else 
		{
			r[i] = r[j];
			i=j;
			j=2*i;
		}    /* 继续筛选 */ 
		}
		r[i] =t;          /* r[k]填入到恰当的位置 */ 
}  