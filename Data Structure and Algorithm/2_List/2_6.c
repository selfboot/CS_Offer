void CreateFromHead(LinkList   L)
{ 
	Node   *s;
	char 	c;
	int 	flag=1;
 	while(flag)   /* flag初值为1，当输入"$"时，置flag为0，建表结束*/
	{
		c=getchar();   
		if(c!='$')
		{
			s=(Node*)malloc(sizeof(Node)); /*建立新结点s*/
			s->data=c;
			s->next=L->next;/*将s结点插入表头*/
			L->next=s;
		}
		else
			flag=0;
	}
}
