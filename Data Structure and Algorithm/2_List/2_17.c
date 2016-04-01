int	DlinkDel(DoubleList L,int i,ElemType *e)
{
	DNode  *p;
	int k;
	p=L;  
	k=0;                     /*从"头"开始，查找第i个结点*/
	while(p->next!=L && k<i)  /*表未查完且未查到第i个时重复，找到p指向第i个*/ 
	{ 
		p=p->next;
		k=k+1; 
	}								
	if(p->next == L)       
	{ 
		return ERROR;
	}
	else
	{
		*e=p->data;
		p->prior->next=p->next;
		p->next->prior=p->prior;
		free(p);
		return OK;
	}
}

