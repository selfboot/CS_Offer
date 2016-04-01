/*广度优先搜索联通子图的算法如下：*/
void BreadthFirstSearch(Graph g,int v0)  /*广度优先搜索图g中v0所在的连通子图*/
{
	visit(v0); 
	visited[v0]=True;
	InitQueue(&Q);  /*初始化空队*/ 
	EnterQueue(&Q,v0);/* v0进队*/
	while(!Empty(Q))
	{ 
		DeleteQueue(&Q,&v);  /*队头元素出队*/
		w=FirstAdjVertex(g,v);  /*求v的第一个邻接点*/
		while(w!=-1)
		{	
			if(!visited(w))
			{ 
				visit(w); 
				visited[w]=True;
				EnterQueue(&Q, w);
            		}
			w=NextAdjVertex(g,v,w);  /*求v相对于w的下一个邻接点*/
		}
	}
}
