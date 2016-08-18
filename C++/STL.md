C++ STL（标准模板库）是一套功能强大的 C++ 模板类，提供了通用的模板类和函数，这些模板类和函数可以实现多种流行和常用的算法和数据结构，如向量、链表、队列、栈。

STL的一个重要特点是`数据结构和算法的分离`。尽管这是个简单的概念，但这种分离确实使得STL变得非常通用。例如，由于STL的sort()函数是完全通用的，你可以用它来操作几乎任何数据集合，包括链表，容器和数组。

STL另一个重要特性是它**不是面向对象**的。为了具有足够通用性，STL主要依赖于模板而不是封装，继承和虚函数（多态性）——OOP的三个要素。你在STL中找不到任何明显的类继承关系。

程序要使用 STL 时，应包含（#include）适当的标准头文件。对大部分容器来说，标准头文件的名称和容器名一致，且不需扩展名。比如说，如果你要用vector，只要在程序最开头添加下面这行代码：

    #include <vector>

容器类型（还有算法、运算符和所有 STL也一样）并不是定义在全局命名空间，而是定义在一个叫“std”的特殊命名空间里。在包含完所有头文件之后，还应该引入std::vector名字空间。

# 六大组件

STL 提供了六大组件，彼此可以组合套用：

* 容器（containers）：各种数据结构，如 vector，list，deque，set，map等。从实现的角度来看，容器是一种 class template。
* 算法（algorithms）：各种常用算法，提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作，比如 sort，search，copy，erase。从实现的角度来看，STL算法是一种 function template。
* 迭代器（iterators）：迭代器用于遍历对象集合的元素，扮演容器与算法之间的胶合剂，是所谓的`泛型指针`，共有5种类型，以及其他衍生变化。从实现角度来看，迭代器是一种将 operator*，operator->，operator++，operator--等指针操作予以重载的 class template。所有的STL容器附带有自己专属的迭代器，因为只有容器设计者才知道如何遍历自己的元素。
* 仿函数（functors）：行为类似函数，可作为算法的某种策略。从实现角度来看，仿函数是一种重载了 operator() 的 class 或者 class template。
* 配接器（Adaptor）：一种用来修饰容器或者仿函数或迭代器接口的东西。例如 STL 提供的queue 和 stack，就是一种空间配接器，因为它们的底部完全借助于 deque。
* 配制器（allocator）：负责空间的配置与管理。从实现的角度来看，配置器是一个实现了动态配置空间、空间管理、空间释放的 class template。

下图展示了 STL 六大组件的交互关系：

![][1]
   
# 容器

一个容器就是一些特定类型对象的集合。STL 中容器分为两大类，序列式容器和关联式容器。

`序列式容器（sequential container）`为程序员提供了控制元素存储和访问顺序的能力。这种顺序不依赖于元素的值，而是与元素加入容器时的位置相对应。

除了序列式容器容器外，标准库还定义了三个序列式容器适配器：stack、queue和priority_queue。`适配器`是标准库中的一个通用概念，容器、迭代器和函数都有适配器。本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。

和序列式容器对应的是`关联容器（associative-container）`，关联容器中的元素是按关键字来保存和访问的。关联容器支持高效的关键字查找和访问，STL有两个主要的关联容器：map 和 set。

更多内容参考 [STL_Container](STL_Container.md)

# 迭代器

迭代器提供对一个容器中的对象的访问方法，并且定义了容器中对象的范围。迭代器就如同一个指针。事实上，C++的指针也是一种迭代器。但是，迭代器不仅仅是指针，因此你不能认为他们一定具有地址值。例如，一个数组索引，也可以认为是一种迭代器。

迭代器有各种不同的创建方法。程序可能把迭代器作为一个变量创建。一个STL容器类可能为了使用一个特定类型的数据而创建一个迭代器。作为指针，必须能够使用*操作符类获取数据。还可以使用其他数学操作符如++操作符用来递增迭代器，以访问容器中的下一个对象。如果迭代器到达了容器中的最后一个元素的后面，则迭代器变成past-the-end值。使用一个past-the-end值得指针来访问对象是非法的，就好像使用NULL或为初始化的指针一样。

对于STL数据结构和算法，可以使用五种迭代器。下面简要说明了这五种类型：

* Input iterators 提供对数据的只读访问
* Output iterators 提供对数据的只写访问
* Forward iterators 提供读写操作，并能向前推进迭代器
* Bidirectional iterators提供读写操作，并能向前和向后操作
* Random access iterators提供读写操作，并能在数据中随机移动

更多内容参考 [STL_Iterator](STL_Iterator.md)  

# 算法

STL通过函数模板提供了很多作用于容器的通用算法，例如查找、插入、删除、排序等，这些算法均需要引入头文件<algorithm>。

所有的 STL 算法都作用在由迭代器 [first, last) 所标示出来的区间上，可以分为两大类：

