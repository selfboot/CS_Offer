/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 14:47:56
*/

#include <iostream>
using namespace std;

struct align_default
{
    char x1;
    double x2;
    short x3;
    int x4;
};

#pragma pack(1) // 设定对齐系数为1
struct align_1
{
    char x1;
    double x2;
    short x3;
    int x4;
};
#pragma pack()

#pragma pack(4) // 设定对齐系数为4
struct align_4
{
    char x1;
    double x2;
    short x3;
    int x4;
};
#pragma pack()

int main()
{
    cout<<"sizeof(char)  : "<<sizeof(char)<<endl;         // 1byte
    cout<<"sizeof(short) : "<<sizeof(short)<<endl;        // 2bytes
    cout<<"sizeof(int)   : "<<sizeof(int)<<endl;          // 4bytes
    cout<<"sizeof(double): "<<sizeof(double)<<endl;       // 8bytes

    cout << sizeof(align_default) << endl;      // 24
    cout << sizeof(align_1) << endl;            // 15
    cout << sizeof(align_4) << endl;            // 20
    return 0;
}
