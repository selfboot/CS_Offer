int visited[MAX_VERTEX_NUM];   /*访问标志数组*/

void TraverseGraph(Graph g)
/*对图g进行深度优先搜索，Graph 表示图的一种存储结构，如数组表示法或邻接表等*/
{
	for(vi=0;vi<g.vexnum;vi++)  
		visited[vi]=False ;/*访问标志数组初始*/
	for(vi=0;vi<g.vexnum;vi++)	/*调用深度遍历连通子图的操作*/
		if (!visited[vi])  
		     DepthFirstSearch(g,vi);	/*若图g是连通图，则此循环调用函数只执行一次*/
}/* TraverseGraph */
