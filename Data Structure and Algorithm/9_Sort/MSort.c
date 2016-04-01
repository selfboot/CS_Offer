void   MSort(RecordType  r1[],  int  low,  int  high,  RecordType  r3[])
/* r1[low..high]经过排序后放在r3[low..high]中，r2[low..high]为辅助空间 */ 
{
	int mid;
	RecordType  r2[20];
	if ( low==high ) 
		r3[low]=r1[low];
	else
	{
		mid=(low+high)/2;
        MSort(r1,low, mid, r2);
        MSort(r1,mid+1,high, r2);
        Merge (r2,low,mid,high, r3);
}
} /*   MSort  */ 
