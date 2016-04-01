#include <stdio.h>
#include <stdlib.h>

#define ENDKEY 0

typedef int KeyType;

typedef struct  node
{
	KeyType  key ; /*关键字的值*/
	int bf;
	struct node  *lchild,*rchild;/*左右指针*/
}AVLTNode, *AVLTree;

