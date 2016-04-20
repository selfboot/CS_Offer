# 2016 实习

## [推箱子](http://hihocoder.com/contest/ntest2015april/problem/1)

推箱子是一款经典游戏。如图所示，灰色格子代表不能通过区域，蓝色方格是箱子，黑色圆形代表玩家，含有圆点的格子代表目标点。

![][1]

规定以下规则：

1. 一局游戏中只会有一个箱子，一个玩家和一个目标点。
2. 通过方向键控制玩家移动。
3. 图中的灰色格子代表墙壁，玩家与箱子都不能通过。
4. 推到墙壁的箱子，就无法再将箱子推离墙壁，因为玩家无法到达箱子靠墙壁的一侧去推箱子。也就是说箱子只能以“被推”的方式被移动，不是以“被拉”的方式被移动。但如果玩家将箱子推至墙壁后，垂直墙壁的两侧没有阻碍物，则玩家可以朝这两个不同的方向推移箱子。如果箱子进入角落，就没有办法再推动这个箱子了。
5. 玩家是不能走出场景的。玩家推着箱子到达场景边缘，如果继续点击使玩家和箱子向墙壁前进的方向键，箱子和人都会保持不动。玩家的前进方向上如果有墙壁，也是不能前进的。但是这些点击都视为合理的输入。
6. 箱子一旦到达目标点，就不能再移动了。但这时，玩家仍然可以在场景内自由行动。如果继续尝试推箱子，那么玩家将会和箱子一起保持在原地不动。

现在，给出一种方向键的点击方案，请判断，这种方案是否能使箱子最终停在目标点上。为了方便表示，我们以0代表空白格子，以4代表不能通过区域，以1代表玩家，以3代表箱子，以2代表目标点。

## 输入、输出

`输入`：第一行数据包含三个整数，N，M，S。其中，N(0 < N <= 100)代表格子的宽度，M(0 < M <= 100)代表格子的高度，S(0 < S <= 200)代表测试点的个数。

接下来的M行，每行都会有N个字符，描述当前的盘面。

接下来的S行，每行都代表一个测试点。每行都以一个整数T(0 < T <= 10000)开头，接下来是一个空格和T个字符。这T个字符仅由d，u，l，r这四个字母组成，分别代表了敲击向下，向上，向左，向右的方向键。

`输出`：对于每个测试点，输出最后箱子是否在目标点上。如果是，输出YES，如果不是，则输出NO。

样例输入

    5 4 3
    00000
    13000
    00200
    00000
    4 rurd
    6 urdldr
    6 rrrurd

样例输出

> YES
> YES
> NO
> EmacsNormalVim

## 程序

    #include <iostream>
    #include <vector>
    #include <map>
    
    using namespace std;
    
    map<char, vector<int>> oper = {{'u', vector<int>{-1, 0}},
                                   {'d', vector<int>{1, 0}},
                                   {'r', vector<int>{0, 1}},
                                   {'l', vector<int>{0, -1}},};
    
    char tables[100][100];
    int N, M, S;
    int target[2];
    int person[2];
    int box[2];
    
    bool can_move(const char op, const int (&pos)[2]){
        int new_pos[2];
        new_pos[0] = pos[0] + oper[op][0];
        new_pos[1] = pos[1] + oper[op][1];
        if(new_pos[0] >= 0 and new_pos[0] < M and
           new_pos[1] >= 0 and new_pos[1] < N and
           tables[new_pos[0]][new_pos[1]] != '4'){
            return true;
        }
        return false;
    }
    
    bool box_people(const char op, const int (&p)[2], const int (&b)[2]){
        if(p[0] + oper[op][0] == b[0] and p[1] + oper[op][1]== b[1]){
            return true;
        }
        return false;
    }
    
    void move_one(const char op, int (&p)[2]){
        p[0] = p[0] + oper[op][0];
        p[1] = p[1] + oper[op][1];
    }
    
    bool people_move(const char op, int (&p)[2], int (&b)[2]){
        // Can't Move edge. person, box don't change.
        if(box_people(op, p, b)){
            if(can_move(op, b)){
                move_one(op, b);
                move_one(op, p);
            }
        }
        else{
            if (can_move(op, p)){
                move_one(op, p);
            }
        }
        if(b[0] == target[0] and b[1] == target[1]){
            return true;
        }
        return false;
    }
    
    int main() {
        cin >> N >> M >> S;
    
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                char c;
                cin >> c;
                tables[i][j] = c;
                if(c=='2'){
                    target[0] = i;
                    target[1] = j;
                }
                if(c=='1'){
                    person[0] = i;
                    person[1] = j;
                }
                if(c=='3'){
                    box[0] = i;
                    box[1] = j;
                }
            }
        }
    
        for(int i=0;i<S;i++){
            int T;
            cin >> T;
            vector<char> operate(T);
            int p[2]={0, 0}, b[2]={0, 0};
            p[0] = person[0], p[1] = person[1];
            b[0] = box[0], b[1] = box[1];
            for(int j=0;j<T;j++){
                cin >> operate[j];
            }
            bool ok = false;
            for(int j=0;j<T;j++){
                if(people_move(operate[j], p, b)){
                    ok = true;
                    break;
                }
            }
            if (ok){
                cout << "YES" << endl;
            }
            else{
                cout << "NO" << endl;
            }
        }
    
        return 0;
    }

