# 声明还是定义

简单来说：

> Declaration is for the compiler to accept a name(to tell the compiler that the name is legal, the name is introduced with intention not a typo).   
>
> A variable is declared when the compiler is informed that a variable exists (and this is its type); it does not allocate the storage for the variable at that point.
>   
> Definition is where a name and its content is associated. The definition is used by the linker to link a name reference to the content of the name.  
> 
>A variable is defined when the compiler allocates the storage for the variable.

变量声明（declaration）用来引入标识符，并对它的类型（对象，函数等）进行说明，有了声明语句，`编译器`就可以理解对该标识符的引用。下面的这些都是声明语句：

    extern int bar;
    extern int g(int, int);
    double f(int, double); // extern can be omitted for function declarations
    class foo; // no extern allowed for type declarations

可以重复声明一个变量，所以下面语句是合法的：

    double f(int, double);
    double f(int, double);
    extern double f(int, double); // the same as the two above
    extern double f(int, double);

变量定义（definition）**用于为变量分配存储空间，还可为变量指定初始值**。可以将定义看作是对声明的变量进行实例化，`链接器`需要根据定义来找到变量具体对应的值。下面是前面声明语句对应的定义部分：

    int bar;
    int g(int lhs, int rhs) {return lhs*rhs;}
    double f(int i, double d) {return i+d;}
    class foo {};

程序中，变量必须有且仅有一个定义。

> No translation unit shall contain more than one definition of any variable, function, class type, enumeration type, or template.

重复定义会导致链接器不知道哪一个是需要的，编译器会报错：`redefinition of`。变量缺少定义链接器会因为 `symbol(s) not found` 链接失败。下面代码片段中 b 没有定义，c重复定义：

    extern int a;
    extern int b;
    
    int main(){
        int a;
        cout << a << b;
        int c;
        int c;
    }

有时候区别声明和定义还真不是那么简单的，看下面的例子：

```c++
struct Test
{
    Test(int) {}
    Test() {}
    void fun() {}
};
void main( void )
{
    Test a(1);  // 定义了一个对象
    a.fun();    // 调用对象的函数 
    Test b();   // 声明了一个函数
    // b.fun();    // Error！！！
}
```

C++ standard section 3.1 节指出

> A declaration introduces names into a translation unit or redeclares names introduced by previous declarations. A declaration specifies the interpretation and attributes of these names.

接着说明 `A declaration is a definition unless`:

```
void sqrt(double);  // 1. declares a function without specifying the function’s body

// 2. declares a static member within a class definition
struct X
{
    int a;          // defines a
    static int b;   // declares b    
};

class Y;            // 3. declares a class name

// 4. contains the extern keyword without an initializer or function body
extern const int i = 0; // defines i
extern int j;           // declares j
extern "C"
{
    void foo();         // declares foo
}

// 5. a typedef or using statement.
typedef long LONG_32;  // declares LONG_32
using namespace std;   // declares std
```

