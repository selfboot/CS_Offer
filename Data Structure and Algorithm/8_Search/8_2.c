int SeqSearch(RecordList l,  KeyType k)
/*不用"监视哨"法，在顺序表中查找关键字等于k的元素*/
{
	int i;
	i=l.length;
	while (i>=1&&l.r[i].key!=k)  i--;
	if (i>=1) 
		return(i);
	else
		return (0);
}