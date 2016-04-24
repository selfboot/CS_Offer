
## 智能指针

智能指针实质是一个栈对象，而并非指针类型。C++的auto_ptr的作用是动态分配对象以及当对象不再需要时自动执行清理。使用std::auto_ptr，要#include <memory>。

1. 尽量不要使用“operator=”（如果使用了，请不要再使用先前对象）。
2. 记住release()函数不会释放对象，仅仅归还所有权。
3. std::auto_ptr最好不要当成参数传递（读者可以自行写代码确定为什么不能）。
4. auto_ptr存储的指针应该为NULL或者指向动态分配的内存块。
5. auto_ptr存储的指针应该指向单一物件（是new出来的，而不是new[]出来的）。auto_ptr不能指向数组，因为auto_ptr在析构的时候只是调用delete,而数组应该要调用delete[]。
6. 使用auto_ptr作为成员变量，以避免资源泄漏。
7. auto_ptr不能共享所有权，即不要让两个auto_ptr指向同一个对象。
8. auto_ptr不能作为容器对象，STL容器中的元素经常要支持拷贝，赋值等操作，在这过程中auto_ptr会传递所有权，那么source与sink元素之间就不等价了。


参考  
[智能指针std::auto_ptr](http://www.cnblogs.com/Braveliu/p/3290441.html)  

