int  ve[MAX_VERTEX_NUM];    /*每个顶点的最早发生时间*/

int TopoOrder(AdjList G,Stack *T) 
/* G为有向网，T为返回拓扑序列的栈，S为存放入度为0的顶点的栈*/
{   
	int count,i,j,k;  
	ArcNode *p;
	int indegree[MAX_VERTEX_NUM];  /*各顶点入度数组*/
	Stack S;
    	InitStack(T);  
	InitStack(&S);   /*初始化栈T,  S*/
    	FindID(G,indegree);  /*求各个顶点的入度*/
    	for(i=0;i<G.vexnum;i++)
		if(indegree[i]==0)	  
			Push(&S,i);
    	count=0;
    	for(i=0;i<G.vexnum;i++)
		ve[i]=0;   /*初始化最早发生时间*/
	while(!IsEmpty(&S))
	{
		Pop(&S,&j);
		Push(T,j);
		count++;
		p=G.vertex[j].firstarc;
		while(p!=NULL)
	    	{	
			k=p->adjvex;
			if(--indegree[k]==0)  
			Push(&S,k);   /*若顶点的入度减为0，则入栈*/
		    	if(ve[j]+p->Info.weight>ve[k])  
			ve[k]=ve[j]+p->Info.weight;
		    	p=p->nextarc;
	    	}  /*while*/
	} /*while*/
    	if(count<G.vexnum) 	
		return(Error);
    	else	
		return(Ok);
}
