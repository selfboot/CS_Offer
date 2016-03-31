int Merge_1 ( MFSst  *SS,  int  root1,  int  root2 )
/* root1和root2是并查集SS中两个互不相交的非空子集树的根，将子集树root2并入子集树root1。*/
{
   if ( root1<0 || root1> SS->nodenum-1 ) 
        return  ERROR;
   if ( root2<0 || root2> SS->nodenum-1 )  
        return  ERROR;
   SS->tree[root2].parent=root1;
   return OK;
}