* 质变算法（mutating algorithms）：运算过程中会更改区间内迭代器所指的元素内容，如分割（partition）、删除（remove）等算法
* 非质变算法（nonmutating algorithms）：运算过程中不会更改区间内迭代器所指的元素内容，如匹配（search），计数（count）等算法

所有泛型算法的前两个参数都是一对迭代器，通常称为first和last，用以标示算法的操作区间。注意，将无效的迭代器传给某个算法，虽然是一种错误，但不保证能够在编译期间被捕捉出来。

更多内容参考 [STL_Algorithm](STL_Algorithm.md)

# 高效、安全使用 STL

都是STL，可能写出来的效率相差几倍，所以要掌握写出高效 STL 代码的技巧。

## 建立指针的容器

当对象很大时，建立指针的容器而不是对象的容器，主要基于下面两个原因：

1. STL基于拷贝的方式的来工作，任何需要放入STL中的元素，都会被复制；这也好理解，STL工作的`容器是在堆内开辟的一块新空间`，而我们自己的变量一般存放在函数栈或另一块堆空间中。如果复制的对象很大，由复制带来的性能代价也不小；对于大对象的操作，使用指针来代替对象能消除这方面的代价；
2. 只涉及到指针拷贝操作，没有额外类的构造函数和赋值构造函数的调用。

下面例子：

        vector <BigObj> vt1;
        vt1.push_back(myBigObj);
        vector <BigObj* > vt2;
        vt2.push_back(new BigObj());

不过要注意：

1. 容器销毁前需要自行销毁指针所指向的对象；否则就造成了内存泄漏；
2. 使用排序等算法时，需要构造基于对象的比较函数，如果使用默认的比较函数，其结果是基于指针大小的比较，而不是对象的比较；
	
## 用区间成员函数

尽量用区间成员函数代替单元素操作，使用区间成员函数有以下好处：

1. 更少的函数调用
2. 更少的元素移动
3. 更少的内存分配

例：将v2后半部的元素赋值给v1：

    for (vector<Widget>::const_iterator ci = v2.begin() + v2.size() / 2;
         ci != v2.end();
         ++ci)
        v1.push_back(*ci);
    // 使用区间成员函数assign()
    v1.assign(v2.begin() + v2.size() / 2, v2.end());
    
## 避免 vector 频繁内存分配

新增元素空间不够时，vector会进行如下操作：

1. 分配当前空间的两倍空间；
2. 将当前元素拷贝到新的空间中；
3. 释放之前的空间；
4. 将新值放入新空间指定位置；

**如果预先知道空间的大小，预先分配空间（使用 reserve，或者定义 vector 时指明大小）避免了重新分配空间和复制的代价**；注：reserve()只是修改了容量，并非大小，向vector中增加元素还是需要通过push_back加入；

## 关联容器还是有序 vector

对一些阶段性的操作：做一系列插入、完成之后，后续操作都是查询。使用vector有以下优势：

1. 因为可以对vector排序，关联容器带来的有序优势丧失；
2. 使用二分法查找的前提下，查询算法对连续的内存空间的访问要快于离散的空间；

## 仿函数还是函数指针

在仿函数（functor, 函数对象）的方式中，内联有效，而作为函数指针时，一般编译器都不会对函数指针指向的函数进行内联；即使指定了inline；

    inline bool doubleGreater(double d1, double d2)
    {
        return d1 > d2;
    }
    vector<double> v;
    sort(v.begin(), v.end(), doubleGreater);

这个调用不是真的把doubleGreater传给sort，它传了一个doubleGreater的指针。更好的方式是使用仿函数：

    struct myclass {
        inline bool operator() (int i, int j) {
            return (i<j);
        }
    } myobject;

    sort(v.begin(), v.end(), myobject);

## 其它小条款

1. 用empty() 代替size()来检查是否为空。对于list，size()会遍历每一个元素来确定大小，时间复杂度 o(n)，线性时间；而empty总是保证常数时间；
2. 尽量用成员函数代替同名的算法。基于效率考虑，成员函数知道自己这个容器和其他容器有哪些特有属性，能够利用到这些特性；而通用算法不可以；此外对于关联容器，成员函数find基于等价搜索，而通用算法find基于相等来搜索；可能导致结果不一样；

# 参考  

《STL 源码剖析》  
[标准模板库（STL）使用入门（上）](http://blog.jobbole.com/87586/)  
[防止缓冲区溢出](http://www.ibm.com/developerworks/cn/security/buffer-defend/index.html)
[高效使用 STL](https://segmentfault.com/a/1190000002932246)  
[cplusplus：vector::reserve](http://www.cplusplus.com/reference/vector/vector/reserve/)  
[C++ STL轻松导学](http://morningspace.51.net/resource/stlintro/stlintro.html)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_1.png


