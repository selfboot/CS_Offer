
## 4 替换空格

请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

    class Solution {
    public:
        void replaceSpace(char *str,int length) {
            if(str == NULL || length<=0){
                return;
            }
            int new_length = 0;
            int old_length = 0;
            for(int i=0;str[i]!='\0';i++){
                if(str[i] == ' '){
                    new_length += 2;
                }
                new_length ++;
                old_length ++;
            }
            if(new_length > length){
                return;
            }
            int newstr_index = new_length;
            int oldstr_index = old_length;
            while(oldstr_index>=0){
                if(str[oldstr_index]!=' '){
                    str[newstr_index--] = str[oldstr_index];
                }
                else{
                    str[newstr_index--] = '0';
                    str[newstr_index--] = '2';
                    str[newstr_index--] = '%';
                }
                oldstr_index --;
            }
            return;
        }
    };

## 5 从尾到头打印链表

输入一个链表，从尾到头打印链表每个节点的值。 

    /**
    *  struct ListNode {
    *        int val;
    *        struct ListNode *next;
    *        ListNode(int x) :
    *              val(x), next(NULL) {
    *        }
    *  };
    */
    
    class Solution {
    public:
        vector<int> printListFromTailToHead(struct ListNode* head) {
            if(head==NULL){
                return {};
            }
            stack<ListNode*> keep;
            while(head){
                keep.push(head);
                head = head->next;
            }
            vector<int> reversed;
            while(!keep.empty()){
                ListNode *tmp = keep.top();
                keep.pop();
                reversed.push_back(tmp->val);
            }
            return reversed;
        }
    };

## 6 重建二叉树

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。

    class Solution {
    public:
        struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
    		return helper(pre, 0, pre.size(), in, 0, in.size());
        }
        
        struct TreeNode* helper(const vector<int>&pre, int p_l, int p_r, const vector<int>&in, int i_l, int i_r){
            if(p_l+1 > p_r || i_l+1 > i_r){
                return NULL;
            }
            TreeNode *root = new TreeNode(pre[p_l]);
            for(int i=i_l;i<i_r;i++){
                if(in[i] == pre[p_l]){
                    root->left = helper(pre, p_l+1, p_l+1+i-i_l, in, i_l, i);
                    root->right = helper(pre, p_l+1+i-i_l, p_r, in, i+1, i_r);
                }
            }
            return root;
        }
    };

## 7 用两个栈实现队列

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

    class Solution
    {
    public:
        void push(int node) {
            stack1.push(node);
        }
    
        int pop() {
            if(stack2.empty()){
                while(!stack1.empty()){
                    int num = stack1.top();
                    stack1.pop();
                    stack2.push(num);
                }
            }
            if(stack2.empty()){
                return -1;    // pop from empty list.
            }
            int pop_num = stack2.top();
            stack2.pop();
            return pop_num;
        }
    
    private:
        stack<int> stack1;	// push
        stack<int> stack2;  // pop
    };

## 8 旋转数组的最小数字

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减序列的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

    class Solution {
    public:
        int minNumberInRotateArray(vector<int> rotateArray) {
            if(rotateArray.empty()){
                return 0;
            }
            int left=0;
            int right=rotateArray.size()-1;
            while(left<right){
                // When there is no rotate, just return self.nums[start]
                if(rotateArray[left] < rotateArray[right])   return rotateArray[left];
                int mid = left + (right-left)/2;
                if(rotateArray[left] < rotateArray[mid]){
                    left = mid+1;
                }
                else if(rotateArray[left] > rotateArray[mid]){
                    right = mid;
                }
                // Can't make sure whether left is in the left part or not.
                // Just move to right for 1 step.
                else{
                    left += 1;
                }
            }
            return rotateArray[left];
        }
    };

## 11 数值的整数次方

给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

    class Solution {
    public:
        double Power(double base, int exponent) {
            if(base-0.0 < 0.000001 && base-0.0 > -0.000001 && exponent != 0){
                return 0.0;
            }
        	if(exponent == 0){
                return 1.0;
            }
    
            bool positive = exponent > 0 ? true:false;
            exponent = abs(exponent);
            
            double result = Power(base, exponent >> 1);
            result *= result;
            if(exponent & 0x1){
                result *= base;
            }
            if(!positive){
                result = 1 / result;
            }
    		return result;
        }
    };

