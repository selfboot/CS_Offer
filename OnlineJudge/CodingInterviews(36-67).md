## 36 数组中的逆序对

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

    class Solution {
    public:
        int InversePairs(vector<int> data) {
            if(data.empty()){
                return 0;
            }
    
            vector<int> sort_data(data.size(), 0);  // 额外的数组保存排序后的结果
            return countMergeSort(data, 0, data.size(), sort_data);
        }
    
        // 将 data[begin: end) 排序, 结果保存在result中, 返回逆序对的数目
        int countMergeSort(vector<int> data, int begin, int end, vector<int>&result){
            if(begin+1==end){
                result[0] = data[begin];
                return 0;
            }
            int mid = begin+(end-begin)/2;
            vector<int> left(mid-begin, 0);
            vector<int> right(end-mid, 0);
            int left_i = mid-begin-1;   // 左部分最后一个元素下标
            int right_i = end-mid-1;    // 右部分最后一个元素下标
    
            int left_count = countMergeSort(data, begin, mid, left);
            int right_count = countMergeSort(data, mid, end, right);
    
            int index = end-begin-1;    // 有序数组最后一个元素下标
            // Merge 操作
            int count=0;
            while(left_i>=0 && right_i>=0){
                if(left[left_i]>right[right_i]){
                    result[index--]=left[left_i--];
                    count += right_i+1;
                }
                else{
                    result[index--]=right[right_i--];
                }
            }
            while(left_i>=0){
                result[index--] = left[left_i--];
            }
            while(right_i>=0){
                result[index--] = right[right_i--];
            }
            return left_count+right_count+count;
        }
    };

## 37 链表公共结点

输入两个链表，找出它们的第一个公共结点。

    class Solution {
    public:
        ListNode* FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2) {
        	ListNode *p1 = pHead1;
            ListNode *p2 = pHead2;
            while(p1!=p2){
                p1 = (p1==NULL ? pHead2 : p1->next);
                p2 = (p2==NULL ? pHead1 : p2->next);
            }
            return p1;
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

# 40 数组中只出现一次的数字

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。

    class Solution {
    public:
        void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
            if(data.size()<2){
                *num1 = 0, *num2 = 0;
                return;
            }
    		int xor_nums = 0;
            for(int &n : data){
                xor_nums ^= n;
            }
            xor_nums &= -xor_nums;
            *num1 = 0, *num2 = 0;
            for(int &n : data){
                if(n & xor_nums){
                    *num1 ^= n;
                }
                else{
                    *num2 ^= n;
                }
            }
            return;
        }
    };

## 41 和为S的连续正数序列

输入一个正数 s，打印出所有和为 s 的连续正数序列（至少有两个数字）。例如输入15，由于 1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、4～6和7～8。

    class Solution {
    public:
        vector<vector<int> > FindContinuousSequence(int sum) {
            vector<vector<int>> ans;
            if(sum < 3){
                return ans;
            }
            int small = 1;
            int big = 2;
            int add = small + big;
            int mid = (sum+1)/2;
            while(small < mid){
                if(add == sum){
                    vector<int> one;
                    get_vector(small, big, one);
                    ans.push_back(one);
                }
                while (add > sum && small < mid){
                    add -= small;
                    small += 1;
                    if(add == sum){
                        vector<int> one;
                        get_vector(small, big, one);
                        ans.push_back(one);
                    }
                }
                big += 1;
                add += big;
            }
            return ans;
        }
    
    private:
        void get_vector(int small, int big, vector<int> &arr){
            for(int i=small; i<=big; i++){
                arr.push_back(i);
            }
        }
    };

## 42（1）翻转单词顺序列

