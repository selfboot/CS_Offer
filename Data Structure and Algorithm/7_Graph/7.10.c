/*普里姆算法描述如下：*/
struct 
{
	VertexData adjvex;
    	int lowcost;
}closedge[MAX_VERTEX_NUM];   /* 求最小生成树时的辅助数组*/

MiniSpanTree_Prim(AdjMatrix gn,VertexData u)
/*从顶点u出发，按普里姆算法构造连通网gn 的最小生成树，并输出生成树的每条边*/
{
	k=LocateVertex(gn, u);
	closedge[k].lowcost=0;   /*初始化，U={u} */
	for(i=0;i<gn.vexnum;i++)    
		if (i!=k)    /*对V-U中的顶点i，初始化closedge[i]*/
	    	{
			closedge[i].adjvex=u; 
			closedge[i].lowcost=gn.arcs[k][i].adj;
		}
	for(e=1;e<=gn.vexnum-1;e++)    /*找n-1条边(n= gn.vexnum) */
	{
		k0=Minium(closedge);     /* closedge[k0]中存有当前最小边（u0,v0）的信息*/
		u0=closedge[k0].adjvex;   /* u0∈U*/
		v0=gn.vexs[k0];          /* v0∈V-U*/
	    	printf("%d,%d",u0, v0);    /*输出生成树的当前最小边（u0,v0）*/
		closedge[k0].lowcost=0;     /*将顶点v0纳入U集合*/
		for(i=0;i<vexnum;i++)    /*在顶点v0并入U之后，更新closedge[i]*/
			if(gn.arcs[k0][i].adj<closedge[i].lowcost)
            		{ 
				closedge[i].lowcost=gn.arcs[k0][i].adj;
				closedge[i].adjvex=v0;
			}  
	}
}
