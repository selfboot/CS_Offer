void   InsSort(RecordType  r[],  int length)
/* 对记录数组r做直接插入排序，length为数组中待排序记录的数目*/
{ 
	int i,j;
	for (i=2;  i<=length;  i++) 
	{
		r[0]=r[i];      /*将待插入记录存放到监视哨r[0]中*/
		j=i-1;	         
		while (r[0].key< r[j].key )     /* 寻找插入位置 */
		{
			r[j+1]= r[j]; 
			j=j-1;
		}
		r[j+1]=r[0];		         /*将待插入记录插入到已排序的序列中*/
	}
} /*  InsSort  */  