# 普通指针

指针是一个存储计算机内存地址的变量。从指针指向的内存读取数据称作指针的取值，指针可以指向某些具体类型的变量地址，例如int、long和double，也可以是void类型、NULL指针和未初始化指针，关于指针的更多内容可以参考 [C++ Pointer](C++_Pointer.md)。

利用指针变量可以表示各种数据结构；能很方便地使用数组和字符串；并能像汇编语言一样处理内存地址，从而编出精练而高效的程序，可以说指针极大地丰富了C/C++的功能。

但是由于C、C++没有自动内存回收机制，关于内存的操作的安全性依赖于程序员的自觉。程序员每次new出来的内存块都需要自己使用delete进行释放，复杂的流程可能会导致忘记释放内存而造成`内存泄漏`。

此外，当有多个指针指向同一个对象时，如果某个指针delete了该对象，对这个指针来说明确了它所指的对象被释放掉了，所以不会再对所指对象进行操作，但是对于剩下的其他指针来说还指向已经被删除的对象。于是悬垂指针就形成了，再次访问已经释放的内存空间，可能会导致程序崩溃。

# 悬垂指针

首先来看下面的代码：

    int * ptr1 = new int (1);
    int * ptr2 = ptr1;
    int * ptr3 = prt2;
       
    cout << *ptr1 << endl;
    cout << *ptr2 << endl;
    cout << *ptr3 << endl;
    
    delete ptr1;
    
    cout << *ptr2 << endl;

输出ptr2时可能并不是期待的1，因为1已经被删除了。这个过程是这样的：

![][1]
![][2]
![][3]

从图可以看出，错误的产生来自于ptr1的"无知"：它并不知道还有其他指针共享着它指向的对象。如果有个办法让ptr1知道，除了它自己外还有两个指针指向基础对象，而它不应该删除基础对象，那么悬垂指针的问题就得以解决了。如下图：

![][4]
![][5]

那么何时才可以删除基础对象呢？当然是只有一个指针指向基础对象的时候，这时通过该指针就可以把基础对象删除了。如何让指针知道还有其他指针的存在呢，加入`引用计数`即可。

# 智能指针

为了避免普通指针可能带来的各种问题，C++标准库中引入了智能指针，先来看下面的这段程序：

    #include <iostream>
    using namespace std;
    
    int main()
    {
        unique_ptr<int> up1(new int(10)); // 不能复制的unique_ptr
        // unique_ptr<int> up2 = up1; // 这样是错的
        cout<<*up1<<endl;
    
        unique_ptr<int> up3 = move(up1); // 现在up3是数据唯一的unique_ptr智能指针
        cout<<*up3<<endl;
        // cout<<*up1<<endl; // 运行时错误
    
        up3.reset(); // 显示释放内存
        up1.reset(); // 即使up1没有拥有任何内存，但是这样调用也没有问题
        // cout<<*up3<<endl; // 已经释放掉up3了，这样会运行时错误
    
        shared_ptr<int> sp1(new int(20));
        shared_ptr<int> sp2 = sp1; // 这是完全可以的，增加引用计数
    
        cout<<*sp1<<endl;
        cout<<*sp2<<endl;
    
        sp1.reset(); // 减少引用计数
        cout<<*sp2<<endl;
    
        return 0;
    }

C++11 中主要提供了unique_ptr、shared_ptr和weak_ptr这三个智能指针来自动回收堆分配的对象。

## unique_ptr

C++11中的unique_ptr是auto_ptr的替代品，它与auto_ptr一样拥有唯一拥有权的特性，与auto_ptr不一样的是，unique_ptr是没有复制构造函数的，这就防止了一些“悄悄地”丢失所有权的问题发生，如果需要将所有权进行转移，可以这样操作：

    nique_ptr<int> up3 = move(up1); // 现在up3是数据唯一的unique_ptr智能指针
    // 或者
    unique_ptr<int> up4(move(up1));

只有在使用者显示的调用std::move之后，才会发生所有权的转移，这样就让使用者知道自己在干什么。再来一段代码，看看将unique_ptr作为函数参数和返回值的使用情况：

    #include <iostream>
    #include <memory>
    using namespace std;
    
    unique_ptr<int> Func(unique_ptr<int> a)
    {         
        cout<<*a<<endl;
        return a;
    }         
    
    int main()
    {         
        unique_ptr<int> up1(new int(10));
    
        up1 = Func(move(up1));
        cout<<*up1<<endl;
    
        return 0;
    }

