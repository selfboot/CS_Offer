
# C++ STL 标准库

C++ STL（标准模板库）是一套功能强大的 C++ 模板类，提供了通用的模板类和函数，这些模板类和函数可以实现多种流行和常用的算法和数据结构，如向量、链表、队列、栈。

C++ 标准模板库的核心包括以下三个组件：

|组件|	描述|
|---|---|
|容器（Containers）|容器是用来管理某一类对象的集合。C++ 提供了各种不同|类型的容器，比如 vector、map 等。|
|算法（Algorithms）|算法作用于容器。它们提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作。|
|迭代器（Iterators）|迭代器用于遍历对象集合的元素。这些集合可能是容器，也可能是容器的子集。|

STL的一个重要特点是`数据结构和算法的分离`。尽管这是个简单的概念，但这种分离确实使得STL变得非常通用。例如，由于STL的sort()函数是完全通用的，你可以用它来操作几乎任何数据集合，包括链表，容器和数组。

STL另一个重要特性是它不是面向对象的。为了具有足够通用性，STL主要依赖于模板而不是封装，继承和虚函数（多态性）——OOP的三个要素。你在STL中找不到任何明显的类继承关系。

程序要使用 STL 时，应包含（#include）适当的标准头文件。对大部分容器来说，标准头文件的名称和容器名一致，且不需扩展名。比如说，如果你要用vector，只要在程序最开头添加下面这行代码：

    #include <vector>

容器类型（还有算法、运算符和所有 STL也一样）并不是定义在全局命名空间，而是定义在一个叫“std”的特殊命名空间里。在包含完所有头文件之后，还应该引入std::vector名字空间。

# 容器

一个容器就是一些特定类型对象的集合。`顺序容器（sequential container）`为程序员提供了控制元素存储和访问顺序的能力。这种顺序不依赖于元素的值，而是与元素加入容器时的位置相对应。

除了顺序容器外，标准库还定义了三个顺序容器适配器：stack、queue和priority_queue。`适配器`是标准库中的一个通用概念，容器、迭代器和函数都有适配器。本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。

和顺序容器对应的是`关联容器（associative-container）`，关联容器中的元素是按关键字来保存和访问的。关联容器支持高效的关键字查找和访问，STL有两个主要的关联容器：map 和 set。

[More：C++_STL_Containe](More/C++_STL_Container.md)

# 算法



# 迭代器

STL 迭代器是访问容器数据的最普通的方式。为迭代器定义如下操作：

* 从迭代器取值，int x = *it；
* 让迭代器自增和自减 it1++，it2–；
* 通过‘!=’和‘<’来比较迭代器大小；
* 向迭代器添加一个常量值 it += 20；（向前移动了 20 个元素位置）
* 获取两个迭代器之间的差值，int n = it2 – it1；

和指针不同，迭代器提供了许多更强大的功能。它们不仅能操作任何类型的容器，还能执行范围检查并分析容器的使用。当然，迭代器的最大优势就是极大地增加了代码重用性：基于迭代器写的算法在大部分的容器上都能使用，而且，自己写的容器要是提供了迭代器，就能作为参数传给各种各样的标准函数。

STL 算法常常使用两个迭代器，称为'begin'和'end'。尾部迭代器不指向最后一个对象，而是指向第一个无效对象，或是紧跟在最后一个对象后面的对象。每一个 STL 容器都有 begin() 和 end() 两个成员函数，分别返回容器的初始迭代器和尾部迭代器。

基于这些原理，只有容器 c 为空时，`c.begin() == c.end()`才成立，而`c.end() – c.begin()`总是会等于 c.size()。（后一句只有在迭代器可以做减法运算时才有效，例如，begin() 和 end() 都返回随机存取迭代器，但不是所有容器都支持。）

每个容器都有 rbegin()/rend() 函数，它们返回反向迭代器（和正常迭代器的指向相反）。反向迭代器用来从后往前地遍历容器。

    // vector<int>::reverse_iterator it;
    vector<int> v1 = {1,2,3}
    for(auto it = v1.rbegin();it!=v1.rend();it++){
        cout << *it << "\t";
    }


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


参考：  
[标准模板库（STL）使用入门（上）](http://blog.jobbole.com/87586/)  
[防止缓冲区溢出](http://www.ibm.com/developerworks/cn/security/buffer-defend/index.html)

