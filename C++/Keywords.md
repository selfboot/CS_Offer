关键字(keyword)又称保留字，是整个语言范围内预先保留的标识符。每个C++关键字都有特殊的含义。经过预处理后，关键字从预处理记号(preprocessing-token)中区别出来，剩下的标识符作为记号(token)，用于声明对象、函数、类型、命名空间等。

# const

欲阻止一个变量被改变，可以使用const关键字。在定义该const变量时，通常需要对它进行初始化，因为以后就没有机会再去改变它了。

const只是在`编译期的保护`，编译期会检查const变量有没有被修改，如果有代码尝试修改一个const变量，编译器就会报错。但是由于const修饰的既然是变量，就有存储空间，我们可以通过地址修改空间里的值，这样还是可以改变的，也就是说const在一定程度上在编译期间使该变量变成了一个常量，然而它并没有实现保证该变量在运行期间内存中的值不被修改。

更多特点如下：

1. const 的引用，对常量的引用不能用作修改它绑定的对象，但是由于对象本身可能是非常量，所以允许通过其他途径改变值。
2. 对指针来说，可以指定指针本身为常量（const pointer, `常量指针`），也可以指定指针所指的对象为常量（pointer to const, `指向常量的指针`），或二者同时指定为const；
3. 在一个函数声明中，const可以修饰形参，表明它是一个输入参数，在函数内部不能改变其值；
4. 对于类的成员函数，有时候必须指定其返回值为const类型，以使得其返回值不为“左值”（返回值是引用类型时，是可以作为左值使用的，一般用于操作符重载）。
5. 对于类的成员函数，可以用const关键字来说明这个函数是 "只读(read-only)"函数，不会修改任何数据成员。为了声明一个const成员函数，把const关键字放在函数括号的后面。

