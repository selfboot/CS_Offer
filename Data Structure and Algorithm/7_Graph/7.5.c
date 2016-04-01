/*用邻接矩阵方式实现深度优先搜索*/
void DepthFirstSearch(AdjMatrix g,int v0)  /* 图g 为邻接矩阵类型AdjMatrix */ 
{
	visit(v0);
	visited[v0]=True;
	for(vj=0;vj<n;vj++)
	    if(!visited[vj]&&g.arcs[v0][vj].adj==1) 
		DepthFirstSearch(g,vj);
}/* DepthFirstSearch */
