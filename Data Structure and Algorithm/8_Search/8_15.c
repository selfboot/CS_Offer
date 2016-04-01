int  HashSearch( HashTable  ht,  KeyType  K)
{
	int h0;
	int i;
	int hi;
	h0=hash(K);
	if  (ht[h0].key==NULLKEY) 
		return (-1);
	else 
		if (ht[h0].key==K) 
			return (h0);
		else   /* 用线性探测再散列解决冲突 */
		{ 
			for (i=1; i<=m-1;  i++)
			{
				hi=(h0+i) % m;
				if  (ht[hi].key==NULLKEY) 
					return (-1);
				else
					if (ht[hi].key==K) 
						return (hi);
			}
			return (-1);
		}
		
}