# [井字棋](http://hihocoder.com/contest/ntest2015april/problem/2)

小武是井字棋的忠实粉丝，井字棋，又称为井字游戏、井字过三关等，是种纸笔游戏。其具体玩法为：

两个玩家，一个打圈(O)，一个打叉(X)，轮流在3乘3的格上打自己的符号，最先以横、直、斜连成一线则为胜。当9个格子画满，双方均无法取胜时，则为和局。当有玩家取胜或者下成平局后，比赛结束。

![][2]

假设每次X方均为先手，给出一个局面，请你判断这个局面是否合法，如果局面合法，则判断当前局面是否是比赛结束局面，如果是，则判断当前局面是X方胜利，O方胜利或者是平局。如果局面暂时未分胜负，则判断下一个下棋的选手下完一步后（假设采用最优策略）能否取胜。

## 输入、输出

`输入`：每个输入数据包含多个测试点。第一行为测试点的个数S <= 2000。之后是S个测试点的数据。

每个测试点的数据包括3行，用于描述整个棋盘。每行包含一个长度为3的字符串，取值范围为{'_', 'O', 'X'}，其中'_'表示该格子为空，'X'表示该格被先手者占领，'O'表示该格被后手者占领。

每个测试点之间会有一个空行相隔。

`输出`：对于每个测试点，对应的结果输出一行。

如果局面非法，则输出"Invalid"。

否则如果局面是比赛结束局面，X取胜则输出"X win", O取胜则输出"O win", 如果是平局则输出"Draw"。

如果局面合法并且不是比赛结束的局面，则判断下一个下棋的选手下完一步后能否取胜，如果可以，则输出"Next win", 否则输出"Next cannot win"。

注意，所有的结果输出均不带引号。

`样例提示`

第一个例子，因为X先下，所以该局面不可能出现。
第二个例子，为结束局面，X取胜。
第三个例子，全部格子下完，双方均无法取胜，平局。
第四个例子，局面未分胜负，下一个下的是X，可以取胜。
第五个例子，局面未分胜负，下一个下的是O，无论下到哪一个格子均无法取胜。

    5
    __O
    _XO
    ___
    
    XXX
    ___
    OO_
    
    XXO
    OOX
    XXO
    
    X_X
    OO_
    ___
    
    XO_
    XX_
    __O

样例输出

