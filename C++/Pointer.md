为了说清楚什么是指针，必须弄清楚数据在内存中是如何存储的，又是如何读取的。

如果在程序中定义了一个变量，在编译时就给这个变量分配内存单元。系统根据程序中定义的变量类型，分配一定长度的空间。例如，C++编译系统一般为整型变量分配4个字节，为单精度浮点型变量分配4个字节，为字符型变量分配1个字节。内存区的每一个字节有一个编号，就是所谓的“地址”，如下图：

![][1]

在程序中一般是通过变量名来对内存单元进行存取操作的。其实程序经过编译以后已经将变量名转换为变量的地址，对变量值的存取都是通过地址进行的。这种按变量地址存取变量值的方式称为`直接存取`方式，或直接访问方式。

还可以采用另一种称为`间接存取(间接访问)`的方式。可以在程序中定义这样一种特殊的变量，它是专门用来存放地址的。

下图是直接访问和间接访问的示意图。

![][2]

为了将数值3送到变量中，可以有两种方法：

1. 直接将数3送到整型变量i所标识的单元中，如a。
2. 将3送到指针变量i_pointer所指向的单元(这就是变量i所标识的单元)中，如b。

所谓指向，就是通过地址来体现的。由于通过地址能找到所需的变量单元，因此可以说，地址指向该变量单元。因此将地址形象化地称为“指针”，一个变量的地址称为该变量的指针。

# 指针变量

**如果有一个变量是专门用来存放另一变量地址(即指针)的，则它称为指针变量。指针变量的值(即指针变量中存放的值)是地址(即指针)。**

指针变量是一种特殊的变量，用它来指向另一个变量。为了表示指针变量和它所指向的变量之间的联系，在C++中用`*`符号（解引用符号）表示指向。例如，i_pointer是一个指针变量，而`*i_pointer`表示i_pointer所指向的变量。

C++ 规定所有变量在使用前必须先定义，即指定其类型，在`编译`时按变量类型分配存储空间。对指针变量来说，必须将它定义为指针类型，在32位机器上，指针类型占4个字节（因为存放的是 32 位的地址值）。

定义指针变量时，必须说明指针变量的`基类型`，用来指定该指针变量可以指向的变量的类型。下面例子中int 指明指针变量指向整型数据，而不是指向浮点型数据。

    int *pointer_1;      //定义指针变量 pointer_1

此外，要使一个指针变量指向另一个变量，只需要把被指向的变量的地址赋给指针变量即可。

    pointer_1=&i;  //将变量i的地址存放到指针变量pointer_1中，& 为取地址运算符。

关于 *（解引用） 和 &（取地址）运算符，假设已执行了 `pointer_1=&a` 语句：

1. &*pointer_1与&a相同，即变量a的地址。（因为 & 和 * 两个运算符的优先级别相同，但按自右至左方向结合）
2. *&a 和 *pointer_1 的作用是一样的，它们等价于变量a
 
指针变量可以有空值，即该指针变量不指向任何变量，可以这样表示 `p=NULL`; 实际上NULL代表整数0，也就是使p指向地址为0的单元，这样可以使指针不指向任何有效的单元。看下面的程序：

```c++
int* p = 0;
// int* p = 1;  
// error: cannot initialize a variable of type 'int *' with an rvalue of type 'int'
```

这里 pint指针指向 0 地址处，如果改为 int *p=1，则会报错。

## 指针运算

C++规定，一个指针变量加/减一个整数是将该指针变量的原值(是一个地址)和它指向的变量所占用的内存单元字节数相加或相减。如 `p+i` 代表这样的地址计算：p+i*d，d为p所指向的变量单元所占用的字节数。这样才能保证p+i指向p下面的第i个元素。

```c++
int* p = 0;
p += 6;
cout << p << endl; // 24
```

`两个指针变量可以相减`：如果两个指针变量指向同一个数组的元素，则两个指针变量值之差是两个指针之间的元素个数。假如p1指向 a[0]，p2指向a[4]，则p2-p1=(a+4)-(a)=4-0=4，但p1+p2并无实际意义。

`两个指针变量比较`：若两个指针指向同一个数组的元素，则可以进行比较。指向前面的元素的指针变量小于指向后面元素的指针变量。

`“野指针”`不是NULL指针，是指向“垃圾”内存的指针。“野指针”的成因主要有三种：

