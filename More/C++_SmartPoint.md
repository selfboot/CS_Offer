C语言、C++语言没有自动内存回收机制，关于内存的操作的安全性依赖于程序员的自觉。程序员每次new出来的内存块都需要自己使用delete进行释放，流程复杂可能会导致忘记释放内存而造成`内存泄漏`。

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


# 更多阅读

[C++ 引用计数技术及智能指针的简单实现](http://www.cnblogs.com/QG-whz/p/4777312.html)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_SmartPoint_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_SmartPoint_2.png

