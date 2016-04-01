int TopoSort(AdjList G)
{ 
	Stack S;
	int indegree[MAX_VERTEX_NUM];
	int i,count,k;
    	ArcNode *p;
    	FindID(G,indegree);  /*求各顶点入度*/
    	InitStack(&S);       /*初始化辅助栈*/
    	for(i=0;i<G.vexnum;i++)
		if(indegree[i]==0) 
			Push(&S,i);    /*将入度为0的顶点入栈*/
    	count=0;
    	while(!IsEmpty(S)) 
    	{
		Pop(&S,&i);
		printf("%c",G.vertex[i].data);
		count++;  /*输出i号顶点并计数*/
        	p=G.vertexes[i].firstarc;
		while(p!=NULL)
		{ 
			k=p->adjvex;
            		indegree[k]--;      /*i号顶点的每个邻接点的入度减1*/
		    	if(indegree[k]==0)  
			Push(&S, k);  /*若入度减为0，则入栈*/
		    	p=p->nextarc;
		}
	} /*while*/
    	if(count<G.vexnum)  
		return(Error);  /*该有向图含有回路*/
    	else  
		return(Ok);
}
