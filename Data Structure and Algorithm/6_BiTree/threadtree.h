#include <stdio.h>
#include <malloc.h>
#include <conio.h>

typedef char DataType;

typedef struct Node
{
	DataType data;
	int      Ltag;
	int      Rtag;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;
