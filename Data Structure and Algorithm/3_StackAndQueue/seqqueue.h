#define  TRUE 1
#define  FALSE 0

#define MAXSIZE 50  /*队列的最大长度*/

typedef struct
{
	QueueElementType  element[MAXSIZE];  /* 队列的元素空间*/
	int front;  /*头指针指示器*/
	int rear;  /*尾指针指示器*/
}SeqQueue;


/*初始化操作*/
void InitQueue(SeqQueue *Q)
{  
	/* 将*Q初始化为一个空的循环队列 */
	Q->front=Q->rear=0;
}

/*入队操作*/
int EnterQueue(SeqQueue *Q, QueueElementType x)
{  
	/*将元素x入队*/
	if((Q->rear+1)%MAXSIZE==Q->front)  /*队列已经满了*/
		return(FALSE);
	Q->element[Q->rear]=x;
	Q->rear=(Q->rear+1)%MAXSIZE;  /* 重新设置队尾指针 */
	return(TRUE);  /*操作成功*/
}

/*出队操作*/
int DeleteQueue(SeqQueue *Q, QueueElementType *x)
{ 
	/*删除队列的队头元素，用x返回其值*/
	if(Q->front==Q->rear)  /*队列为空*/
		return(FALSE);
	*x=Q->element[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;  /*重新设置队头指针*/
	return(TRUE);  /*操作成功*/
}

int GetHead(SeqQueue *Q, QueueElementType *x)
{ 
	/*提取队列的队头元素，用x返回其值*/
	if(Q->front==Q->rear)  /*队列为空*/
		return(FALSE);
	*x=Q->element[Q->front];
	return(TRUE);  /*操作成功*/
}

int IsEmpty(SeqQueue *Q)
{ 
	/*提取队列的队头元素，用x返回其值*/
	if(Q->front==Q->rear)  /*队列为空*/
		return(TRUE);
	else
		return(FALSE);  /*操作成功*/
}