
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

## 20 二叉树的镜像

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



## 栈的压入、弹出序列

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
            return  stack.empty();
        }
    };


## 复制复杂链表

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

# 平衡二叉树

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

    class Solution {
    public:
        bool isBalanced(TreeNode* root, int &height){
            if(!root){
                return true;
            }
            int left = 0;
            int right = 0;
            if (isBalanced(root->left, left) && isBalanced(root->right, right)){
                int diff = left - right;
                if (diff < -1 or diff > 1){
                    return false;
                }
                height = (left > right ? left: right) + 1;
                return true;
            }
            return false;
        }
        bool IsBalanced_Solution(TreeNode* pRoot) {
            int height = 0;
            return isBalanced(pRoot, height);
        }
    };

# 数组中出现次数超过一半的数字

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

# 把数组排成最小的数

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

## 39 二叉树的深度 

1. 输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

        class Solution {
        public:
            int TreeDepth(TreeNode* pRoot)
            {
            	if(pRoot == NULL){
                    return 0;
                }
                return max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
            }
        };

2. 输入一棵二叉树，判断该二叉树是否是平衡二叉树。

        class Solution {
        public:
            bool IsBalanced_Solution(TreeNode* pRoot) {
                int height = 0;
        		return isBalanced(pRoot, height);
            }
            
            // 后序遍历，避免重复访问同一个节点
            bool isBalanced(TreeNode* node, int &height){
                if(node == NULL){
                    height = 0;
                    return true;
                }
                int left_h=0, right_h=0;
                if(isBalanced(node->left, left_h) && isBalanced(node->right, right_h)){
                    int diff = left_h - right_h;
                    if(diff <= 1 && diff >= -1){
                        height = (left_h > right_h ? left_h : right_h)+1;
                        return true;
                    }
                }
                return false;
            }
        };

# 47 不用加减乘除做加法

写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。

    class Solution {
    public:
        int Add(int num1, int num2)
        {
    		int sum, carry;
            do{
                sum = num1 ^ num2;
                carry = (num1&num2) << 1;
                
                num1 = sum;
                num2 = carry;
            }while(num2!=0);
            
            return sum;
        }
    };

