typedef unsigned int WeightType;
typedef WeightType AdjType;
typedef SeqList VertexSet;

ShortestPath_DJS(AdjMatrix g,int v0,WeightType dist[MAX_VERTEX_NUM],VertexSet path[MAX_VERTEX_NUM])
/* path[i]中存放顶点i的当前最短路径。dist[i]中存放顶点i的当前最短路径长度*/
{ 
	VertexSet s;                  /*  s为已找到最短路径的终点集合 */
	for(i=0;i<g.vexnum;i++)      /* 初始化dist[i]和path [i]  */
	{ 
		InitList(&path[i]);
		dist[i]=g.arcs[v0][i].adj;
		if(dist[i]<INFINITY)
		{ 
			AddTail(&path[i],g.vexs[v0]);  /* AddTail为表尾添加操作*/
			AddTail(&path[i],g.vexs[i]);
        	}
	}
	InitList(&s);
	AddTail(&s,g.vexs[v0]);      /* 将v0看成第一个已找到最短路径的终点*/
/*以上部分完成了对向量最短路径长度dist[ ]，路径path[],顶点集s[]的初始化工作*/

/*以下部分通过n-1次循环，将第二组顶点集V-S中的顶点按照递增有序方式加入到S集合中，并求得从顶点v0出发到达图中其余顶点的最短路径。*/
	for(t=1;t<=g.vexnum-1;t++)  /*求v0到其余n-1个顶点的最短路径(n= g.vexnum )*/
	{ 
		min=INFINITY;
		for(i=0;i<g.vexnum;i++)
		if(!Member(g.vex[i],s)&&dist[i]<min)  
		{
			k =i; 
			min=dist[i];
		}
		AddTail(&s,g.vexs[k]);
		for(i=0;i<g.vexnum;i++)     /*修正dist[i],  i∈V-S*/
			if(!Member(g.vex[i],s)&&g.arcs[k][i].adj!=INFINITY&&(dist[k]+g.arcs[k][i].adj<dist[i]))
			{
				dist[i]=dist[k]+g.arcs[k][i].adj;
				path[i]=path[k];
				AddTail(&path[i],g.vexs[i]);      /* path[i]=path[k]∪{Vi} */
			}
	}
}
