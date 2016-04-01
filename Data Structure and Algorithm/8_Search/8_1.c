int SeqSearch(RecordList  l,  KeyType  k)
/*在顺序表l中顺序查找其关键字等于k的元素，若找到，则函数值为该元素在表中的位置，否则为0*/
{
	int i;
	l.r[0].key=k; 
	i=l.length;
	while (l.r[i].key!=k)  i--;
	return(i);
}