int  LayerOrder(BiTree bt)
{ 
	SeqQueue *Q;
	BiTree  p;
	Q=(SeqQueue *)malloc(sizeof(SeqQueue));
	
	InitQueue(Q);  /*初始化空队列Q*/
	if(bt == NULL)
		return ERROR; /* 若二叉树bt为空树，则结束遍历*/
	EnterQueue(Q, bt);/* 若二叉树bt非空，则根结点bt入队，开始层次遍历*/
	while(!IsEmpty(Q))/*若队列非空，则遍历为结束，继续进行*/
	{ 
		DeleteQueue(Q, &p);/*队头元素出队并访问 */
		printf("%c  ",p->data);
		if(p->LChild )  
			EnterQueue(Q, p->LChild);/*若p的左孩子非空，则进队*/
		if(p->RChild ) 
			EnterQueue(Q, p->RChild); /*若p的右孩子非空，则进队*/
	}/*while*/
	return OK;
}/* LayerOrder */
