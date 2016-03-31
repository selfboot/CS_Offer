Boolean  srch_mbtree (Mbtree  mbt,  KeyType  k,  Mbtree  *np,  int *pos)
/*在根为mbt的B_树中查找关键字k，如果查找成功，则将所在结点地址放入np，将结点内位置序号放入pos，并返回true；否则，将k应被插入的结点地址放入np，将结点内应插位置序号放入pos，并返回false*/
{
	Mbtree p,fp;
	Boolean found;
	int i;
	p = mbt;
	fp = NULL; 
	found = false; 
	i = 0;
	while (p != NULL && !found)
	{ 
		i = search (p, k);
		if (i>0 && p->key[i] == k) 
			found = true;
		else 
		{ 
			fp = p; 
			p = p->ptr[i]; 
		}
	}
	if (found) 
	{ 
		*np = p; 
		*pos = i; 
		return true;
	}
	else 
	{
		*np = fp; 
		*pos = i; 
		return false;
	}
}