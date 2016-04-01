void  HeapSort(RecordType  r[],int length)
/* 对r[1..n]进行堆排序，执行本算法后，r中记录按关键字由大到小有序排列 */ 
{
	int i,n;
	RecordType b;
	crt_heap(r, length);
		n= length;
	for (  i=n ; i>= 2; --i) 
	{
		b=r[1];              /* 将堆顶记录和堆中的最后一个记录互换 */ 
		r[1]= r[i];
		r[i]=b; 
		sift(r,1,i-1);  /* 进行调整，使r[1..i-1]变成堆 */ 
	}
} /* HeapSort */ 