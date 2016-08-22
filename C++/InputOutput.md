# C++ 输入输出流

输入和输出并不是C++语言中的正式组成成分。C和C++本身都没有为输入和输出提供专门的语句结构。输入输出不是由C++本身定义的，而是在编译系统提供的I/O库中定义的。

C++ 的程序把输入和输出看做字节流。输入时，程序从输入流中抽取字节；输出时，程序将字节插入输出流中，流充当了程序和流源或流目标之间的桥梁。

C++输入输出中有两个基类，分别为ios_base和ios，而基于这两个基类实现了输入流istream和输出流ostream，然后基于这两个流实现了针对三种不同应用的类（或对象）：

1. `标准输入输出`：为了程序员使用方便，C++直接以对象的形式提供了几个标准输入输出工具，分别为：cin(标准输入)，cout(标准输出)，cerr(不带缓存的标准错误输出)，clog(带缓存的标准错误输出)。
2. `文件输入输出`：C++ 提供了三个类以方便程序员进行文件读写操作，分别为：ifstream（读文件），ofstream（写文件），fstream（读写文件）
3. `字符串输入输出流`：将字符串作为输入输出流进行处理，有三个对应的类，分别为：istringstream（字符串输入流），ostringstream（字符串输出流），stringstream（字符串输入输出流）。

如下图：

![][1]

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

## 文件输入输出

文件流是以外存文件为输入输出对象的数据流。输出文件流是从内存流向外存文件的数据，输入文件流是从外存文件流向内存的数据。每一个文件流都有一个内存缓冲区与之对应。

头文件 fstream 定义了3个用于文件操作的文件类：

* ifstream类，它是从istream类派生的，用来支持从磁盘文件的输入。
* ofstream类，它是从ostream类派生的，用来支持向磁盘文件的输出。
* fstream类，它是从iostream类派生的，用来支持对磁盘文件的输入输出。

要以磁盘文件为对象进行输入输出，必须定义一个`文件流类的对象`，并将对象与文件关联起来。其实在用标准设备为对象的输入输出中，也是要定义流对象的，如cin、cout就是流对象，C++是通过流对象进行输入输出的。由于cin、cout已在iostream.h中事先定义，所以用户不需自己定义。在用磁盘文件时，由于情况各异，无法事先统一定义，必须由用户自己定义。

每一个文件流对象都定义了一个成员函数 open 来定位给定的文件，并视情况打开为读或写模式。如果在创建文件流对象时，提供了文件名，则open会被自动调用。没有提供文件名，将会创建空文件流对象，可以随后调用 open 将它与文件关联起来。

    ifstream in(ifile); // 构造一个 ifstream 对象并打开给定文件；
    ofstream out;      // 输出文件流，未关联任何文件
    out.open(ofile);   // 打开指定文件

调用 open 可能会失败（相应文件不存在或者对一个打开的文件流再次调用open），因此需要检查 open 是否成功：

    if(out)

一旦一个文件流已经打开，就会保持与对应文件的关联。为了将文件流关联到另一个文件，必须首先用 close 函数关闭已经关联的文件。

    out.close();
    out.open(ofile_2);
    
注意，当一个 ifstream 对象离开其作用域时，与之关联的文件会自动关闭。

### 文件模式

每个流都有一个关联的 文件模式（file mode），用来指出如何使用文件。

|文件模式|             描述            | 
|-------|----------------------------|
| in    | 以读方式打开                 |
| out   | 以写方式打开                 |
| app   | 每次写操作均定位到文件末尾，只要没有trunc，就可以设定app     |
| ate   | 打开文件后立即定位到文件末尾，适用于任何类型的文件流对象|
| trunc | 截断文件（out被设定才可设定trunc，out默认是trunc的） 
| binary| 以二进制方式进行 IO，适用于任何类型的文件流对象     |

每个文件流类型都定义了一个默认的文件模式，ifstream 关联的文件默认 in 打开，ofstream 关联的文件默认 out 模式打开，fstream 关联的文件默认 in 和 out 打开。下面是一些打开时选定模式的例子：

    ofstream outfile("filename", ofstream::out);  // 隐含截断文件
    ofstream outfile("filename", ofstream::app); // 追加模式
 
## 字符串输入输出

sstream 头文件定义了三个类型来支持`内存 IO`，这些类型可以向 string 写入数据，从 string 读取数据，就像 string 是一个 IO 流一样。

