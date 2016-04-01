#define  TRUE 1
#define  FALSE 0

#define MAXSIZE 50  /*队列的最大长度*/

typedef struct Node
{
	QueueElementType data;     /*数据域*/
	struct Node *next;     /*指针域*/
}LinkQueueNode;

typedef struct 
{
	LinkQueueNode *front;
	LinkQueueNode *rear;
}LinkQueue;

/*初始化操作。*/
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
	else return(FALSE);    /* 溢出！*/
}

/*入队操作。*/
int EnterQueue(LinkQueue *Q,QueueElementType x)
{  
	/* 将数据元素x插入到队列Q中 */
	LinkQueueNode *NewNode;
	NewNode=(LinkQueueNode * )malloc(sizeof(LinkQueueNode));
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

/*出队操作。*/
int DeleteQueue(LinkQueue *Q,QueueElementType *x)
{  
	/* 将队列Q的队头元素出队，并存放到x所指的存储空间中 */
	LinkQueueNode * p;
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

int GetHead(SeqQueue *Q, int *x)
{ 
	/*提取队列的队头元素，用x返回其值*/
	if(Q->front==Q->rear)  /*队列为空*/
		return(FALSE);
	*x=Q->element[Q->front];
	return(TRUE);  /*操作成功*/
}