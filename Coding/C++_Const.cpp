/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-04-11 22:47:29
 */

#include <iostream>
using namespace std;

class MyClass
{
private:
    int counter;
public:
    void Foo()
    {
        counter++;
        std::cout << "Foo" << std::endl;
    }

    void Foo() const
    {
        // cannot assign to non-static data member within const member function 'Foo'
        // counter++; //this will not compile
        std::cout << "Foo const" << std::endl;
    }

};

int main(){

    // 2. 对常量的引用
    int num = 10;
    const int &ref = num;
    num += 100;
    // ref += 100;    // 编译不通过
    // cannot assign to variable 'b' with const-qualified type 'const int &'
    cout << num << endl;

    // 6. 成员函数后面加 const
    MyClass c;
    const MyClass& const_c = c;
    c.Foo();
    const_c.Foo();

    return 0;
}