由于在unique_ptr中是没有复制构造函数的，所以在直接传参时，进行值传递时，建立临时变量时，就会出错了，所以需要显示的调用move，转移所有权；而函数的返回值已经进行了move操作，而不用显示的进行调用。

## shared_ptr

shared_ptr名如其名，它允许多个该智能指针共享地“拥有”同一堆分配对象的内存；由于它的资源是可以共用的，所以也就可以透过operator=等方法，来分享shared_ptr所使用的资源。

由于shared_ptr内部实现上使用的是`引用计数`这种方法，所以一旦一个shared_ptr指针放弃了“所有权”，其它的shared_ptr对对象的引用并不会发生变化；只有在引用计数归零的时候，shared_ptr才会真正的释放所占有的堆内存空间的。

下面是一段简单的使用示例：[gist](https://gist.github.com/xuelangZF/eaf00ecca8a1053a6da5ca85018cc839)。

### shared_ptr指向数组
 在默认情况下，shared_ptr将调用delete进行内存的释放；当分配内存时使用new[]时，我们需要对应的调用delete[]来释放内存；为了能正确的使用shared_ptr指向一个数组，我们就需要定制一个删除函数，例如：

    #include <iostream>
    #include <memory>
    using namespace std;
    
    class A
    {
    public:
        A() { cout<<"constructor"<<endl; }
        ~A() { cout<<"destructor"<<endl; }
    };
    
    int main()
    {
        shared_ptr<A> arrayObj(new A[5], [](A *p){delete[] p;});
    
        return 0;
    }

如果确实需要共享地托管一个对象，使用unique_ptr也许会更简单一些，比如：

    #include <iostream>
    #include <memory>
    using namespace std;
    
    class A
    {
    public:
        A() { cout<<"constructor"<<endl; }
        ~A() { cout<<"destructor"<<endl; }
    };
    
    int main()
    {
        unique_ptr<A[]> arrayObj(new A[5]);
    
        return 0;
    }

### 环形引用
 对于使用引用计数实现的智能指针，总是避免不了这个问题的。如果出现类似下面的代码，那就出现了环形引用的问题了。

    class Parent
    {
    public:
        shared_ptr<Child> child;
    };
    
    class Child
    {
    public:
        shared_ptr<Parent> parent;
    };
    
    shared_ptr<Parent> pA(new Parent);
    shared_ptr<Child> pB(new Child);
    pA->child = pB;
    pB->parent = pA;

要解决环形引用的问题，没有特别好的办法，一般都是在可能出现环形引用的地方使用weak_ptr来代替shared_ptr。

### [weak_ptr](http://en.cppreference.com/w/cpp/memory/weak_ptr)

weak_ptr一般和shared_ptr配合使用，它可以指向shared_ptr所指向的对象，但是却不增加对象的引用计数。这样就有可能出现weak_ptr所指向的对象实际上已经被释放了的情况。因此，weak_ptr有一个lock函数，尝试取回一个指向对象的shared_ptr。

> std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr. It must be converted to std::shared_ptr in order to access the referenced object.

下面是一个简单的例子：

```c++
#include <iostream>
#include <memory>

std::weak_ptr<int> gw;
void f() {
    if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
        std::cout << *spt << "\n";
    }
    else {
        std::cout << "gw is expired\n";
    }
}

int main() {
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
        f();
    }
    f();
}
```

# 更多阅读

[C++ 引用计数技术及智能指针的简单实现](http://www.cnblogs.com/QG-whz/p/4777312.html)  
[从auto_ptr说起](http://www.jellythink.com/archives/673)  
[到C++11中的智能指针](http://www.jellythink.com/archives/684)  
[C++11 新特性之智能指针](http://blog.jobbole.com/104569/)  
[When is std::weak_ptr useful?](http://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_SmartPoint_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_SmartPoint_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_SmartPoint_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_SmartPoint_4.png
[5]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_11_SmartPoint_5.png


