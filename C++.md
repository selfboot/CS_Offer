# 面向对象程序设计

面向对象程序设计的核心思想是数据抽象（封装）、继承和多态（动态绑定）

* 数据抽象：把客观事物封装成抽象的类，同时将类的接口和实现分离。（优点：可以隐藏实现细节，使得代码模块化）
* 继承：定义相似的类型，并对其相似关系建模。（优点：可以扩展已存在的代码模块）
* 多态：一定程度上忽略相似类型的区别，以统一的方式使用它们的对象。

面向对象设计的 5 大原则：

* SRP(The Single Responsibility Principle) 单一职责原则：一个类应该有且只有一个去改变它的理由，这意味着一个类应该只有一项工作。
* OCP(The Open Closed Principle) 开放封闭原则：对象或实体应该对扩展开放，对修改封闭，这就意味着一个类应该无需修改类本身但却容易扩展。
* LSP(The Liskov Substitution Principle) 里氏替换原则：每一个子类或派生类应该可以替换它们的基类或父类。
* ISP(The Interface Segregation Principle) 接口隔离原则：不应强迫客户端实现一个它用不上的接口，或是说客户端不应该被迫依赖它们不使用的方法。
* D(The Dependency Inversion Principle) 依赖倒置原则：实体必须依靠抽象而不是具体实现。它表示高层次的模块不应该依赖于低层次的模块，它们都应该依赖于抽象。

