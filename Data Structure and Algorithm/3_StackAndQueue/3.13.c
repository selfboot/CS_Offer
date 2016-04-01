#include "seqstack2.h"
#include "stdio.h"
#include <conio.h>


char ch;

int ExpEvaluation()/*读入一个简单算术表达式并计算其值。operatsign和operatdata分别为运算符栈和运算数栈，OPS为运算符集合*/
{
	char x,y;
	char op;
	int a,b,v;
	
	nStack operatdata;
	strStack operatsign;
	nInitStack(&operatdata);
	strInitStack(&operatsign);
	strPush(&operatsign,'#');
	
	printf("\nPlease input an expression (Ending with #) :\n");
    ch=getchar();

 	
 	strGetTop(&operatsign,&y);

 	while(ch!='#'||y!='#') /* strGetTop()通过函数值返回栈顶元素*/
   	{
		if(!In(ch))                   /*不是运算符，是运算数*/
		{
			
			int temp; 		   /*存放数字的临时变量*/
			temp=ch-'0';
			/*将字符转换为十进制数*/
			fflush(stdin);
			ch=getchar();
			while(!In(ch))  //用ch逐个读入运算数的各位数码，并转化为十进制数temp
			{
				temp=temp*10+ch-'0'; // 将逐个读入运算数的各位转化为十进制数
	 			fflush(stdin);
				ch=getchar();
			}  
   			nPush(&operatdata,temp);
		}
		else
      		switch(Compare(y,ch))
			{
	 			case '<': 
					strPush(&operatsign,ch); 
              		fflush(stdin);
					ch=getchar();
					break;
	 			case '=': 
					strPop(&operatsign,&x); 
					fflush(stdin);
					ch=getchar(); 
					break;
				case '>': 
					strPop(&operatsign,&op);
					nPop(&operatdata,&b);
					nPop(&operatdata,&a);
					v=Execute(a,op,b);  /* 对a和b进行op运算 */
					nPush(&operatdata,v);
					break;
			}
		strGetTop(&operatsign,&y);
	}
	nGetTop(&operatdata,&v);
	return (v);
}

void main()
{
	int result;   
    result=ExpEvaluation();
    printf("\n%d",result);
}