> Invalid
> X win
> Draw
> Next win
> Next cannot win

    #include <iostream>
    #include <map>
    using namespace std;
    
    map<char, int> convert{{'X', 1}, {'_', 0}, {'O', -1}};
    
    pair<int, int> get_state(const int tables[3][3], int (&situations)[8]){
        situations[0] = tables[0][0] + tables[0][1] + tables[0][2];
        situations[1] = tables[1][0] + tables[1][1] + tables[1][2];
        situations[2] = tables[2][0] + tables[2][1] + tables[2][2];
        situations[3] = tables[0][0] + tables[1][0] + tables[2][0];
        situations[4] = tables[0][1] + tables[1][1] + tables[2][1];
        situations[5] = tables[0][2] + tables[1][2] + tables[2][2];
        situations[6] = tables[0][0] + tables[1][1] + tables[2][2];
        situations[7] = tables[2][0] + tables[1][1] + tables[0][2];
        pair<int, int> count(0, 0);
        for(int i=0; i< 8;i++){
            if(situations[i] == 3){
                count.first += 1;
            }
            if(situations[i] == -3){
                count.second += 1;
            }
        }
        return count;
    }
    
    bool valid_state(const int (&state)[8], const int num, pair<int, int> count){
        /* Invalid
         * ooo
         * ___
         * xxx
         *
         * xxx
         * oox
         * oo_
         *
         * ooo
         * xx_
         * xx_
         */
        if(num != 1 && num != 0){
            return false;
        }
        if(count.first > 1 && count.second > 1){
            return false;
        }
        if(count.first >= 1 && num == 0){
            return false;
        }
        if(count.second >= 1 && num == 1){
            return false;
        }
        return true;
    }
    
    bool end_state(const int (&state)[8], int empty_num) {
        if (empty_num == 0) {
            return true;
        }
        for (int i = 0; i < 8; i++) {
            if (state[i] == 3 or state[i] == -3) {
                return true;
            }
        }
        return false;
    }
    
    void print_res(const int (&state)[8]){
        for(int i=0; i<8;i++){
            if(state[i] == 3){
                cout << "X win" << endl;
                return;
            }
            if(state[i] == -3){
                cout << "O win" << endl;
                return;
            }
        }
        cout << "Draw" << endl;
    }
    
    void print_next_win(const int (&state)[8], int v_num){
        // next: O
        bool can_win = false;
        if (v_num == 1){
            for(int i=0;i<8;i++){
                if(state[i] == -2){
                    can_win = true;
                    break;
                }
            }
        }
    
        // next: X
        else{
            for(int i=0;i<8;i++) {
                if (state[i] == 2) {
                    can_win = true;
                    break;
                }
            }
        }
        if(can_win){
            cout << "Next win" << endl;
        }
        else{
            cout << "Next cannot win" << endl;
        }
        return;
    }
    
    int main()
    {
        int S;
        cin >> S;
        for(int i=0; i<S;i++)
        {
            int tables[3][3];
            int valid_num = 0;
            int empty_num = 0;
            for(int m=0;m<3;m++){
                for(int n=0;n<3;n++){
                    char c;
                    cin >> c;
                    if(c=='_'){
                        empty_num += 1;
                    }
                    valid_num += convert[c];
                    tables[m][n] = convert[c];
                }
            }
            int states[8] = {0};
            pair<int, int> count_3 = get_state(tables, states);
    
            // Valid or not.
            if(!valid_state(states, valid_num, count_3)){
                cout << "Invalid" << endl;
                continue;
            }
    
            // end state
            if(end_state(states, empty_num)) {
                print_res(states);
                continue;
            }
    
            // not end, determine if next can win.
            print_next_win(states, valid_num);
        }
        return 0;
    }
    

# 连连看

小江最喜欢玩的游戏"天下3"最近推出了连连看的小玩法。玩家可以将2个相同图案的牌子连接起来，连接线不多于3根线段（即最多拐2折），就可以成功将这对牌子消除。如示意图所示，红色，黄色和蓝色的消除都是合法的，因为它们分别需要2个，0个和1个折。而黑色的消除是不合法的，因为这对牌至少需要拐3个折才能连接起来。

![][3]

但是小江并不满足于这个游戏规则，因为他觉得最多只能拐2折这个限制并不合理。好奇的小江想知道的是，给定一个连连看的状态以及某一个牌子，在K折以内可以到达的所有具有相同图案的牌子的数量是多少。

## 输入、输出

每个输入数据包含多个测试点。

第一行为测试点的个数S <= 20。之后是S个测试点的数据。

每个测试点的第一行为1 <= N <= 200, 1 <= M <= 200，表示连连看的大小。接下来的N行，每一行有M个整数，表示连连看该行的状态，如果为0，则表示该格为空，否则代表一种图案的牌子。

然后是三个整数X <= N, Y <= M，0 <= K <= 10000，表示查询(X, Y)这个牌子在K折以内能消除的所有相同牌子总数。其中连连看左上角的格子坐标为(1, 1)，右下角为(N, M)。保证查询的格子是有图案的。

`输出`：对于每个测试点，输出对应的能消除的所有牌子总数。

提示：样例第一个例子，第(1, 1), (2, 3)和(2, 5)为3个可以在3折内被消除的相同牌子。

样例输入
    3
    4 5
    1 0 1 0 2
    0 0 1 3 1
    3 3 1 5 9
    6 1 4 8 7
    1 3 3
    4 5
    1 0 1 0 2
    0 0 1 3 1
    3 3 1 5 9
    6 1 4 8 7
    1 3 1
    2 2
    1 10
    2 3
    1 1 10

样例输出

