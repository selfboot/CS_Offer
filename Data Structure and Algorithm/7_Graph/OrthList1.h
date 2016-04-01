/*图的十字链表结构形式化定义如下：*/
#include <malloc.h>
#include <stdio.h>
#define MAX_VERTEX_NUM 10              /*最多顶点个数*/
#define INFINITY 32768             /*表示极大值，即∞*/
#define True 1
#define False 0

#define Error -1
#define Ok 1
typedef enum{DG, DN, UDG, UDN} GraphKind;  /*图的种类*/
typedef char VertexData;    /*假设顶点数据为字符型*/


typedef struct ArcNode 
{
	int tailvex,headvex;  
	struct ArcNode *hlink,*tlink;    
}ArcNode;

typedef struct VertexNode
{
	VertexData data;    /*顶点信息*/
	ArcNode *firstin,*firstout;   
}VertexNode;

typedef struct
{
	VertexNode vertex[MAX_VERTEX_NUM];   
	int vexnum,arcnum;   /*图的顶点数和弧数*/
	GraphKind kind;              /*图的种类*/
}OrthList;      /*图的十字链表表示法(Orthogonal List)*/

int LocateVertex(OrthList *G,VertexData v)    /*求顶点位置函数*/
{
	int j=Error,k;
	for(k=0;k<G->vexnum;k++)
		if(G->vertex[k].data==v)
		{ 
			j=k; 
			break; 
		}
	return(j);
}