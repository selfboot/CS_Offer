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

编译会给出下面的提示：

![][1]


# 更多阅读
[函数中局部变量的返回](http://blog.csdn.net/jackystudio/article/details/11523353)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Function_1.png


