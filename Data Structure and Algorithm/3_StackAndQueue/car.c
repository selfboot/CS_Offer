/*设停车场是一个可停放n辆车的狭长通道，且只有一个大门可供汽车进出。在停车场内，汽车按到达的先后次
序，由北向南依次排列（假设大门在最南端）。若车场内已停满n辆车，则后来的汽车需在门外的便道上等候，
当有车开走时，便道上的第一辆车即可开入。当停车场内某辆车要离开时，在它之后进入的车辆必须先退出车
场为它让路，待该辆车开出大门后，其它车辆再按原次序返回车场。每辆车离开停车场时，应按其停留时间的
长短交费在便道上停留的时间不收费）。试编写程序，模拟上述管理过程。要求以顺序栈模拟停车场，以链队
列模拟便道。从终端读入汽车到达或离去的数据，每组数据包括三项：①是"到达"还是"离去"；②汽车牌照号
码；③"到达"或"离去"的时刻。与每组输入信息相应的输出信息为：如果是到达的车辆，则输出其在停车场中
或便道上的位置；如果是离去的车辆，则输出其在停车场中停留的时间和应交的费用。（提示：需另设一个栈
，临时停放为让路而从车场退出的车。）*/

/*下面给出实验用数据及其结果。

输出:1. 车辆到达 2. 车辆离开 3. 列表显示 4. 退出系统
输入:1
输出:请输入车牌号(例:陕A1234):
输入:陕A1234
输出:车辆在车厂第1位置。
输出:请输入到达时间:**:**
输入:10:00
输出:1. 车辆到达 2. 车辆离开 3. 列表显示 4. 退出系统
输入:1
输出:请输入车牌号(例:陕A1234):
输入:陕C4321
输出:车辆在车厂第2位置。
输出:请输入到达时间:**:**
输入:10:30
输出:1. 车辆到达 2. 车辆离开 3. 列表显示 4. 退出系统
输入:1
输出:请输入车牌号(例:陕A1234):
输入:陕A5678
输出:该车须在便道等待！
输出:1. 车辆到达 2. 车辆离开 3. 列表显示 4. 退出系统
输入:3
输出:请选择1|2|3:
输出:1.车场2.便道3.返回
输入:1
输出:
车场:
位置 到达时间 车牌号
1		10:00	陕A1234
2		10:30	陕C4321
输出:请选择1|2|3:
输出:1.车场2.便道3.返回
输入:2
输出:等待车辆的号码为:陕A5678
输出:请选择1|2|3:
输出:1.车场2.便道3.返回
输入:3
输出:1. 车辆到达 2. 车辆离开 3. 列表显示 4. 退出系统
输入:2
输出:请输入车在车场的位置/1--2/
输入:1
输出:请输入离开的时间:**:**
输入:11:00
输出:
离开的车牌号为:陕A1234
其到达的时间为: 10:00 离开的时间为:11:00
应缴费用为:3.0元
便道的陕A5678号车进入停车场第2位置.
请输入现在的时间**:**
输入:11:00
*/



/*源程序如下：*/


/*停车场管理系统*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*------------------------------------------------------------------------------*/

#define MAX 2 /*车库容量*/
#define price 0.05 /*每车每分钟费用*/

typedef struct time
{
	int hour;
	int min;
}Time; /*时间结点*/

typedef struct node
{
	char num[10];
	Time reach;
	Time leave;
}CarNode; /*车辆信息结点*/

typedef struct NODE
{
	CarNode *stack[MAX+1];
	int top;
}SeqStackCar; /*模拟车站*/

typedef struct car
{
	CarNode *data;
	struct car *next;
}QueueNode;

typedef struct Node
{
	QueueNode *head;
	QueueNode *rear;
}LinkQueueCar; /*模拟通道*/

/*------------------------------------------------------------------------------*/

void InitStack(SeqStackCar *); /*初始化栈*/ 
int InitQueue(LinkQueueCar *); /*初始化便道*/
int Arrival(SeqStackCar *,LinkQueueCar *); /*车辆到达*/ 
void Leave(SeqStackCar *,SeqStackCar *,LinkQueueCar *); /*车辆离开*/
void List(SeqStackCar,LinkQueueCar); /*显示存车信息*/ 

/*------------------------------------------------------------------------------*/

void main()
{
	SeqStackCar Enter,Temp;
	LinkQueueCar Wait;
	int ch;
	InitStack(&Enter); /*初始化车站*/ 
	InitStack(&Temp); /*初始化让路的临时栈*/
	InitQueue(&Wait); /*初始化通道*/
	while(1)
	{ 
		printf("\n1. 车辆到达");
		printf(" 2. 车辆离开");
		printf(" 3. 列表显示");
		printf(" 4. 退出系统\n");
		while(1)
		{
			scanf("%d",&ch);
			if(ch>=1&&ch<=4)
				break;
			else 
				printf("\n请选择： 1|2|3|4.");
		}
		switch(ch)
		{ 
		case 1:
			Arrival(&Enter,&Wait);
			break; /*车辆到达*/
		case 2:
			Leave(&Enter,&Temp,&Wait);
			break; /*车辆离开*/
		case 3:
			List(Enter,Wait);
			break; /*列表打印信息*/
		case 4:
			exit(0); /*退出主程序*/
		default: break;
		} 
	}
}

/*------------------------------------------------------------------------------*/

void InitStack(SeqStackCar *s) /*初始化栈*/ 
{ 
	int i;
	s->top=0;
	for(i=0;i<=MAX;i++)
		s->stack[s->top]=NULL;
}

