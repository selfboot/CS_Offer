函数指针指向的`是函数而非对象`，和其他指针一样，函数指针指向某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。例如

    // 比较两个 string 对象的长度
    bool lengthCompare(const string&, const string&);

该函数的类型是 `bool (const string&, const string&)`，要声明一个可以指向函数的指针，只需要用指针替换函数名即可。

    bool (*pf) (const string&, const string&); // 未初始化

从声明的名字开始观察，pf前面有 ＊，因此pf是指针，右侧是形参列表，表示 pf 指向的是函数，再观察左侧，发现函数的返回类型是 bool。

# 使用函数指针

当我们把函数名作为一个值使用时，该函数自动地转换为指针。

    pf = lengthCompare; // pf 指向名为 lengthCompare 的函数
    pf = &lengthCompare; // 等价的赋值语句：取地址符是可选的

还可以直接使用指向函数的指针调用该函数，无需提前解引用指针：

    bool b1 = pf("hello", "goodbye"); // 调用 lengthCompare 函数
    bool b2 = (*pf)("hello", "goodbye"); // 等价的调用
    bool b1 = lengthCompare("hello", "goodbye"); // 等价

指向不同函数类型的指针间不存在转换规则，但是可以为函数指针赋一个 nullptr 或者值为 0 的整型常量表达式。

# 重载函数的指针

如果定义了指向重载函数的指针，指针类型必须与重载函数中的某一个精确匹配。

    void ff(int *);
    void ff(unsigned int);
    
    void (*pf1)(unsigned int) = ff; // pf1 指向 ff(unsigned)
    void (*pf2)(int) = ff; // 错误，没有任何一个 ff 与该形参列表匹配
    double (*pf3)(int *) = ff; // 错误，ff 和 pf3 的返回类型不匹配

# 函数指针形参

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

# 返回指向函数的指针

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
 
# 参考  

《C++ Primer》 P221


