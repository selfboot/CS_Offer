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


