#include "stdlib.h"
#include "stdio.h"

#define MAX_VERTEX_NUM 10             /*最多顶点个数*/
#define INFINITY 32768             /*表示极大值，即∞*/
#define True 1
#define False 0
#define Error -1
#define Ok 1

typedef enum{DG, DN, UDG, UDN} GraphKind;  /*图的种类：DG表示有向图, DN表示有向网, UDG表示无向图, UDN表示无向网*/
typedef char VertexData;    /*假设顶点数据为字符型*/

typedef struct ArcNode
{
	int adj;   /*对于无权图，用1或0表示是否相邻；对带权图，则为权值类型*/

} ArcNode;

typedef struct
{
	VertexData vexs[MAX_VERTEX_NUM];                        /*顶点向量*/
	ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   /*邻接矩阵*/
	int vexnum,arcnum;          /*图的顶点数和弧数*/
	GraphKind kind;                 /*图的种类标志*/
}AdjMatrix;      /*(Adjacency Matrix Graph)*/

int LocateVertex(AdjMatrix *G,VertexData v)    /*求顶点位置函数*/
{
	int j=Error,k;
	for(k=0;k<G->vexnum;k++)
		if(G->vexs[k]==v)
		{ 
			j=k; 
			break; 
		}
	return(j);
}
