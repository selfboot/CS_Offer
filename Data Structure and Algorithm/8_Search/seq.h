#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 20 

typedef char KeyType;
typedef int OtherType;

typedef struct
{
	KeyType key;
	OtherType other_data;
}RecordType;

typedef struct
{
	RecordType  r[LIST_SIZE+1];  /* r[0]为工作单元 */
	int length;
}RecordList;
