int EnterQueue(SeqQueue *Q,QueueElementType x)
{  
	/*将元素x入队*/
	if((Q->rear+1)%MAXSIZE==Q->front)  /*队列已经满了*/
		return(FALSE);
	Q->element[Q->rear]=x;
	Q->rear=(Q->rear+1)%MAXSIZE;  /* 重新设置队尾指针 */
	return(TRUE);  /*操作成功*/
}
