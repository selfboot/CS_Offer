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


# 40 数组中出现次数超过一半的数字

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


