#define MAX_VERTEX_NUM 20              /*最多顶点个数*/
#define INFINITY 32768             /*表示极大值，即∞*/
#define True 1
#define False 0
#define Error -1
#define Ok 1
typedef enum{DG, DN, UDG, UDN} GraphKind;  /*图的种类*/
typedef char VertexNode;    /*假设顶点数据为字符型*/
typedef struct EdgeNode 
{
	int mark,ivex,jvex;
	struct EdgeNode *ilink,*jlink;
}EdgeNode;

typedef struct 
{
    	VertexData data;
    	EdgeNode *firstedge;
}VertexNode;

typedef struct
{
    	VertexNode vertex[MAX_VERTEX_NUM];   
    	int vexnum,arcnum;           /*图的顶点数和弧数*/
    	GraphKind kind;                     /*图的种类*/
}AdjMultiList;         /*基于图的邻接多重表表示法(Adjacency Multi_list)*/
