Node *Locate( LinkList L,ElemType key)
/*在带头结点的单链表L中查找其结点值等于key的结点，若找到则返回该结点的位置p，否则返回NULL*/ 
{ 
	Node *p;
	p=L->next;    /*从表中第一个结点开始 */
	while (p!=NULL)
	{
		if (p->data!=key)
			p=p->next; 
		else  
			break;      /*找到结点值=key时退出循环 */
	}
	return p;
} 