int InitQueue(LinkQueueCar *Q) /*初始化便道*/
{
	Q->head=(QueueNode *)malloc(sizeof(QueueNode));
	if(Q->head!=NULL)
	{
		Q->head->next=NULL;
		Q->rear=Q->head;
		return(1);
	}
	else return(-1);
}

void PRINT(CarNode *p,int room) /*打印出站车的信息*/ 
{
	int A1,A2,B1,B2;
	printf("\n请输入离开的时间:/**:**/");
	scanf("%d:%d",&(p->leave.hour),&(p->leave.min));
	printf("\n离开车辆的车牌号为:");
	puts(p->num);
	printf("\n其到达时间为: %d:%d",p->reach.hour,p->reach.min);
	printf("离开时间为: %d:%d",p->leave.hour,p->leave.min);
	A1=p->reach.hour;
	A2=p->reach.min;
	B1=p->leave.hour;
	B2=p->leave.min;
	printf("\n应交费用为: %2.1f元",((B1-A1)*60+(B2-A2))*price);
	free(p);
}

int Arrival(SeqStackCar *Enter,LinkQueueCar *W) /*车辆到达*/ 
{ 
	CarNode *p;
	QueueNode *t;
	p=(CarNode *)malloc(sizeof(CarNode));
	flushall();
	printf("\n请输入车牌号(例:陕A1234):");
	gets(p->num);
	if(Enter->top<MAX) /*车场未满，车进车场*/
	{
		Enter->top++;
		printf("\n车辆在车场第%d位置.",Enter->top);
		printf("\n请输入到达时间:/**:**/");
		scanf("%d:%d",&(p->reach.hour),&(p->reach.min));
		Enter->stack[Enter->top]=p;
		return(1);
	}
	else /*车场已满，车进便道*/
	{ 
		printf("\n该车须在便道等待!");
		t=(QueueNode *)malloc(sizeof(QueueNode));
		t->data=p;
		t->next=NULL; 
		W->rear->next=t;
		W->rear=t;
		return(1);
	}
}

void Leave(SeqStackCar *Enter,SeqStackCar *Temp,LinkQueueCar *W)
{ /*车辆离开*/
	int room;
	CarNode *p,*t;
	QueueNode *q;
	/*判断车场内是否有车*/
	if(Enter->top>0) /*有车*/ 
	{ 
		while(1) /*输入离开车辆的信息*/ 
		{
			printf("\n请输入车在车场的位置/1--%d/：",Enter->top);
			scanf("%d",&room);
			if(room>=1&&room<=Enter->top) break;
		}
		while(Enter->top>room) /*车辆离开*/
		{
			Temp->top++;
			Temp->stack[Temp->top]=Enter->stack[Enter->top];
			Enter->stack[Enter->top]=NULL;
			Enter->top--;
		} 
		p=Enter->stack[Enter->top];
		Enter->stack[Enter->top]=NULL;
		Enter->top--;
		while(Temp->top>=1)
		{
			Enter->top++;
			Enter->stack[Enter->top]=Temp->stack[Temp->top];
			Temp->stack[Temp->top]=NULL;
			Temp->top--;
		}
		PRINT(p,room);
		/*判断通道上是否有车及车站是否已满*/
		if((W->head!=W->rear)&&Enter->top<MAX) /*便道的车辆进入车场*/
		{ 
			q=W->head->next;
			t=q->data;
			Enter->top++;
			printf("\n便道的%s号车进入车场第%d位置.",t->num,Enter->top);
			printf("\n请输入现在的时间/**:**/:");
			scanf("%d:%d",&(t->reach.hour),&(t->reach.min));
			W->head->next=q->next;
			if(q==W->rear) 
				W->rear=W->head;
			Enter->stack[Enter->top]=t;
			free(q);
		}
		else 
			printf("\n便道里没有车.\n");
	}
	else printf("\n车场里没有车."); /*没车*/ 
}

void List1(SeqStackCar *S) /*列表显示车场信息*/
{ 
	int i;
	if(S->top>0) /*判断车站内是否有车*/
	{
		printf("\n车场:");
		printf("\n 位置 到达时间 车牌号\n");
		for(i=1;i<=S->top;i++)
		{
			printf(" %d ",i);
			printf("%d:%d ",S->stack[i]->reach.hour,S->stack[i]->reach.min);
			puts(S->stack[i]->num);
		}
	}
	else printf("\n车场里没有车");
}

void List2(LinkQueueCar *W) /*列表显示便道信息*/
{ 
	QueueNode *p;
	p=W->head->next;
	if(W->head!=W->rear) /*判断通道上是否有车*/
	{
		printf("\n等待车辆的号码为:");
		while(p!=NULL)
		{
			puts(p->data->num);
			p=p->next;
		}
	}
	else printf("\n便道里没有车.");
}

void List(SeqStackCar S,LinkQueueCar W)
{
	int flag,tag;
	flag=1;
	while(flag)
	{
		printf("\n请选择 1|2|3:");
		printf("\n1.车场\n2.便道\n3.返回\n");
		while(1)
		{ 
			scanf("%d",&tag);
			if(tag>=1||tag<=3) break;
			else printf("\n请选择 1|2|3:");
		}
		switch(tag)
		{
		case 1:
			List1(&S);
			break; /*列表显示车场信息*/
		case 2:
			List2(&W);
			break; /*列表显示便道信息*/
		case 3:
			flag=0;
			break;
		default: break;
		}
	}
}