## 14 调整数组顺序使奇数位于偶数前面

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

    class Solution {
    public:
        void reOrderArray(vector<int> &array) {
            vector<int> even;
            auto iter = array.begin();
            while(iter!=array.end()){
                if((*iter & 0x1) == 0){
                    even.push_back(*iter);
                    array.erase(iter);
                }
                else {
                    iter++;
                }
            }
            for(auto it=even.begin(); it!=even.end(); it++){
                array.push_back(*it);
            }
            return;
    	}
    };

## 16 反转链表

定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。

    /*
    struct ListNode {
    	int val;
    	struct ListNode *next;
    	ListNode(int x) :
    			val(x), next(NULL) {
    	}
    };*/
    class Solution {
    public:
        ListNode* ReverseList(ListNode* pHead) {
    		ListNode *pre_head = NULL;
            while(pHead!=NULL){
                ListNode *next_node = pHead->next;
                pHead->next = pre_head;
                pre_head = pHead;
                pHead = next_node;
            }
            return pre_head;
        }
    };

## 17 合并两个排序的链表

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

递归法

    class Solution {
    public:
        ListNode* Merge(ListNode* l1, ListNode* l2)
        {
            if(l1==NULL)    return l2;
            if(l2==NULL)    return l1;
    
            ListNode *head = NULL;
            if(l1->val <= l2->val){
                head = l1;
                head->next = Merge(l1->next, l2);
            }
            else{
                head = l2;
                head->next = Merge(l1, l2->next);
            }
            return head;
        }
    };

迭代法（注意使用指向头指针的指针！！！）

    class Solution {
    public:
        ListNode* Merge(ListNode* l1, ListNode* l2)
    	{
            ListNode *pre_head = new ListNode(0);
            ListNode *cur = pre_head;
            while(l1!=NULL && l2!=NULL){
                if(l1->val <= l2->val){
                    cur->next = l1; // 这里是关键
                    l1 = l1->next;
                }
                else{
                    cur->next = l2;
                    l2 = l2->next;
                }
                cur = cur->next;    // 更新指针
            }
            while(l1!=NULL){
                cur->next = l1;
                l1 = l1->next;
                cur = cur->next;
            }
            while(l2!=NULL){
                cur->next = l2;
                l2 = l2->next;
                cur = cur->next;
            }
            return pre_head->next;
        }
    };

## 18 树的子结构

输入两颗二叉树A，B，判断B是不是A的子结构。

    class Solution {
    public:
        bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
        {
            bool result = false;
            if(pRoot1 != NULL && pRoot2 != NULL){
                if(pRoot1->val == pRoot2->val){
                    result = isSubtree(pRoot1, pRoot2);
                }
                if(!result) {
                    result = HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
                }
            }
            return result;
        }
    
        bool isSubtree(TreeNode* parent, TreeNode* child){
            if(child == NULL){
                return true;
            }
            if(parent == NULL){
                return false;
            }
            if(parent->val == child->val){
                return isSubtree(parent->left, child->left) && isSubtree(parent->right, child->right);
            }
            else{
                return false;
            }
        }
    };

## 19 二叉树的镜像

操作给定的二叉树，将其变换为源二叉树的镜像。

    class Solution {
    public:
        void Mirror(TreeNode *pRoot) {
            if(pRoot == NULL){
                return;
            }
    		TreeNode *tmp = pRoot->left;
            pRoot->left = pRoot->right;
            pRoot->right = tmp;
            Mirror(pRoot->left);
            Mirror(pRoot->right);
        }
    };

