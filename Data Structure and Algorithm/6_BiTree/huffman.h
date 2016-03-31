
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  N 20
#define  M 2*N-1

typedef char* HuffmanCode[N+1];/*存储N个哈夫曼编码串的头指针数组*/

typedef struct 
{
	unsigned int weight ; /* 用来存放各个结点的权值*/
	unsigned int parent, LChild,RChild ; /*指向双亲、孩子结点的指针*/
}HTNode, HuffmanTree[M+1];   /*动态分配数组，存储哈夫曼树*/