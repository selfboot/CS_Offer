Node * Get (LinkList  L, int i)
/*在带头结点的单链表L中查找第i个结点，若找到(1≤i≤n)，则返回该结点的存储位置; 否则返回NULL*/
{  
	int j;
	Node  *p;
	p=L;
	j=0;   /*从头结点开始扫描*/ 
	while ((p->next!=NULL)&&(j<i))
	{ 
		p=p->next;    /* 扫描下一结点*/
		j++;   /* 已扫描结点计数器 */
	}
	if(i == j)
		return p;   /* 找到了第i个结点 */
	else 
		return NULL;   /* 找不到，i≤0或i>n */
}   