参考  
[S.O.L.I.D：面向对象设计的头 5 大原则](http://blog.jobbole.com/86267/)  

C++ 有关类的更多内容，参见 [C++_Class.md](More/C++_Class.md)

# 关键字

## const 关键字

1. 欲阻止一个变量被改变，可以使用const关键字。在定义该const变量时，通常需要对它进行初始化，因为以后就没有机会再去改变它了；
2. const 的引用，对常量的引用不能用作修改它绑定的对象，但是由于对象本身可能是非常量，所以允许通过其他途径改变值。
3. 对指针来说，可以指定指针本身为常量（const pointer, `常量指针`），也可以指定指针所指的对象为常量（pointer to const, `指向常量的指针`），或二者同时指定为const；
4. 在一个函数声明中，const可以修饰形参，表明它是一个输入参数，在函数内部不能改变其值；
5. 对于类的成员函数，有时候必须指定其返回值为const类型，以使得其返回值不为“左值”。
6. 对于类的成员函数，可以用const关键字来说明这个函数是 "只读(read-only)"函数，不会修改任何数据成员。为了声明一个const成员函数，把const关键字放在函数括号的后面。

［[改变 const 变量的值](http://www.nowcoder.com/questionTerminal/36f828664d2d4d14a1428ae49f701f23)］

代码实例参见 [C++_Const.cpp](C++_Code/C++_Const.cpp)

参考  
[Meaning of “const” last in a C++ method declaration?](http://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-c-method-declaration)  

## static 关键字

static 用法

1. 在函数体内，一个被声明为静态的变量在这一函数被调用过程中维持上一次的值不变，即只初始化一次（该变量存放在静态变量区，而不是栈区）。
2. 在模块内（但在函数体外），一个被声明为静态的变量可以被模块内所用函数访问，但不能被模块外访问。（注：模块可以理解为文件）
3. 在模块内，一个被声明为静态的函数只可被这一模块内的其它函数调用。那就是，这个函数被限制在声明它的模块的本地范围内使用。

《C和指针》中说static有两层含义：`指明存储属性；改变链接属性`。（1）全局变量（包括函数）加上static关键字后，链接属性变为internal，也就是将他们限定在了本作用域内；（2）局部变量加上static关键字后，存储属性变为静态存储，不存储在栈区，下一次将保持上一次的尾值。除此之外，C++中还有新用法：

* 在类中的static成员变量意味着它为该类的所有实例所共享，也就是说当某个类的实例修改了该静态成员变量，其修改值为该类的其它所有实例所见；
* 在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量(当然，可以通过传递一个对象来访问其成员)。

## extern 关键字

全局变量(外部变量)是在函数的外部定义的，它的作用域为从变量的定义处开始，到本程序文件的末尾。在此作用域内，全局变量可以为本文件中各个函数所引用。编译时将全局变量分配在静态存储区。

有时需要用**extern来声明全局变量，以扩展全局变量的作用域**。

1. 在一个文件内声明全局变量

    `提前引用声明`：如果外部变量不在文件的开头定义，其有效的作用范围只限于定义处到文件结尾了。如果在定义点之前的函数想引用该全局变量，则应该在引用之前用关键字extern对该变量作外部变量声明，表示该变量是一个将在下面定义的全局变量。

2. 在多文件的程序中声明外部变量
    
    如果一个程序包含两个文件，在两个文件中都要用到同一个外部变量num，不能分别在两个文件中各自定义一个外部变量num。正确的做法是：在任一个文件中定义外部变量num，而在另一文件中用extern对num作外部变量声明。即
    
        extern int num;
    
    编译系统由此知道num是一个已在别处定义的外部变量，它先在本文件中找有无外部变量num，如果有，则将其作用域扩展到本行开始(如上节所述)，如果本文件中无此外部变量，则在程序连接时从其他文件中找有无外部变量num，如果有，则把在另一文件中定义的外部变量num的作用域扩展到本文件，在本文件中可以合法地引用该外部变量num。

## extern "C" 函数名修饰机制

作为一种面向对象的语言，C++支持函数重载，而过程式语言C则不支持。函数被C++编译后在symbol库中的名字与C语言的不同，例如，假设某个函数的原型为：    

    void foo(int x, int y);   

该函数被C编译器编译后在symbol库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。_foo_int_int这样的名字包含了函数名和函数参数数量及类型信息，C++就是靠这种机制来实现函数重载的。   

为了实现C和C++的混合编程，C++提供了C连接交换指定符号`extern "C"`来解决名字匹配问题，函数声明前加上extern "C"后，则编译器就会按照C语言的方式将该函数编译为_foo，这样C语言中就可以调用C++的函数了。

extern "C"用法如下：

    extern "C"{
        int func(int);
        int var;
    }

C++编译器会将在extern "C" 的大括号内部的代码当作C语言代码处理。所以很明显，上面的代码中，C++的名称修饰机制将不会起作用。它声明了一个C的函数func，定义了一个整形全局变量var。

参考： [extern "C"](http://book.51cto.com/art/200904/121028.htm)

## volatile（透彻理解 cpu 的寄存器缓存机制）

volatile 关键字是一种类型修饰符，用它声明的类型变量表示编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。
    
volatile 指出变量是随时可能发生变化的，每次使用的时候必须从它所在的内存地址中读取，即使它前面的指令刚刚从该处读取过数据，而且读取的数据立刻被保存。而优化做法是，由于编译器发现两次读数据之间程序没有对变量进行过操作，它会自动使用上次读的数据。这样一来，如果是一个寄存器变量或者一个`端口数据`就会出错（它们的值由程序直接控制之外的过程控制），所以说volatile可以保证对特殊地址的稳定访问。

volatile 关键字不能保证全局变量多线程安全，因为 volatile 仅仅是告诫 compiler 不要对这个变量作优化，每次都要从 memory 取数值，而不是从register。

参考： [详解C中volatile关键字](http://www.cnblogs.com/yc_sunniwell/archive/2010/06/24/1764231.html)

## register 关键字

一般情况下，变量的值是存放在内存中的。当程序中用到哪一个变量的值时，由控制器发出指令将内存中该变量的值送到CPU中的运算器。经过运算器进行运算，如果需要存数，再从运算器将数据送到内存存放。

为提高执行效率，C++允许将局部变量的值放在CPU中的寄存器中，需要用时直接从寄存器取出参加运算，不必再到内存中去存取。这种变量叫做寄存器变量，用关键字register作声明。

    int fac(int n)
    {
       register int i,f=1; //定义i和f是寄存器变量
       for(i=1;i<=n;i++) f=f*i;
       return f;
    }

定义f和i是存放在寄存器的局部变量，如果n的值大，则能节约许多执行时间。不过要注意在程序中定义寄存器变量对编译系统只是建议性(而不是强制性)的。此外，现在的优化编译系统能够识别使用频繁的变量，自动地将这些变量放在寄存器中。

## final 关键字

final关键字可用于修饰类、变量和方法。final修饰的类不能被继承，final修饰的方法不能被重写，final修饰的变量不可被修改，一旦获得初始值，该变量就不能被重新赋值。
    
    class NoDerived final  { /* */ };
    class Base { /* */ };               // Base 必须定义后才能作为基类
    class Last final: Base { /* */ };
    class Bad: Last  { /* */ };         // 错误，Last 是 final的
    class Bad_2: NoDerived { /* */ };   // 错误，NoDerived 是 final的

［[final 描述错误](http://www.nowcoder.com/questionTerminal/8272c92814ca40c39f9a534485c90be2)］

## inline 关键字

内联机制用于优化规模较小、流程直接、频繁调用的函数，因为调用函数一般比求等价表达式的值要慢一些。在大多数机器上，一次函数调用包括：调用前保存寄存器并在返回时恢复，可能需要拷贝实参等。

inline函数背后的整体观念就是，将对此函数的每一个调用都以函数本体替换之。这通常是在编译时期完成的，但是需要注意的是inline只是对编译器发出的一个请求，编译器可以选择忽略这个请求。inline 可以是显式，也可以隐式。class 内部定义的函数被隐式的声明为 inline 。

inline函数可以调用又不至于导致函数调用的开销，但是仍有一些弊端。比如导致代码膨胀，进而造成额外的换页行为，降低指令高速缓存装置的命中率，以及伴随而来的效率损失。

此外，有时候编译器虽然愿意 inlining 某个函数，但还可能为该函数生成一个函数本体。比如如果程序要取某个 inline 函数的地址，编译器必须为此函数生成一个本体。

参考：Effective C++：条款30， 透彻理解 inlining的里里外外

## typedef 关键字

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
    const pt a;         // a 是常量指针(pt是指针，前面加 const，说明是const pointer)
    int * const a;      // 等同于上一句  
	  pt c, d;           // cd 都是 int * 类型的

参考  
[Type aliases (typedef / using)](http://www.cplusplus.com/doc/tutorial/other_data_types/)  
[揭秘 typedef四用途与两陷阱](http://niehan.blog.techweb.com.cn/archives/325.html)  
[typedef 用法总结](http://blog.csdn.net/gaohuaid/article/details/16829599)  

# 数组

数组名指代一种数据结构，这种数据结构就是数组。

    char str[10];
    cout << sizeof(str) << endl; // 输出 10

此外，数组名可以转换为指向其指代实体的指针，而且是一个常量指针，不能作自增、自减等操作；

    int nums[] = {1,2,3,4};
    *nums = 2;
    nums++; // cannot increment value of type 'int [4]'

再来看另一个例子：

    int a[5]={1,2,3,4,5};
    int *ptr=(int *)(&a+1);
    printf("%d",*(ptr-1));

这里 &a+1 并不是数组的首地址a+1，因为 &a 是指向数组的指针，其类型为int(* )[5]。而指针加1要根据指针类型加上一定的值，不同类型的指针+1之后增加的大小不同，a是长度为5的int数组指针，所以要加5 * sizeof(int)，所以ptr指向的位置是a+5。但是ptr与（&a+1）类型是不一样的，所以ptr-1只会减去sizeof(int*)。

## 数组形参

数组作为形参时，会退化为指针，这是因为数组的两个性质：

1. 不允许拷贝数组（无法以值传递的方式使用数组参数）；
2. 使用数组时会将其转换为指针。

所以给函数传递指针时，实际上传递的是指向数组首元素的指针。

    // 尽管形式不同，但是这三个 print 函数是等价的
    void print(const int*);
    void print(const int[]);   
    void print(const int[10]); // 纬度表示期望数组含有多少元素，实际并不一定

［[数组合法参数](http://www.nowcoder.com/questionTerminal/e2ac8bddb9e5434a92511320221c8513)］

# 指针

指针的更多内容参考 [C++_Pointer](More/C++_Pointer.md)

## 指针与引用：

将“引用”作为函数返回值类型，好处是在内存中不产生被返回值的副本。正是因为这点原因，所以返回一个局部变量的引用是不可取的。因为随着该局部变量生存期的结束，相应的引用也会失效!也不能返回函数内部new分配的内存的引用，被函数返回的引用只是作为一个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。

指针与引用区别如下：

1. 指针是一个变量，只不过这个变量存储的是一个地址，指向内存的一个存储单元；而引用只不过是变量的一个别名而已。
2. 指针的值可以为空，也可能指向一个不确定的内存空间，但是引用的值不能为空，并且引用在定义的时候必须初始化为特定对象；
3. 指针的值在初始化后可以改变，即指向其它的存储单元，而引用在进行初始化后就不可以改变引用对象了；
4. 指针可以有多级，但是引用只能是一级；
5. sizeof引用得到的是所指向的变量(对象)的大小，而sizeof指针得到的是指针本身的大小；

## 指针和const

指向常量的指针（`pointer to const`）不能用于改变其所指对象的值，要想存放常量对象的地址，只能使用指向常量的指针。

    const int *a = 3;
    int const *a = 3;
    int const* a = 3;

指针本身是对象，因此可以把指针本身定为常量。常量指针（`const pointer`）必须初始化，而且一旦初始化完成，则它的值（也就是存放在指针中的那个地址）就不能再改变了。

    int errNumb = 0;
    int *const curErr = &errNumb;

也可以定义一个指向常量的常量指针（const pointer to const）。

    const double pi=3.14;
    const double * const pip = &pi;

为了判断const到底对谁起作用（即谁是const的），可以用以下简单规则：**const只对它左边的东西起作用，当const本身就是最左边的修饰符时，它才会对右边的东西起作用**。

［[指向常量的指针](http://www.nowcoder.com/questionTerminal/524cd1e7926a44e38d9d7c3a3359b822)］  
［[指针改变常量的值](http://www.nowcoder.com/questionTerminal/36f828664d2d4d14a1428ae49f701f23)］  

## 函数指针

函数指针指向的`是函数而非对象`，和其他指针一样，函数指针指向某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。

当我们把函数名作为一个值使用时，该函数自动地转换为指针。还可以直接使用指向函数的指针调用该函数，无需提前解引用指针。

指向不同函数类型的指针间不存在转换规则，但是可以为函数指针赋一个 nullptr 或者值为 0 的整型常量表达式。

和数组类似，虽然不能定义函数类型的形参，但是形参可以是指向函数的指针，此时，形参看起来是函数类型，实际上却是当成指针使用。

和数组类似，虽然不能直接返回一个函数，但是能返回指向函数类型的指针。这里，`必须把返回类型写成指针形式`，编译器不会自动地将函数返回类型当成对应的指针类型来处理。

更多内容参见 [C++_Pointer.md](More/C++_Pointer.md)  

［[函数指针定义](http://www.nowcoder.com/questionTerminal/960f8047a9ee4a6f8227768f3bc2734d)］  
［[函数指针应用](http://www.nowcoder.com/questionTerminal/2c18fc889b924cc1b21ce6ec387fd853)］  
［[成员函数的函数指针](http://www.nowcoder.com/questionTerminal/648f3eaef4234a34a5d5dbd268a77fa7)］  

《C++ Primer》 P221

# 函数

## 重载函数

如果`同一个作用域内`的几个`函数名字相同`但`形参列表`不同，称之为重载函数（main函数不能重载）。对于重载函数来说，它们应该在形参数量或形参类型上有所不同。不允许两个函数除了返回类型外其它所有的要素都相同。

一个拥有顶层 const 的形参无法和另一个没有顶层 const 的形参区分开来：

    int getnum(int);
    int getnum(const int);    // 重复声明
    
    int getpos(int *);
    int getpos(int * const);  // 重复声明

如果形参是某种类型的引用或者指针，则通过其指向的是常量对象还是非常量对象可以实现函数重载，此时 const 是底层的：

    int getnum(int &);
    int getnum(const int &);  // 新函数，作用于常量引用
    
    int getpos(int *);
    int getpos(const int *);  // 新函数，作用于指向常量的指针

［[C++ 重载函数原型](http://www.nowcoder.com/questionTerminal/dcb7cdf4d47747faa3be0d14d3b886e2)］   
［[重载函数调用错误的](http://www.nowcoder.com/questionTerminal/a4311c49cc3843249e6b36e05b55edd4)］

# 存储相关

## 内存对齐、struct 结构

许多实际的计算机系统对基本类型数据在内存中存放的位置有限制，它们会要求这些数据的首地址的值是某个数k（通常它为4或8）的倍数，这就是所谓的内存对齐。

每个特定平台上的编译器都有自己的默认“对齐系数”（32位机一般为4，64位机一般为8）。我们可以通过预编译命令#pragma pack(k)，k=1,2,4,8,16来改变这个系数，其中k就是需要指定的“对齐系数”；也可以使用#pragma pack()取消自定义字节对齐方式。

struct 或者 union 成员对齐规则如下：

1. 第一个数据成员放在offset为0的地方，每个成员按照对齐系数和自身占用字节数中，二者比较小的那个进行对齐；
2. 在数据成员完成各自对齐以后，struct或者union本身也要进行对齐，对齐将按照对齐系数和struct或者union中最大数据成员长度中比较小的那个进行；

先局部成员对齐，然后再全局对齐。（[memory_align.cpp](C++_Code/memory_align.cpp)）

此外，值得注意的是，enum 内部是 int 实现的，所以大小为 4。用 typedef 声明指针时，并不为指针分配空间。

［[enum，typedef声明指针](http://www.nowcoder.com/questionTerminal/f12da06f01594f4d8d04a1f242399dc5)］  
［[结构体中 : 的含义](http://www.nowcoder.com/questionTerminal/f4e20747a2dd4649bac0c028daa234f4)］    

参考  
[C、C++内存对齐](http://www.jellythink.com/archives/413)

## 联合体存储特点以及CPU字节序

`联合体`：在C/C++程序的编写中，当多个基本数据类型或复合数据结构要占用同一内存块时，就要用到联合体。联合体变量所占内存长度是各成员中最长的成员占的内存长度。union所有成员都从低地址开始存放。

`Little endian` 和 `Big endian` 是CPU 存放数据的两种不同顺序。对于整型、长整型等数据类型，Big endian 认为第一个字节是最高位字节（按照从低地址到高地址的顺序存放数据的高位字节到低位字节）；而Little endian 则相反，它认为第一个字节是最低位字节（按照从低地址到高地址的顺序存放数据的低位字节到高位字节）。

例如，假设从内存地址0x0000开始有以下数据：0x12 0x34 0xab 0xcd。如果我们去读取一个地址为 0x0000 的四个字节变量，若字节序为big-endian，则读出结果为0x1234abcd；若字节序位little-endian，则读出结果为 0xcdab3412。

一般来说，x86系列CPU 都是little-endian 的字节序，PowerPC通常是Big endian，还有的CPU 能通过跳线来设置CPU 工作于Little endian 还是Big endian 模式。

我们可以利用 union 的存储特点，写一个简单的程序来判定当前 CPU 的字节序([union_endian.cpp](C++_Code/union_endian.cpp))。

［[判断 CPU大小端](http://www.nowcoder.com/questionTerminal/a903ebe93add411d9c94b114f5fabb36)］  
［[溢出，大小端](http://www.nowcoder.com/questionTerminal/c7298be0b2ce42698b80987631cf8fca)］  
［[大小端，网络发送](http://www.nowcoder.com/questionTerminal/d7c1ff50fab44443b61903eccd791f1d)］  

## sizeof 运算符
    
sizeof 运算符返回`一条表达式或者一个类型名字所占的字节数`，sizeof 运算符满足右结合律，所得的值是一个 size_t 类型的常量表达式。sizeof 运算符的运算对象有两种形式：

1. sizeof *(type)*
2. sizeof *expr*

第二种形式中，返回的是表达式结果类型的大小（注意**，sizeof 并不实际计算其运算对象的值**）。

    Sales_data data, *p;        
    sizeof(Sales_data); // 存储 Sales_data 类型的对象所占空间的大小
    sizeof data;        // data 的类型的大小，即 Sales_data
    sizeof p;           // 指针所占空间的大小
    sizeof *p;          // p所指类型的空间大小，即sizeof(Sales_data)
    sizeof data.revenue;// Sales_data 的 revenue 成员对应类型的大小
    sizeof Sales_data::revenue;// 另一种获取 revenue 大小的方式

在 sizeof 的运算对象中解引用一个无效指针仍然是一种安全的行为，因为指针实际上并没有被真正使用，sizeof 并不需要真的解引用指针也能知道它所指对象的类型。这是一件可以在程序运行前（编译时）完成的事情，所以，sizeof(*p)直接就被具体数字给取代了，在运行时也就不会有了解引用这个表达式。

    int i = 10;
    printf("%d\n",i);                           // 10
    // sizeof 并不计算 i++
    printf("%d\n",sizeof(i++));                 // 4
    printf("%d\n",i);                           // 10
    
sizeof 运算符的结果部分地依赖于其作用的类型：

* 对 char 或者类型为 char 的表达式执行 sizeof 运算，结果得 1；
* 对引用类型执行 sizeof 运算得到被引用对象所占空间的大小；
* 对指针执行 sizeof 运算得到指针本身所占空间的大小；
* 对解引用指针执行 sizeof 运算得到指针指向的对象所占空间的大小，指针不需要有效；
* 对数组执行 sizeof 运算得到整个数组所占空间的大小（sizeof 不会把数组转换成指针来处理，可以用数组的大小除以单个元素的大小得到数组中元素的个数）。
* 对 string 对象或 vector 对象执行 sizeof 运算只返回该类型固定部分的大小（**24**），不会计算对象占用了多少空间；

此外求类的大小时遵循下面规则（只统计与类的实例有关的，只与类型相关的不统计）：

1. 类的非静态成员数据的类型大小之和，也就是说静态成员数据不作考虑。
2. 普通成员函数与sizeof无关，调用普通成员函数只需要知道函数的地址即可，而这些地址只与类型相关，与类型的实例无关。
3. 虚函数由于要维护在虚函数表，所以要占据一个指针大小
4. 类的总大小也遵守类似 struct 字节对齐的调整规则
5. 空类的大小为 1（空类型的实例中不包含任何信息，但是声明空类的实例时，必须在内存中占有一定的空间，否则无法使用这些实例。占有空间数由编译器决定，一般是1）。

[sizeof_demo.cpp](C++_Code/sizeof_demo.cpp)  

［[字符数组，八进制坑](http://www.nowcoder.com/questionTerminal/a7b35bc367604e73823d2dded6496e38)］  
［[类的大小](http://www.nowcoder.com/questionTerminal/33f3a63dc5d449adb351168ada7f47c6)］  
［[C中整型字符常量，C++字符字面量大小](http://www.nowcoder.com/questionTerminal/e16ca070d715455fa8f6916aa324138d)］  
［[引用的大小](http://www.nowcoder.com/questionTerminal/31095437d232497c9ea40c5c7a629dc4)］  

参考    
[sizeof() a vector](http://stackoverflow.com/questions/2373189/sizeof-a-vector)

## C++内存堆栈

堆区，栈区的区别：

* 管理方式：对于栈来讲，是由编译器自动管理；对于堆来说，分配释放工作由程序员控制，容易造成内存泄露。
* 空间大小：一般来讲在32位系统下，堆内存可以达到4G的空间，从这个角度来看堆内存几乎是没有什么限制的。但是对于栈来讲，一般都是有一定的空间大小的。
* 碎片问题：对于堆来讲，频繁的new/delete势必会造成内存空间的不连续，从而造成大量的碎片，使程序效率降低。对于栈来讲，则不会存在这个问题。
* 生长方向：对于堆来讲，向着内存地址增加的方向增长；对于栈来讲，向着内存地址减小的方向增长。
* 分配方式：堆都是动态分配（运行期）的，没有静态分配（编译期）的堆。栈有2种分配方式：静态分配和动态分配（alloca()函数可以动态分配栈的内存空间，释放的时候由编译器自己释放）。
* 分配效率：计算机在底层对栈提供支持，分配专门的寄存器存放栈的地址，压栈出栈都有专门的指令执行，这就决定了栈的效率比较高。堆则是C/C++函数库提供的，它的机制是很复杂的，效率比栈要低得多。

［[栈空间分布，printf 函数参数](http://www.nowcoder.com/questionTerminal/b5e03f2361f04631b2eaf567029385c6)］  

## 常见的内存错误

常见内存错误以及解决办法:

* 内存分配未成功，却使用了它。（在使用内存之前检查指针是否为NULL）
* 内存分配虽然成功，但是尚未初始化就引用它。（无论用何种方式创建数组，都应该初始化）
* 内存分配成功并且已经初始化，但操作越过了内存的边界。例如在使用数组时经常发生下标“多1”或者“少1”的操作。特别是在for循环语句中，循环次数很容易搞错，导致数组操作越界。
* 忘记了释放内存，造成内存泄露。动态内存的申请与释放必须配对，程序中malloc与free的使用次数一定要相同，否则肯定有错误（new/delete）。
* 释放了内存却继续使用它。

## new 和 delete 操作

有时候需要一次为很多对象分配/释放内存，为此 C++ 提供了 new/delete 操作符。为了让 new 分配一个对象数组，需要在类型名后跟一对方括号，在其中指明要分配的对象的数目。

    int *pia = new int[10];
    typedef int arrT[10];   // arrT 表示 10 个int的数组类型 
    int *p = new arrT;      // 分配一个 10 个 int 的数组，p指向第一个int。编译器执行时和第一句完全一样

虽然通常称new T[] 分配的内存为动态数组，但当我们用new分配一个数组时，并未得到一个`数组类型的对象`，而是得到一个相应元素类型的**指针**。由于分配的内存并不是一个数组类型，因此不能对动态数组调用 begin 或 end，也不能用范围 for 语句来处理动态数组中的元素，sizeof 的结果也和真正的数组类型的对象不同。

默认情况下，new 分配的对象，不管是单个分配的还是数组中的，都是默认初始化的。不过也可以对数组中的元素进行值初始化，方法是在大小之后跟一对空括号。

    int *pia = new int[10];
    int *pia2 = new int[10](0);

使用new操作符来分配对象内存时会经历三个步骤：

1. 调用operator new 函数（对于数组是operator new[]）分配一块足够大的，原始的，未命名的内存空间以便存储特定类型的对象。
2. 编译器运行相应的构造函数以构造对象，并为其传入初值。
3. 对象构造完成后，返回一个指向该对象的指针。

当我们使用一条 delete 表达式删除一个动态分配的对象时：

    delete sp;          // 销毁 *sp, 然后释放 sp 指向的内存空间
    delete [] arr;      // 销毁数组中的元素，然后释放对应的内存空间

实际上执行了两步操作：

1. 对 sp 所指的对象或者 arr 所指的数组中的元素执行对应的析构函数。
2. 编译器调用标准库operator delete(或operator delete[])函数释放内存空间。

数组中的元素按逆序销毁，即最后一个元素首先被销毁，然后是倒数第二个，依次类推。当释放一个指向数组的指针时，空方括号对是必需的：它指示编译器此指针指向一个对象数组的第一个元素。**如果在 delete 一个指向数组的指针时忽略了方括号，或者在 delete 一个指向单一对象的指针时使用了方括号，其行为是未定义的。**

［[内存管理错误代码](http://www.nowcoder.com/questionTerminal/84598a88502c499d995db941c5fb62a2)］  
［[delete 内存泄漏](http://www.nowcoder.com/questionTerminal/9fb652d48bee45bcb47771b2e3c6f690)］  

## new 和 malloc 的对比

1. new/delete是C++操作符，malloc/free是C/C++函数。
2. 使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算，而malloc则需要显式地指出所需内存的尺寸。
3. new/delete会调用对象的构造函数/析构函数以完成对象的构造/析构。而malloc只分配空间。
4. new 操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换，故new是符合类型安全性的操作符。而malloc内存分配成功则是返回void * ，需要通过强制类型转换将 void* 指针转换成我们需要的类型。
5. 效率上：malloc的效率高一点，因为只分配了空间。
6. opeartor new /operator delete 可以被重载，而malloc/free并不允许重载。

参考  
[细说new与malloc的10点区别](http://www.cnblogs.com/QG-whz/p/5140930.html)

## 浮点数存储

整数可以很方便地用二进制来存储，对于小数来说，直观上来看，转为二进制也很简单，分整数部分和小数部分分别转换，比如十进制数 9.3125 表示为二进制为 1001.0101。（整数部分用2除，取余数；小数部分用2乘，取整数位。）

    0.3125 * 2 = 0.625 整数位是 0   --> .0
    0.625 * 2 = 1.25   整数位是 1   --> .01
    0.25 * 2 ＝ 0.5    整数位是 0   --> .010
    0.5 * 2 = 1.0      整数位是 1   --> .0101

通常，浮点数可以被表示成 N = S * r^j ，其中 S 为尾数，j为阶码，r是基数。`阶码是整数，阶符和阶码的位数合起来反映浮点数的表示范围及小数点的实际位置。尾数是小数，其位数反映了浮点数的精度。`

在计算机中，基数一般取 2，所以数 N=11.0101，可以写为：

0.110101 * 2^2  
1.10101 * 2^1  
1101.01 * 2^-2  

为了提高精度以及便于浮点数的比较，在计算机中规定浮点数的尾数用纯小数表示，此外将尾数最高位为1的浮点数称为`规格化数`，即 N=0.110101 为N的规格化形式。

C++ 编译器中浮点数存储采用的是 IEEE 754标准，它定义的单精度浮点数的长度为 32 位，按位域可划分为：符号位、阶码位与尾数位。

单精度浮点数位域划分如下：

     31----------------------22----------------------------------------------------------0
      |                       |                                                          |
      X X X X    X X X X    X X X X    X X X X    X X X X    X X X X    X X X X    X X X X
      | |-------------------| |----------------------------------------------------------|
    符号        阶码                                     尾数

其中：

* `符号位`：取 0 表示正数，取 1 表示负数。
* `阶码`：阶码用移码表示，阶码的真值都被加上一个常数（偏移量），单精度偏移量为 127 (0x7f) 。
* `尾数`：尾数长度在图示中是 23 位，但实际上却是 24 位，还有一个位是“不可见”的，其值固定为 1，也就是说 IEEE 754 标准所定义的浮点数，其有效数字是介于 1 与 2 之间的小数。规格化尾数时注意小数范围为 1 到 2.

下面以数字 0.75 为例：

> 十进制 0.75 转换为二进制 -- 0.11  
> 二进制 0.11 规格化-------- 1.1*2^-1  
> 计算阶码----------------- -1+127=126  
> 符号位 指数部分    尾数部分  
> 0 ----01111110 -10000000000000000000000  
> 以单精度浮点格式存储该数  0011 1111 0100 0000 0000 0000 0000 0000  

一个十进制数能否用二进制浮点数精确表示，关键在于小数部分。我们来看一个最简单的小数 0.1，它会得到一个无限循环的二进制小数 0.000110011...，用有限位无法表示无限小数，因此无法用IEEE 754 浮点数精确表示。

IEEE 754 标准所定义的单精度浮点数所表示的数的范围大约为 -2^128 ~ 2^128 （-10^38 ～ 10^38 ），因为尾数的最大值是接近 2，而指数的范围是 [-127, 127]，那么这个范围就可以表示为2*2^127 。单精度浮点数的精度为小数点后面 5～6（2^23 =8388608）个十进制位。

    float b = 54.00001;
    float c = 54.000001;
    cout << setprecision(10) << b << endl; // 54.00001144
    cout << setprecision(10) << c << endl; // 54

［[double 精度丢失](http://www.nowcoder.com/questionTerminal/d12c2556b4614d8b87a7b64d0d0c24bb)］

参考  
[IEEE 754 浮点数的表示精度探讨](http://www.cnblogs.com/bossin/archive/2007/04/08/704567.html)  
[IEEE 754浮点数在机器中的格式](http://blog.csdn.net/glgoober/article/details/6209881)  
[一个浮点数跨平台产生的问题](http://coolshell.cn/articles/11235.html)  
[float and double](http://www.cplusplus.com/forum/beginner/83526/)  

# 其它语言特征

## 四种类型转换

* reinterpret_cast：一个指针转化为其他类型的指针时，不做类型检测，操作结果是一个指针指向另一个指针的值的二进制拷贝；

        class A{}; 
        class B{}; 
        A* a = new A;
        B* b = reinterpret_cast(a);
        
* static_cast：该运算符没有运行时类型检查来保证转换的安全性。可以用于以下场景：
    * 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换，进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
    * 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
    * 把任何类型的表达式转换成void类型。

            class Base {}; 
            class Derive:public Base{}; 
            Base* a = new Base; 
            Derive *b = static_cast(a);

* dynamic_cast：用于对象的指针和引用，当用于多态类型转换时，允许隐式转换及相反的过程中。与static_cast的不同之处在于，将一个基类对象指针（或引用）转换到派生类指针时，dynamic_cast会检测操作的有效性，如果返回的不是被请求的有效完整对象，则返回null，反之返回这个有效的对象，如果是引用返回无效时则会抛出bad_cast异常；
* const_cast：这个转换操作会操纵传递对象的const属性，或者设置或者移除该属性。

        class C{}; 
        const C* a = new C; 
        C *b = const_cast(a);

［[虚函数继承类型转换](http://www.nowcoder.com/questionTerminal/5e5bb7214788436cb966e67305a8041e)］  

## include 头文件

 `#inlcude <>` 只搜索系统目录，不会搜索用户工作目录（用户的工作目录是通过编译器指定的）。比如你自己写一个头文件，用#include <>会出错；`#inlude ""` 则首先搜索用户工作目录，如果用户工作目录没有才会搜索系统目录。
 
 因此语句`#include <stdlib.h>` 是正确的，而且程序编译速度比`#include “stdlib.h”`要快

［[include 路径](http://www.nowcoder.com/questionTerminal/8272c92814ca40c39f9a534485c90be2)］

## 按值传递和按引用传递

`传值参数`：当初始化一个非引用类型的变量时，初始值被拷贝给变量，此时对变量的改动不会影响到初始值。

指针的行为和其他非引用类型一样，执行指针拷贝操作时，拷贝的是指针的值，拷贝之后，两个指针是不同的指针。因为指针可以使我们间接地访问所指向的对象，所以通过指针可以修改它所指向的对象的值。

［[复杂的参数传递](http://www.nowcoder.com/questionTerminal/2b09b944ce7342ab8ca645690afd207b)］  
［[指针传递](http://www.nowcoder.com/questionTerminal/960f8047a9ee4a6f8227768f3bc2734d)］

`传引用参数`：通过使用引用形参，允许函数改变一个或者多个实参的值。使用引用可以避免拷贝，因为有时候拷贝较大的类对象或者容器对象比较低效，甚至有的类类型（包括 IO 类型在内）根本不支持拷贝操作。

## If 判断语句

零值的比较

`bool`：根据布尔类型的语义，零值为“假”（记为FALSE），任何非零值都是“真”（记为TRUE）

    if (flag)  
    if (!flag)  

int 型变量：

    if (n == 0)  
    if (n != 0)  

float 型变量：浮点型变量并不精确，所以不可将float变量用“==”或“！=”与数字比较，应该设法转化成“>=”或“<=”形式。
    
    const float EPSINON = 0.00001;  
    if ((x>=-EPSINON) && (x<=EPSINON)) // EPSINON 是允许的误差（即精度） 

指针变量：

    if (p == NULL)  
    if (p != NULL)
    
以下是一些不良的风格：

    if (p == 0)        // 容易让人误解p是整型变量  
    if ( n )              // 会让人误解 n 是布尔变量 
    if (x == 0.0)   // 错误的写法

不良风格很多都能通过编译，但是语句并不能很好的表达与零值进行比较的逻辑依据。

［[相等判断语句](http://www.nowcoder.com/questionTerminal/230d0664d5104b73b4c9b4fa51c5e735)］

## 逗号运算符

C++ 提供一种特殊的运算符，逗号运算符，它的优先级别最低。

    表达式1，表达式2，表达式3，...... ，表达式n

逗号表达式的特点：

1. 逗号表达式的运算过程为：从左往右逐个计算表达式。
2. 逗号表达式作为一个整体，它的值为最后一个表达式（也即表达式n）的值。
3. 逗号运算符的优先级别在所有运算符中最低。

（3+5，6+8）的值是14，（`a=3*5,a*4`）的值是60，原因在于赋值运算优先级高于逗号表达式。

下列程序的结果为

    int x,y,z;
    x=y=1;
    z=x++,y++,++y;
    printf("%d,%d,%d\n",x,y,z); // 231

    int a,b;
    b=(a=1,a+1,a++);
    printf("%d,%d\n",a,b)；// 2, 1

［[逗号表达式的值](http://www.nowcoder.com/questionTerminal/5971372060a24eac874d43b830864189)］

## enum 枚举类型

enum中首元素不赋值的话，默认为0；后一个元素不赋值的话比前一个元素大1。

［[枚举类型取值](http://www.nowcoder.com/questionTerminal/3e7a04654ead493aaa65b055d5ffd6e1)］  

# 编程实现

## String 类的实现

类的构造函数，赋值函数，析构函数。

    class String
    {
    public:
        String(const char *str=NULL);//普通构造函数
        String(const String &str);//拷贝构造函数
        String & operator =(const String &str);//赋值函数
        ~String();//析构函数
    private:
        char* m_data;//用于保存字符串w
    };

具体实现（[String.cpp](C++_Code/String.cpp)）

# C++ 11 新特性

Lambda、变参模板、auto、decltype、constexpr、智能指针、列表初始化、正则表达式、线程库、静态断言、委托构造。

# 其它问题记录

［[代码膨胀问题](http://www.nowcoder.com/questionTerminal/f6ee5023f5334873980247cf496aa641)］  
［[C++不是类型安全](http://www.nowcoder.com/questionTerminal/f80ec593dcbd44e7a13975b53e9bdaab)］  

# 更多阅读

《C++ Primer（第五版）》  
《深度探索 C++ 对象模型》  
《STL 源码剖析》   
《Effective C++》   
《More Effective C++》

[C/C++内存管理详解](http://chenqx.github.io/2014/09/25/Cpp-Memory-Management/)  
[那些不能遗忘的知识点回顾——C/C++系列](http://www.cnblogs.com/webary/p/4754522.html)  
[Can we change the value of a constant through pointers?](http://stackoverflow.com/questions/3801557/can-we-change-the-value-of-a-constant-through-pointers/3801601#3801601)   



