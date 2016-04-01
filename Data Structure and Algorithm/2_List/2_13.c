LinkList MergeLinkList(LinkList LA, LinkList LB)
/*将递增有序的单链表LA和LB合并成一个递增有序的单链表LC*/
{  
	Node *pa,*pb;
	Node *r;
	LinkList LC;
/*将LC初始置空表。pa和pb分别指向两个单链表LA和LB中的第一个结点,r初值为LC*/
	pa=LA->next;
	pb=LB->next;
	LC=LA;
	LC->next=NULL;
	r=LC;
/*当两个表中均未处理完时，比较选择将较小值结点插入到新表LC中。*/
	while(pa!=NULL && pb!=NULL)
	{
		if(pa->data <= pb->data)
		{
			r->next=pa;
			r=pa;
			pa=pa->next;
		}
		else
		{
			r->next=pb;
			r=pb;
			pb=pb->next;
		}
	}
	if(pa) /*若表LA未完，将表LA中后续元素链到新表LC表尾*/
		r->next=pa;
	else	 /*否则将表LB中后续元素链到新表LC表尾*/
		r->next=pb;
	free(LB);
	return(LC);
}
