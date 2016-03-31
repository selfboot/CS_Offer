# C++ 输入输出流

输入和输出并不是C++语言中的正式组成成分。C和C++本身都没有为输入和输出提供专门的语句结构。输入输出不是由C++本身定义的，而是在编译系统提供的I/O库中定义的。

C++ 的程序把输入和输出看做字节流。输入时，程序从输入流中抽取字节；输出时，程序将字节插入输出流中，流充当了程序和流源或流目标之间的桥梁。

C++输入输出中有两个基类，分别为ios_base和ios，而基于这两个基类实现了输入流istream和输出流ostream，然后基于这两个流实现了针对三种不同应用的类（或对象）：

1. `标准输入输出`：为了程序员使用方便，C++直接以对象的形式提供了几个标准输入输出工具，分别为：cin(标准输入)，cout(标准输出)，cerr(不带缓存的标准错误输出)，clog(带缓存的标准错误输出)。
2. `文件输入输出`：C++ 提供了三个类以方便程序员进行文件读写操作，分别为：ifstream（读文件），ofstream（写文件），fstream（读写文件）
3. `字符串输入输出流`：将字符串作为输入输出流进行处理，有三个对应的类，分别为：istringstream（字符串输入流），ostringstream（字符串输出流），stringstream（字符串输入输出流）。

注意 I/O 对象不能进行拷贝或者赋值操作！

I/O 操作一个与生俱来的问题是可能发生错误，I/O类定义了一些函数和标志，用来访问和操纵流的条件状态。一共有4个流状态：

* strm::badbit：流已经崩溃
* strm::failbit：有一个 I/O 操作失败
* strm::eofbit：到达文件结尾
* strm::goodbit：用来指出流未处于错误状态

一旦一个流发生错误，其上后续的 IO 操作都会失败，只有当一个流处于无错状态时，才可以从它读取数据，向它写入数据。确保一个流对象的状态的最简单的方法是将它当作一个条件来使用。
    
    while(cin >> word){
        // 读操作成功
    }

## 标准输入输出

使用 `cin` 读取数据，操作符读取指定类型的数据，直到与目标类型不匹配的第一个字符为止，期间会跳过空格，制表符和tab。

**注意，不能用cin语句把空格字符和回车换行符作为字符输入给字符变量，它们将被跳过**。如果想将空格字符或回车换行符(或任何其他键盘上的字符)输入给字符变量，可以使用`getchar`函数。

使用 `cout` 输出数据时，可以使用控制符（控制符在头文件 iomanip 中），来进行格式化输出。例如要求以十六进制或八进制形式输出一个整数，或者对输出的小数只保留两位小数等。常用的控制符如下：

| 控制符 | 作用 |
| ------| ----|
| dec   | 设置数值的基数为10
| hex   | 设置数值的基数为16
| oct   | 设置数值的基数为8
| setprecision(n) | 设置浮点数的精度为n位。在以一般十进制小数形式输出时，n代表有效数字。在以fixed(固定小数位数)形式和 scientific(指数)形式输出时，n为小数位数
|setw(n) |设置字段宽度为n位
| setiosflags( ios::fixed) | 设置浮点数以固定的小数位数显示(ios::left 左对齐，ios::right 数据右对齐)

其它istream类方法如下：

* `cin.get(char &)`：从输入流中读取一个字符，赋给字符变量ch。如果读取成功则函数返回true(真)，如失败(遇文件结束符) 则函数返回false(假)。
* `cin.get(void)`：从指定的输入流中提取一个字符（包括空白字符），函数的返回值就是读入的字符。若遇到输入流中的文件结束符，则函数值返回文件结束标志EOF(End Of File)。
* `get(char *, int, char)`：从输入流中读取n-1个字符，赋给指定的字符数组(或字符指针指向的数组)，如果在读取n-1个字符之前遇到指定的终止字符，则提前结束读取。如果读取成功则函数返回true(真)，如失败(遇文件结束符) 则函数返回false(假)。
* `getline(char*, int, char)`：从输入流中读取一行字符，其用法与带3个参数的get函数类似。默认是读取整行！