> 3
> 2
> 0

    #include <iostream>
    #include <queue>
    using namespace std;
    
    struct State {
        int x, y;
        int num;
        int cx, cy;
        State() {}
        State(int ox, int oy, int onum, int ocx, int ocy):x(ox), y(oy),num(onum),cx(ocx),cy(ocy) {
        }
    };
    
    // Up, Right, Down, Left
    const int X_OFFSET[] = {0, 1, 0, -1};
    const int Y_OFFSET[] = {-1, 0, 1, 0};
    
    int tables[202][202];
    bool visited[202][202];
    int S,N,M,X,Y,K;
    
    bool is_valid(const int x, const int y){
        return (x >= 0 && x <= N+1 && y >= 0 && y <= M+1);
    }
    
    int main(){
        cin >> S;
        while(S--){
            memset(tables, 0, sizeof(tables));
            memset(visited, false, sizeof(visited));
            cin >> N >> M;
            for(int i=1;i<=N;i++){
                for(int j=1;j<=M;j++){
                    cin >> tables[i][j];
                }
            }
            cin >> X >> Y >> K;
            visited[X][Y] = true;
            int count = 0;
            queue<State> que;
    
            // First go along 4 directions
            for(int i=0;i<4;i++){
                int new_x = X;
                int new_y = Y;
                while(true){
                    new_x += X_OFFSET[i];
                    new_y += Y_OFFSET[i];
                    if (!is_valid(new_x, new_y)){
                        break;
                    }
                    if(tables[new_x][new_y] == 0){
                        if(!visited[new_x][new_y]){
                            que.push(State(new_x, new_y, 0, X_OFFSET[i], Y_OFFSET[i]));
                            visited[new_x][new_y] = true;
                        }
                        continue;
                    }
                    if(!visited[new_x][new_y] && tables[new_x][new_y] == tables[X][Y]){
                        count += 1;
                        visited[new_x][new_y] = true;
                    }
                    break;
                }
            }
    
            while(!que.empty()){
                State cur_s = que.front();
                que.pop();
                if(cur_s.num == K){
                    continue;
                }
                for(int i=0;i<4;i++){
                    // 跳过相同方向,只往不同方向扩展;
                    if(cur_s.cx == X_OFFSET[i] && cur_s.cy == Y_OFFSET[i]) continue;
                    if(cur_s.cx + X_OFFSET[i] == 0 && cur_s.cy + Y_OFFSET[i] == 0) continue;
    
                    // 搜索不同的方向
                    int new_x = cur_s.x, new_y = cur_s.y;
                    while(true){
                        new_x += X_OFFSET[i];
                        new_y += Y_OFFSET[i];
                        if(!is_valid(new_x, new_y)) break;
                        if(tables[new_x][new_y] == 0){
                            if(!visited[new_x][new_y]){
                                que.push(State(new_x, new_y, cur_s.num+1, X_OFFSET[i], Y_OFFSET[i]));
                                visited[new_x][new_y] = true;
                            }
                            continue;
                        }
                        if(!visited[new_x][new_y] && tables[new_x][new_y] == tables[X][Y]){
                            count += 1;
                            visited[new_x][new_y] = true;
                        }
                        break;
                    }
                }
            }
            cout << count << endl;
        }
    }

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_OJ_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_OJ_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_OJ_3.png

参考

