void   freenode(StaticList space, int *av, int k)
/*将下标为 k的空闲结点插入到备用链表*/
{
	space[k].cursor=*av;
	*av=k;
}