
## 函数返回值

一般说来，函数中是可以进行局部变量的返回的，但是要注意了，这里所谓的局部变量的返回很有内涵，什么样的值才可以进行返回而不出错？

其实使用局部变量时只要遵守一句话即可：`函数不能返回指向栈内存的指针`！

这是因为`局部变量`的作用域是函数内部，函数一旦执行结束，栈上的局部变量会进行销毁，内存得到释放。因此，如果函数返回的是该局部变量的值拷贝，这是没有问题的。但是如果返回的是局部变量的地址，那么返回的只是该局部变量指针的拷贝，而随着函数运行结束，该拷贝指针所指向的栈内存已经被释放，那么指向一个未知区域就会导致调用的错误。

具体看下面的例子：

    #include <iostream>
    using namespace std;
    
    int* test_1(){
        int d=2;
        int c = d;
        // return &d;
        return &c;
    }
    
    int* test_2(){
        int d[] = {1,2};
        return d;
    }
    
    int* test_3(){
        int d[] = {1,2};
        int *t = d;
        return t;
    }
    
    char* test_4()
    {
        char str[]="HelloJacky";
        return str;
    }
    
    char* test_5()
    {
        char* str=(char*)"HelloJacky";
        return str;
    }
    
    int* test_6(){
        int a = 1;
        int *b = &a;
        return b;
    }
    
    int main(void)
    {
        int *p = 0;
        cout << *test_1() << endl;
        cout << *test_2() << endl;
        cout << *test_3() << endl;
        cout << *test_4() << endl;
        cout << *test_5() << endl;
        cout << *test_6() << endl;
    }

编译器会给出下面的提示：

![][1]

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

# 更多阅读

[函数中局部变量的返回](http://blog.csdn.net/jackystudio/article/details/11523353)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Function_1.png


