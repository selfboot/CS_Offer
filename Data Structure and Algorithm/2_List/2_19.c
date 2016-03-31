int getnode(StaticList space, int *av)
/*从备用链表摘下一个结点空间，分配给待插入静态链表中的元素*/
{
	int i;
	i=*av;
	*av=space[*av].cursor;
	return i;
}