[Apac Test](https://code.google.com/codejam/apactest) 是 Google 每年招聘的在线笔试，一般有很多轮，通过任意一轮就可以进入面试环节。

题目和国内的没有太大区别，不过在处理输入输出和判题上有点区别。每道题有大小两个数据集，需要在本地运行程序，生成输出结果，然后上传输出结果，google 会比对这个文件来判断程序是否错误。

# 一般程序框架 

大部分题目都是有 T 个测试用例，然后输出一定格式的计算结果，所以可以有一个大致的程序模板，每次只需要补充最主要的处理输入和计算部分即可。

```c++
#include <iostream>
#include <fstream>
...
using namespace std;

//ifstream in_file("/Users/feizhao/Desktop/A-small-practice.in");
ifstream in_file("/Users/feizhao/Desktop/A-large-practice.in");
//ifstream in_file("/Users/feizhao/Desktop/demo.in");   
ofstream out_file("/Users/feizhao/Desktop/output.in");

int T, case_cnt;

// Global variables declared here.

int main() {
    case_cnt = 1;
    in_file >> T;
    while (case_cnt <= T){
        // TODO
        // Calculate part
        out_file << "Case #" << case_cnt << ": ";
        if(case_cnt != T) out_file << endl;
        case_cnt ++;
    }
    return 0;
}
```

# 2017 

## Round 1

### A 

很简单的一个题目，注意在用 getline 读取输入时，要先用 get 吃掉换行符，不然 getline 会读取紊乱。代码在 [Google_apac_2017_1_A.cpp](https://gist.github.com/xuelangZF/10336e60efb87abb4fc39314594f33f5)。


