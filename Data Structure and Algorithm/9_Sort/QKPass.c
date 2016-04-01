int   QKPass(RecordType r[],int left,int right)
/*对记录数组r 中的r[left]至r[right]部分进行一趟排序，并得到基准的位置，使得排序后的结果满足其之后（前）的记录的关键字均不小于（大于）于基准记录*/
{ 
	RecordType x;
	int low,high;
	x= r[left];             /* 选择基准记录*/ 
	low=left;  
	high=right;
	while ( low<high )
	{
		while (low< high && r[high].key>=x.key ) 
			/* high从右到左找小于x.key的记录 */
			high--;
		if ( low <high ) 
		{ 
			r[low]= r[high];
			low++;
		}  
		/* 找到小于x.key的记录，则进行交换*/
		while (low<high && r[low].key<x.key  )    /* low从左到右找大于x.key的记录 */
			low++; 
		if (  low<high  )
		{ 
			r[high]= r[low];
			high--; 
		} /* 找到大于x.key的记录，则交换*/
	}
	r[low]=x;                     /*将基准记录保存到low=high的位置*/
	return low;                     /*返回基准记录的位置*/
} /* QKPass */ 