用getline函数从输入流读字符时，遇到终止标志字符时结束，指针移到该终止标志字符之后，下一个getline函数将从该终止标志的下一个字符开始接着读入。如果用cin.get函数从输入流读字符时，遇终止标志字符时停止读取，指针不向后移动，仍然停留在原位置，下一次读取时仍从该终止标志字符开始。这是getline函数和get函数不同之处。

## 文件输入输出

文件流是以外存文件为输入输出对象的数据流。输出文件流是从内存流向外存文件的数据，输入文件流是从外存文件流向内存的数据。每一个文件流都有一个内存缓冲区与之对应。

头文件 fstream 定义了3个用于文件操作的文件类：

* ifstream类，它是从istream类派生的，用来支持从磁盘文件的输入。
* ofstream类，它是从ostream类派生的，用来支持向磁盘文件的输出。
* fstream类，它是从iostream类派生的，用来支持对磁盘文件的输入输出。

要以磁盘文件为对象进行输入输出，必须定义一个`文件流类的对象`，并将对象与文件关联起来。其实在用标准设备为对象的输入输出中，也是要定义流对象的，如cin、cout就是流对象，C++是通过流对象进行输入输出的。由于cin、cout已在iostream.h中事先定义，所以用户不需自己定义。在用磁盘文件时，由于情况各异，无法事先统一定义，必须由用户自己定义。



## 字符串输入输出


# 输入输出缓冲区

有时候程序会出现奇怪的输出，或者输入中读取的数据和想象不一致，这通常是由于存在输出输入缓冲区导致的。

在定义流对象时，系统会在内存中开辟一段缓冲区，用来暂存输入输出流的数据。缓冲区是用作中介的内存块，它是将信息从设备传输到程序或者从程序传输到设备的临时存储工具，用以匹配程序和设备之间速率的差距。

## 输出缓冲区

通常会把输出流中内容顺序存放在输出缓冲区中，直到输出缓冲区满或遇到cout语句中的endl(或'\n'，flush)为止，此时将缓冲区中已有的数据一起输出，并清空缓冲区。看下面的例子：

    #include <stdio.h>
    #include <sys/types.h>
    #include <unistd.h>
    
    int main(void)
    {
        int i;
        for(i=0; i<2; i++){
            fork();
            printf("-");
        }
        // 输出 8 个 -
        return 0;
    }


## 输入缓冲区

cin.ignore(a, ch)方法是从输入流（cin）中提取字符，提取的字符被忽略（ignore）。如果遇到 a 个字母或者遇到 ch，则执行终止；否则，它继续等待。它的一个常用功能就是用来清除以回车结束的输入缓冲区的内容，消除上一次输入对下一次输入的影响。下面是一个简单的示例：

    char first, second;

    cout << "Please, enter a word: ";
    first = cin.get();
    cin.clear();
    cin.ignore(3);

    cout << "Please, enter another word: ";
    second = cin.get();

    cout << "The first word began by " << first << '\n';
    cout << "The second word began by " << second << '\n';

如果输入发生错误，那么流状态会被标记，必须用 `cin.clear()` 清除错误状态，以使程序能正确适当地继续运行。

不建议使用 `std::cin.sync()` 丢弃缓冲区内容，因为有的平台并不支持（OS X就不支持）。

## 一个陷阱

`OJ 输入提前 break！！！`有时候会犯这类错误，且不容易察觉。
 
    while(cin >> p >> n){
       set<int> basket;
       int ans = -1;
       for(int i=0;i<n;i++){
           int xi;
           cin >> xi;
           if(basket.find(xi%p)!=basket.end()){
               ans = i+1;
               break;  // 后面的数据并没有读，仍然在缓冲区中！！！
           }
           else{
               basket.insert(xi%p);
           }
       }
       cout << ans << endl;
    }

# 参考  
C++ Primer 文件输入输出  
[cplusplus: Clear Input Stream](http://www.cplusplus.com/forum/beginner/48568/)  
[cplusplus: Flush output stream buffer](http://www.cplusplus.com/reference/ostream/ostream/flush/) 
[How do I flush the cin buffer?](http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer)  
[The difference between cin.ignore and cin.sync](http://stackoverflow.com/questions/10585392/the-difference-between-cin-ignore-and-cin-sync)  
[C++输入输出详解：C++标准输入输出流、文件流、字符串流](http://c.biancheng.net/cpp/biancheng/cpp/rumen_13/)


