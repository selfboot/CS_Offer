## 宏定义

宏仅仅是在C预处理阶段的一种文本替换工具，编译完之后对二进制代码不可见。

`标示符别名`：
    
    #define BUFFER_SIZE 1024

预处理阶段
    
    foo = (char *) malloc (BUFFER_SIZE)；

会被替换成
    
    foo = (char *) malloc (1024)。

宏名之后带括号的宏被认为是`宏函数`。用法和普通函数一样，只不过在预处理阶段，宏函数会被展开。优点是没有普通函数保存寄存器和参数传递的开销，展开后的代码有利于CPU cache的利用和指令预测，速度快。缺点是可执行代码体积大。

    #define min(X, Y)  ((X) < (Y) ? (X) : (Y))
    y = min(1, 2);

会被扩展成
    
    y = ((1) < (2) ? (1) : (2));

需要注意的问题：

1. 语法问题：由于是纯文本替换，C预处理器不对宏体做任何语法检查，像缺个括号、少个分号之类的错误预处理器是不管的。
2. 算符优先级问题：不仅宏体是纯文本替换，**宏参数也是纯文本替换**。有以下一段简单的宏，实现乘法： 

        #define MULTIPLY(x, y) x * y
    
    MULTIPLY(1, 2)没问题，会正常展开成1 * 2。有问题的是这种表达式MULTIPLY(1+2, 3)，展开后成了1+2 * 3，显然优先级错了。在宏体中，给引用的参数加个括号就能避免这问题。

        #define MULTIPLY(x, y) (x) * (y)
        
3. 宏参数重复调用

    有如下宏定义：

        #define min(X, Y)  ((X) < (Y) ? (X) : (Y))

    当有如下调用时 next = min (x + y, foo (z)); 宏体被展开成next = ((x + y) < (foo (z)) ? (x + y) : (foo (z))); 可以看到，foo(z)被重复调用了两次，做了重复计算。更严重的是，如果foo是不可重入的(foo内修改了全局或静态变量)，程序会产生逻辑错误。所以，**尽量不要在宏参数中传入函数调用**。

