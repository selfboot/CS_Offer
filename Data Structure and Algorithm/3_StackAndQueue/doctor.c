#include "stdio.h"
#include "seqqueue.h"

void SeeDoctor()
{ 
	int flag=1;
	char ch;
	int n;
	SeqQueue Q;
	InitQueue(&Q);
 	
 	while(flag) 
 	{
   		printf("\n请输入命令：");
   		fflush(stdin);
		ch=getchar();
   		switch(ch) 
   		{
			case  'a':  
				printf("\n病历号：");
           		scanf("%d", &n);
           		EnterQueue(&Q, n);    /* 将新到的患者加入队列中候诊 */
           		break;
			case  'n':  
				if(!IsEmpty(&Q)) 
				{ 
					DeleteQueue(&Q,&n);    /* 下一患者出队就诊 */
					printf("\n病历号为 %d 的病人就诊", n);
                }
                else  printf("\n无病人等候就诊");
				break;
			case  'q':  
				printf("\n今天停止挂号，下列病人依次就诊：");
				while (!IsEmpty(&Q))         /* 打印所有剩余患者*/
				{ 
					DeleteQueue(&Q, &n);
					printf("%d  ",  n);
				}
				flag=0;
				break;
			default:  printf("\n非法命令！");
		}
	}
}

void main()
{
	SeeDoctor();
}