
## 替换空格

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

