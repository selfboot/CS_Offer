C++11 曾经被叫做 C++0x，是对目前C++语言的扩展和修正，C++11不仅包含核心语言的新机能，而且扩展了C++的标准程序库（STL）。C++11包括大量的新特性：包括lambda表达式，类型推导关键字auto、decltype，和模板的大量改进。

C++11修复大量缺陷和降低代码拖沓，比如lambda表达式的支持将使代码更简洁。新的标准库同时也会包含新的特性，包括对多线程的支持和优化智能指针，后者将给那些还没用类似boost::shared_ptr的人提供更简单的内存管理方法。

# 类型推导 auto

编译时常常需要把表达式的值赋值给变量，这就要求在声明变量时清楚的知道表达式的类型，然后做到这点并非容易，有时甚至根本做不到。为了解决这个问题，C++ 11 新标准引入了 auto 类型说明符。用它就能让编译器替我们去分析表达式所属的类型。比如，你可以这样写：

```c++
auto x=0;       //x has type int because 0 is int
auto c='a';     //char
auto d=0.5;     //double
auto national_debt=14400000000000LL;    //long long
```

编译器在编译阶段就可以推导出x的类型是int，c的类型是 char。当然，这不是一个证明auto有用的一个漂亮的例子，当使用模板特别是STL时auto很好用，比如：STL中的容器的迭代子类型。

```c++
vector<int>::const_iterator ci = vi.begin();
auto ci = vi.begin();
```

使用auto必需一个初始化值，编译器可以通过这个初始化值推导出类型。因为auto是来简化模板类引入的代码难读的问题，如上面的示例，iteration这种类型就最适合用auto的。但是，我们不应该把其滥用。比如下面的代码的可读性就降低了。因为，我不知道ProcessData返回什么？int? bool? 还是对象？或是别的什么？这让后面的程序不知道怎么做。

```c++
auto obj = ProcessData(someVariables);
```

再来看下面的例子：

```c++
const int a=12;
auto b = a;
b= 3;
cout << b << endl;      // 3
```

这是因为**编译器推断出来的 auto 类型有时候和初始值的类型并不完全一样，编译器会适当地改变结果类型使其更符合初始化规则**。首先，使用引用时，编译器以引用对象的类型作为 auto 的类型；其次 **auto 一般会忽略顶层 const，同时底层const则会保留下来**（这就可以解释上面的结果）。如果希望推断出的 auto 是一个顶层 const，需要明确指出：

```c++
const int a=12;
const auto b = a;
```

此外，还可以将引用的类型设置为 auto，这时引用的初始化规则仍然适用，也即不能为非常量引用绑定字面值。注意，设置一个类型为 auto 的引用时，**初始值中的顶层常量属性仍然保留**。

```c++
const int ci=10;        // 顶层常量属性
auto &g = ci;
// auto &h = 42;        // Error, 不能为非常量引用绑定字面值
const auto &j = 42;     // 正确: 可以为常量引用绑定字面值
```

# 区间迭代

下面迭代器的例子是C++11提供的一种处理迭代的更好方法，有些人叫做区间迭代（基本上所有的现代语言都支持），下面例子足够证明这种语法是多么优雅：

```c++
vector<int> vec;
vec.push_back(10);
vec.push_back(20);
    
for (int &i: vec)
{
   cout<<i;
}
```

你需要做的就是给出一个变量和要迭代的区间。但是如果你想迭代一个map怎么办？你怎么设置map中值的类型？你知道vector值的类型是int，但map的值类型是pair，通过.first和.second给你提供键和值。但是用auto，你根本无需关心确切类型，你可以简单的写成：

```c++
for (auto address_entry: address_book)
{
   cout<<address_entry.first<<" "<address_entry.second<<endl;
}
```

假如想修改你正在迭代的容器的值，或者你想避免拷贝大对象，你可以用引用的变量遍历。比如，下面的迭代对一个整形vector中每个元素的值加1。

```c++
vector<int> vec;
vec.push_back(1);
vec.push_back(2);
    
for (int& i: vec)
{
   i++; // increments the value in the vector
}
```

