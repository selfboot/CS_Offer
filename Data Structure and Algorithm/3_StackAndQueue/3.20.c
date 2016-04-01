int DeleteQueue(LinkQueue *Q,QueueElementType *x)
{  
	/* 将队列Q的队头元素出队，并存放到x所指的存储空间中 */
	LinkQueueNode *p;
	if(Q->front==Q->rear)
		return(FALSE);
	p=Q->front->next;
	Q->front->next=p->next;  /* 队头元素p出队 */
	if(Q->rear==p)  /* 如果队中只有一个元素p，则p出队后成为空队 */
	Q->rear=Q->front;  
	*x=p->data;
	free(p);   /* 释放存储空间 */
	return(TRUE);	
}