［[宏定义中存在依赖时展开问题](http://www.nowcoder.com/questionTerminal/c33295e54974412095ebadab0f5bb820)］  

## C 风格字符串的函数

C风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法。按此习惯写的字符串存放在`字符数组中并以空字符（'\0'）结束`，一般利用指针来操作这些字符串。

C 语言标准库提供了一组函数用于操作 C 风格字符串，定义在 cstring 头文件中。

1. strcat(p1, p2)：将p2附加到p1之后，且会覆盖null字符，最后返回p1；［[题目](https://www.nowcoder.com/questionTerminal/3004651f5407480b8ae8e9dbdead9073)］
2. strlen(p)：返回p的长度，**遇到空字符'\0'结束**，空字符不计算在内；sizeof返回数组所占的字节数。［[题目](http://www.nowcoder.com/questionTerminal/81cc723e49fc402ca7fa62a97a121251)］
3. strcmp(p1, p2)：比较 p1 和 p2 的相等性，如果 p1 == p2，返回0，p1 > p2返回一个正值；p1 < p2 返回一个负值。
4. strcpy(p1, p2)：将p2拷贝给p1，返回p1。

（[c_string_func.cpp](../Coding/c_string_func.cpp)）

［[字符串常量赋值](http://www.nowcoder.com/questionTerminal/462f7c3746814b1cadde05a1084f8740)］  
［[strcpy 拷贝](http://www.nowcoder.com/questionTerminal/74d917fe09a94a2fb03b5371a2417372)］  
［[字符串常量和字符数组](http://www.nowcoder.com/questionTerminal/0db8ed5d69464f0bbb98d5eba3c08b9a)］

## printf 格式化字符串

printf 函数是一个标准库函数，它的函数原型在头文件“stdio.h”中。printf函数调用的一般形式为：
    
    int printf ( const char * format, ... );

其中格式控制字符串用于指定输出格式。格式控制串可由`格式字符串`和非格式字符串两种组成。格式字符串是以%开头的字符串，在%后面跟有各种格式字符，以说明输出数据的类型、形式、长度、小数位数等。`printf 返回值是输出的字符个数`。

格式字符串的一般形式为：`[标志][输出最小宽度][.精度][长度]类型`。其中方括号[]中的项为可选项。

`类型`字符用以表示输出数据的类型，其格式符和意义如下所示：

* d：以十进制形式输出带符号整数(正数不输出符号)
* o：以八进制形式输出无符号整数(不输出前缀0)
* x,X：以十六进制形式输出无符号整数(不输出前缀Ox)
* u：以十进制形式输出无符号整数
* f：以小数形式输出单、双精度实数
* e,E：以指数形式输出单、双精度实数
* c：输出单个字符
* s：输出字符串
* p：输出指针保存的地址

简单程序

    int i=123, m=0123, n = 0x123;   //注意八进制, 十六进制
    printf("%d %d %d\n", i, m, n);  //123 83 291
    printf("%o %o %o\n", i, m, n);  //173 123 443

［[八进制输出](http://www.nowcoder.com/questionTerminal/25bce0284ec040fabdf6629dbd0c5dc9)］

## 整型溢出

对于整型溢出，分为**无符号整型溢出和有符号整型溢出**。对于unsigned整型溢出，C的规范是有定义的——`溢出后的数会以2^(8*sizeof(type))作模运算`，也就是说，如果一个unsigned char（1字符，8bits）溢出了，会把溢出的值与256求模。

当一个算术表达式中既有无符号数又有有符号数时，就会将有符号值转换为无符号值。

    unsigned int u=10;
    int i=-42;
    cout << "i+i: " << i+i << endl; // -84
    cout << "i+u: " << i+u << endl; // 4294967264

第二个表达式中，相加前首先把整数 －42 转换成无符号数。把负数转换成无符号数类似于直接给无符号数赋一个负值，结果等于这个负数加上无符号数（ 2^32 ）的模。

    unsigned char c = -1, d = -2, e=0xff;
    printf("%d, %d", c, d, e);         // 255, 254, 255

对于signed整型的溢出，C的规范定义是`undefined behavior`，也就是说，编译器爱怎么实现就怎么实现。

［[For 循环次数](http://www.nowcoder.com/questionTerminal/7183f3428a444efe8a3f91247ddf6b7a)］  

## 位段

有些信息在存储时，并不需要占用一个完整的字节， 而只需占几个或一个二进制位。例如在存放一个开关量时，只有0和1 两种状态， 用一位二进位即可。为了节省存储空间，并使处理简便，C语言又提供了一种数据结构，称为“位域”或“位段”。

所谓“位域”是把一个字节中的二进位划分为几个不同的区域，并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作。 这样就可以把几个不同的对象用一个字节的二进制位域来表示。

    struct mybitfields
    {
        int a : 4;
        int b : 5;
        int c : 7;
    } test

位域虽然简单好用，但使用时需要注意：

1. 如果相邻位域字段的类型相同，且其位宽之和小于类型的sizeof大小，则后面的字段将紧邻前一个字段存储，直到不能容纳为止；
2. 如果相邻位域字段的类型相同，但其位宽之和大于类型的sizeof大小，则后面的字段将从新的存储单元开始，其偏移量为其类型大小的整数倍；
3. 整个结构体的总大小为最宽基本类型成员大小的整数倍。
4. 不能对位段进行取地址操作；
5. 对位段赋值时，最好不要超过位段所能表示的最大范围，否则可能会造成意想不到的结果。
6. 如果一个位段结构中只有一个占有0位的无名位段，则只占1或0字节的空间(C语言中是占0字节，而C++中占1字节)；否则其他任何情况下，一个位段结构所占的空间至少是一个位段类型的大小；
7. 位域可以无位域名，这时它只用来作填充或调整位置。无名的位域是不能使用的。

［[位域结构体的大小](http://www.nowcoder.com/questionTerminal/07adfd96a2364433a6538c9bb0fcda16)］  

## 柔性数组



［[结构体柔性数组作用](http://www.nowcoder.com/questionTerminal/be5269b8c2d340c3add69510d0089747)］

# 更多阅读

《C++ Primer》 Page109  
《Effective C++》 条款02：尽量以const, enum, inline 代替 #define，预处理器不够安全。  

[What is the difference between char s[] and char *s in C?](http://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s-in-c)      
[Why do I get a segmentation fault when writing to a string initialized with “char *s” but not “char s[]”?](http://stackoverflow.com/questions/164194/why-do-i-get-a-segmentation-fault-when-writing-to-a-string-initialized-with-cha)  
[Where is %p useful with printf?](http://stackoverflow.com/questions/2369541/where-is-p-useful-with-printf)    
[cplusplus: printf](http://www.cplusplus.com/reference/cstdio/printf/?kw=printf)    
[Arrays of Length Zero](https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html)

[C语言宏的特殊用法和几个坑](http://hbprotoss.github.io/posts/cyu-yan-hong-de-te-shu-yong-fa-he-ji-ge-keng.html)  
[C语言的谜题](http://coolshell.cn/articles/945.html)  
[语言的歧义](http://coolshell.cn/articles/830.html)
[C语言格式输出函数printf()详解](http://c.biancheng.net/cpp/html/33.html)  
[C语言的整型溢出问题](http://coolshell.cn/articles/11466.html)  
[从Swap函数谈加法溢出问题](http://blog.csdn.net/dataspark/article/details/9703967)  
[浅谈C语言中的位段](http://www.cnblogs.com/dolphin0520/archive/2011/10/14/2212590.html)  
[C语言结构体里的成员数组和指针](http://coolshell.cn/articles/11377.html)  
[深入理解C语言](http://coolshell.cn/articles/5761.html)  

