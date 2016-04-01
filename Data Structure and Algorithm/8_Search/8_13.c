void insert(Mbtree mbp,	int ipos, KeyType key,  Mbtree rp)
/* 在mbp->key[ipos +1]处插上key, 在mbp->ptr[ipos+1]处插上rp  */
{
	int j;
	for (j=mbp->keynum; j>= ipos +1 ; j--)
	{ 
		mbp->key[j+1]=mbp->key[j];
		mbp->ptr[j+1]=mbp->ptr[j];
	}
	mbp->key[ipos+1]=key;
	mbp->ptr[ipos+1]=rp;
	mbp->keynum++;
}