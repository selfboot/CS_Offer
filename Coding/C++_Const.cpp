/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-15 15:53:55
 */

#include <iostream>
using namespace std;

class MyClass
{
private:
    int counter;

public:
    MyClass(){
        counter = 100;
    }

    /*
    成员函数的 const 和 non-const 是重载版本, 各自的隐藏参数分别是 const *this 和 *this.

    1. non-const 对象调用 non-const 函数,如果没有对应的 non-const 函数,则调用 const 函数
        因为 non-const *this 指针可以隐式转换为 const *this 指针, 反之则不能。
    2. const 对象只能调用 const 成员函数
        因为const 对象调用成员函数时,传递 const this 指针, non-const 函数只接受普通的this 指针
     */
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

    void Bar(){
        std::cout << "Bar const" << std::endl;
    }

    // const 参数
    void add(const int another){
        counter += another;
        // another = 12;                   // Error!
        std::cout << counter << endl;
    }

    // 返回值为 const 类型
    const int& get_c(){
        return counter;
    }

    int& get(){
        return counter;
    }
};

int main(){

    // 对常量的引用不能用作修改它绑定的对象
    int num = 10;
    const int &ref = num;
    num += 100;
    // ref += 100;    // 编译不通过
    // cannot assign to variable 'b' with const-qualified type 'const int &'
    cout << num << endl;

    // const 成员函数和 non-const成员函数
    MyClass c;
    const MyClass& const_c = c;
    c.Foo();
    const_c.Foo();
    c.Bar();
    // const_c.Bar();  // Error, 'this' argument has type 'const MyClass', but function is not marked const.

    c.get() = 1000;
    cout << c.get() << endl;
    // c.get_c() = 1000;    // Error!

    // const pointer and pointer to const
    int i=10, j=20;
    const int *p_to_const = &i;
    // *p_to_const = 11;        // Error.
    p_to_const = nullptr;       // OK.
    int *const const_p = &i;
    // const_p = nullptr;       // Error.
    *const_p = 12;              // OK.
    const int *const c_p_to_const = &i;
    // c_p_to_const = nullptr;  // Error.
    // *c_p_to_const = 12;      // OK.


    /* 顶层 const 和 底层 const
     * 在执行对象的拷贝动作时，常量是顶层const 时不受影响。
     * 另一方面，底层 const 的限制不能忽视，当执行拷贝操作时，拷入和拷出的对象必须具有相同的底层 const 资格，
     * 或者两个对象的数据类型必须能够转换。
     */

    int tmp = 22;
    const int const_tmp = 88;   // 顶层 const
    tmp = const_tmp;            // OK, 常量是顶层const 时不受影响
    std::cout << tmp << endl;
    const int *p2 = &tmp;       // 底层 const,允许改变 p2 的值
    int tt = 10;
    const int *const p3 = &tt;  // 前一个为顶层const, 后一个为顶层const
    p2 = p3;                    // OK,
    std::cout << *p2 << std::endl;

    // int *pp = p3;           // Error. p3 包含底层 const 的定义, 而 pp 没有
    const int *ppp = p3;        // OK.
    int *pInt = &tmp;
    ppp = pInt;                 // int * 能够转换为 const int *

    // int &r = const_tmp;     // 普通的 int& 不能绑定到 int 常量上
    const int &r2 = tmp;        // const int& 可以绑定到一个普通 int 上
    return 0;
}
