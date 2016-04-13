# 使用 GDB 调试程序

GDB是UNIX下面的程序调试工具, 可以调试多种类型程序, 主要可以完成以下四个功能:

1. 启动你的程序，可以按照你的自定义的要求随心所欲的运行程序。 
2. 可让被调试的程序在指定的调置的断点处停住。（断点可以是条件表达式）
3. 当程序被停住时，可以检查此时程序中所发生的事。
4. 动态的改变程序的执行环境。

# 简单的调试例子

测试程序如下：

    #include <stdio.h>
    int func(int n)
    {
        int sum=0,i;
        for(i=0; i<n; i++)
        {
            sum+=i;
        }
        return sum;
    }
    void main()
    {
        int i; long result = 0;
        for(i=1; i<=100; i++)
        {
            result += i;
        }
        printf(“result[1-100] = %d \n”, result );
        printf(“result[1-250] = %d \n”, func(250) );
    }

编译生成执行文件（要调试C/C++的程序，在编译时必须要把调试信息加到可执行文件中：-g 选项）：

    gcc -g C++_GDB_test.cpp -o C++_GDB_test.o

一个简单的调试过程如下：

    $ gdb C++_GDB_test.o
    GNU gdb (GDB) 7.10.1
    ......
    done.
    (gdb) l                    ----> l(list), 列出源码
    6	*/
    7
    8	#include <stdio.h>
    9	int func(int n)
    10	{
    11	    int sum=0,i;
    12	    for(i=0; i<n; i++)
    13	    {
    14	        sum+=i;
    15	    }
    (gdb)                      ----> 直接回车表示重复上一次命令
    16	    return sum;
    17	}
    18	int main()
    19	{
    20	    int i; long result = 0;
    21	    for(i=1; i<=100; i++)
    22	    {
    23	        result += i;
    24	    }
    25	    printf("result[1-100] = %ld\n", result );
    (gdb)
    26	    printf("result[1-250] = %d\n", func(250));
    27	}
    (gdb) br 20                 ----> 设置断点，在源程序 20 行处
    Breakpoint 1 at 0x100000edf: file C++_GDB_test.cpp, line 20.
    (gdb) br func               ----> 设置断点，在函数func()入口处
    Breakpoint 2 at 0x100000e97: file C++_GDB_test.cpp, line 11.
    (gdb) info br               ----> 查看断点信息
    Num     Type           Disp Enb Address            What
    1       breakpoint     keep y   0x0000000100000edf in main() at C++_GDB_test.cpp:20
    2       breakpoint     keep y   0x0000000100000e97 in func(int) at C++_GDB_test.cpp:11
    (gdb) r                     ----> r(run) 运行程序
    Starting program: .../C++_Code/C++_GDB_test.o
    Breakpoint 1, main () at C++_GDB_test.cpp:20  ----> 在断点处停住
    20	    int i; long result = 0;
    (gdb) n                     ----> n(next)单条语句执行
    21	    for(i=1; i<=100; i++)
    (gdb) n
    23	        result += i;
    (gdb) n
    21	    for(i=1; i<=100; i++)
    (gdb) c                     ----> c(continue)继续运行程序到下一个断点
    Continuing.
    result[1-100] = 5050        ----> 程序输出
    
    Breakpoint 2, func (n=250) at C++_GDB_test.cpp:11
    11	    int sum=0,i;
    (gdb) n
    12	    for(i=0; i<n; i++)
    (gdb) br 14 if i==50        ----> 设置条件断点
    Breakpoint 3 at 0x100000eb1: file C++_GDB_test.cpp, line 14.
    (gdb) c
    Continuing.
    
    Breakpoint 3, func (n=250) at C++_GDB_test.cpp:14
    14	        sum+=i;
    (gdb) p i                   ----> p(print): 打印变量i的值
    $1 = 50
    (gdb) p sum                 ----> p: 打印变量sum的值
    $2 = 1225
    (gdb) bt                    ----> 查看函数堆栈
    #0  func (n=250) at C++_GDB_test.cpp:14
    #1  0x0000000100000f36 in main () at C++_GDB_test.cpp:26
    (gdb) finish                ----> 退出函数
    Run till exit from #0  func (n=250) at C++_GDB_test.cpp:14
    0x0000000100000f36 in main () at C++_GDB_test.cpp:26
    26	    printf("result[1-250] = %d\n", func(250));
    Value returned is $6 = 31125
    (gdb) c
    Continuing.
    result[1-250] = 31125
    [Inferior 1 (process 8845) exited normally]   ----> 程序退出，调试结束 
    (gdb) q 

# 调试参数

gdb调试中需要用到的命令

* file [filename]：装入想要调试的可执行文件
* kill [filename]：终止正在调试的程序
* break [file:]function：在(file文件的)function函数中设置一个断点
* clear：删除一个断点，这个命令需要指定代码行或者函数名作为参数
* run [arglist]：运行您的程序 (如果指定了arglist,则将arglist作为参数运行程序)
* bt Backtrace：显示程序堆栈信息
* `x`：查看内存
* print expr：打印表达式的值
* continue：继续运行您的程序 (在停止之后，比如在一个断点之后)
* list：列出产生执行文件的源代码的一部分
* next：单步执行 (在停止之后); 跳过函数调用（与step相对应，step会进入函数内部）
* set：设置变量的值。例如：set nval=54 将把54保存到nval变量中；设置输入参数也可以通过这个命令(例如当三个入参分别为a、b、c的话，set args a b c)
* watch：使你能监视一个变量的值而不管它何时被改变
* finish：继续执行，直到当前函数返回
* ignore：忽略某个断点制定的次数。例：ignore 4 23 忽略断点4的23次运行，在第24次的时候中断
* info [name]：查看name信息
* xbreak：在当前函数的退出的点上设置一个断点
* whatis：显示变量的值和类型
* ptype：显示变量的类型
* shell：使你能不离开 gdb 就执行 UNIX shell 命令
* help [name]：显示GDB命令的信息，或者显示如何使用GDB的总体信息
* quit：退出gdb.
  
`命令行参数`

有时候，我们需要调试的程序需要有命令行参数，可以通过下面两种方式设置调试的程序的命令行参数：

* gdb命令行的 –args 参数
* gdb环境中 set args命令。

# 高级的用法

比如为了搞清楚柔性数组的内存分布特征，我们可以用下面的程序来验证：

    #include <stdlib.h>
    #include <string.h>
    
    struct line {
       int length;
       char contents[0]; // C99：char contents[]; 没有指定数组长度
    };
    
    int main(){
        int this_length=10;
        struct line *thisline = (struct line *)
                         malloc (sizeof (struct line) + this_length);
        thisline->length = this_length;
        memset(thisline->contents, 'a', this_length);
        return 0;
    }

然后用下面的调试过程来理解柔性数组的内存分布：

![][1]

# 参考

[使用gdb调试程序详解](http://www.vimer.cn/2009/11/使用gdb调试程序详解.html)  
[GDB中应该知道的几个调试方法](http://coolshell.cn/articles/3643.html)  
[Codesign gdb on Mac OS X Yosemite](http://andresabino.com/2015/04/14/codesign-gdb-on-mac-os-x-yosemite-10-10-2/)

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_GDB_Debug_1.png


