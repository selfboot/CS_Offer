# RAII

RAII是 Resource Acquisition Is Initialization 的缩写，意为“资源获取即初始化”。它是C++之父Bjarne Stroustrup 提出的设计理念，其核心是把资源和对象的生命周期绑定，对象创建获取资源，对象销毁释放资源。在RAII的指导下，C++把底层的资源管理问题提升到了对象生命周期管理的更高层次。

说起来，RAII的含义倒也不算复杂。用白话说就是：在类的构造函数中分配资源，在析构函数中释放资源。这样，当一个对象创建的时候，构造函数会自动地被调用；而当这个对象被释放的时候，析构函数也会被自动调用。于是乎，一个对象的生命期结束后将会不再占用资源，资源的使用是安全可靠的。
C++ RAII体现出了简洁、安全、实时的特点：

1. 概念简洁性：让资源（包括内存和非内存资源）和对象的生命周期绑定，资源类的设计者只需用在类定义内部处理资源问题，提高了程序的可维护性；
2. 类型安全性：通过资源代理对象包装资源（指针变量），并利用运算符重载提供指针运算方便使用，但对外暴露类型安全的接口；
3. 异常安全性：栈语义保证对象析构函数的调用，提高了程序的健壮性；
4. 释放实时性：和GC相比，RAII达到了和手动释放资源一样的实时性，因此可以承担底层开发的重任。



# 更多阅读  

[What is meant by Resource Acquisition is Initialization (RAII)?](http://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii)  
[RAII and smart pointers in C++](http://stackoverflow.com/questions/395123/raii-and-smart-pointers-in-c)  

