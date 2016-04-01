int pre[];
void one_path(Graph *G, int u, int v)
/*在连通图G中找一条从第u个顶点到v个顶点的简单路径*/
{
	int i;
    	pre=(int *)malloc(G->vexnum*sizeof(int));
    	for(i=0;i<G->vexnum;i++) 
    		pre[i]=-1;
    	pre[u]=u;               /*将pre[u]置为非-1，表示第u个顶点已被访问*/
    	DFS_path(G, u, v);       /*用深度优先搜索找一条从u到v的简单路径。*/
    	free(pre);
}

int DFS_path(Graph *G, int u, int v)
  /*在连通图G中用深度优先搜索策略找一条从u到v的简单路径。*/
{
	int j;
        	for(j=firstadj(G,u);j>=0;j=nextadj(G,u,j))
             		if(pre[j]==-1)
		          {
                  		pre[j]=u;
                  		if(j==v) 
                  		      {print_path(pre ,v); return 1;}/*输出路径*/
                  		else 
                  		      if(DFS_path(G,j,v))  return 1; 
              	          }
               return 0;
}
