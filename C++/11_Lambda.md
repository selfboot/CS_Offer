在 C++ 11 中，lambda 表达式（通常称为 "lambda"）是一种在被调用的位置或作为参数传递给函数的位置定义匿名函数对象的简便方法。Lambda 通常用于封装传递给算法或异步方法的少量代码行。下面代码展示了作为第三个参数传递给 std::sort() 函数的简单 lambda：

    #include <algorithm>
    #include <cmath>
    
    void abssort(float* x, unsigned n) {
        std::sort(x, x + n,
            // Lambda expression begins
            [](float a, float b) {
                return (std::abs(a) < std::abs(b));
            } // end of lambda expression
        );
    }

接着看下 lambda 的语法内容吧。

# lambda 语法

简单来说，Lambda函数也就是一个函数，它的语法定义如下：

    [capture](parameters) mutable ->return-type{statement}

如下图所示：

![][1]

具体解释如下：

1.	`[capture]：捕捉列表`。捕捉列表总是出现在Lambda函数的开始处，实际上，[]是Lambda引出符。编译器根据该引出符判断接下来的代码是否是Lambda函数。捕捉列表能够捕捉上下文中的变量以供Lambda函数使用;
2.	`(parameters)：参数列表`。与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略;
3.	`mutable：mutable修饰符`。默认情况下，Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）;
4.	`->return-type：返回类型`。用追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导;
5.	`{statement}：函数体`。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。

与普通函数最大的区别是，除了可以使用参数以外，Lambda函数还可以通过捕获列表访问一些上下文中的数据。具体地，捕捉列表描述了上下文中哪些数据可以被Lambda使用，以及使用方式（以值传递的方式或引用传递的方式）。语法上，在“[]”包括起来的是捕捉列表，捕捉列表由多个捕捉项组成，并以逗号分隔。捕捉列表有以下几种形式：

1.	[var]表示值传递方式捕捉变量var；
2.	[=]表示值传递方式捕捉所有父作用域的变量（包括this）；
3.	[&var]表示引用传递捕捉变量var；
4.	[&]表示引用传递方式捕捉所有父作用域的变量（包括this）；
5.	[this]表示值传递方式捕捉当前的this指针。

上面提到了一个父作用域，也就是包含Lambda函数的语句块，说通俗点就是包含Lambda的“{}”代码块。上面的捕捉列表还可以进行组合，例如：

