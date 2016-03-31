void  split (Mbtree  oldp,	Mbtree  *newp)
{/* B_树的分裂过程 */
	int s,n,i;
	s=ceil((float)m/2);       /* s=  */
	n=m-s;
	*newp=(Mbtree)malloc(sizeof(Mbtnode));
	(*newp)->keynum=n;
	(*newp)->parent=oldp->parent;
	(*newp)->ptr[0]=oldp->ptr[s];
	for (i=1 ; i<=n ; i++)
	{ (*newp)->key[i]=oldp->key[s+i];
	(*newp)->ptr[i]=oldp->ptr[s+i];
	}
	oldp->keynum=s-1;
}