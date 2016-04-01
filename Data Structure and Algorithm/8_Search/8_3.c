int BinSrch(RecordList  l,  KeyType  k)
/*在有序表l中折半查找其关键字等于k的元素，若找到，则函数值为该元素在表中的
位置*/
{
	int low,high,mid;
	low=1;  
	high=l.length;/*置区间初值*/
	while( low <= high)
	{
		mid=(low+high) / 2;
		if  (k==l.r[mid]. key)  
			return (mid);/*找到待查元素*/
		else  
			if (k<l.r[mid]. key) 
				high=mid-1;/*未找到，则继续在前半区间进行查找*/
			else  
				low=mid+1;/*继续在后半区间进行查找*/
	}
	return (0);
}