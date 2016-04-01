void PreOrder(BiTree root){
	if(root!=NULL){
		Visit(root->data);
		PreOrder(root->LChild);
		PreOrder(root->RChild);
	}
}
void InOrder(BiTree root){
	if(root!=NULL){
		InOrder(root->LChild);
		Visit(root->data);
		InOrder(root->RChild);
	}
}
void PostOrder(BiTree root){
	if(root!=NULL){
		PostOrder(root->LChild);
		PostOrder(root->RChild);
		Visit(root->data);
	}
}