# 自动化推导 decltype

decltype是auto的反面兄弟。auto让你声明了一个指定类型的变量，decltype让你从一个变量（或表达式）中得到类型。

```c++
int x = 3;
decltype(x) y = x; // 相当于 auto y = x;
```

可以对基本上任何类型使用decltype，包括函数的返回值。decltype用于获取一个表达式的类型，而不对表达式进行求值（类似于sizeof）。decltyp(e)规则如下：

1.	如果表达式e是一个变量，那么就是这个变量的类型。
2.	如果表达式e是一个函数，那么就是这个函数返回值的类型。
3.	如果不符合1和2，如果e是左值，类型为T，那么decltype(e)是T&；如果是右值，则是T。

# 统一的初始化语法

在引入C++11之前，只有数组能使用初始化列表，其他容器想要使用初始化列表，只能用以下方法：

```c++
int arr[3] = {1, 2, 3}
vector<int> v(arr, arr + 3);
```

在C++11中，我们可以使用以下语法来进行替换：

```c++
int arr[3]{1, 2, 3};
vector<int> iv{1, 2, 3};
string str{"Hello World"};
```

# nullptr

nullptr是为了解决原来C++中NULL的二义性问题而引进的一种新的类型，因为NULL实际上代表的是0。具体看下面程序：

```c++
#include<iostream>
#include <cassert>
    
using namespace std;
    
void F(int a){
   cout<< "Call int: " << a <<endl;
}
    
void F(int *p){
   cout << "Call *p: " << p  << endl;
}
    
int main(){
    
   int *p = nullptr;
   int *q = NULL;
   bool equal = ( p == q ); // equal的值为true，说明p和q都是空指针
   cout << equal << endl;
   // int a = nullptr;      // 编译失败，nullptr不能转型为int
   F(0);                    // 在C++98中编译失败，有二义性；在C++11中调用F（int）
   F(nullptr);
    
   return 0;
}
```

# lambda 匿名函数

Lambda 表达式用来创建匿名函数，算得上是 C++ 11 新增特性中最激动人心的一个。举个例子，标准 C++ 库中有一个常用算法的库，其中提供了很多算法函数，比如 sort() 和 find()。这些函数通常需要提供一个“谓词函数 predicate function”。所谓谓词函数，就是进行一个操作用的临时函数。比如 find() 需要一个谓词，用于查找元素满足的条件；能够满足谓词函数的元素才会被查找出来。这样的谓词函数，使用临时的匿名函数，既可以减少函数数量，又会让代码变得清晰易读。

关于lambda 的更多内容，参考 [Lambda Function](11_Lambda.md)

# 智能指针

c++的内存管理是让很多人头疼的事，当我们写一个new语句时，一般就会立即把delete语句直接也写了，但是我们不能避免程序还未执行到delete时就跳转了或者在函数中没有执行到最后的delete语句就返回了，如果我们不在每一个可能跳转或者返回的语句前释放资源，就会造成内存泄露。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。

现在能使用的，带引用计数，并且能自动释放内存的智能指针包括以下几种：

* unique_ptr: 如果内存资源的所有权不需要共享，就应当使用这个（它没有拷贝构造函数），但是它可以转让给另一个unique_ptr（存在move构造函数）。
* shared_ptr: 如果内存资源需要共享，那么使用这个（所以叫这个名字）。
* weak_ptr: 持有被shared_ptr所管理对象的引用，但是不会改变引用计数值。它被用来打破依赖`循环`。
 
另一方面，auto_ptr已经被废弃，不会再使用了。

关于智能指针的更多内容，参见 [Smart Point](11_SmartPoint.md)。

# 更多阅读  

[C++11系列-什么是C++11](http://towriting.com/blog/2013/08/01/what-is-cpp11/)  
[C++11 中值得关注的几大变化（详解）](http://coolshell.cn/articles/5265.html)  
[C++开发者都应该使用的10个C++11特性](http://blog.jobbole.com/44015/)  
[C++11有哪些新特性？](http://harttle.com/2015/10/08/cpp11.html)  