输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符合和普通字母一样处理。例如输入字符串"I am a student"，则输出 "Student. a am I"。

    class Solution {
    public:
        string ReverseSentence(string str) {
            reverse(str.begin(), str.end());
            string ans="";
            int start=0;
            int i=0;
            while(i<str.size()){
                while(i<str.size() && str[i] != ' '){
                    i++;
                }
                string word = str.substr(start, i-start);
                reverse(word.begin(), word.end());
                ans += word;
                while(i<str.size() && str[i]==' '){
                    start = ++i;
                    ans += ' ';
                }
            }
            return ans;
        }
    };

## 42（2）左旋转字符串

字符串的坐旋转操作是把字符串前面的若干个字符移到字符串的尾部。请定义一个函数实现字符串坐旋转操作的功能。比如输入字符串"abcdefg"和2，该函数返回左旋转2位得到的结果"cdefgab"。

笨方法

    class Solution {
    public:
        string LeftRotateString(string str, int n) {
            if(n<=0)    return str;
            if(str.size()==0)   return string();
            n %= str.size();
            string pre_half = str.substr(0, n);
            reverse(pre_half.begin(), pre_half.end());
            string post_half = str.substr(n, str.size()-n);
            reverse(post_half.begin(), post_half.end());
            string ans = pre_half + post_half;
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

`机智的方法`

    class Solution {
    public:
        string LeftRotateString(string str, int n) {
            int len = str.length();
            if(len == 0) return "";
            n = n % len;
            str += str;
            return str.substr(n, len);
        }
    };

## 44 扑克牌顺子

从扑克牌中随机抽取 5 张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10 为数字本身，A 为 1，J 为 11，Q 为12，K 为13，而大、小王可以看成任意数字。

    class Solution {
    public:
        bool IsContinuous( vector<int> numbers ) {
            if(numbers.size()!=5)   return false;
            sort(numbers.begin(), numbers.end());
            int zero_cnt = 0;
            for(auto &n: numbers){
                if(n == 0)  zero_cnt += 1;
                else        break;
            }
            int gap_cnt = 0;
            for(int i=zero_cnt+1;i<5;i++){
                if(numbers[i]==numbers[i-1] && numbers[i]!=0)
                    return false;
                gap_cnt += numbers[i] - numbers[i-1] - 1;
            }
            return zero_cnt >= gap_cnt;
        }
    };

## 45 圆圈中最后剩下的数

0,1,...,n-1 这 n 个数字排成一个圆圈，从数字0开始每次从这个圆圈里删除第 m 个数字。求出这个圆圈里剩下的最后一个数字。

    class Solution {
    public:
        int LastRemaining_Solution(unsigned int n, unsigned int m)
        {
            if(n<1 || m<1)  return -1;
            int remain = 0;
            for(int i=2;i<=n;i++){
                remain = (remain + m) % i;
            }
            return remain;
        }
    };

## 46 求1+2+3+...+n

求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

1. 利用逻辑与的短路特性

        class Solution {
        public:
            int Sum_Solution(int n) {
                int sum=n;
                n && (sum += Sum_Solution(n-1));
                return sum;
            }
        };

2. 用函数指针做

        class Solution {
        public:
            typedef int (*fun_ptr)(int n);
        
            int Sum_Solution(int n) {
                return sum_recursive(n);
            }
            static int sum_recursive(int n){
                fun_ptr f[2]={&Solution::sum_terminate, &Solution::sum_recursive};
                return n+f[!!n](n-1);
            }
            static int sum_terminate(int n){
                return 0;
            }
        };

## 47 不用加减乘除做加法

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
    
## 51 数组中重复的数字

在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是重复的数字2或者3。

    class Solution {
    public:
       bool duplicate(int numbers[], int length, int* duplication) {
            int i=0;
            while(i<length){
                while(i!=numbers[i]){
                    if(numbers[i] == numbers[numbers[i]]){
                        *duplication = numbers[i];
                        return true;
                    }
                    swap(numbers[i], numbers[numbers[i]]);
                }
                i++;
            }
            return false;
        }
    };    

## 52 构建乘积数组

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0] * A[1] * ... * A[i-1] * A[i+1] * ... * A[n-1]。不能使用除法。

    class Solution {
    public:
        vector<int> multiply(const vector<int>& A) {
            int len=A.size();
            vector<int> ans(len, 1);
    
            // 计算 A[0]*A[1]*...*A[i-1]
            for(int i=1; i<len; i++){
                ans[i] = ans[i-1]*A[i-1];
            }
            int reverse=1;
            for(int i=len-2;i>=0;i--){
                reverse *= A[i+1];
                ans[i] *= reverse;
            }
            return ans;
        }
    };

## 55 字符流中第一个不重复的字符

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。如果当前字符流没有存在出现一次的字符，返回#字符。

    class Solution
    {
    public:
        Solution():count(1){
            memset(occurrence, 0, sizeof(occurrence));
        }
        //Insert one char from stringstream
        void Insert(char ch)
        {
            if(occurrence[ch]==0){
                occurrence[ch]=count;
            }
            else{
                occurrence[ch]=-1;
            }
            count++;
        }
        //return the first appearence once char in current stringstream
        char FirstAppearingOnce()
        {
            int first_occur = numeric_limits<int>::max();
            char ch='#';
            for(int i=0; i<256; i++){
                if(occurrence[i]>0 && occurrence[i]<first_occur){
                    first_occur = occurrence[i];
                    ch = char(i);
                }
            }
            return ch;
        }
    private:
        int count;
        int occurrence[256];
    };

## 56 链表中环的入口结点
    
一个链表中包含环，请找出该链表的环的入口结点。

    class Solution {
    public:
        ListNode* EntryNodeOfLoop(ListNode* pHead)
        {
            bool hasCycle=false;
    		ListNode* fast=pHead;
            ListNode* slow=pHead;
            while(fast && fast->next){
                fast=fast->next->next;
                slow=slow->next;
                if(fast==slow){
                    hasCycle=true;
                    break;
                }
            }
            if(!hasCycle){
                return NULL;
            }
            slow = pHead;
            while(slow!=fast){
                slow=slow->next;
                fast=fast->next;
            }
            return fast;
        }
    };

## 57 删除链表中重复的结点

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

    class Solution {
    public:
        ListNode* deleteDuplication(ListNode* pHead)
        {
            if(pHead==NULL || pHead->next==NULL){
                return pHead;
            }
            if(pHead->val==pHead->next->val){
                ListNode* cur_node = pHead->next->next;
                while(cur_node && cur_node->val==pHead->val){
                    cur_node = cur_node->next;
                }
                return deleteDuplication(cur_node);
            }
            else{
                pHead->next = deleteDuplication(pHead->next);
                return pHead;
            }
        }
    };

## 58 二叉树的下一个结点

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

    class Solution {
    public:
        TreeLinkNode* GetNext(TreeLinkNode* pNode)
        {
            if(pNode==NULL) return NULL;
            if(pNode->right!=NULL){
                TreeLinkNode *right_node = pNode->right;
                while(right_node->left!=NULL){
                    right_node = right_node->left;
                }
                return right_node;
            }
            else{
                TreeLinkNode* parent_node = pNode->next;
                TreeLinkNode* cur_node = pNode;
                while(parent_node!=NULL && parent_node->left != cur_node){
                    cur_node = parent_node;
                    parent_node = parent_node->next;
                }
                return parent_node;
            }
        }
    };

## 59 对称的二叉树

请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

    class Solution {
    public:
        bool isSymmetrical(TreeNode* pRoot)
        {
            return  isSym(pRoot, pRoot);
        }
        bool isSym(TreeNode* l, TreeNode* r){
            if(l == NULL || r == NULL){
                return l==r;
            }
            if(l->val != r->val){
                return false;
            }
            
            return isSym(l->left, r->right) && isSym(l->right, r->left);
        }
    };

## 60 把二叉树打印成多行

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

    class Solution {
    public:
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int>> ans;
            if(pRoot==NULL) return ans;
    
            deque<TreeNode*> nodes;
            nodes.push_back(pRoot);
    
            while(!nodes.empty()){
                int index = 0;
                int level = nodes.size();
                vector<int> vals;
    
                // 一次扫描一整个层次
                while(index++<level){
                    TreeNode *head = nodes.front();
                    nodes.pop_front();
                    vals.push_back(head->val);
                    if(head->left!=NULL){
                        nodes.push_back(head->left);
                    }
                    if(head->right!=NULL){
                        nodes.push_back(head->right);
                    }
                }
    
                ans.push_back(vals);
            }
            return ans;
        }
    };