[连连看——网易游戏2016实习生招聘](http://blog.csdn.net/wangtaoking1/article/details/45035465)

# 2016 校招

## [Amusing Digits](http://hihocoder.com/contest/ntest2015septdev/problem/1)

    #include <iostream>
    using namespace std;
    
    int main() {
        int T;
        cin >> T;
        while(T){
            string S;
            int count = 0;
            cin >> S;
            int pos = 0, i =0;
            int start = pos;
            int len = S.size();
            string target = "9706";
            while (pos < len && i<4){
                if (S[pos] != '9' && S[pos] != '7' && S[pos] != '0' && S[pos] != '6'){
                    pos += 1;
                    continue;
                }
                if(S[pos] == target[i]){
                    S[pos] = '#';
                    if(i==0){
                        start = pos;
                    }
                    if(i==3){
                        count += 1;
                        pos = start + 1;
                        i = 0;
                        continue;
                    }
                    pos++;
                    i++;
                }
                else{
                    pos += 1;
                }
            }
            cout << count << endl;
            T--;
        }
        return 0;
    }
    

## [Best Compression Algorithms](http://hihocoder.com/contest/ntest2015septdev/problem/2)

    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    inline bool is_char(const char c){
        return ((c >= 'A' && c <= 'Z') || c=='(' || c== ')');
    }
    
    int get_num(const string &str, int &i){
        int len = str.size();
        int num = 0;
        for(;i<len;i++){
            if(!is_char(str[i])){
                num = num * 10 + (str[i] - '0');
            }
            else{
                // 返回到最后一个数组的下标上面
                i -= 1;
                break;
            }
        }
        return num;
    }
    
    int main() {
        int T;
        cin >> T;
        while(T){
            string pattern;
            cin >> pattern;
            vector<char> stack;
            int all_count = 0, stack_num = 0, i=0;
            int len = pattern.size();
            while(i<len){
                if(pattern[i] == '('){
                    stack.push_back(pattern[i]);
                }
                else if(pattern[i] == ')'){
                    stack.pop_back();
                    i += 1;
                    if(i<len){
                        if(!is_char(pattern[i])){
                            int num = get_num(pattern, i);
                            all_count += stack_num * num;
                        }
                    }
                    else{
                        all_count += stack_num;
                    }
                }
                else if(!stack.empty()){
                    if(!is_char(pattern[i])) stack_num += (get_num(pattern, i)-1);
                    else stack_num += 1;
                }
                else{
                    if(!is_char(pattern[i])) all_count += (get_num(pattern, i)-1);
                    else all_count += 1;
                }
                i += 1;
            }
            cout << all_count << endl;
            T--;
        }
        return 0;
    }

# 2017 实习

    #include <iostream>
    #include <map>
    #include <set>
    #include <vector>
    #include <algorithm>
    
    using namespace std;
    map<int, vector<int>> Situations = {{1, vector<int>{1, 4}},
                                     {2, vector<int>{1,2,3,7}},
                                     {3, vector<int>{5, 6}},
                                     {4, vector<int>{1, 7, 0}},
                                     {5, vector<int>{1, 3, 4, 5, 7, 9}},
                                     {6, vector<int>{2}},
                                     {7, vector<int>{1, 4, 7}}
    };
    int K, N;
    
    int get_count(const vector<int> &all, const vector<int> &less, const vector<int> &equal, int pos, bool big){
        // 计算总数目
        // cout << "____" << big << endl;
        int count = 0;
        if(big){
            count = 1;
            for(int j=pos;j<K;j++){
                // cout << "***" <<all[j] << endl;
                count *= all[j];
            }
            return count;
        }
        if(less[pos] > 0){
            count = less[pos];
            for(int j=pos+1;j<K;j++) count *= all[j];
        }
        if(equal[pos] == 1){
            if (pos+1 < K){
                count += get_count(all, less, equal, pos+1, false);
            }
        }
        return count;
    }
    
    
    int main() {
        int Cases;
        cin >> Cases;
        while(Cases){
            cin >> K >> N;
            string str;
            getline(cin, str);
            vector<vector<int>> K_nums(K, vector<int>(10, 1));
            for(int i=0;i<K;i++){
                getline(cin, str);
                for(auto c: str){
                    if(c > '0' && c < '8'){
                        int up = c - '0';
                        for(auto num: Situations[up]){
                            K_nums[i][num] = 0;
                        }
                    }
                }
                // for(int s=0;s<10;s++)  cout << K_nums[i][s];
            }
            // 存放对应的数字
            vector<int> target(K, 0);
            int pos = K-1;
            bool big = false;
            while(N > 0){
                if(pos >= 0) target[pos] = N%10;
                else{
                    big = true;
                    break;
                }
                N /= 10;
                pos -= 1;
            }
            // 统计每一位可以放的数字数目
            // 统计每一位比给定值小的数字数目
            // 统计每一位等于给定值的数字数目
            vector<int> can_put(K, 0);
            vector<int> less_than(K, 0);
            vector<int> equal(K, 0);
            bool can = true;
            for(int i=0; i<K;i++){
                for(int j=0; j<10;j++){
                    if(K_nums[i][j]){
                        can_put[i] ++;
                        if(j < target[i]) less_than[i]++;
                        if(j == target[i]) equal[i]++;
                    }
                }
                if(can_put[i] == 0){
                    can = false;
                }
                // cout << "AAA" << can_put[i] << endl;
            }
            int count = 0;
            if(can){
                count = get_count(can_put, less_than, equal, 0, big);
            }
    
            cout << count;
            if (Cases != 1){
                cout << endl;
            }
            Cases--;
        }
        return 0;
    }


