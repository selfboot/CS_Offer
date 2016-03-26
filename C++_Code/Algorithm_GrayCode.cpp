#include <iostream>
#include <vector>
using namespace std;

/* 递归生成格雷码
 * 格雷码（循环二进制单位距离码）是任意两个相邻数的代码只有一位二进制数不同的编码。
 * n位元的格雷码可以从n-1位元的格雷码以上下镜射后加上新位元的方式快速的得到.
 */
vector<string> GetGrayCode(const int n){
    if(n==1){
        vector<string> gray_codes{"0", "1"};
        return gray_codes;
    }
    long len = (1<<n);
    vector<string> gray_codes(len, "");
    vector<string> pre_codes = GetGrayCode(n-1);
    for(int i=0; i<(1<<(n-1)); i++){
        gray_codes[i] = "0" + pre_codes[i];
        gray_codes[len-1-i] = "1" + pre_codes[i];
    }
    return gray_codes;
}

vector<int> GetGrayCode_decimal(const int n){
    if(n==1){
        vector<int> gray_codes{0, 1};
        return gray_codes;
    }
    long len = (1<<n);
    vector<int> gray_codes(len, 0);
    vector<int> pre_codes = GetGrayCode_decimal(n-1);
    for(int i=0; i< (1<<(n-1)); i++){
        gray_codes[i] = pre_codes[i];
        gray_codes[len-1-i] = (1 << (n-1))+ pre_codes[i];
    }
    return gray_codes;
}

int main(){
    int num;
    cin >> num;
    vector<string> all_codes = GetGrayCode(num);
    for(auto code : all_codes){
        cout << code << endl;
    }

    vector<int> all_decimal_codes = GetGrayCode_decimal(num);
    for(auto code : all_decimal_codes){
        cout << code << endl;
    }
    return 0;
}
