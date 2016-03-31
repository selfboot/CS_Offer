typedef SeqList VertexSet;

ShortestPath_Floyd(AdjMatrix g, 
	WeightType dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM],  
	VertexSet path[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
/* g为带权有向图的邻接矩阵表示法， path [i][j]为vi到vj的当前最短路径，dist[i][j]为vi到vj的当前最短路径长度*/
{
	int i,j,k;
	for(i=0;i<g.vexnum;i++)    
		for(j=0;j<g.vexnum;j++)
		{         /*初始化dist[i][j]和path[i][j] */
			InitList(&path[i][j]);
			dist[i][j]=g.arcs[i][j].adj;
			if(dist[i][j]<INFINITY)  
			{
				AddTail(&path[i][j],g.vexs[i]);
				AddTail(&path[i][j],g.vexs[j]);
			}
		}
	for(k=0;k<g.vexnum;k++)
		for(i=0;i<g.vexnum;i++)
			for(j=0;j<g.vexnum;j++)
				if(dist[i][k]+dist[k][j]<dist[i][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					paht[i][j]=JoinList(paht[i][k],paht[k][j]);  
				}    /*JoinList为合并线性表操作*/
}
