函数是一组一起执行一个任务的语句，函数还有很多叫法，比如方法、子例程或程序，等等。每个 C++ 程序都至少有一个函数，即主函数 main() ，所有简单的程序都可以定义其他额外的函数。

函数声明告诉编译器函数的名称、返回类型和参数，函数定义提供了函数的实际主体。C++ 标准库提供了大量可以调用的内置函数，例如，函数 strcat() 用来连接两个字符串，函数 memcpy() 用来复制内存到另一个位置。

# 函数定义

C++ 中的函数定义的一般形式如下：

    return_type function_name( parameter list )
    {
       body of the function
    }

在 C++ 中，函数由一个函数头和一个函数主体组成。下面列出一个函数的所有组成部分：

* 返回类型：一个函数可以返回一个值。return_type 是函数返回的值的数据类型。有些函数执行所需的操作而不返回值，在这种情况下，return_type 是关键字 void。
* 函数名称：这是函数的实际名称，函数名和参数列表一起构成了函数签名。
* 参数：参数就像是占位符。当函数被调用时，您向参数传递一个值，这个值被称为实际参数。参数列表包括函数参数的类型、顺序、数量。参数是可选的，也就是说，函数可能不包含参数。
* 函数主体：函数主体包含一组定义函数执行任务的语句。

创建 C++ 函数时，会定义函数做什么，然后通过调用函数来完成已定义的任务。当程序调用函数时，程序控制权会转移给被调用的函数。被调用的函数执行已定义的任务，当函数的返回语句被执行时，或到达函数的结束括号时，会把程序控制权交还给主程序。调用函数时，传递所需参数，如果函数返回一个值，则可以存储返回值。

## 函数参数

如果函数要使用参数，则必须声明接受参数值的变量。这些变量称为函数的`形式参数`。形式参数就像函数内的其他局部变量，在进入函数时被创建，退出函数时被销毁。当调用函数时，有两种向函数传递参数的方式：

* `传值调用`：该方法把参数的实际值复制给函数的形式参数，在这种情况下，修改函数内的形式参数对实际参数没有影响。注意，这里如果传的是指针，那么会把参数的地址复制给形式参数。在函数内，该地址用于访问调用中要用到的实际参数。这意味着，修改形式参数会影响实际参数。
* `引用调用`：该方法把参数的引用复制给形式参数。在函数内，该引用用于访问调用中要用到的实际参数。这意味着，修改形式参数会影响实际参数。

默认情况下，C++ 使用传值调用来传递参数。一般来说，这意味着函数内的代码不能改变用于调用函数的参数。

定义一个函数后，可以为参数列表中后边的每一个参数指定默认值。当调用函数时，如果实际参数的值留空，则使用这个默认值。如果指定了值，则会忽略默认值，使用传递的值。

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

# 函数重载

如果`同一个作用域内`的几个`函数名字相同`但`形参列表`不同，称之为重载函数（main函数不能重载）。对于重载函数来说，它们应该在形参数量或形参类型上有所不同。**不允许两个函数除了返回类型外其它所有的要素都相同**。

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

# 常用库函数

## memcpy

memcpy是c和c++使用的内存拷贝函数，从源src所指的内存地址的起始位置开始拷贝**n个字节**到目标dest所指的内存地址的起始位置中，函数返回指向dest的指针。函数原型如下：

    // #include <cstring>
    // #include <string.h> 
    void *memcpy(void *dest, const void *src, size_t n);

要注意下面两个问题：

1. src和dest所指的内存区域可能重叠，并不能够确保src所在重叠区域在拷贝之前不被覆盖。而使用 `memmove` 可以用来处理重叠区域。
2. 如果目标区域dest本身已有数据，执行memcpy后，将覆盖原有数据（最多覆盖n）。

strcpy和memcpy主要有以下3方面的区别。

1. 复制的内容不同。strcpy只能复制字符串，而memcpy可以复制任意内容，例如字符数组、整型、结构体、类等。
2. 复制的方法不同。strcpy不需要指定长度，它遇到被复制字符的串结束符"\0"才结束，所以容易溢出。memcpy则是根据其第3个参数决定复制的长度。
3. 用途不同。通常在复制字符串时用strcpy，而需要复制其他类型数据时则一般用memcpy。