1. 指针变量没有被初始化。指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的，它会乱指一气。所以，指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存。
2. 指针p被free或者delete之后，没有置为NULL，让人误以为p是个合法的指针。
3. 指针操作超越了变量的作用域范围。

## 指向指针的指针

指针变量也是变量，因此我们可以定义指向指针变量的指针变量，简称指向指针的指针。

如果在一个指针变量中存放一个目标变量的地址，这就是`单级间址`，见下图a。指向指针的指针用的是`二级间址`方法，见下图b。从理论上说，间址方法可以延伸到更多的级，见下图c，但实际上在程序中很少有超过二级间址的。

![][3]

如下例子：

    int num = 10;
    int *ptr = &num;
    int **pptr = &ptr;
    cout << **pptr;         // 10
    int ***ppptr = &pptr;
    cout << ***ppptr;       // 10

## 指针与引用

指针与引用区别如下：

1. 指针是一个变量，只不过这个变量存储的是一个地址，指向内存的一个存储单元；而引用只不过是变量的一个别名而已。
2. 指针的值可以为空，也可能指向一个不确定的内存空间，但是引用的值不能为空，并且引用在定义的时候必须初始化为特定对象；
3. 指针的值在初始化后可以改变，即指向其它的存储单元，而引用在进行初始化后就不可以改变引用对象了；
4. 指针可以有多级，但是引用只能是一级；
5. sizeof引用得到的是所指向的变量(对象)的大小，而sizeof指针得到的是指针本身的大小；

## 指针和const

指向常量的指针（`pointer to const`）不能用于改变其所指对象的值，要想存放常量对象的地址，只能使用指向常量的指针。

```c++
const int *a = 3;
int const *a = 3;
int const* a = 3;
```

指针本身是对象，因此可以把指针本身定为常量。常量指针（`const pointer`）必须初始化，而且一旦初始化完成，则它的值（也就是存放在指针中的那个地址）就不能再改变了。

```c++
int errNumb = 0;
int *const curErr = &errNumb;
```

也可以定义一个指向常量的常量指针（const pointer to const）。

    const double pi=3.14;
    const double * const pip = &pi;

为了判断const到底对谁起作用（即谁是const的），可以用以下简单规则：**const只对它左边的东西起作用，当const本身就是最左边的修饰符时，它才会对右边的东西起作用**。有时候，情况可能会比较复杂，比如：

```c++
const char * const * pp; 
pp++;       // OK
(*pp)++;    // Error
**pp = 'c'; // Error
```

怎么去理解呢？先从一级指针说起吧： 

* const char p: 限定变量p为只读。这样如p=2这样的赋值操作就是错误的。 
* const char \*p: p为一个指向char类型的指针，const只限定p指向的对象为只读。这样，p=&a或  p++等操作都是合法的，但如\*p=4这样的操作就错了，因为企图改写这个已经被限定为只读属性的对象。 
* char \*const p: 限定此指针为只读，这样p=&a或p++等操作都是不合法的。而\*p=3这样的操作合法，因为并没有限定其最终对象为只读。 
* const char \*const p: 两者皆限定为只读，不能改写。 

有了以上的对比，再来看二级指针问题：
 
* const char \*\*p：p为一个指向指针的指针，const限定其最终对象为只读，显然这最终对象也是为char类型的变量。故像\*\*p=3这样的赋值是错误的，而像`*p=？，p++`这样的操作合法。 
* const char \* const \*p：限定最终对象和p指向的指针为只读。这样 `*p=?`的操作也是错的。 
* const char * const * const p：全部限定为只读，都不可以改写。

# 指针和数组

通常情况下，使用取地址符来获取指向某个对象的指针，取地址符可以用于任何对象。数组的元素也是对象，对数组使用下标运算符得到该数组指定位置的元素。因此，像其他对象一样，对数组的元素使用取地址符就能得到指向该元素的指针：

    string nums[] = {"one", "two", "threee"};
    string *p = &nums[0];
    string *p2 = nums;       // 等价于 p2 = &nums[0]

一维数组：

    a[i]=*(a+i)
    a <=> &a[0],  a+1 <=> &a[1]
    *a <=> a[0],  *(a+1) <=> a[1]  

二维数组：

    a[0] <=>&a[0][0]  a[1] <=> &a[1][0]  a[1]+1 <=> &a[1][1]
    *a[0] <=>a[0][0]  *a[1]<=>a[1][0]    *(a[1]+1 )<=>a[1][1]

