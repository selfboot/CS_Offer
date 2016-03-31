//顺序表的查找运算
int  Locate(SeqList L, ElemType e)
{	
	int i=0;        /*i为扫描计数器，初值为0，即从第一个元素开始比较*/
	while ((i<=L.last)&&(L.elem[i]!=e))/*顺序扫描表，直到找到值为e的元素, 或扫描到表尾而没找到*/
		i++; 
	if  (i<=L.last)
		return(i+1);  /*若找到值为e的元素，则返回其序号*/
	else
		return(-1);  /*若没找到，则返回空序号*/
}