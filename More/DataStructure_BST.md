二叉查找树，也称排序二叉树，是指一棵空树或者具备下列性质的二叉树(每个结点都不能有多于两个儿子的树)：

1. 若任意结点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
2. 若任意结点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
3. 任意结点的左、右子树也分别为二叉查找树；
4. **没有键值相等的结点**。

从其性质可知，定义排序二叉树树的一种自然的方式是递归的方法，其算法的核心为递归过程，由于它的平均深度为O(logN)，所以递归的操作树，一般不必担心栈空间被耗尽。

BST 的结点结构体定义如下，结点中除了 key 域，还包含域 left, right 和 parent，它们分别指向结点的左儿子、右儿子和父结点：

    typedef struct Node
    {
        int key;
        Node* left;
        Node* right;
        Node* parent;
    } *BSTree;

## 插入结点

由于二叉查找树是递归定义的，插入结点的过程是：若原二叉查找树为空，则直接插入；否则，若关键字 k 小于根结点关键字，则插入到左子树中，若关键字 k 大于根结点关键字，则插入到右子树中。

    int BST_Insert(BSTree *T, int k, Node* parent=NULL)
    {
        if(T == NULL)
        {
            T = (BSTree)malloc(sizeof(Node));
            T->key = k;
            T->left = NULL;
            T->right = NULL;
            T->parent = parent;
            return 1;  // 返回1表示成功
        }
        else if(k == T->key)
            return 0;  // 树中存在相同关键字
        else if(k < T->key)
            return BST_Insert(T->left, k, T);
        else
            return BST_Insert(T->right, k, T);
    }

## 搜索结点

BST 的查找是从根结点开始，若二叉树非空，将给定值与根结点的关键字比较，若相等，则查找成功；若不等，则当给定值小于根结点关键字时，在根结点的左子树中查找，否则在根结点的右子树中查找。显然，这是一个递归的过程。

    Node* BST_Search(BSTree *T, int k)
    {
    	if(T == NULL || k == T->key)
    		return T;
    	if(k < T->key)
    		return BST_Search(T->left, k);
    	else
    		return BST_Search(T->right, k);
    }

也可以使用非递归的实现：

    Node* BST_Search_NonRecur(BSTree *T, int k)
    {
    	while(T != NULL && k != T->key)
    	{
    		if(k < T->key)
    			T = T->left;
    		else
    			T = T->right;
    	}
    	return T;
    }

由二叉查找树的性质可知，最左下结点即为关键字最小的结点，最右下结点即为关键字最大的结点。

## 删除结点

二叉查找树的删除操作是相对复杂一点，它要按 3 种情况来处理：

1. 若被删除结点 z 是叶子结点，则直接删除，不会破坏二叉排序树的性质；
2. 若结点 z 只有左子树或只有右子树，则让 z 的子树成为 z 父结点的子树，替代 z 的位置；
3. 若结点 z 既有左子树，又有右子树，则用 z 的直接前驱（或后继）代替 z，然后从二叉查找树中删除这个前驱（或后继）结点，这样就转换成了第一或第二种情况。（**这里z的前驱一定为z的左子树中值最大的结点，前驱一定为叶子结点或者前驱只有左子树**）。

删除一个有左、右子树的结点的示意图（用前驱替换被删除结点）如下：

![][1]

`前驱`和`后继`即为该结点在中序遍历中的前一个结点和后一个结点。如果所有的关键字均不相同，则某结点 x 的后继是：

* 若结点 x 的右子树不为空，则 x 的后继就是它的右子树中值最小的结点；
* 若结点 x 的右子树为空，为了找到其后继，从结点 x 开始向上查找，直到遇到一个祖先结点 y，它的左儿子为 x 或者为结点 x 的祖先，则结点 y 就是结点 x 的后继。如下图

如下图：

![][2]

寻找后继结点的实现如下：

    Node* BST_Successor(Node* node)
    {
        if(node->right != NULL)
            return BST_Minimum(node->right);
        Node* p = node->parent;
        while(p!=NULL && p->right == node)
        {
            node = p;
            p = p->parent;
        }
        return p;
    }

其中 BST_Minimum 返回值最小的结点，即最左下方的结点，实现如下：

    Node* BST_Minimum(BSTree *T)
    {
    	while(T->left != NULL)
    		T = T->left;
    	return T;
    }

参考：
[二叉查找树（BST）](http://songlee24.github.io/2015/01/13/binary-search-tree/)


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/DataStructure_BST_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/DataStructure_BST_2.png


