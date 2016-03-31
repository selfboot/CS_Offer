void TinOrder(BiTree root)
{
	BiTNode *p;
	p=TinFirst(root);
	while(p!=NULL)
	{
		printf("%c  ",p->data);
		p=InNext(p);
	}
}