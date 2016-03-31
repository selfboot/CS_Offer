int  search (Mbtree  mbt,  KeyType  key )
/*在mbt指向的结点中，寻找小于等于key的最大关键字序号*/
{
	int n,i;
	n = mbt->keynum ;
	i = 1 ;
	while (i <= n && mbt->key[i] <= key )  i ++;
	return (i - 1);    /* 返回小于等于key的最大关键字序号 ，为0 时表示应到
		最左分支找，越界时表示应到最右分支找 */
}