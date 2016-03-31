LinkList   merge_1(LinkList LA,LinkList LB)
{  /*此算法将两个采用头指针的循环单链表的首尾连接起来*/
	Node *p, *q;
	p=LA;
	q=LB;
	while (p->next!=LA)	p=p->next;	/*找到表LA的表尾，用p指向它*/
	while (q->next!=LB)	q=q->next;	/*找到表LB的表尾，用q指向它*/
	q->next=LA;	/*修改表LB 的尾指针，使之指向表LA 的头结点*/
	p->next=LB->next; /*修改表LA的尾指针，使之指向表LB 中的第一个结点*/
	free(LB);
	return(LA);
}