## 20 顺时针打印矩阵

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16. 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

    class Solution {
    public:
        vector<int> printMatrix(vector<vector<int> > matrix) {
            if(matrix.empty() || matrix[0].empty()){
                return vector<int>{};
            }
            int rows = matrix.size();
            int cols = matrix[0].size();
            vector<int> ans;
    
            int circle_start = 0;
            while(circle_start*2 < rows && circle_start*2<cols){
                int end_x = cols - 1 - circle_start;
                int end_y = rows - 1 - circle_start;
    
                // 从左向右打印
                for(int i=circle_start;i<=end_x;i++){
                    ans.push_back(matrix[circle_start][i]);
                }
    
                // 从上往下打印(保证高度至少为2)
                for(int i=circle_start+1;i<=end_y;i++){
                    ans.push_back(matrix[i][end_x]);
                }
    
                // 从右往左打印(保证宽度, 高度至少为2)
                if(circle_start < end_y){
                    for(int i=end_x-1; i>=circle_start;i--){
                        ans.push_back(matrix[end_y][i]);
                    }
                }
    
                // 从下往上打印(保证宽度, 高度至少为2)
                if(circle_start < end_x){
                    for(int i=end_y-1; i> circle_start; i--){
                        ans.push_back(matrix[i][circle_start]);
                    }
                }
                circle_start += 1;
            }
            return ans;
        }
    };

## 21 包含min函数的栈

定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。

    class Solution {
    public:
        void push(int value) {
            data.push(value);
            if(min_n.empty() || value <= min()){
                min_n.push(value);
            }
        }
    
        void pop() {
            if(top() == min()){
                min_n.pop();
            }
            data.pop();
        }
    
        int top() {
            return data.top();
        }
    
        int min() {
            return min_n.top();
        }
    private:
        stack<int> data;
        stack<int> min_n;
    };

## 22 栈的压入、弹出序列

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。

    class Solution {
    public:
        bool IsPopOrder(vector<int> pushV,vector<int> popV) {
            if (pushV.empty()) {
                return false;
            }
            vector<int> stack;
            for(int i=0, j=0; i<pushV.size(); i++){
                stack.push_back(pushV[i]);
                while(j < popV.size() && stack.back() == popV[j]){
                    stack.pop_back();
                    j++;
                }
            }
            return stack.empty();
        }
    };

## 23 从上往下打印二叉树

从上往下打印出二叉树的每个节点，同层节点从左至右打印。

    /*
    struct TreeNode {
    	int val;
    	struct TreeNode *left;
    	struct TreeNode *right;
    	TreeNode(int x) :
    			val(x), left(NULL), right(NULL) {
    	}
    };*/
    class Solution {
    public:
        vector<int> PrintFromTopToBottom(TreeNode *root) {
    		if(root==NULL){
                return vector<int>{};
            }
            vector<int> nodes;
            deque<TreeNode*> que{root};
    
            while(!que.empty()){
                TreeNode *head = que.front();
                que.pop_front();
                nodes.push_back(head->val);
                if(head->left!=NULL){
                    que.push_back(head->left);
                }
                if(head->right!=NULL){
                    que.push_back(head->right);
                }
            }
            return nodes;
        }
    };

## 24 二叉搜索树的后序遍历序列

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

    class Solution {
    public:
        bool VerifySquenceOfBST(vector<int> sequence) {
    		if(sequence.empty()){
                return false;
            }
            int length = sequence.size();
            int root = sequence[length-1];
            
            vector<int> left;
            int pos=0;
            while(sequence[pos] < root){
                left.push_back(sequence[pos++]);
            }
            
            vector<int> right;
            while(pos < length-1){
                if(sequence[pos] < root){
                    return false;
                }
                right.push_back(sequence[pos++]);
            }
            // left, right 可能为空
            return (left.empty() || VerifySquenceOfBST(left)) && (right.empty() || VerifySquenceOfBST(right));
        }
    };

## 25 二叉树中和为某一值的路径

输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

    class Solution {
    public:
        vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
            vector<vector<int>> pathList;
            vector<int> path;
            pathSum(root, expectNumber, path, pathList);
            return pathList;
        }
        void pathSum(TreeNode* root, int sum, vector<int> path, vector<vector<int>> &pathList){
            if(root==NULL)  return;
            path.push_back(root->val);
            if(root->left == NULL && root->right==NULL && root->val==sum){
                pathList.push_back(path);
            }
            pathSum(root->left, sum-root->val, path, pathList);
            pathSum(root->right, sum-root->val, path, pathList);
            path.pop_back(); // backtracking
        }
    };

