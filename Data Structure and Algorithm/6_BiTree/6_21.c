void Initialization ( MFSst  *SS,  SeqList  *S)
/* 用S中的n个元素构造n个单根树，代表n个单元素集合S0，S1，…，Sn-1，这n个单根树构成一个森林，代表并查集SS  */
{ 
    int i;
    SS->nodenum=S->last+1;
    for(i=0;  i<SS->nodenum;  i++)
    { 
       SS->tree[i].data= S->elem[i];
       SS->tree[i].parent= -1;
    }
}
