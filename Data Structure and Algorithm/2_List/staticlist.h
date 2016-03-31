#include<stdio.h>
#include<stdlib.h>

#define  Maxsize 100
#define  ElemType char

typedef  struct
{	
	ElemType data;
	int cursor;
}Component, StaticList[Maxsize];