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

1. 语法问题：由于是纯文本替换，C预处理器不对宏体做任何语法检查，像缺个括号、少个分号神马的预处理器是不管的。
2. 算符优先级问题：不仅宏体是纯文本替换，**宏参数也是纯文本替换**。有以下一段简单的宏，实现乘法： 

        #define MULTIPLY(x, y) x * y
    
    MULTIPLY(1, 2)没问题，会正常展开成1 * 2。有问题的是这种表达式MULTIPLY(1+2, 3)，展开后成了1+2 * 3，显然优先级错了。在宏体中，给引用的参数加个括号就能避免这问题。

        #define MULTIPLY(x, y) (x) * (y)
        
3. 宏参数重复调用

    有如下宏定义：

        #define min(X, Y)  ((X) < (Y) ? (X) : (Y))

    当有如下调用时 next = min (x + y, foo (z)); 宏体被展开成next = ((x + y) < (foo (z)) ? (x + y) : (foo (z))); 可以看到，foo(z)被重复调用了两次，做了重复计算。更严重的是，如果foo是不可重入的(foo内修改了全局或静态变量)，程序会产生逻辑错误。所以，**尽量不要在宏参数中传入函数调用**。

［[对应题目](http://www.nowcoder.com/question/next?pid=1227362&qid=15947&tid=2494453)］

参考： [C语言宏的特殊用法和几个坑](http://hbprotoss.github.io/posts/cyu-yan-hong-de-te-shu-yong-fa-he-ji-ge-keng.html)  
《Effective C++》 条款02：尽量以const, enum, inline 代替 #define，预处理器不够安全。

## C 风格字符串的函数

C风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法。按此习惯写的字符串存放在`字符数组中并以空字符（'\0'）结束`，一般利用指针来操作这些字符串。

C 语言标准库提供了一组函数用于操作 C 风格字符串，定义在 cstring 头文件中。

1. strcat(p1, p2)：将p2附加到p1之后，且会覆盖null字符，最后返回p1；［[对应题目](http://www.nowcoder.com/test/question/done?tid=2494453&qid=25523#summary)］
2. strlen(p)：返回p的长度，**遇到空字符'\0'结束**，空字符不计算在内； ［[对应题目](http://www.nowcoder.com/questionTerminal/81cc723e49fc402ca7fa62a97a121251)］
3. strcmp(p1, p2)：比较 p1 和 p2 的相等性，如果 p1 == p2，返回0，p1 > p2返回一个正值；p1 < p2 返回一个负值。
4. strcpy(p1, p2)：将p2拷贝给p1，返回p1。

（[c_string_func.cpp](C++_Code/c_string_func.cpp)）

［[字符串常量赋值](http://www.nowcoder.com/questionTerminal/462f7c3746814b1cadde05a1084f8740)］  
［[strcpy 拷贝](http://www.nowcoder.com/questionTerminal/74d917fe09a94a2fb03b5371a2417372)］

参考：   
《C++ Primer》 Page109  
[What is the difference between char s[] and char *s in C?](http://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s-in-c)      
[Why do I get a segmentation fault when writing to a string initialized with “char *s” but not “char s[]”?](http://stackoverflow.com/questions/164194/why-do-i-get-a-segmentation-fault-when-writing-to-a-string-initialized-with-cha)  

## printf 格式化字符串

printf 函数是一个标准库函数，它的函数原型在头文件“stdio.h”中。printf函数调用的一般形式为：
    
    printf(“格式控制字符串”, 输出表列)

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

简单程序

    int i=123, m=0123, n = 0x123;   //注意八进制, 十六进制
    printf("%d %d %d\n", i, m, n);  //123 83 291
    printf("%o %o %o\n", i, m, n);  //173 123 443

［[八进制输出](http://www.nowcoder.com/questionTerminal/25bce0284ec040fabdf6629dbd0c5dc9)］

参考：[C语言格式输出函数printf()详解](http://c.biancheng.net/cpp/html/33.html)

## 柔性数组



［[结构体柔性数组作用](http://www.nowcoder.com/questionTerminal/be5269b8c2d340c3add69510d0089747)］

参考：  
[C语言结构体里的成员数组和指针](http://coolshell.cn/articles/11377.html)  
[Arrays of Length Zero](https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html)

## 参考

[C语言的谜题](http://coolshell.cn/articles/945.html)  
[语言的歧义](http://coolshell.cn/articles/830.html)

