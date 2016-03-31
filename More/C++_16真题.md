# [添加回文串](http://www.nowcoder.com/practice/cfa3338372964151b19e7716e19987ac?rp=2&ru=/activity/oj&qru=/ta/2016test/question-ranking)

对于一个字符串，我们想通过添加字符的方式使得新的字符串整体变成回文串，但是只能在原串的结尾添加字符，请返回在结尾添加的最短字符串。给定原字符串A及它的长度n，请返回添加的字符串。保证原串不是回文串。

    class Palindrome {
    public:
        bool isPalindrome(const string &s,const int start){
            int len = s.size();
            for(int i=start;i<(len+start)/2;i++){
                if (s[i] != s[len-1-(i-start)]){
                    return false;
                }
            }
            return true;
        }
        string addToPalindrome(string A, int n) {
            // write code here
            string answers = "";
            for(int i=0; i<n;i++){
                if (not isPalindrome(A, i)){
                    answers = A[i] + answers;
                }
                else{
                    break;
                }
            }
            return answers;
        }
    };

# [纸牌博弈](http://www.nowcoder.com/practice/7036f62c64ba4104a28deee98a6f53f6?rp=3&ru=/activity/oj&qru=/ta/2016test/question-ranking)

有一个整型数组A，代表数值不同的纸牌排成一条线。玩家a和玩家b依次拿走每张纸牌，规定玩家a先拿，玩家B后拿，但是每个玩家每次只能拿走最左或最右的纸牌，玩家a和玩家b都绝顶聪明，他们总会采用最优策略。请返回最后获胜者的分数。

给定纸牌序列A及序列的大小n，请返回最后分数较高者得分数(相同则返回任意一个分数)。保证A中的元素均小于等于1000。且A的大小小于等于300。

    /**
    考虑记忆化搜索，dp[l][r]表示l..r区间内取纸牌，先手的最大收益。
    每个人要让自己收益最大，也就是让对手收益最小。
    收益是l..r区间内所有纸牌的和 - 我取了之后剩下区间对手的收益。
    */
    class Cards {
    public:
        const static int size = 300;
        int sums[size] = {0};
        int dp[size][size];
    
        int dfs_cache(const int &l, const int &r, const vector<int> &cards){
            if(l==r){
                dp[l][r] = cards[l];
            }
            if(dp[l][r]!=-1){
                return dp[l][r];
            }
            int all_sum = sums[r] - (l == 0 ? 0:sums[l-1]);
            dp[l][r] = all_sum - min(dfs_cache(l+1, r, cards), dfs_cache(l, r-1, cards));
            return dp[l][r];
        }
    
        int cardGame(vector<int> A, int n) {
            sums[0] = A[0];
            for(int i=1; i<n;i++){
                sums[i] = sums[i-1] + A[i];
            }
            memset(dp, -1, sizeof(dp));
            int first_profit = dfs_cache(0, n-1, A);
            // 最后不一定先手的利益最大
            return max(first_profit, sums[n-1]-first_profit);
        }
    };


# [股票交易日](http://www.nowcoder.com/practice/3e8c66829a7949d887334edaa5952c28?rp=6&ru=/activity/oj&qru=/ta/2016test/question-ranking)

在股市的交易日中，假设最多可进行两次买卖(即买和卖的次数均小于等于2)，规则是必须一笔成交后进行另一笔(即买-卖-买-卖的顺序进行)。给出一天中的股票变化序列，请写一个程序计算一天可以获得的最大收益。请采用实践复杂度低的方法实现。

给定价格序列prices及它的长度n，请返回最大收益。保证长度小于等于500。测试样例：
[10,22,5,75,65,80],6
返回：87

    class Stock {
    public:
        int maxProfit(vector<int> prices, int n) {
            if (n==0){
                return 0;
            }
            vector<int> pre_profit(n,0);
            vector<int> post_profit(n,0);
    
            int min_buy = prices[0];
            for(int i=1;i<n;i++){
                min_buy = min(prices[i], min_buy);
                pre_profit[i] =  max(pre_profit[i-1], prices[i]-min_buy);
            }
    
            int max_sell = prices[n-1];
            for(int j=n-2;j>=0;j--){
                max_sell = max(prices[j], max_sell);
                post_profit[j] = max(post_profit[j+1], max_sell-prices[j]);
            }
    
            int max_profit = 0;
            for(int i=0; i<n;i++){
                max_profit = max(max_profit, pre_profit[i] + post_profit[i]);
            }
            return max_profit;
        }
    };

