int Fib(int n)
{ 
	int x,y,z,i;
	if(n==0||n==1)
		return n;    /*º∆À„ Fib (0)ªÚFib(1) */      
  	else 
  	{ 
		x=0;
		y=1;             /* x= Fib (0)  y= Fib (1) */
		for(i=2;i<=n;i++)
		{ 
			z=y;      /*  z= Fib (i-1)  */
        	                            y=x+y;    /*  y= Fib (i-1)+ Fib (i-2)  «ÛFib (i) */
        	                            x=z;      /*  x= Fib (i-1) */
	 	}
		return y ;
      	}
}
