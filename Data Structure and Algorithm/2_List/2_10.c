int	ListLength(LinkList L)
/*求带头结点的单链表L的长度*/
{   
	Node *p;
	int j;
	p=L->next;
	j=0;   /*用来存放单链表的长度*/
	while(p!=NULL)
	{	  
		p=p->next;
		j++;
	}
	return j;	/*j为求得的单链表长度*/
}  
