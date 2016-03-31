/*建立一个有向图的十字链表的算法如下：*/

#include "OrthList.h"


void  CrtOrthList(OrthList *g)
/*从终端输入n个顶点的信息和e条弧的信息，以建立一个有向图的十字链表*/
{
	int n,e;
	int i,j,k;
	char vt,vh;

	ArcNode *p;
	printf("从键盘输入图的顶点个数和弧的个数");
	fflush(stdin);
	scanf("%d,%d",&n,&e);  /*从键盘输入图的顶点个数和弧的个数*/
	g->vexnum = n;
	g->arcnum = e;
	for(i=0;i<n;i++) 
	{
		printf("输入图的顶点");
		fflush(stdin);
		scanf("%c",&g->vertex[i].data);
		g->vertex[i].firstin=NULL;g->vertex[i].firstout=NULL;
	}
	for(k=0;k<e;k++) 
	{
		printf("输入一条弧的两个顶点");
		fflush(stdin);
		scanf("%c,%c",&vt,&vh);
		i=LocateVertex(g,vt);
		j = LocateVertex(g,vh);
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->tailvex=i;
		p->headvex=j;
		p->tlink=g->vertex[i].firstout;
		g->vertex[i].firstout=p;
		p->hlink=g->vertex[j].firstin;
		g->vertex[j].firstin=p;
    }
}/* CrtOrthList */

void main()
{
	OrthList g;
	CrtOrthList(&g);
}