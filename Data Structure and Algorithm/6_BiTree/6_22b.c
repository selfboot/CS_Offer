int Find_2 ( MFSst  *SS,  DataType  x)
/* 确定x属于并查集SS中哪个子集合，同时调整子集树，降低其高度。如果x不属于SS中任一子集，则返回-1，否则首先找到x所在子集树的根root，然后将x及x的所有祖先（除了root）均改为root的子结点，最后返回root。 */
{
    pos=Locate (SS, x);        /* 确定x在SS->tree[ ]中的下标 */
    if ( pos<0 )  return -1;      /* 如果x不属于SS中任一子集，则返回-1 */
    i=pos;                   /* 从pos开始，沿着双亲指针查找根结点 */
    while ( SS->tree[i].parent > 0 )  
       i= SS->tree[i].parent ;
    root=i;         /*  记录x所在子集树的根结点下标  */
    i=pos;         /* 从pos开始，将x及x的所有祖先（除了root）均改为root的子结点 */
    while ( i !=root )
   {
      temp= SS->tree[i].parent ;
      SS->tree[i].parent = root;
      i= temp ;
   }
    return  root;              /* 返回x所在子集树的根结点下标 */
}