例子(把一个char组成的字符串循环右移n位，n小于字符串长度)

    const int MAX_LEN = 100;
    
    void LoopMove (char *pStr, int steps )
    {
        int n = strlen( pStr ) - steps;
        char tmp[MAX_LEN];
    
        memcpy(tmp, pStr + n, steps );
        memmove(pStr + steps, pStr, n );    // 防治内存区域重叠
        memcpy(pStr, tmp, steps );
    }
    
    int main(){
        char temp[] = "abcdefg";
        LoopMove(temp, 2);
        printf("%s", temp);
    }

［[memmove 实现方式](http://www.nowcoder.com/questionTerminal/32859fcd17ab47468a2899935829f3de)］

## memset

memset 将s所指向的某一块内存中的前n个`字节`的内容全部设置为ch指定的ASCII值，第一个值为指定的内存地址，块的大小由第三个参数指定，这个函数通常为新申请的内存做初始化工作，其返回值为指向s的指针。是对较大的结构体或数组进行`清零`操作（memset(&Address, 0, sizeof(Address))）的一种最快方法.
    
    // #include <cstring>
    // #include <string.h>
    void *memset(void *s, int ch, size_t n);

**用 memset 对非字符型数组赋非零的初值是不可取的**！如下例子：

    int a[5];
    // memset(a,1,5*sizeof(int));
    memset(a,1,sizeof(a));

    for(int i=0;i<5;i++)
        cout<<a[i];
    // 1684300916843009168430091684300916843009

这是因为memset对a指向的内存的20个字节进行赋值，每个都用数1去填充，转为二进制后，1就是00000001，占一个字节。一个int元素是4字节，合一起是0000 0001,0000 0001,0000 0001,0000 0001，转化成十六进制就是0x01010101，就等于16843009，就完成了对一个int元素的赋值了。

# 高危库函数

C 中大多数缓冲区溢出问题可以直接追溯到标准 C 库。最有害的罪魁祸首是不进行自变量检查的、有问题的字符串操作（strcpy、strcat、sprintf 和 gets）。

**永远不要使用 gets()**

最新的编译器会提醒：warning: this program uses gets(), which is unsafe.  这是因为gets函数从标准输入读入用户输入的一行文本，它在遇到 EOF 字符或换行字符之前，不会停止读入文本。也就是gets() 根本不执行边界检查。因此，使用 gets() 总是有可能使任何缓冲区溢出。作为一个替代方法，可以使用方法 `fgets(buf, size, stdin)`，它可以做与 gets() 所做的同样的事情，但它接受用来限制读入字符数目的大小参数，因此，提供了一种防止缓冲区溢出的方法。

    #define BUFSIZE 10
    
    int main(){
        char buf[BUFSIZE];
        // gets(buf);
        fgets(buf, BUFSIZE, stdin);
    }

如果有可能，避免使用下面的函数：

* strcpy，strcat
* printf，sprintf, fprintf, ...
* scanf，sscanf, fscanf, ...

**strcpy()函数**

strcpy()函数将源字符串复制到目的缓冲区，但是没有指定要复制字符的具体数目。复制字符的数目直接取决于源字符串中的数目，如果源字符串碰巧来自用户输入，且没有专门限制其大小，则有可能会陷入大的麻烦中！

如果知道目的地缓冲区的大小，可以添加明确的检查。或者使用 `strncpy() 函数`：

    strncpy(dest, src, dst_size-1);
    dst[dst_size-1] = '\0'; /* Always do this to be safe! */
    
如果 src 比 dst 大，则该函数不会抛出一个错误；当达到最大尺寸时，它只是停止复制字符，注意上面dst_size-1。

strcat()函数非常类似于 strcpy()，除了它将一个字符串合并到缓冲区末尾。它也有一个类似的、更安全的替代方法 `strncat()`。如果可能，使用 strncat() 而不要使用 strcat()。

# 更多阅读

[C Function Call Conventions and the Stack](http://www.csee.umbc.edu/~chang/cs313.s02/stack.shtml)  
[函数中局部变量的返回](http://blog.csdn.net/jackystudio/article/details/11523353)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_Function_1.png


