/*
* @Author: xuelangZF
* @Last Modified time: 2016-03-18 09:32:33
*/

#include <iostream>
#include <vector>
using namespace std;

// 计算模式字符串的 next 数组
void get_next(const string &str, vector<int> &next){
    next[0] = -1;
    int i=0, k=-1;
    while(i<str.size()-1){
        if(k== -1 || str[i] == str[k]){
            // 当两个字符相等时要跳过
            if(str[++i] == str[++k]){
                next[i] = next[k];
            }
            else{
                next[i] = k;
            }
        }
        else {
            k = next[k];
        }
    }
}

/*
 * 返回 target 在 source 中第一次出现的下标
 * 如果没有, 则返回-1
 */
int KMP(const string &source, const string &pattern){

    // What the FUCK!!!! Auto--> Unsigned!!!!!
    // auto pattern_s = pattern.size();
    // auto source_s = source.size();

    int pattern_s = pattern.size();
    int source_s = source.size();
    vector<int> next(pattern_s, 0);
    get_next(pattern, next);
    int i=0, j=0;
    while (i<source_s && j<pattern_s){
        // 当j为-1时，要移动的是i，同时j也要归0
        if((j== -1) || (source[i] == pattern[j])){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j == pattern_s){
        return i-j;
    }
    else{
        return -1;
    }
}

int main(){
    string a, b;
    cin >> a >> b;
    cout << KMP(a, b) << endl;
}
