void  ShellInsert(RecordType r[], int length,  int  delta)
/*对记录数组r做一趟希尔插入排序，length为数组的长度,delta 为增量*/
{
	int i,j;
	for(i=1+delta;i<= length; i++)      /* 1+delta为第一个子序列的第二个元素的下标 */
		if(r[i].key < r[i-delta].key)
		{
			r[0]= r[i];           /*  备份r[i]  (不做监视哨) */
				for(j=i-delta; j>0 &&r[0].key < r[j].key; j-=delta)
					r[j+delta]= r[j];
					r[j+delta]= r[0];
		}
}/*ShellInsert*/

void  ShellSort(RecordType r[], int length, int delt[], int n)
/*对记录数组r做希尔排序，length为数组r的长度，delta 为增量数组，n为delta[]的长度 */
{ 
	int i;
	for(i=0 ;  i<=n-1;  ++i)
		ShellInsert(r, length, delt[i]);
}