void    BinSort (RecordType  r[],  int length)
/*对记录数组r进行折半插入排序，length为数组的长度*/
{
	int i,j;
	RecordType x;
	int low,high,mid;
	for (  i=2; i<=length ; ++i ) 
	{
		x= r[i];
		low=1;  high=i-1;
		while (low<=high )                  /* 确定插入位置*/ 
		{
			mid=(low+high) / 2;
			if (  x.key< r[mid].key   )    
				high=mid-1;
			else 
				low=mid+1;
		}
		for (  j=i-1 ; j>= low; --j )   r[j+1]= r[j];         /*  记录依次向后移动 */ 
		r[low]=x;                                                            /* 插入记录 */ 
	}
}/*BinSort*/