大多数表达式中，使用数组类型的对象名称其实就是使用一个指向该数组首元素的指针（编译器会做这种转换）。但是要注意数组对象名称是一个`常量指针`，不能对其进行赋值、++ 等操作。

    int ia[] = {0, 1, 2, 3, 4, 5};
    auto ia2(ia); // ia2 是一个整形指针，指向 ia 的第一个元素
    ia++; // 错误！常量指针不能进行 ++ 操作

关于指针数组和数组指针：

* `指针数组`(array of pointers)：即用于存储指针的数组，也就是数组元素都是指针
* `数组指针`(a pointer to an array)：即指向数组的指针

还要注意的是他们用法的区别，下面举例说明。

    int* (a[4]);         // 指针数组：数组a中的元素都为int型指针
    int* a[4];           // 指针数组：和上面是一样的，因为[]优先级高于*。
    int (*a)[4];         // 数组指针：指向数组a的指针

## 复杂例子分析

下面看一个比较复杂的例子，来理解指针数组和指向指针的指针：

    char *c[] = { "ENTER", "NEW", "POINT", "FIRST" };
    char **cp[] = {c+3, c+2, c+1, c};
    char ***cpp = cp;

    printf("%s", **++cpp);
    printf("%s", *--*++cpp+3);
    printf("%s", *cpp[-2]+3);
    printf("%s\n", cpp[-1][-1]+1);

首先理清楚c, cp, cpp 之间的指向关系。

![][4]

然后用以下规则可以清晰知道指针之间的转换关系：

1. * 和 ++ 是属于同一个优先级的，它的结合方式是右结合。所以 *++cpp 等价于 *(++cpp)
2. [] 运算符与解引用 * 可以相互转换：c[i]=*(c+i)
3. 一个指针变量加/减一个整数是将该指针变量的原值(是一个地址)和它指向的变量所占用的内存单元字节数相加或相减。

所以可以得到下面的指针指向图：

![][5]

［[多级指针引用](http://www.nowcoder.com/questionTerminal/2fd94d94ccca407dbc82e705c1f1ecbc)］  

# 函数指针

函数指针指向的`是函数而非对象`，和其他指针一样，函数指针指向某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。例如

    // 比较两个 string 对象的长度
    bool lengthCompare(const string&, const string&);

该函数的类型是 `bool (const string&, const string&)`，要声明一个可以指向函数的指针，只需要用指针替换函数名即可。

    bool (*pf) (const string&, const string&); // 未初始化

从声明的名字开始观察，pf前面有 *，因此pf是指针，右侧是形参列表，表示 pf 指向的是函数，再观察左侧，发现函数的返回类型是 bool。

当我们把函数名作为一个值使用时，该函数自动地转换为指针。

    pf = lengthCompare; // pf 指向名为 lengthCompare 的函数
    pf = &lengthCompare; // 等价的赋值语句：取地址符是可选的

还可以直接使用指向函数的指针调用该函数，无需提前解引用指针：

    bool b1 = pf("hello", "goodbye"); // 调用 lengthCompare 函数
    bool b2 = (*pf)("hello", "goodbye"); // 等价的调用
    bool b1 = lengthCompare("hello", "goodbye"); // 等价

指向不同函数类型的指针间不存在转换规则，但是可以为函数指针赋一个 nullptr 或者值为 0 的整型常量表达式。

## 函数指针形参

和数组类似，虽然不能定义函数类型的形参，但是形参可以是指向函数的指针，此时，形参看起来是函数类型，实际上却是当成指针使用。

    void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &));
    void useBigger(const string &s1, const string &s2, bool (*pf)(const string &, const string &)); // 等价的声明

可以把函数作为实参使用，此时它会`自动转换为指针`：

    useBigger(s1, s2, lengthCompare);

直接使用函数指针类型显得冗长而繁琐，类型别名和 `decltype` 可以让我们简化使用函数指针的代码。

    // Func 和 Func2 是函数类型
    typedef bool Func(const string&, const string&);
    typedef decltype(lengthCompare) Func2;
       
    // FuncP 和 FuncP2 是指向函数的指针
    typedef bool (*FuncP)(const string&, const string&);
    typedef decltype(lengthCompare) *FuncP2;

    void useBigger(const string&, const string&, Func);
    void useBigger(const string&, const string&, Func);
    // 使用类型别名

