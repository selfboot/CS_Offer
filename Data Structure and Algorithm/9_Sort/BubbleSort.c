void  BubbleSort(RecordType r[], int length )
/*对记录数组r做冒泡排序，length为数组的长度*/
{
	int n,i,j;
	int change;
	RecordType x;
	n=length;  
	change=TRUE;
		for ( i=1 ; i<= n-1 && change ;++i ) 
		{
			change=FALSE;
				for ( j=1 ; j<= n-i ; ++j) 
					if (r[j].key > r[j+1].key )  
					{
						x= r[j];
						r[j]= r[j+1];
						r[j+1]= x;
						change=TRUE;
					} 
		}
} /*  BubbleSort  */ 