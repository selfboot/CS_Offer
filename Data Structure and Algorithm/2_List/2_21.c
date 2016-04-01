void polycreate(Polylist head)
{
	Polynode *rear, *s;
	int c,e;
	rear=head;	                            /* rear 始终指向单链表的尾，便于尾插法建表*/
	scanf("%d,%d",&c,&e);                   /*键入多项式的系数和指数项*/
	while(c!=0)	                            /*若c=0，则代表多项式的输入结束*/
	{
		s=(Polynode*)malloc(sizeof(Polynode));	/*申请新的结点*/
		s->coef=c;
		s->exp=e;
		rear->next=s;		/*在当前表尾做插入*/
		rear=s;
		scanf("%d,%d",&c,&e); 
	}
	rear->next=NULL;	/*将表的最后一个结点的next置NULL，以示表结束*/
}