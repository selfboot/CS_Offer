void QKSort(RecordType r[],int low, int high )
/*对记录数组r[low..high]用快速排序算法进行排序*/
{
	int pos;
	if(low<high)
	{
		pos=QKPass(r, low, high);  /*调用一趟快速排序，将枢轴元素为界划分两个子表*/
		QKSort(r, low, pos-1);     /*对左部子表快速排序*/
		QKSort(r, pos+1, high); /*对右部子表快速排序*/
		
	}
}