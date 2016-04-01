/*用邻接表方式实现深度优先搜索*/
void DepthFirstSearch(AdjList g,int v0)   /*图g为邻接表类型AdjList */
{
	visit(v0);
	visited[v0]=True;
	p=g.vertex[v0].firstarc;
	while(p!=NULL)
	{
		if(!visited[p->adjvex])
			DepthFirstSearch(g,p->adjvex);
		p=p->nextarc;
	}
}/*DepthFirstSearch*/