## 26 复制复杂链表

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），复制该链表。

    /*
    struct RandomListNode {
        int label;
        struct RandomListNode *next, *random;
        RandomListNode(int x) :
                label(x), next(NULL), random(NULL) {
        }
    };
    */
    class Solution {
    public:
        RandomListNode* Clone(RandomListNode* pHead)
        {
            if(pHead == NULL){
                return NULL;
            }
            map<RandomListNode*, RandomListNode*> dict;
            RandomListNode *cur_node = pHead;
            RandomListNode *copy_node;
            while (cur_node){
                copy_node = new RandomListNode(cur_node->label);
                dict[cur_node] = copy_node;
                cur_node = cur_node->next;
            }
    
            cur_node = pHead;
            while(cur_node){
                copy_node = dict[cur_node];
                copy_node->next = dict[cur_node->next];
                copy_node->random = dict[cur_node->random];
                cur_node = cur_node->next;
            }
    
            return dict[pHead];
        }
    };

## 27 二叉搜索树与双向链表

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
    
迭代实现（中根遍历）

    class Solution {
    public:
        TreeNode* Convert(TreeNode* pRootOfTree)
        {
        	TreeNode *head_keep = NULL;
            TreeNode *pre_node = NULL;
            
            vector<TreeNode*> stack;
            while(pRootOfTree!=NULL || !stack.empty()){
                if(pRootOfTree!=NULL){
                    stack.push_back(pRootOfTree);
                    pRootOfTree = pRootOfTree->left;
                }
                else{
                    TreeNode *cur_root = stack.back();
                    stack.pop_back();
                    
                    // 建立双向链表部分的操作
                    // 首先找到中序遍历的头部，为双向链表的头部
                    if(head_keep == NULL){
                        head_keep = cur_root;
                    	pre_node = cur_root;
                    }
                    // 建立和中序遍历的结果中前一个结点的指针关系
                    else{
                        pre_node->right = cur_root;
                        cur_root->left = pre_node;
                        pre_node = cur_root;
                    }
                    
                    pRootOfTree = cur_root->right;
                }
            }
            return head_keep;
        }
    };

递归实现如下：

    class Solution {
    public:
        TreeNode* Convert(TreeNode* pRootOfTree)
        {
            if(pRootOfTree == NULL){
                return NULL;
            }
    
            // 1. 对左子树递归进行转换
            TreeNode* left_head = Convert(pRootOfTree->left);
            if(left_head!=NULL){
                // 左子树不为空，tmp 为左子树中最后的的结点；
                TreeNode* tmp = left_head;
                while(tmp->right){
                    tmp = tmp->right;
                }
                // 建立根节点和左子树的关系
                tmp->right = pRootOfTree;
                pRootOfTree->left = tmp;
            }
          
            // 2. 对右子树递归进行转换
            TreeNode* right_head = Convert(pRootOfTree->right);
            if(right_head!=NULL){
                right_head->left = pRootOfTree;
                pRootOfTree->right = right_head;
            }
            
            return left_head == NULL ? pRootOfTree : left_head;
        }
    };

## 28 字符串的排列

输入一个字符串（可能有字符重复），按字典序打印出该字符串中字符的所有排列。例如输入字符串abc，则打印出由字符a, b, c 所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。结果请按字母顺序输出。

    class Solution {
    public:
        vector<string> Permutation(string str) {
            vector<string> ans;
            sort(str.begin(), str.end());
            helper(str, 0, ans);
            return ans;
        }
        
        void helper(string str, int begin, vector<string> &ans){
            if(begin == str.size()-1){
                ans.push_back(str);
                return;
            }
            for(int i=begin; i<str.size();i++){
                if(i!=begin && str[i]==str[begin]){
                    continue;
                }
                swap(str[i], str[begin]);
                helper(str, begin+1, ans);
            }
        }
    };

