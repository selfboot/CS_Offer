void PreTreeDepth(BiTree bt, int h)
/* 前序遍历求二叉树bt高度的递归算法，h为bt指向结点所在层次，初值为1*/
/*depth为当前求得的最大层次，为全局变量，调用前初值为0 */
{
  if(bt!=NULL)
  {
     if(h>depth)   depth = h;     /*如果该结点层次值大于depth，更新depth的值*/
     PreTreeDepth(bt->Lchild, h+1);  /* 遍历左子树 */
     PreTreeDepth(bt->Rchild, h+1);  /* 遍历右子树 */
  }
}
