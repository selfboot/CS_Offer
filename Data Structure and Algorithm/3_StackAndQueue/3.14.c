void hanoi(int n,char x,char y,char z)
{
	/* 将塔座X上从上到下编号为1至n，且按直径由小到大叠放的n个圆盘，
	按规则搬到塔座Z上，Y用作辅助塔座。*/
	if(n==1)
	{
		move(x,1,z);         /*将编号为1的圆盘从x移动z*/
	}
	else
	{
		hanoi(n-1,x,z,y);    /* 将X上编号为1至n-1的圆盘移到y,z作辅助塔 */
		move(x,n,z);         /* 将编号为n的圆盘从x移到z */
		hanoi(n-1,y,x,z);  /* 将y上编号为1至n-1的圆盘移到z，x作辅助塔 */ 
	}
} 
