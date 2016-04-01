int DlinkIns(DoubleList L,int i,ElemType e)
{
	DNode  *s,*p;
	int k;
	p=L;  
	k=0;                     /*从"头"开始，查找第i-1个结点*/
	while(p->next!=L&&k<i)  /*表未查完且未查到第i-1个时重复，找到p指向第i个*/ 
	{ 
		p=p->next;
		k=k+1; 
	}									/*查找第i-1结点*/
	if(p->next == L)      /*如当前位置p为空表已找完还未数到第i个，说明插入位置不合理*/ 
	{ 
		printf("插入位置不合理!");
		return ERROR;
	}
	s=(DNode*)malloc(sizeof(DNode));
 	if (s)
	{
		s->data=e;
		s->prior=p->prior;		
		p->prior->next=s;	
		s->next=p;			
		p->prior=s;			
		return OK;
	}
	else 
		return ERROR;
}