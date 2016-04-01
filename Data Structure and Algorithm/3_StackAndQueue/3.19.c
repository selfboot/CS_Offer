int EnterQueue(LinkQueue *Q,QueueElementType x)
{  
	/* 将数据元素x插入到队列Q中 */
	LinkQueueNode  *NewNode;
	NewNode=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(NewNode!=NULL)
	{
		NewNode->data=x;
		NewNode->next=NULL;
		Q->rear->next=NewNode;
	  	Q->rear=NewNode;
		return(TRUE);
	}
	else  return(FALSE);    /* 溢出！*/
}
