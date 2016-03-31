void init_linklist(LinkList *l)/*对单链表进行初始化*/
{
	*l=(LinkList)malloc(sizeof(Node)); /*申请结点空间*/
	(*l)->next=NULL;                      /*置为空表*/
}