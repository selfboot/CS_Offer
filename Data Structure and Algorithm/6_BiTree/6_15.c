BiTNode * InNext(BiTNode * p) 
/*在中序线索二叉树中查找p的中序后继结点，并用next指针返回结果*/
{ 
	BiTNode *Next;
	BiTNode *q;
	if (p->Rtag==1)  
		Next = p->RChild;  /*直接利用线索*/
	else
	{ /*在p的右子树中查找"最左下端"结点*/
		if(p->RChild!=NULL)
		{
			for(q=p->RChild; q->Ltag==0 ;q=q->LChild);
			Next=q; 
		}
		else
			Next = NULL;
		
	} 
	return(Next);
}