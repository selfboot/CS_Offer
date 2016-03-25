# 剑指Offer

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

   