1.	[=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量;
2.	[&,a,this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。不过值得注意的是，**捕捉列表不允许变量重复传递**。下面一些例子就是典型的重复，会导致编译时期的错误。例如：
    *	[=,a]这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;
    *	[&,&this]这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复。

# Lambda的使用

首先回顾下C++ STL库中的仿函数对象，相对于普通函数来说，仿函数可以拥有初始化状态，而这些初始化状态是在声明仿函数对象时，通过参数指定的，一般都是保存在仿函数对象的私有变量中。在C++中，对于要求具有状态的函数，我们一般都是使用仿函数来实现，比如以下代码：

    #include<iostream>
    using namespace std;
     
    typedef enum
    {
        add = 0,
        sub,
        mul,
        divi
    }type;
    
    class Calc
    {
        public:
            Calc(int x, int y):m_x(x), m_y(y){}
     
            int operator()(type i)
            {
                switch (i)
                {
                    case add:
                        return m_x + m_y;
                    case sub:
                        return m_x - m_y;
                    case mul:
                        return m_x * m_y;
                    case divi:
                        return m_x / m_y;
                }
            }
     
        private:
            int m_x;
            int m_y;
    };
    
    int main()
    {
        Calc addObj(10, 20);
        cout<<addObj(add)<<endl; // 发现C++11中，enum类型的使用也变了，更“强”了                                                                                                                                              
        return 0;
    }

现在我们有了Lambda这个利器，那是不是可以重写上面的实现呢？看代码：

    #include<iostream>
    using namespace std;
          
    typedef enum
    {     
        add = 0,
        sub,
        mul,
        divi
    }type;
          
    int main()
    {     
        int a = 10;
        int b = 20;
          
        auto func = [=](type i)->int {
            switch (i)
            {
                case add:
                    return a + b;
                case sub:
                    return a - b;
                case mul:
                    return a * b;
                case divi:
                    return a / b;
            }
        };
          
        cout<<func(add)<<endl;
    }

# 一些陷阱

先看以下一段代码：

    #include<iostream>         
    using namespace std;       
                               
    int main()                 
    {                          
        int j = 10;            
        auto by_val_lambda = [=]{ return j + 1; };
        auto by_ref_lambda = [&]{ return j + 1; };
        cout<<"by_val_lambda: "<<by_val_lambda()<<endl;     // 11
        cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;     // 11
                               
        ++j;                   
        cout<<"by_val_lambda: "<<by_val_lambda()<<endl;     // 11
        cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;     // 12
                               
        return 0;              
    }

在by_val_lambda中，**j 被视为一个常量，一旦初始化后不会再改变（可以认为之后只是一个跟父作用域中j同名的常量），而在by_ref_lambda中，j仍然在使用父作用域中的值**。所以，在使用Lambda函数的时候，如果需要捕捉的值成为Lambda函数的常量，我们通常会使用按值传递的方式捕捉；相反的，如果需要捕捉的值成成为Lambda函数运行时的变量，则应该采用按引用方式进行捕捉。

再来看一段代码：

```c++
#include<iostream>
using namespace std;

int main()
{
    int val = 0;
    // auto const_val_lambda = [=](){ val = 3; }; wrong!!!
    // If a lambda is marked mutable (e.g. []() mutable { }) it is allowed to mutate the values that have been captured by value.
    auto mutable_val_lambda = [=]() mutable{ val = 3; };
    mutable_val_lambda();
    cout<<val<<endl; // 0

    auto const_ref_lambda = [&]() { val = 4; };
    const_ref_lambda();
    cout<<val<<endl; // 4

    auto mutable_ref_lambda = [&]() mutable{ val = 5; };
    mutable_ref_lambda();
    cout<<val<<endl; // 5

    return 0;
}
```

这段代码主要是用来理解Lambda表达式中的mutable关键字的。默认情况下，Lambda函数总是一个const函数，这意味着我们**不能改变按照值传递方式捕捉的变量**（可以改变引用方式捕捉的变量）。不过我们可以用 mutable 取消其常量性，这样就可以在函数体中改变变量的值。

再来看一个简单的例子：

```c++
int i = 0;
int* p = &i;
auto l = [=]{ ++*p; };
l();
std::cout << i << std::endl;  // outputs 1
```

内部实现相当于下面的代码：

```
struct lambda {
    int* p;
    lambda(int* p_) : p(p_) {}
    void operator()() const { ++*p; }
};
```

可以看到 operator()() 是常量成员函数，相当于声明了 p 是常量指针，如下：

```c++
int* const p;
```

因此不允许我们更改指针 p 的值，不过我们仍然可以更改 p 指向的值(*p)。对按照引用捕获值来说，我们的引用本身是 “const” 的（要注意引用本来就不能再指向其他对象了），但是可以改变引用指向的值。


# 更多阅读

[What is a lambda expression in C++11?](http://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11)   
[Passing by constant reference in the lambda capture list](http://stackoverflow.com/questions/31179355/passing-by-constant-reference-in-the-lambda-capture-list)  
[Lambda: Why are captured-by-value values const, but capture-by-reference values not?](http://stackoverflow.com/questions/16764153/lambda-why-are-captured-by-value-values-const-but-capture-by-reference-values)   
[MSDN：C++ Lambda](https://msdn.microsoft.com/zh-cn/library/dd293608.aspx)  
[C++中的Lambda表达式](http://www.jellythink.com/archives/668)  



[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_Lambda_1.png

