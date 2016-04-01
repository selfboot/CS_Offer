BiTNode * InPre(BiTNode *p)
/* 在中序线索二叉树中查找p的中序前驱, 并用pre指针返回结果 */
{  
	BiTNode *q;
	if(p->Ltag==1)
		pre = p->LChild;  /*直接利用线索*/
	else 
	{ /* 在p的左子树中查找"最右下端"结点 */
		for(q = p->LChild;q->Rtag==0;q=q->RChild);
		pre=q;
	}
	return(pre);
}