## 61 按之字形顺序打印二叉树

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

    class Solution {
    public:
        vector<vector<int>> Print(TreeNode* pRoot) {
            if(pRoot==NULL){
                return {};
            }
            vector<vector<int>> ans;
            deque<TreeNode*> levels{pRoot};
            bool order=true;
            while(!levels.empty()){
                vector<int> cur_level;
                int l_size = levels.size();
                for(int i=0;i<l_size;i++){
                    TreeNode* cur_node = levels.front();
                    levels.pop_front();
                    cur_level.push_back(cur_node->val);
                    if(cur_node->left)  levels.push_back(cur_node->left);
                    if(cur_node->right) levels.push_back(cur_node->right);
                }
                if(!order)  reverse(cur_level.begin(),cur_level.end());
                ans.push_back(cur_level);
                order = !order;
            }
            return ans;
        }
    };

## 62 序列化二叉树

请实现两个函数，分别用来序列化和反序列化二叉树

    class Solution {
    public:
        char* Serialize(TreeNode *root) {
            ostringstream out;
            serialize(root, out);
            const char *str = out.str().c_str();
            char *ans=new char[strlen(str)];
            strcpy(ans, str);
            return ans;
        }
        TreeNode* Deserialize(char *str) {
            string tmp(str);
            istringstream in(tmp);
            return deserialize(in);
        }
    private:
        void serialize(TreeNode *root, ostringstream &out){
            if(root!=NULL){
                out << root->val << " ";
                serialize(root->left, out);
                serialize(root->right, out);
            }
            else{
                out << "# ";
            }
        }
    
        TreeNode* deserialize(istringstream &in){
            string val;
            in >> val;
            if(val=="#"){
                return NULL;
            }
            TreeNode *root = new TreeNode(stoi(val));
            root->left = deserialize(in);
            root->right = deserialize(in);
            return root;
        }
    };