详细内容参考 [What is the difference between a definition and a declaration?](https://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration)  

# 左值还是右值

左值与右值这两概念是从 c 中传承而来的，在 c 中，左值指的是既能够出现在等号左边也能出现在等号右边的变量(或表达式)，右值指的则是只能出现在等号右边的变量(或表达式)。

```c++
int a;
int b;
    
a = 3;
b = 4;
a = b;
b = a;
    
// 以下写法不合法。
3 = a;
a+b = 4;
```

在 C 语言中，通常来说有名字的变量就是左值(如上面例子中的 a, b)，而由运算操作(加减乘除，函数调用返回值等)所产生的中间结果(没有名字)就是右值，如上的 3 + 4， a + b 等。可以认为**左值就是在程序中能够寻址的东西，右值就是没法取到它的地址的东西**。

如上概念到了 c++ 中，就变得稍有不同。具体来说，在 c++ 中，`每一个表达式或者是一个左值，或者是一个右值`，相应的，该表达式也就被称作“左值表达式"，"右值表达式"。对于内置的基本数据类型来说(primitive types)，左值右值的概念和 c 没有太多不同，不同的地方在于自定义的类型:

* 对于内置的类型，右值是不可被修改的(non-modifiable)，也不可被 const, volatile 所修饰；
* 对于自定义的类型(user-defined types)，右值却允许通过它的成员函数进行修改。

C++ 中自定义类型允许有成员函数，而通过右值调用成员函数是被允许的，但成员函数有可能不是 const 类型，因此通过调用右值的成员函数，也就可能会修改了该右值。此外，**右值只能被 const 类型的 reference 所指向**，当一个右值被 const reference 指向时，它的生命周期就被延长了。

具体示例在 [C++_LR_Value](../Coding/C++_LR_Value.cpp)。

# 引用

引用（reference）是c++对c语言的重要扩充，引用就是某一变量（目标）的一个别名，对引用的操作与对变量直接操作完全一样。引用是除指针外另一个可以产生多态效果的手段。这意味着，一个基类的引用可以指向它的派生类实例。引用的定义方法：

    类型标识符 &引用名=目标变量名；

类型标识符是指目标变量的类型，这里的 & 不是求地址运算，而是起标识作用。**在定义引用时，必须同时对其进行初始化**，引用定义完毕后，相当于目标变量名有两个名称，即该目标原名称和引用名，且不能再将该引用指向其它变量。

    int a=2,
    int &ra=a;

a为原变量名称，ra为引用名。给ra赋值：ra=1; 等价于 a=1。对引用求地址，就是对目标变量求地址，因此&ra与&a相等。注意我们**不能建立引用的数组**，因为数组是一个由若干个元素所组成的集合，所以无法建立一个由引用组成的集合。

    int& ref[3]= {2,3,5}; //int& ref[3]= {2,3,5}; //不能声明引用的数组
    const int (&ref)[3] ={2,3,5};                 // 可以

编译器一般将引用实现为`const指针`，即指向位置不可变的指针，也就是说引用实际上与一般指针同样占用内存，不过我们没有办法获得这个指针的地址。

## 引用传参

传统的c中，函数在调用时参数是通过值来传递的，这就是说函数的参数不具备返回值的能力。当给函数传递参数时，变量值被拷贝给参数，此时对参数的改动不会影响到初始值。

所以在传统的c中，如果需要函数的参数具有返回值的能力，往往是通过指针来实现的。这是因为执行指针拷贝操作时，虽然拷贝的是指针的值，拷贝之后，两个指针是不同的指针。但是指针可以使我们间接地访问所指向的对象，所以通过指针可以修改它所指向的对象的值。比如，实现两整数变量值交换的c程序如下：

    void swap(int *a,int *b)
    {
        int temp;
        temp=*a;
        *a=*b;
        *b=temp;
    }

通过使用引用形参，允许函数改变一个或者多个实参的值。使用引用机制后，以上程序的c++版本为：

    void swap(int &a,int &b)
    {
        int temp=a;
        a=b;
        b=temp;
    }

当大型对象被传递给函数时，使用引用参数可使参数传递效率得到提高，因为引用并不产生对象的副本，也就是参数传递时，对象无须复制。有时甚至有的类类型（包括 IO 类型在内）根本不支持拷贝操作，只能用引用传递。

［[复杂的参数传递](http://www.nowcoder.com/questionTerminal/2b09b944ce7342ab8ca645690afd207b)］  

## 引用返回值

将“引用”作为函数返回值类型，好处是在内存中不产生被返回值的副本。正是因为这点原因，所以**返回一个局部变量的引用是不可取的**。因为随着该局部变量生存期的结束，相应的引用也会失效！

同时也**不能返回函数内部new分配的内存的引用**`，被函数返回的引用只是作为一个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。正确的做法如下：

```c++
#include <iostream>
using namespace std;
int& fun(int& a){
    a++;
    return a;
} //把a返回引用函数,也就是说这个fun()就是a的别名
int main(void){
    int b =10;
    fun(b); //同理,fun(b)就是b自增后的b的别名
    cout << b <<endl;
    return 0;
}
```

# sizeof 运算符
    
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

在 sizeof 的运算对象中解引用一个无效指针仍然是一种安全的行为，因为指针实际上并没有被真正使用，sizeof 并不需要真的解引用指针也能知道它所指对象的类型。这是一件可以在程序运行前（`编译时`）完成的事情，所以，sizeof(*p)直接就被具体数字给取代了，在运行时也就不会有了解引用这个表达式。

```c++
int i = 10;
printf("%d\n",i);                           // 10
// sizeof 并不计算 i++
printf("%d\n",sizeof(i++));                 // 4
printf("%d\n",i);                           // 10
```
    
sizeof 运算符的结果部分地依赖于其作用的类型：

* 对 char 或者类型为 char 的表达式执行 sizeof 运算，结果得 1；
* 对引用类型执行 sizeof 运算得到被引用对象所占空间的大小；
* 对指针执行 sizeof 运算得到指针本身所占空间的大小；
* 对解引用指针执行 sizeof 运算得到指针指向的对象所占空间的大小，指针不需要有效；
* 对数组执行 sizeof 运算得到整个数组所占空间的大小，等同于对数组中所有的元素各执行一次 sizeof 运算并将所得结果求和。（sizeof 不会把数组转换成指针来处理，可以用数组的大小除以单个元素的大小得到数组中元素的个数）。
* 对 string 对象或 vector 对象执行 sizeof 运算只返回该类型固定部分的大小（**24**），不会计算对象占用了多少空间；
* 对于 enum 类型的变量，它保存的枚举对象本身并不是真的变量，它们只是类型安全的 #define，用来以可读的方式保存一串数字而已。编译器一般是用 int 类型的来保存一个 enum，所以sizeof 结果为 4。

此外求类的大小时遵循下面规则（只统计与类的实例有关的，只与类型相关的不统计）：

1. 类的非静态成员数据的类型大小之和，也就是说静态成员数据不作考虑。
2. 普通成员函数与sizeof无关，调用普通成员函数只需要知道函数的地址即可，而这些地址只与类型相关，与类型的实例无关。
3. 虚函数由于要维护在虚函数表，所以要占据一个指针大小
4. 类的总大小也遵守类似 struct 字节对齐的调整规则
5. 空类的大小为 1（空类型的实例中不包含任何信息，但是声明空类的实例时，必须在内存中占有一定的空间，否则无法使用这些实例。占有空间数由编译器决定，一般是1）。

可以看示例程序： [sizeof_demo.cpp](../Coding/sizeof_demo.cpp)  

［[字符数组，八进制坑](http://www.nowcoder.com/questionTerminal/a7b35bc367604e73823d2dded6496e38)］  
［[类的大小](http://www.nowcoder.com/questionTerminal/33f3a63dc5d449adb351168ada7f47c6)］  
［[C中整型字符常量，C++字符字面量大小](http://www.nowcoder.com/questionTerminal/e16ca070d715455fa8f6916aa324138d)］  
［[引用的大小](http://www.nowcoder.com/questionTerminal/31095437d232497c9ea40c5c7a629dc4)］    
［[枚举类型，typedef 函数指针](http://www.nowcoder.com/questionTerminal/07684925aaaf4885ad574b2a2debe930)］  

# 内存对齐

许多实际的计算机系统对基本类型数据在内存中存放的位置有限制，它们会要求这些数据的首地址的值是某个数k（通常它为4或8）的倍数，这就是所谓的`内存对齐`。

每个特定平台上的编译器都有自己的默认“对齐系数”（32位机一般为4，64位机一般为8）。我们可以通过预编译命令#pragma pack(k)，k=1,2,4,8,16来改变这个系数，其中k就是需要指定的“对齐系数”；也可以使用#pragma pack()取消自定义字节对齐方式。

struct 或者 union 成员对齐规则如下：

1. 第一个数据成员放在offset为0的地方，每个成员按照对齐系数和自身占用字节数中，二者比较小的那个进行对齐；
2. 在数据成员完成各自对齐以后，struct或者union本身也要进行对齐，对齐将按照对齐系数和struct或者union中最大数据成员长度中比较小的那个进行；

先局部成员对齐，然后再全局对齐。（[memory_align.cpp](../Coding/C++_Memory_Align.cpp)）此外，值得注意的是，**enum 内部是 int 实现的，所以大小为 4。用 typedef 声明指针时，并不为指针分配空间**。

［[enum，typedef声明指针](http://www.nowcoder.com/questionTerminal/f12da06f01594f4d8d04a1f242399dc5)］  
［[结构体中 : 的含义](http://www.nowcoder.com/questionTerminal/f4e20747a2dd4649bac0c028daa234f4)］    

# 联合体、CPU字节序

`联合体`：在C/C++程序的编写中，当多个基本数据类型或复合数据结构要占用同一内存块时，就要用到联合体。联合体变量所占内存长度是各成员中最长的成员占的内存长度。union所有成员都从低地址开始存放。

`Little endian` 和 `Big endian` 是CPU 存放数据的两种不同顺序。对于整型、长整型等数据类型，Big endian 认为第一个字节是最高位字节（按照从低地址到高地址的顺序存放数据的高位字节到低位字节）；而Little endian 则相反，它认为第一个字节是最低位字节（按照从低地址到高地址的顺序存放数据的低位字节到高位字节）。

例如，假设从内存地址0x0000开始有以下数据：0x12 0x34 0xab 0xcd。如果我们去读取一个地址为 0x0000 的四个字节变量，若字节序为big-endian，则读出结果为0x1234abcd；若字节序位little-endian，则读出结果为 0xcdab3412。

一般来说，x86系列CPU 都是little-endian 的字节序，PowerPC通常是Big endian，还有的CPU 能通过跳线来设置CPU 工作于Little endian 还是Big endian 模式。

我们可以利用 union 的存储特点，写一个简单的程序来判定当前 CPU 的字节序([union_endian.cpp](../Coding/union_endian.cpp))。

［[判断 CPU大小端](http://www.nowcoder.com/questionTerminal/a903ebe93add411d9c94b114f5fabb36)］  
［[溢出，大小端](http://www.nowcoder.com/questionTerminal/c7298be0b2ce42698b80987631cf8fca)］  
［[大小端，网络发送](http://www.nowcoder.com/questionTerminal/d7c1ff50fab44443b61903eccd791f1d)］  

# 类型转换

类型转换就是将给定类型的表达式转换为另一种类型。C++中的转型可分为两种：隐式类型转换和显式类型转换。

隐式类型转换是C中的遗留物，在C++中并不推荐使用（C++有专门的转型操作符，见下文的显式转型）。将某种类型的对象拷贝到另一种不同类型的对象中时就会发生隐式转型。比如异型赋值，返回值（函数声明的返回值与代码块实际返回值不同的情况下），按值传递异型参数等情况均会发生隐式类型转换。

```c++
short a = 128;
int b;
b = a;
```

short 类型的对象被赋值给 int 型的对象，这是C++语言内建支持的标准转换。隐式类型转换是件麻烦事，它们很可能导致错误或非预期的函数被调用（参看ME 条款5）。

因此应该尽量避免隐式类型转换，为此 C++ 提供了显式类型转换关键字：static_cast, const_cast, dynamic_cast 以及 reinterpret_cast。

## static_cast

static_cast 很像 C 语言中的旧式类型转换。可以用于以下场景：

* 用于在存有继承关系的类之间的指针或引用的转换（即可将基类转换为子类，也可将子类转换为基类），把派生类的指针或引用转换成基类时是安全的；把基类指针或引用转换成派生类表示时，由于没有类型检查，所以是不安全的。
* 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。
* 把任何类型的表达式转换成void类型。
* 还能将 non-const 对象转换为 const对象（注意：反之则不行，那是const_cast的职责）。

如下示例：

```c++
class CBase {};
class CDerived: public CBase {};

double d = 3.14159265;
int i = static_cast<int>(d);

CBase *base = new CBase;
CDerived *derived = static_cast<CDerived *>(base);
```

**static_cast 转换时并不进行运行时安全检查，所以是非安全的，很容易出问题。**因此 C++ 引入 dynamic_cast 来处理安全转型。

## dynamic_cast

dynamic_cast 主要用来在继承体系中的**安全向下转型**。它能安全地将指向基类的指针转型为指向子类的指针或引用，并获知转型动作成功是否。

**dynamic_cast 只能用在指针和引用类型的转换中**，它是唯一进行运行期(runtime)检查的类型转换符，它的主要目的就是保证转换后的类型是一个完整类型(Complete type）。dynamic_cast在转换指针类型时，如果结果不是一个Complete Type, 它会返回NULL; dynamic_cast在转换引用类型时，如果结果不是一个Complete Type，它会抛出bad_cast的异常。dynamic_cast 会动用运行时信息（RTTI）来进行类型安全检查，因此 dynamic_cast 存在一定的效率损失。

```c++
class CBase { };
class CDerived: public CBase { };

int main(){
    CBase b;
    CBase* pb;
    CDerived d;
    CDerived* pd;
    pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
    pd = dynamic_cast<CDerived*>(&b);  // error: base-to-derived
}
```

上面的代码最后一行会出错（error: 'CBase' is not polymorphic），**因为dynamic_cast 只有在基类带有虚函数的情况下才允许将基类转换为子类**。

```c++
class CBase
{
    virtual void dummy() { }
};

class CDerived : public CBase {
    int a;
};

int main()
{
    CBase *pba = new CDerived;
    CBase *pbb = new CBase;
    CDerived *pd1, *pd2;
    pd1 = dynamic_cast<CDerived *>(pba);
    pd2 = dynamic_cast<CDerived *>(pbb);
}
```

上面代码中的 pd1 不为 null,而 pd2 为 null。

## const_cast

这个转换操作会操纵传递对象的const属性，或者设置或者移除该属性。

```c++
class C{}; 
const C* a = new C; 
C *b = const_cast(a);
```
    
## reinterpret_cast

一个指针转化为其他类型的指针时，不做类型检测，操作结果是一个指针指向另一个指针的值的二进制拷贝；

```c++
class A{}; 
class B{}; 
A* a = new A;
B* b = reinterpret_cast(a);
```
        
reinterpret_cast 用来执行低级转型，如将执行一个 int 的指针强转为 int。其转换结果与编译平台息息相关，不具有可移植性，因此在一般的代码中不常见到它。

reinterpret_cast 常用的一个用途是转换函数指针类型，即可以将一种类型的函数指针转换为另一种类型的函数指针，但这种转换可能会导致不正确的结果。总之，reinterpret_cast 只用于底层代码，一般我们都用不到它，如果你的代码中使用到这种转型，务必明白自己在干什么。

［[虚函数继承类型转换](http://www.nowcoder.com/questionTerminal/5e5bb7214788436cb966e67305a8041e)］  

# If 判断语句

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

# 逗号运算符

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
    printf("%d,%d,%d\n",x,y,z); // 2,3,1

    int a,b;
    b=(a=1,a+1,a++);
    printf("%d,%d\n",a,b)；// 2,1

［[逗号表达式的值](http://www.nowcoder.com/questionTerminal/5971372060a24eac874d43b830864189)］


# 更多内容

[what is the size of an enum type data in C++?](http://stackoverflow.com/questions/8115550/what-is-the-size-of-an-enum-type-data-in-c)    
[What is the difference between a definition and a declaration?](http://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration)  
[c++中的左值与右值](http://www.cnblogs.com/catch/p/3500678.html)  
[C++ Rvalue References Explained](http://thbecker.net/articles/rvalue_references/section_01.html)  
[C、C++内存对齐](http://www.jellythink.com/archives/413)  
[sizeof() a vector](http://stackoverflow.com/questions/2373189/sizeof-a-vector)  
[C++类型转换（Type Casting）详解](http://lang.9sssd.com/vcpp/art/962)  


