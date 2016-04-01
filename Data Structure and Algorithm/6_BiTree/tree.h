#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct CSNode
{
	DataType  data;                  /*结点信息*/
	struct CSNode  *FirstChild;      /*第一个孩子*/
	struct CSNode  *Nextsibling;     /*下一个兄弟*/
}CSNode, *CSTree;
