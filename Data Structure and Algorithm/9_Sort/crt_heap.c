void   crt_heap(RecordType r[], int length )
/*对记录数组r建堆，length为数组的长度*/
{
	int i,n;
              n= length;
	for ( i=n/2; i >= 1; --i)         /* 自第[n/2]个记录开始进行筛选建堆 */ 
                  sift(r,i,n);
}