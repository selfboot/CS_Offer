void  polyadd(Polylist polya, Polylist polyb)
/*此函数用于将两个多项式相加，然后将和多项式存放在多项式polya中，并将多项式ployb删除*/
{
	Polynode  *p, *q, *pre, *temp;
	int sum;
	p=polya->next;   /*令 p和q分别指向polya和polyb多项式链表中的第一个结点*/
	q=polyb->next;        
	pre=polya;  /* r指向和多项式的尾结点*/
	while (p!=NULL && q!=NULL) /*当两个多项式均未扫描结束时*/
	{ 
		if  (p->exp < q->exp)
			/*如果p指向的多项式项的指数小于q的指数，将p结点加入到和多项式中*/
		{ 
			pre->next=p;  
			pre=p; 
			p=p->next;
		}
		else
			if ( p->exp == q->exp)  /*若指数相等，则相应的系数相加*/
			{  
				sum=p->coef + q->coef;
				if (sum != 0)
				{ 
					p->coef=sum;
					pre->next=p; 
					pre=p;
					p=p->next;
					temp=q; 
					q=q->next; 
					free(temp);
				}
				else
				{  
					temp=p;
					p=p->next;
					free(temp); 
		/*若系数和为零，则删除结点p与q，并将指针指向下一个结点*/
					temp=q; 
					q=q->next;
					free(temp);
				}
			}
			else
			{  
				pre->next=q;
				pre=q; /*将q结点加入到和多项式中*/
				q = q->next; 
			}
	}
	if(p!=NULL)  /*多项式A中还有剩余，则将剩余的结点加入到和多项式中*/
		pre->next=p;
	else      /*否则，将B中的结点加入到和多项式中*/
		pre->next=q;
}