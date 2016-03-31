/*用非递归过程实现深度优先搜索*/
void DepthFirstSearch(Graph g,int v0)  /*从v0出发深度优先搜索图g*/
{
	InitStack(S);  /*初始化空栈*/
	Push(S,v0);
	while(!Empty(S))
	{ 
		v=Pop(S);  
		if(!visited(v))  /*栈中可能有重复结点*/
		{ 
			visit(v);  
			visited[v]=True; 
                                          w=FirstAdjVertex(g,v);  /*求v的第一个邻接点*/
		              while(w!=-1)
		              {	
			     if(!visited(w))  
				Push(S,w);
			     w=NextAdjVertex(g,v,w);  /*求v相对于w的下一个邻接点*/
		              }
		}
		
	}
}
