int  like(BiTree  b1,  BiTree  b2) 
{ 
	int like1, like2;
	if (b1==NULL && b2==NULL)  
		return (1);
	else 
		if (b1==NULL || b2==NULL) 
			return (0);
		else 
		{
			like1=like(b1->LChild, b2->LChild);
			like2=like(b1->RChild, b2->RChild);
			return (like1 && like2);
		}
}