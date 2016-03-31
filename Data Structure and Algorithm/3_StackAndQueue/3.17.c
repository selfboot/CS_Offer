long Fact(int n)
{
	int i;
	int fac=1;
	for(i=1;i<=n;i++)   /*ÒÀ´Î¼ÆËãf(1)¡­ f(n)*/
		fac=fac* i;        /* f(i)= f(i-1)*i */
    return fac;
}
