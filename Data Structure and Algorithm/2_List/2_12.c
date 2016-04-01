int DelList(LinkList L,int i,ElemType *e)
/*在带头结点的单链表L中删除第i个元素，并将删除的元素保存到变量*e中*/
{  
	Node *pre,*r;
	int k;
	pre=L;
	k=0;
	while(pre->next!=NULL && k<i-1)	/*寻找被删除结点i的前驱结点i-1使p指向它*/
	{ 
		pre=pre->next; 
		k=k+1;
	}								/*查找第i-1个结点*/
	if(!(pre->next))     /* 即while循环是因为p->next=NULL或i<1而跳出的,而是因为没有找到合法的前驱位置，说明删除位置i不合法。*/
	{
		printf("删除结点的位置i不合理!");
		return ERROR;
	}
	r=pre->next;
	pre->next=pre->next->next;    /*修改指针，删除结点r*/
	*e = r->data;
	free(r);    /*释放被删除的结点所占的内存空间*/
	printf("成功删除结点!");
	return OK;
}