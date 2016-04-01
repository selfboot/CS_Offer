void InsNode(BiTNode *p ,  BiTNode *r)
{
	BiTNode *s;
	if(p->Rtag==1)    /* p无右孩子 */
	{
		r->RChild=p->RChild;  /* p的后继变为r的后继 */
		r->Rtag=1;
		p->RChild=r;  /* r成为p的右孩子 */
		r->LChild=p;  /* p变为r的前驱 */
		r->Ltag=1;
	}
	else  /* p有右孩子 */
	{ 
		s=p->RChild;
		while(s->Ltag==0)
			s=s->LChild;  /* 查找p结点的右子树的"最左下端"结点 */
		r->RChild=p->RChild;  /* p的右孩子变为r的右孩子 */
		r->Rtag=0;
		r->LChild=p;  /* p变为r的前驱 */
		r->Ltag=1;
		p->RChild=r;  /* r变为p的右孩子 */
		s->LChild=r;  /* r变为p原来右子树的"最左下端"结点的前驱 */
	}
}