## 63 二叉搜索树的第k个结点

给定一颗二叉搜索树，请找出其中的第k大的结点。

    class Solution {
    public:
        TreeNode* KthNode(TreeNode* pRoot, unsigned int k)
        {
            unsigned int count = 0;
            vector<TreeNode*> node_stack;
            while(pRoot || !node_stack.empty()){
                if(pRoot!=NULL){
                    node_stack.push_back(pRoot);
                    pRoot = pRoot->left;
                }
                else{
                    TreeNode *tmp = node_stack.back();
                    node_stack.pop_back();
                    count += 1;
                    if(count==k){
                        return tmp;
                    }
                    pRoot = tmp->right;
                }
            }
            return NULL;
        }
    };

## 64 数据流中的中位数

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

    class Solution {
    public:
        void Insert(int num)
        {
            count+=1;
            // 元素个数是偶数时,将小顶堆堆顶放入大顶堆
            if(count%2==0){
                big_heap.push(num);
                small_heap.push(big_heap.top());
                big_heap.pop();
            }
            else{
                small_heap.push(num);
                big_heap.push(small_heap.top());
                small_heap.pop();
            }
        }
    
        double GetMedian()
        {
            if(count&0x1){
                return big_heap.top();
            }
            else{
                return double((small_heap.top()+big_heap.top())/2.0);
            }
        }
    private:
        int count=0;
        priority_queue<int, vector<int>, less<int>> big_heap;        // 左边一个大顶堆
        priority_queue<int, vector<int>, greater<int>> small_heap;   // 右边一个小顶堆
        // 大顶堆所有元素均小于等于小顶堆的所有元素.
    };

