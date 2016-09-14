# 深处的秘密

## 失败的多态？

下面多态函数调用的输出？

```c++
class B
{
public:
    virtual void vfun(int i = 10){
        cout << "B:vfun " << i << endl;
    }
};

class D : public B
{
public:
    virtual void vfun(int i = 20){
        cout << "D:vfun " << i << endl;
    }
};

int main()
{
    D* pD = new D();
    B* pB = pD;
    pD->vfun();     // D:vfun 20
    pB->vfun();     // D:vfun 10
}
```

为了解释清楚，先来看四个概念：

* 对象的静态类型：对象在声明时采用的类型，是在编译期确定的。
* 对象的动态类型：目前所指对象的类型，是在运行期决定的。对象的动态类型可以更改，但是静态类型无法更改。
* 静态绑定：绑定的是对象的静态类型，某些特性依赖于对象的静态类型，发生在编译期。
* 动态绑定：绑定的是对象的动态类型，某些特性（比如多态）依赖于对象的动态类型，发生在运行期。

假设类B是一个基类，类C继承B，类D继承B，那么：

    D* pD = new D();//pD的静态类型是它声明的类型D*，动态类型也是D*
    B* pB = pD;     //pB的静态类型是它声明的类型B*，动态类型是pB所指向的对象pD的类型D*
    C* pC = new C();  
    pB = pC;        //pB的动态类型是可以更改的，现在它的动态类型是C*

只有虚函数才使用的是动态绑定，其他的全部是静态绑定。当缺省参数和虚函数一起出现的时候情况有点复杂，极易出错。虚函数是动态绑定的，但是为了执行效率，**缺省参数是静态绑定的**。

所以对于上面的例子，pD->vfun()和pB->vfun()调用都是函数D::vfun()，但是缺省参数是静态绑定的，所以 pD->vfun() 时，pD的静态类型是D*，所以它的缺省参数应该是20；同理，pB->vfun()的缺省参数应该是10。

不是很容易接受是吧，所以`Effective C++ 条款37：绝不要重新定义继承而来的缺省参数`。

## 继承中重复的数据成员

派生类中数据成员和基类数据成员重复时，该如何调用？看下面例子：

```c++
#include "stdio.h"

class A {
public:
    int _a;

    A(){
        _a = 1;
    }

    void print(){
        printf("%d", _a);
    }
};

class B : public A {
public:
    int _a;

    B() {
        _a = 2;
    }
};

int main() {
    B b;
    b.print();          // 1    
    printf("%d", b._a); // 2
}
```
首先要知道继承的时候，允许**子类存在与父类同名的成员变量，但是并不覆盖父类的成员变量，他们同时存在**。

子类公有（public）继承父类，所以子类可以通过对象访问父类的公有成员函数，由于调用的是父类的公有成员函数（**该函数中的this指针存放的是父类对象的地址**），所以打印的是父类A的_a。

# 该死的未定义行为

未定义行为（Undefined Behavior）是指C语言标准未做规定的行为。同时，标准也从没要求编译器判断未定义行为，所以这些行为有编译器自行处理，在不同的编译器可能会产生不同的结果，又或者如果程序调用未定义的行为，可能会成功编译，甚至一开始运行时没有错误，只会在另一个系统上，甚至是在另一个日期运行失败。当一个未定义行为的实例发生时，正如语言标准所说，“什么事情都可能发生”，也许什么都没有发生。一句话，未定义行为就是运行结果不确定。

## abs 并不绝对

下面代码：

    int a = 0x80000000;
    int b = 0x7fffffff;
    cout << a << ", " << b << endl;           // -2147483648, 2147483647
    cout << abs(a) << ", " << abs(b) << endl; // -2147483648, 2147483647

考虑 int 型来说负数的范围比正数大一个，比如32位int，可以表示范围为 -2^31 ~ 2^31 -1。所以abs(-2^31 )并不能表示为2^31 。

C++ 对于这种abs之后超出表示类型的行为`没有定义`，不同编译器有不同的实现，一般返回原值。所以 int 函数原型为

    int abs (int n); 

返回值是int，而不是 unsigned int。

> If the result cannot be represented by the returned type (such as abs(INT_MIN) in an implementation with two's complement signed values), it causes undefined behavior.

# 语言的细节

## 字符数组、常量字符串

```c++
char a[] = "abcde";
char arr[] = {4, 3, 9, 9, 2, 0, 1, 5};
cout << sizeof(a)<<endl;        //6
cout << sizeof(arr) << endl;    //8
cout << strlen(a);              //5
```

字符串常量后面会有 '\0'，sizeof计算时会加上 '\0' 后计算长度。'\0' 的ASCII码值为0，strlen 计算时遇到 '\0'结束。


# 更多阅读

[Cplusplus: abs](http://www.cplusplus.com/reference/cstdlib/abs/?kw=abs)  
[What are all the common undefined behaviours that a C++ programmer should know about? ](http://stackoverflow.com/questions/367633/what-are-all-the-common-undefined-behaviours-that-a-c-programmer-should-know-a)  
[What are the common undefined/unspecified behavior for C that you run into?](http://stackoverflow.com/questions/98340/what-are-the-common-undefined-unspecified-behavior-for-c-that-you-run-into)   
[Undefined, unspecified and implementation-defined behavior](http://stackoverflow.com/questions/2397984/undefined-unspecified-and-implementation-defined-behavior)  

