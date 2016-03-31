#include <stdio.h>
#include <stdlib.h>

#define  m   13
#define  NULLKEY  0
typedef  int  KeyType;    /* 假设关键字为整型 */
typedef  struct
{
	KeyType  key;
}RecordType;

typedef  RecordType  HashTable[m];