
#include <stdio.h>
#include <stdlib.h>

#define RADIX 10
#define KEY_SIZE 6
#define LIST_SIZE 20

typedef int KeyType;
typedef int OtherType;

typedef struct 
{
	KeyType key[KEY_SIZE];      /* 子关键字数组 */ 
	OtherType other_data;        /* 其它数据项 */ 
	
	int  next;                   /* 静态链域 */ 
} RecordType1;

typedef struct 
{
	RecordType1  r[LIST_SIZE+1];  /* r[0]为头结点 */
	int length;
	int keynum;
}SLinkList;                  /* 静态链表 */

typedef int PVector[RADIX];
