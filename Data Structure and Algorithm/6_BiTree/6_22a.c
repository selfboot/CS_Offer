int Find_1 ( MFSst  *SS,  DataType  x)
/* 确定x属于并查集SS中哪个子集合。如果不属于SS中任一子集，则返回-1，否则返回所在子集树的根结点下标。*/
{
    pos=Locate (SS, x);        /* 确定x在SS->tree[ ]中的下标 */
    if ( pos<0 )  return -1;      /* 如果x不属于SS中任一子集，则返回-1 */
    i=pos;                   /* 从pos开始，沿着双亲指针查找根结点 */
    while(SS->tree[i].parent > 0 )  
        i= SS->tree[i].parent ;
    return  i;                /* 返回x所在子集树的根结点下标 */
}
