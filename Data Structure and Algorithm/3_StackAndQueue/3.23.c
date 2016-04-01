int DeleteQueue(SeqQueue *Q,QueueElementType *x)
{ 
	/*删除队列的队头元素，用x返回其值*/
	if(Q->front==Q->rear)  /*队列为空*/
		return(FALSE);
	*x=Q->element[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;  /*重新设置队头指针*/
	return(TRUE);  /*操作成功*/
}