输出时数据不是流向外存文件，而是流向内存中的一个存储空间。输入时从内存中的存储空间读取数据。在严格的意义上说，这不属于输入输出，称为读写比较合适。 因为输入输出一般指的是在计算机内存与计算机外的文件（外部设备也视为文件）之间 的数据传送。

sstream 定义来的类型增加了一些成员来管理与流相关联的 string，可以对 stringstream 对象调用这些操作，但不能对其它 IO 调用。

* stringstream strm： 未绑定的 stringstream 对象；
* stringstream strm(s)：一个 stringstream 对象，保存了 string s 的一个拷贝；
* strm.str()：返回 strm 所保存的 string 的拷贝；
* strm.str(s)：将 string s拷贝到 strm 中，返回 void.

对字符串流的几点说明：

1. 用字符串流时不需要打开和关闭文件。
2. 通过字符串流从字符数组读数据就如同从键盘读数据一样，可以从字符数组读入字符数据，也可以读入整数、浮点数或其他类型数据。如果不用字符串流，只能从字符数组逐个访问字符，而不能按其他类型的数据形式读取数据。这是用字符串流访问字符数组的优点，使用方便灵活。

一个简单的例子，反转 vector 中的数字：

    vector<int> nums{123,456,789};
    vector<int> reversed_nums;
    for(auto n : nums){
        ostringstream digit;
        digit << n;
        string str_n = digit.str();
        reverse(str_n.begin(), str_n.end());

        int reversed_n;
        istringstream rev_n(str_n);
        rev_n >> reversed_n;
        reversed_nums.push_back(reversed_n);
    }
    // reversed_nums: {321, 654, 987}

我们知道在要求使用基类对象的地方，可以使用继承类型的对象取代，所以在接受一个 iostream 类型引用或者指针参数的函数，可以用一个对应的 fstream(或 sstream)类型来调用。

## 相关函数

istream, ostream 类提供了许多函数，常用的有 get, getline 等。

`std::istream::get` 从输入流中读取一个字符，赋给字符变量ch，常用的原型为：

```c++
istream& get (char& c);
```

`std::istream::getline` 从输入流中读取字符，直到遇到终止符号，默认换行符为终止符号，读到换行符后，丢弃换行符（C++ 还提供一个功能类似的全局函数 std::getline）。常用的原型如下：

```c++
istream& getline (char* s, streamsize n );
istream& getline (char* s, streamsize n, char delim );
```

用getline函数从输入流读字符时，遇到终止标志字符时结束，指针移到该终止标志字符之后，下一个getline函数将从该终止标志的下一个字符开始接着读入。如果用cin.get函数从输入流读字符时，遇终止标志字符时停止读取，指针不向后移动，仍然停留在原位置，下一次读取时仍从该终止标志字符开始，这是getline函数和get函数不同之处。简单来说，**getline将丢弃换行符，而get()将换行符保留在输入序列里**，千万要注意 get 之后的换行符（ **>> 操作符也不会丢弃换行符**，同样需要注意）。

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

## 陷阱

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

读取操作时，`>> 操作符` 会跳过空白制表符，但是 getline 不会跳过。也就是说 getline 可能会读取 >> 操作后剩余下的换行符。假设一个输入流数据如下：

> 10 2  
> name Jack  
> name John

如果用下面的程序读取数据：

```c++
cin >> N >> M;
for(int i=0; i<2; i++){
    cin.getline(names[i]);
}
```

那么读到的names数组前两项将会是 "", "name Jack"。因为 >> 读完 M 后还剩下一个换行符，将被 getline 读取到。解决办法就是在 第一句后面加上一句，**吃掉换行符**。（后面就不用吃掉换行符了，因为 getline 会丢弃换行符）

```c++
cin >> N >> M;
cin.get();
...
```

# 参考  
C++ Primer 文件输入输出  
[cplusplus: Clear Input Stream](http://www.cplusplus.com/forum/beginner/48568/)  
[cplusplus: Flush output stream buffer](http://www.cplusplus.com/reference/ostream/ostream/flush/) 
[How do I flush the cin buffer?](http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer)  
[The difference between cin.ignore and cin.sync](http://stackoverflow.com/questions/10585392/the-difference-between-cin-ignore-and-cin-sync)  
[C++输入输出详解：C++标准输入输出流、文件流、字符串流](http://c.biancheng.net/cpp/biancheng/cpp/rumen_13/)


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_InputOutput.gif

