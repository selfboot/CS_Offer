/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 20:23:03
*/

#include<iostream>
using namespace std;
class MyClass
{
public:
    MyClass(int i = 0)
    {
        cout << i;
    }

    // 拷贝构造函数
    MyClass(const MyClass &x)
    {
        cout << 2;
    }

    MyClass &operator=(const MyClass &x)
    {
        cout << 3;
        return *this;
    }
    ~MyClass()
    {
        cout << 4;
    }
};
int main()
{
    MyClass obj1(1), obj2(2);
    MyClass obj3 = obj1;            // 调用拷贝构造函数
    MyClass obj4;
    obj4 = obj1;                    // 调用赋值函数
    return 0;
}

// 122034444
