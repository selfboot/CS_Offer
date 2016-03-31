/*邻接表存储结构的形式化说明如下：*/

#define INFINITY 32768             /*表示极大值，即∞*/
#define True 1
#define False 0
#define Error -1
#define NULL 0
#define Ok 1
#define MAX_VERTEX_NUM 20             /*最多顶点个数*/
typedef enum{DG, DN, UDG, UDN} GraphKind;  /*图的种类*/
typedef char VertexNode;

typedef struct ArcNode
{
	int adjvex;     /*该弧指向顶点的位置*/
    	struct ArcNode *nextarc;    /*指向下一条弧的指针*/
    	OtherInfo info;       /*与该弧相关的信息*/
}ArcNode;

typedef struct VertexNode
{
	VertexData data;        /*顶点数据*/
    	ArcNode *firstarc;    /*指向该顶点第一条弧的指针*/
}VertexNode;

typedef struct
{
    VertexNode vertex[MAX_VERTEX_NUM];   
    int vexnum,arcnum;               /*图的顶点数和弧数*/
    GraphKind kind;                        /*图的种类标志*/
}AdjList;           /*基于邻接表的图(Adjacency List Graph)*/