## 返回指向函数的指针

和数组类似，虽然不能直接返回一个函数，但是能返回指向函数类型的指针。这里，`必须把返回类型写成指针形式`，编译器不会自动地将函数返回类型当成对应的指针类型来处理。

要声明一个返回函数指针的函数，最简单的方法是使用类型别名：

    using F = int(int *, int) // F 是函数类型，不是指针
    using PF = int(*)(int *, int) // PF 是函数指针
    PF f1(int);     // 正确，f1 返回指向函数的指针
    F f1(int);      // 错误，f1 不能返回一个函数
    F *f1(int);     // 正确，显式指定返回类型是指向函数的指针

当然也可以使用下面的方式直接声明 f1:

    int (*f1(int))(int *, int);

按照`由内向外`的顺序阅读这条声明语句。看到 f1 有 形参列表，所以 f1 是个函数；f1 前面有*, 所以 f1 返回一个指针；进一步观察，指针的类型本身也包含形参列表，因此指针指向函数，该函数的返回类型是 int。

［[指针传递](http://www.nowcoder.com/questionTerminal/960f8047a9ee4a6f8227768f3bc2734d)］

## 重载函数的指针

如果定义了指向重载函数的指针，指针类型必须与重载函数中的某一个精确匹配。

    void ff(int *);
    void ff(unsigned int);
    
    void (*pf1)(unsigned int) = ff; // pf1 指向 ff(unsigned)
    void (*pf2)(int) = ff; // 错误，没有任何一个 ff 与该形参列表匹配
    double (*pf3)(int *) = ff; // 错误，ff 和 pf3 的返回类型不匹配

# 类成员函数指针

具体看下面例子：

    #include <iostream>
    using namespace std;
    
    class Container{
    public:
        void fun(){
            cout << "member func" << endl;
        }
        static void static_fun(){
            cout << "Static func" << endl;
        };
    };
    
    int main()
    {
        void (Container::*f)(); //指明是普通成员函数的指针
        f = &Container::fun;
        Container c;
        (c.*f)();
    
        void (*s_f)();         //指明是静态成员函数的指针
        s_f = &Container::static_fun;
        s_f();
        return 0;
    }

# 牛客网题目

［[指向常量的指针](http://www.nowcoder.com/questionTerminal/524cd1e7926a44e38d9d7c3a3359b822)］  
［[指针改变常量的值](http://www.nowcoder.com/questionTerminal/36f828664d2d4d14a1428ae49f701f23)］  
［[二维数组运算结果](http://www.nowcoder.com/questionTerminal/8e78bcf76d0241938dc5f08ed8b2a065)］  
［[多维数组下标操作](http://www.nowcoder.com/questionTerminal/7b4220df2f8c4729b3a716ce7cd2056d)］  
［[指针数组的读取](http://www.nowcoder.com/questionTerminal/5a6e0056f81648fe97f9a85462e256c6)］   
［[数组和指针相关操作](http://www.nowcoder.com/questionTerminal/621ea797eea249cb9f4db93218e7929f)］  
［[指针取值](http://www.nowcoder.com/questionTerminal/9c55cfec4cce4c9fac74845359968cb0)］  
［[指针赋值语句](http://www.nowcoder.com/questionTerminal/b6f566ba692442d4b7cce66bf6804c53)］  
［[函数指针定义](http://www.nowcoder.com/questionTerminal/960f8047a9ee4a6f8227768f3bc2734d)］  
［[函数指针应用](http://www.nowcoder.com/questionTerminal/2c18fc889b924cc1b21ce6ec387fd853)］  
［[成员函数的函数指针](http://www.nowcoder.com/questionTerminal/648f3eaef4234a34a5d5dbd268a77fa7)］  
［[指向含有10个函数指针的数组的指针](https://www.nowcoder.com/questionTerminal/242d747044bd417e95fe37d69884dff8)］

# 参考  

《C++ Primer》  
[C++指针：指针变量、数组指针、字符串指针、函数指针](http://c.biancheng.net/cpp/biancheng/cpp/rumen_6/)  
[C++ 函数指针 & 类成员函数指针](http://blog.csdn.net/crayondeng/article/details/16868351)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Pointer_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Pointer_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Pointer_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Pointer_4.png
[5]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Pointer_5.png


