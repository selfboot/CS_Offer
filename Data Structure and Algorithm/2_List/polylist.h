
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK   1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct Polynode 
{
	int coef;
	int exp;
	Polynode *next;
}Polynode, *Polylist;
