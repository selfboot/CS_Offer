void initial(StaticList space, int *av)
{
    int k;
	space[0].cursor=0;      /*设置已用静态单链表的头指针指向位置0*/
	for(k=0;k<Maxsize-1;k++)
		space[k].cursor=k+1;    /*连链*/
	space[Maxsize-1].cursor=0;    /*标记链尾*/
	*av=1;  /*设置备用链表头指针初值*/
}