#include "seqqueue1.h"
#include <stdio.h>

void YangHuiTriangle( )
{ 
	int n;
	int i;
	int temp;
	int x;
	int N;
	SeqQueue Q;
	InitQueue(&Q);
	EnterQueue(&Q,1);  /* 第一行元素入队*/
	printf("please input N:");
	scanf("%d",&N);
	for(n=2;n<=N;n++)   /* 产生第n行元素并入队，同时打印第n-1行的元素*/
	{
		EnterQueue(&Q,1);   /* 第n行的第一个元素入队*/
		for(i=1;i<=n-2;i++)  /* 利用队中第n-1行元素产生第n行的中间n-2个元素并入队*/
		{
			DeleteQueue(&Q,&temp);
			printf("%6d",temp);     /* 打印第n-1行的元素*/
			GetHead(&Q,&x);
			temp=temp+x;      /*利用队中第n-1行元素产生第n行元素*/
			EnterQueue(&Q,temp);  
		}
		DeleteQueue (&Q,&x);  
		printf("%6d",x);    /* 打印第n-1行的最后一个元素*/
		EnterQueue(&Q,1);   /* 第n行的最后一个元素入队*/
		printf("\n");
	}
}

void main()
{
	YangHuiTriangle( );
}
