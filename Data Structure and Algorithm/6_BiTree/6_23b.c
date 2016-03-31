int Merge_2 ( MFSst  *SS,  int  root1,  int  root2 )
/* root1和root2是并查集SS中两个互不相交的非空子集树的根，根结点的parent域存放树中结点数目的负值。本算法将结点数目较少的子集树并入结点数目较多的子集树。*/
{
    if ( root1<0 || root1> SS->nodenum-1 )  return  ERROR;
    if ( root2<0 || root2> SS->nodenum-1 )  return  ERROR;
    if ( SS->tree[root1].parent < SS->tree[root2].parent )  /* 第一棵子集树中结点数目较多 */
    {  
        SS->tree[root2].parent=root1;
        SS->tree[root1].parent+= SS->tree[root2].parent ;
     }
    else  /* 第二棵子集树中结点数目较多 */
    {  
        SS->tree[root1].parent=root2;
        SS->tree[root2].parent+= SS->tree[root1].parent ;
     }
    return OK;
}
