/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 14:02:56
*/


#include <iostream>
using namespace std;

bool checkCPU(){
    // If CPU is Little endian, return True; else false
    union Test{
        int m;
        char c;
    } t;
    t.m = 1;
    return (t.c == 1);
}

int main()
{
    cout << (checkCPU() ? "Little endian": "Big endian") << endl;

    union Demo
    {
        char a[4];
        short b;
    };
    Demo d;
    d.a[0]=256;         // 0,     0000 0000
    d.a[1]=255;         // -1,    1111 1111
    d.a[2]=254;         // -2,    1111 1110
    d.a[3]=253;         // -3,    1111 1101

    /* short是2字节（a[0]和a[1]），
     * 由于80X86是小端模式，即数据的低位保存在内存的低地址中，而数据的高位保存在内存的高地址中
     * 在本例中，a[0]中存放的是b的低位，a[1]中存放的是b的高位，
     * 即b的二进制补码表示是：1111 1111 0000 0000，表示-256
     */
    cout << d.b << endl;

    return 0;
}
