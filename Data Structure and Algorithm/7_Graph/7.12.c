void FindID(AdjList G,int indegree[MAX_VERTEX_NUM]) 
/*求各顶点的入度*/
{
	int i;   
	ArcNode *p;
    	for(i=0;i<G.vexnum;i++)
		indegree[i]=0;  
    	for(i=0;i<G.vexnum;i++)
    	{
		p=G.vertexes[i].firstarc;
	 	while(p!=NULL)
	    	{
			indegree[p->adjvex]++;
	        	p=p->nextarc;
	    	}
    	} /* for */
}
