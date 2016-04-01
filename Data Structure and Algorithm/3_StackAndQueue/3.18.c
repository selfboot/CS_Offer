int InitQueue(LinkQueue *Q)
{ 
	/* 将Q初始化为一个空的链队列 */
	Q->front=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
 		return(TRUE);
	}
	else  	return(FALSE);    /* 溢出！*/
}
