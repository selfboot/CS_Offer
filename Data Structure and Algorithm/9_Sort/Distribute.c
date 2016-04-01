void   Distribute(RecordType1 r[],  int  i,  PVector head,  PVector tail)
/*  记录数组r中记录已按低位关键字key[i+1]，…，key[d]进行过"低位优先"排序。本算法按第i位关键字key[i]建立RADIX个队列，同一个队列中记录的key[i]相同。head[j]和tail[j]分别指向各队列中第一个和最后一个记录（j=0，1，2，…，RADIX-1）。head[j]=0表示相应队列为空队列*/ 
{
	int j;
	int p;
	for ( j=0 ; j<=RADIX-1 ; ++j)
		head[j]=0;                        /*  将RADIX个队列初始化为空队列 */ 
		p= r[0].next;                    /*  p指向链表中的第一个记录 */ 
		while( p!=0 ) 
		{
			j=r[p].key[i];          /* 用记录中第i位关键字求相应队列号 */
			if  ( head[j]==0 ) 
				head[j]=p;    /* 将p所指向的结点加入第j个队列中 */ 
			else
				r[tail[j]].next=p;
			tail[j]=p;
			p= r[p].next;
		}
} /*  Distribute  */ 

void  Collect(RecordType1  r[],  PVector head,  PVector tail)
/* 本算法从0到RADIX-1 扫描各队列，将所有非空队列首尾相接，重新链接成一个链表 */ 
{
	int j;
	int t;
	j=0;
	while (head[j]==0 )                 /* 找第一个非空队列 */ 
		++j;
	r[0].next =head[j];
	t=tail[j];
	while ( j<RADIX-1 )                 /* 寻找并串接所有非空队列 */
	{
		++j;
		while ( (j<RADIX-1 ) && (head[j]==0 ) )     /* 找下一个非空队列 */ 
			++j;
		if ( head[j]!=0 )       /* 链接非空队列 */ 
		{
			r[t].next =head[j];
			t=tail[j];
		} 
	}
	r[t].next =0;             /* t指向最后一个非空队列中的最后一个结点 */ 
}   /* Collect */ 

void  RadixSort (RecordType1 r[],int length )
/* length个记录存放在数组r中，执行本算法进行基数排序后，链表中的记录将按关键字从小到大的顺序相链接。 */ 
{
	int i,n;
	int d;
	PVector head;
	PVector tail;
    n= length;
	for ( i=0 ; i<= n-1 ; ++i)  
		r[i].next=i+1;  /* 构造静态链表 */
	r[n].next =0;
	d= 3;
	for ( i =d-1; i>= 0; --i )       /* 从最低位子关键字开始，进行d趟分配 和 收集*/
	{ 
		Distribute(r,i,head,tail);  /* 第i趟分配 */ 
		Collect(r,head,tail);       /* 第i趟收集 */ 
	}
}  /* RadixSort  */
