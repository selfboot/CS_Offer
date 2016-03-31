void  DepthFirstSearch(Graph g,int v0) /*深度遍历v0所在的连通子图*/
{
	visit(v0);
	visited[v0]=True;/*访问顶点v0，并置访问标志数组相应分量值*/
	w=FirstAdjVertex(g,v0);
	while(w!=-1)  /*邻接点存在.*/
	{ 
		if(!visited[w])   
			DepthFirstSearch(g,w);  /*递归调用DepthFirstSearch*/
		w=NextAdjVertex(g,v0,w); /*找下一个邻接点*/
	}
} /*DepthFirstSearch*/
