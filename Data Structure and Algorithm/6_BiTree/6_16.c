BiTNode* TinFirst(BiTree root)
{
	BiTNode *p;
	p = root;
	if(p)
		while(p->LChild!=NULL)
			p=p->LChild;
	return p;
}