# [比较重量](http://www.nowcoder.com/questionTerminal/ac27e60e63b549d6a9b59f815d9bc6e2)

小明陪小红去看钻石，他们从一堆钻石中随机抽取两颗并比较她们的重量。这些钻石的重量各不相同。在他们们比较了一段时间后，它们看中了两颗钻石g1和g2。现在请你根据之前比较的信息判断这两颗钻石的哪颗更重。

给定两颗钻石的编号g1,g2，编号从1开始，同时给定关系数组vector,其中元素为一些二元组，第一个元素为一次比较中较重的钻石的编号，第二个元素为较轻的钻石的编号。最后给定之前的比较次数n。请返回这两颗钻石的关系，若g1更重返回1，g2更重返回-1，无法判断返回0。输入数据保证合法，不会有矛盾情况出现。

    class Cmp {
    public:
        int cmp(int g1, int g2, vector<vector<int> > records, int n) {
            // write code here
            const int Max = 10000000;
            const int Min = -1;
            set<int> g1_max, g1_min;
            set<int> g2_max, g2_min;
            for(int i=0;i<n;i++){
                int less = records[i][1];
                int more = records[i][0];
                if(more == g1 && less == g2){
                    return 1;
                }
                else if(more == g2 && less == g1){
                    return -1;
                }
                if(more == g1){
                    g1_min.insert(less);
                }
                else if(less == g1){
                    g1_max.insert(more);
                }
                if(more == g2){
                    g2_min.insert(less);
                }
                else if(less == g2){
                    g2_max.insert(more);
                }
            }
            set<int> intersection;
            set_intersection(g1_min.begin(), g1_min.end(), g2_max.begin(),g2_max.end(),inserter(intersection,intersection.begin()));
            if(!intersection.empty()){
                return 1;
            }
            set<int> intersection_2;
            set_intersection(g1_max.begin(), g1_max.end(), g2_min.begin(),g2_min.end(),inserter(intersection_2,intersection_2.begin()));
            if(!intersection_2.empty()){
                return -1;
            }
            return 0;
        }
    };

# [二叉树](http://www.nowcoder.com/questionTerminal/d567727f21a247f7b64ba32431cb9a19)

有一棵二叉树，树上每个点标有权值，权值各不相同，请设计一个算法算出权值最大的叶节点到权值最小的叶节点的距离。二叉树每条边的距离为1，一个节点经过多少条边到达另一个节点为这两个节点之间的距离。
给定二叉树的根节点root，请返回所求距离。

    class Tree {
    public:
        map<int, set<int>> parents;
        set<int> leafs;
     
        // BFS, Get all nodes' parents
        void get_parents(TreeNode *root){
            if(root == NULL){
                return;
            }
     
            set<int> temp(parents[root->val]);
            temp.insert(root->val);
            if(root->left!=NULL){
                TreeNode* left_c = root->left;
                parents[left_c->val] = temp;
            }
            if(root->right!=NULL){
                TreeNode* left_c = root->right;
                parents[left_c->val] = temp;
            }
            if(root->left == NULL && root->right==NULL){
                leafs.insert(root->val);
            }
            get_parents(root->left);
            get_parents(root->right);
        }
     
        int getDis(TreeNode* root) {
            if (root == NULL) {
                return 0;
            }
            get_parents(root);
            if (leafs.size() < 2) {
                return 0;
            }
            auto iter = leafs.begin();
            int leaf_1 = *iter;
            iter = leafs.end();
            int leaf_2 = *(--iter);
     
            set<int> intersect;
            set_intersection(parents[leaf_1].begin(), parents[leaf_1].end(),
                             parents[leaf_2].begin(), parents[leaf_2].end(),
                             inserter(intersect, intersect.begin()));
     
            return parents[leaf_1].size() + parents[leaf_2].size() - 2 * (intersect.size()-1);
        }
    };