［[改变 const 变量的值](http://www.nowcoder.com/questionTerminal/36f828664d2d4d14a1428ae49f701f23)］

const 可以分为 `顶层const` 和 `底层const`，顶层const可以表示任意的对象是常量，这一点对任何数据类型都适用，如算术类型、类指针等。底层 const 则与指针或者引用等复合类型的基本类型部分有关。比较特别的是，指针既可以是顶层 const 又可以是底层 const。

```c++
int i=0;
const int ci = 42;  // 不能改变 ci 的值，是顶层 const;
int* const p1 = &i; // 不能改变 p1 的值，是顶层 const;
const int *p2 = &ci;// 允许改变 p2 的值，是底层 const;
const int *const p3 = p2;// 前一个const底层，后一个顶层
const int &r = ci;  // 用于声明引用的都是 底层 const
```

在执行对象的拷贝动作时，常量是顶层const 时不受影响。拷贝执行操作并不会改变被拷贝对象的值，因此拷入和拷出的对象是否是常量都没什么影响。另一方面，**底层 const 的限制不能忽视**，当执行拷贝操作时，拷入和拷出的对象必须具有相同的底层 const 资格，或者两个对象的数据类型必须能够转换。一般来说，**非常量可以转换为常量**，反之则不行，如下：

```c++
int tmp = 88;           // 顶层 const
const int * pp = &tmp;  // 底层const
// int *p = pp;         // pp 包含底层 const 的定义, 而 p 没有
```

上面例子中如果允许`*pp = p3`，那么就可以通过 p 改变 pp 所指对象的值，这样 pp 就失去了底层 const 的约束。

详细的代码示例参见 [C++_Const.cpp](../Coding/C++_Const.cpp)。

# static

《C和指针》中说static有两层含义：`指明存储属性；改变链接属性`。（1）全局变量（包括函数）加上static关键字后，链接属性变为internal，也就是将他们限定在了本作用域内；（2）局部变量加上static关键字后，存储属性变为静态存储，不存储在栈区，下一次将保持上一次的尾值。

C 面向过程程序设计中的static：

1. 静态局部变量。在函数体内，一个被声明为静态的变量在这一函数被调用过程中维持上一次的值不变，即只初始化一次（该变量存放在.bss 或者 .data 区，而不是栈区）。
2. 静态全局变量。在模块内（但在函数体外），一个被声明为静态的变量可以被模块内函数访问，但不能被模块外访问。（注：模块可以理解为文件）。这样其它文件中可以定义相同名字的变量，不会发生冲突。
3. 静态全局函数。在模块内，一个被声明为静态的函数只可被这一模块内的其它函数调用。那就是，这个函数被限制在声明它的模块的本地范围内使用。

关于静态局部变量的存放位置，下面是一个不错的解释：

> Where your statics go depends on if they are 0 initialized or not. 0 initialized static data goes in .BSS (Block Started by Symbol), non 0 initialized data goes in .DATA 

关于静态全局变量和静态全局函数，下面是不错的解释：

> The whole and entire purpose of static is to declare that a variable is private to the source file that it is declared in. Thus, it is doing precisely its job in preventing a connection from an extern.  It is not visible to externs in other files, and you can have many different files that all declare static TYPE blah;, and they are all different.

简单来说，对于static 的全局变量，它对链接器不可以见，所以这个变量只能在当前文件中使用。下面是一个简单的例子，分别在两个文件里面都定义了全局变量num，结果会导致重复定义：

    $ cat test_1.cpp
    int num = 5;
    $ cat test_2.cpp
    #include <stdio.h>
    
    int num = 2;
    
    int main(void) {
        printf("num = %d\n", num);
        return 0;
    }
    $ g++ test_1.cpp test_2.cpp -o test_2.o
    duplicate symbol _num in: 
    ...
    clang: error: linker command failed with exit code 1 (use -v to see invocation)

将其中任意一个（当然，两个全部改也可以） num 改为 static 全局变量，则没有问题。

C++面向对象程序设计中的static：

* 静态成员变量：在类中的static成员变量意味着它为该类的所有实例所共享，也就是说当某个类的实例修改了该静态成员变量，其修改值为该类的其它所有实例所见；
* 静态成员函数：在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量(当然，可以通过传递一个对象来访问其成员)。

在类成员的声明之前加上关键字 static 使得成员与类本身直接相关，而不是与类的各个对象保持关联。和其他成员一样，静态成员可以是 public 或 private 的，静态数据成员的类型可以是常量、引用、指针、类类型等。类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。

# extern

简单来说，extern可以置于变量或者函数前，以标示变量或者函数的定义在别的地方。

extern 可以用于`提前引用声明`：如果全局变量不在文件的开头定义，其生命周期只限于定义处到文件结尾。如果在变量定义之前的函数想引用该全局变量，则应该在引用之前用关键字extern对该变量作外部变量声明，如下：

    extern int global;
    void show(){
        cout << global << "\n";
    }
    
    int global = 10;
    int main(){
        show();
        return 0;
    }

一个更加一般和常见的用法是在多文件的程序中声明外部变量。如果一个程序包含两个文件，在两个文件中都要用到同一个外部变量num，不能在两个文件中各自定义一个外部变量num（变量只能被定义一次）。正确的做法是：在任一个文件中定义外部变量num，而在另一文件中用extern对num作外部变量声明。

    $ cat test_1.cpp
    int num = 5;
    $ cat test_2.cpp
    #include <stdio.h>
    
    extern int num;
    
    int main(void) {
        printf("num = %d\n", num);
        return 0;
    }
    $ g++ test_1.cpp test_2.cpp -o test_2.o
    $ ./test_2.o
    num = 5
    
背后的工作机制如下：编译系统在遇到 extern int num 时，了解到num是一个在别处定义的全局变量，它先在本文件中找全局变量num，如果有，则将其作用域扩展到本行开始；如果本文件中无此全局变量，则在程序链接时从其他文件中找全局变量num，如果有，则把在另一文件中定义的外部变量num的作用域扩展到本文件，然后在本文件中可以合法地引用该外部变量num。

在大型项目中，如果有许多个文件要用到共同的全局变量可以将其放置在一个专门的头文件中，然后在其中一个源文件定义变量，在其他的源文件中使用该变量。具体的例子可以参考 [C++_Static_Global.h](../Coding/C++_Static_Global.h)，[C++_Static_Global.cpp](../Coding/C++_Static_Global.cpp) 和 [C++_Static_Global_Main.cpp](../Coding/C++_Static_Global_Main.cpp)。

# extern "C" 

`函数名修饰机制`

作为一种面向对象的语言，C++支持函数重载，而过程式语言C则不支持。函数被C++编译后在symbol库中的名字与C语言的不同，假设某个函数的原型为：    

    void foo(int x, int y);   

该函数被C编译器编译后在symbol库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。_foo_int_int这样的名字包含了函数名和函数参数数量及类型信息，C++就是靠这种机制来实现函数重载的。   

为了实现C和C++的混合编程，C++提供了C连接交换指定符号`extern "C"`来解决名字匹配问题，函数声明前加上extern "C"后，则编译器就会按照C语言的方式将该函数编译为_foo，这样C语言中就可以调用C++的函数了。

extern "C"用法如下：

    extern "C"{
        int func(int);
        int var;
    }

C++编译器会将在extern "C" 的大括号内部的代码当作C语言代码处理。所以很明显，上面的代码中，C++的名称修饰机制将不会起作用。它声明了一个C的函数func，定义了一个整形全局变量var。

# volatile

volatile 关键字是一种类型修饰符，用它声明的类型变量表示**编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问**。
    
volatile 指出变量是随时可能发生变化的，每次使用的时候必须从它所在的内存地址中读取，即使它前面的指令刚刚从该处读取过数据，而且读取的数据立刻被保存。而优化做法是，由于编译器发现两次读数据之间程序没有对变量进行过操作，它会自动使用上次读的数据。这样一来，如果是一个寄存器变量或者一个`端口数据`就会出错（它们的值由程序直接控制之外的过程控制），所以说volatile可以保证对特殊地址的稳定访问。

volatile 关键字不能保证全局变量多线程安全，因为 volatile 仅仅是告诫 compiler 不要对这个变量作优化，每次都要从 memory 取数值，而不是从register。

# inline

内联机制用于优化规模较小、流程直接、频繁调用的函数，因为调用函数一般比求等价表达式的值要慢一些。在大多数机器上，一次函数调用包括：调用前保存寄存器并在返回时恢复，可能需要拷贝实参等。

inline函数背后的整体观念就是，将对此函数的每一个调用都以函数本体替换之。这通常是在编译时期完成的，但是需要注意的是**inline只是对编译器发出的一个请求，编译器可以选择忽略这个请求**。inline 可以是显式，也可以隐式，class 内部定义的函数被隐式的声明为 inline 。

inline函数可以调用又不至于导致函数调用的开销，但是仍有一些弊端。比如导致代码膨胀，进而造成额外的换页行为，降低指令高速缓存装置的命中率，以及伴随而来的效率损失。

此外，有时候编译器虽然愿意 inlining 某个函数，但还可能为该函数生成一个函数本体。比如如果程序要取某个 inline 函数的地址，编译器必须为此函数生成一个本体，比如虚函数和递归函数。

**内联函数的定义最好是放在头文件中**，这样每一个包含该头文件的源文件均可以在编译器将调用该内联函数的代码展开。如果仅仅在头文件中声明内联函数，而在一个源文件中定义该函数，那么只有定义它的那个源文件可以在编译器展开内联函数。（这和模版类，函数模版的定义放在头文件中是基于同样的原理。）

[inline 函数的观点](http://www.nowcoder.com/questionTerminal/0cd6af2fd4374df597b49e09302b1a5a)  

## typedef

C++ 中，可以给一个合法的类型起一个`别名`，用以下句子：

    typedef existing_type new_type_name;

其中 existing_type 可以是简单的基本类型，也可以是混合类型（比如 int *[]），new_type_name 是这个类型的一个标识符。如下例子：

    typedef unsigned int WORD;
    typedef char * pChar;
    typedef char field [50];   // 合法的

c++ 11 中也可以使用关键字 using 来进行类型别名的声明，上面类型别名也可用下面语句来进行声明（它们在语义上是对等的）：

    using WORD = unsigned int;
    using pChar = char *;
    using field = char [50]; 

当定义一个函数指针时，typedef 用法稍微不同，

    // pFun 为函数 int(int, char * ) 的指针
    typedef int (* pFun )(int, char* );
    using pFun = int(*)(int, char *); 

此外，要注意 typedef 并不同于 define 那样做简单的文本替换，而是**类型别名**，看下面的两个例子。

    typedef int *pt;    	  
    const pt a;     // a 是常量指针(pt是指针，前面加 const，说明是const pointer)
    int * const a;  // 等同于上一句  
    pt c, d;        // cd 都是 int * 类型的

# register

一般情况下，变量的值是存放在内存中的。当程序中用到哪一个变量的值时，由控制器发出指令将内存中该变量的值送到CPU中的运算器。经过运算器进行运算，如果需要存储，再从运算器将数据送到内存存放。

为提高执行效率，C++允许将局部变量的值放在CPU中的寄存器中，需要用时直接从寄存器取出参加运算，不必再到内存中去存取。这种变量叫做寄存器变量，用关键字register作声明。

    int fac(int n)
    {
       register int i,f=1; //定义i和f是寄存器变量
       for(i=1;i<=n;i++) f=f*i;
       return f;
    }

定义f和i是存放在寄存器的局部变量，如果n的值大，则能节约许多执行时间。不过要注意在程序中**定义寄存器变量对编译系统只是建议性(而不是强制性)的**。此外，现在的优化编译系统能够识别使用频繁的变量，自动地将这些变量放在寄存器中。

# explicit

> The [explicit specifier](http://en.cppreference.com/w/cpp/language/explicit) specifies that a constructor or **conversion function** (since C++11) doesn't allow **implicit conversions** or **copy-initialization**. 

复制初始化（[copy initialization](http://en.cppreference.com/w/cpp/language/copy_initialization)）是指用一个对象来初始化另一个对象。主要分下面六种情况：

* T object = other;	 用`=操作符`声明一个非引用对象。
* T object = {other}; C++ 11 中的列表初始化。
* f(other); 向函数按照值传递传参数。
* return other; 函数返回一个值。
* throw object; catch (T object); throw 或者 catch 一个意外值。
* T array[N] = {other}; 

有时候在需要类型 T2 的地方，我们给了类型 T1，并且没有显式地进行类型转换。这时候可能就用到了**隐式类型转换**（[Implicit conversions](http://en.cppreference.com/w/cpp/language/implicit_conversion)），编译器在背后默默地将 T1 转换为 T2（编译器背着程序员做了太多的事情）。

关键字的使用详情可以参考下面：

```c++
struct A
{
    A(int) { }      // converting constructor
    A(int, int) { } // converting constructor (C++11)
    operator bool() const { return true; }
};

struct B
{
    explicit B(int) { }
    explicit B(int, int) { }
    explicit operator bool() const { return true; }
};

int main()
{
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2(2);       // OK: direct-initialization selects A::A(int)
    A a3 {4, 5};   // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A)1;   // OK: explicit cast performs static_cast
    if (a1) cout << "true" << endl; // OK: A::operator bool()
    bool na1 = a1; // OK: copy-initialization selects A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization

//  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
    B b2(2);       // OK: direct-initialization selects B::B(int)
    B b3 {4, 5};   // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)
    B b5 = (B)1;   // OK: explicit cast performs static_cast
    if (b5) cout << "true" << endl; // OK: B::operator bool()
//  bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()
    bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization
}
```

# final

C++ 11 中引入了final关键字，用来阻止类的进一步派生和虚函数的进一步重载。

> Specifies that a virtual function cannot be overridden in a derived class or that a class cannot be inherited from.

看一个简单的例子：

```c++
struct Base
{
    virtual void foo();
};
 
struct A : Base
{
    virtual void foo() final; // A::foo is final
    void bar() final; // Error: non-virtual function cannot be final
};
 
struct B final : A // struct B is final
{
    void foo(); // Error: foo cannot be overridden as it's final in A
};
 
struct C : B // Error: B is final
{
};
```

# override

一个派生类可以覆盖在基类中声明的虚函数，这是面向对象设计的基础。然而这么简单的操作也会出错，关于覆盖虚函数的两个常见错误如下： 

* `无意中覆盖`：派生类不小心实现了一个和基类名字和参数列表相同的虚函数。
* `签名不匹配`：本来要覆盖基类的虚函数，结果导致产生了一个新的函数。

使用 override 可以避免这两个问题。因为 override 明确告诉编译器该函数覆盖了基类中的虚函数，任何违反了这一语义的实现编译器都将显式地给出错误提示。

> In a member function declaration or definition, override ensures that the function is virtual and is overriding a virtual function from the base class. The program is ill-formed (a compile-time error is generated) if this is not true.

看一个简单的例子：

```c++
struct A
{
    virtual void foo();
    void bar();
};
 
struct B : A
{
    void foo() const override; // Error: B::foo does not override A::foo
                               // (signature mismatch)
    void foo() override; // OK: B::foo overrides A::foo
    void bar() override; // Error: A::bar is not virtual
};
```

编译器实现 override 的方法很简单，如下：

> The override special identifier means that the compiler will check the base class(es) to see if there is a virtual function with this exact signature. And if there is not, the compiler will error out.

不过注意 override 和 final 一样，不是C++保留字：

> Note that neither override nor final are language keywords. They are technically identifiers; they only gain special meaning when used in those specific contexts. In any other location, they can be valid identifiers.

# new 操作符

new和delete对堆中的内存进行申请和释放，而且这两个操作符是不能被重载的。要实现不同的内存分配行为，需要重载operator new，而不是new和delete。

看如下代码：

    class foo{};
    foo* pfoo = new foo;
    
这里的new实际上是执行如下3个过程：

1. 调用operator new分配内存；
2. 调用构造函数生成类对象；
3. 返回相应指针。

operator new 就像 operator+ 一样，是可以重载的，但是不能在全局对原型为void operator new(size_t size)这个原型进行重载，一般只能在类中进行重载。

如果类中没有重载operator new，那么调用的就是全局的::operator new来完成堆的分配。同理，operator new[]、operator delete、operator delete[]也是可以重载的。

new 操作符分配内存需要在堆中查找足够大的剩余空间，这个操作速度是很慢的，而且有可能出现无法分配内存的异常（空间不够）。

# 更多阅读

[Meaning of “const” last in a C++ method declaration?](http://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-c-method-declaration)  
[Type aliases (typedef / using)](http://www.cplusplus.com/doc/tutorial/other_data_types/)   
[How do I use extern to share variables between source files in C?](http://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files-in-c)  
[When to use extern in C++](http://stackoverflow.com/questions/10422034/when-to-use-extern-in-c)  
[What does the explicit keyword in C++ mean?](http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean)   
[What is the meaning of “operator bool() const”](http://stackoverflow.com/questions/4600295/what-is-the-meaning-of-operator-bool-const)  
[Appearing and Disappearing consts in C++](http://aristeia.com/Papers/appearing%20and%20disappearing%20consts.pdf)  

[揭秘 typedef四用途与两陷阱](http://niehan.blog.techweb.com.cn/archives/325.html)  
[typedef 用法总结](http://blog.csdn.net/gaohuaid/article/details/16829599)  
[C/C++中的static关键字的总结](https://yq.aliyun.com/articles/47641)  
[Where are static variables stored (in C/C++)?](http://stackoverflow.com/questions/93039/where-are-static-variables-stored-in-c-c)  
[extern "C"](http://book.51cto.com/art/200904/121028.htm)
[详解C中volatile关键字](http://www.cnblogs.com/yc_sunniwell/archive/2010/06/24/1764231.html)   
[关于C++ const 的全面总结](http://blog.csdn.net/eric_jo/article/details/4138548)  
 
Effective C++：条款30， 透彻理解 inlining的里里外外  