## 65 滑动窗口的最大值

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： [2,3,4], [3,4,2], [4,2,6], [2,6,2], [6,2,5], [2,5,1]。

    class Solution {
    public:
        vector<int> maxInWindows(const vector<int>& num, unsigned int size)
        {
            vector<int> ans;
            if(num.size()<size || size<=0) return ans;
            deque<int> may_value;
            for (int i = 0; i < size; i++) {
                while(!may_value.empty() && num[may_value.back()]<=num[i])
                    may_value.pop_back();
                may_value.push_back(i);
            }
            ans.push_back(num[may_value.front()]);
            for(int i=size; i<num.size(); i++){
                while(!may_value.empty() && num[may_value.back()] <= num[i])
                    may_value.pop_back();
                // 可能需要删除已经不在滑动窗口中的队列头
                if(!may_value.empty() && may_value.front() <= i-size)
                    may_value.pop_front();
                may_value.push_back(i);
                ans.push_back(num[may_value.front()]);
            }
            return ans;
        }
    };

## 66 矩阵中的路径

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。 例如 a b c e s f c s a d e e 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。

    class Solution {
    public:
        bool helper(char *matrix, int rows, int cols, int r, int l, char *str, int length, vector<vector<bool>> &visited){
            if(str[length] == '\0') return true;
            bool has_path = false;
            if(r>=0 && r <rows && l>=0 && l<cols && matrix[r*cols+l]==str[length] && !visited[r][l]){
                visited[r][l]= true;
                has_path = helper(matrix, rows, cols, r-1, l, str, length+1, visited) ||
                           helper(matrix, rows, cols, r+1, l, str, length+1, visited) ||
                           helper(matrix, rows, cols, r, l+1, str, length+1, visited) ||
                           helper(matrix, rows, cols, r, l-1, str, length+1, visited);
                if(!has_path){
                    visited[r][l]=false;
                }
            }
            return has_path;
        }
    
        bool hasPath(char* matrix, int rows, int cols, char* str)
        {
            if(matrix==NULL || rows <1 || cols < 1 || str==NULL){
                return false;
            }
            vector<vector<bool>> visited(rows, vector<bool>(cols, false));
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(helper(matrix, rows, cols, i, j, str, 0, visited)){
                        return true;
                    }
                }
            }
            return false;
        }
    };

## 67 机器人的运动范围

地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？

    class Solution {
    public:
        int digit_sum(int num){
            int sum=0;
            while(num){
                sum += num%10;
                num /= 10;
            }
            return sum;
        }
    
        void check_sum(int threshold, int rows, int cols, vector<vector<bool>> &can_visit){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(digit_sum(i)+digit_sum(j) > threshold){
                        can_visit[i][j] = false;
                    }
                }
            }
        }
    
        void moving_helper(int rows, int cols, int r, int l, vector<vector<bool>> &visited, const vector<vector<bool>> &can_visit, int &count)
        {
            if(r>=0 && r<rows && l>=0 && l<cols && can_visit[r][l] && !visited[r][l]){
                count += 1;
                visited[r][l]=true;
                moving_helper(rows, cols, r-1, l, visited, can_visit, count);
                moving_helper(rows, cols, r+1, l, visited, can_visit, count);
                moving_helper(rows, cols, r, l-1, visited, can_visit, count);
                moving_helper(rows, cols, r, l+1, visited, can_visit, count);
            }
        }
        int movingCount(int threshold, int rows, int cols)
        {
            vector<vector<bool>> can_visit(rows, vector<bool>(cols, true));
            vector<vector<bool>> visited(rows, vector<bool>(cols, false));
            check_sum(threshold, rows, cols, can_visit);
            int count = 0;
            moving_helper(rows, cols, 0, 0, visited, can_visit, count);
            return count;
        }
    
    };