## 29 数组中出现次数超过一半的数字

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

    class Solution {
    public:
        int MoreThanHalfNum_Solution(vector<int> numbers) {
            int count = 0, num = 0, size = numbers.size();
            for(int i=0; i<size; i++){
                if (count == 0){
                    num = numbers[i];
                }
                if (num == numbers[i]){
                    count += 1;
                }
                else{
                    count -= 1;
                }
            }
            int num_cnt = 0;
            for(int i=0; i<size; i++){
                if(num == numbers[i]){
                    num_cnt += 1;
                }
            }
            if(num_cnt > size / 2){
                return num;
            }
            return 0;
        }
    };

## 30 最小的K个数

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8 这8个数字，则最小的4个数字是1,2,3,4。

    class Solution {
    public:
        vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
            if(k<=0 || k>input.size()){
                // k < size时返回空
                return vector<int>();
            }
            priority_queue<int> heap;
            for(int &n : input){
                if(heap.size() < k){
                    heap.push(n);
                }
                else{
                    if(n<heap.top()){
                        heap.pop();
                        heap.push(n);
                    }
                }
            }
    
            vector<int> ans;
            while(!heap.empty()){
                ans.push_back(heap.top());
                heap.pop();
            }
            return vector<int>(ans.rbegin(), ans.rend());
        }
    };

## 31 连续子数组的最大和

HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。你会不会被他忽悠住？

    class Solution {
    public:
        int FindGreatestSumOfSubArray(vector<int> array) {
            if(array.empty()){
                return 0;
            }
        	int length = array.size();
            int pre_sum = array[0];
            int cur_sum=0;
            int max_sum = array[0];
            for(int i=1;i<length;i++){
                cur_sum = max(array[i], pre_sum+array[i]);
                max_sum = max(cur_sum, max_sum);
                pre_sum = cur_sum;
            }
            return max_sum;
        }
    };

## 32 从1到n整数中1出现的次数

求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数。

    class Solution {
    public:
        int NumberOf1Between1AndN_Solution(int n)
        {
            if(n<=0) return 0;
            int count = 1;
            while(n){
                if(n<10){
                    break;
                }
                int digit = n % 10;
                n /= 10;
                count += n;
                if(digit == 0)	count -= 1;
                count += NumberOf1Between1AndN_Solution(n-1) * 10;
    
                // 最后一行中数组1出现的次数
                while(n){
                    if(n%10==1) count += digit+1;
                    n /= 10;
                }
            }
            return count;
        }
    };

## 33 把数组排成最小的数

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

    class Solution {
    public:
        static bool compare(const string &str1, const string &str2){
            string s1 = str1 + str2;
            string s2 = str2 + str1;
            return s1 < s2;
        }
        string PrintMinNumber(vector<int> numbers) {
            int size = numbers.size();
            if (size == 0){
                return "";
            }
            vector<string> str_num;
            for(int i=0;i<size;i++){
                stringstream s;
                s << numbers[i];
                string str = s.str();
                str_num.push_back(str);
            }
    
            sort(str_num.begin(), str_num.end(), compare);
            string result = "";
            for(int i=0;i<size;i++){
                result += str_num[i];
            }
            return result;
        }
    };

## 34 丑数

把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含因子7。习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

    class Solution {
    public:
        int GetUglyNumber_Solution(int index) {
        	vector<int> ugly_nums(index, 0);
            ugly_nums[0]=1;
            int i=1;
            int p_2=0, p_3=0, p_5=0;
            while(i<index){
                int v_2 = ugly_nums[p_2]*2;
                int v_3 = ugly_nums[p_3]*3;
                int v_5 = ugly_nums[p_5]*5;
                int val = min(v_2, min(v_3, v_5));
                ugly_nums[i] = val;
                
                // 更新指针 
                if(val==v_2)	p_2++;
                if(val==v_3)	p_3++;
                if(val==v_5)	p_5++;
                i++;
            }
            return ugly_nums[index-1];
        }
    };

## 35 第一个只出现一次的字符位置

在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符的位置。若为空串，返回-1。位置索引从0开始

    class Solution {
    public:
        int FirstNotRepeatingChar(string str) {
    		int hash[256] = {0};
            for(auto c : str){
                hash[c] ++;
            }
    		
            for(int i=0;i<str.size();i++){
                if(hash[str[i]] == 1){
                    return i;
                }
            }
            return -1;
        }
    };


