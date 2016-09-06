模板是C++支持参数化多态的工具，使用模板可以使用户为类或者函数声明一种一般模式，使得类中的某些数据成员或者成员函数的参数、返回值取得任意类型。

通常有两种形式：函数模板和类模板；

* 函数模板针对仅参数类型不同的函数；
* 类模板针对仅数据成员和成员函数类型不同的类。

使用模板的目的就是能够让`程序员编写与类型无关的代码`。比如编写了一个交换两个整型int 类型的swap函数，这个函数就只能实现int 型，对double，字符这些类型无法实现，要实现这些类型的交换就要重新编写另一个swap函数。使用模板的目的就是要让这程序的实现与类型无关，比如一个swap模板函数，即可以实现int 型，又可以实现double型的交换。

注意：**模板的声明或定义只能在全局，命名空间或类范围内进行。**即不能在局部范围，函数内进行，比如不能在main函数中声明或定义一个模板。

# 函数模板

函数模板(Templates)使得我们可以生成通用的函数，这些函数能够接受任意数据类型的参数，可返回任意类型的值，而不需要对所有可能的数据类型进行函数重载。它们的原型定义可以是下面两种中的任何一个：

```c++
template <class identifier> function_declaration;
template <typename identifier> function_declaration;
```

其中template和class是关键字，class可以用typename代替，在这里typename和class没区别，<>括号中的参数叫模板形参，模板形参和函数形参很相像，模板形参不能为空。

一旦声明了模板函数就可以用模板函数的形参名来声明类中的成员变量和成员函数，也即在该函数中使用内置类型的地方都可以使用模板形参名。比如 max 的模板函数形式为：

```c++
template <class T>

T max (const T &a, const T &b) { 
    return (a>b?a:b); 
}
```

当调用该模板函数时类型T就会被调用时的类型所代替，一旦编译器确定了实际的模板实参类型就会实例化函数模板。以上面 max 函数为例，当我们用 max(1, 2) 调用时，这时模板函数 max 中的形参T就会被int所代替，编译器会生成一个int版本的函数 `int max(const int &a, const int &b)`。而当a和b是都double类型时，又会生成 double 版本的函数。

```c++
std::cout << max(1, 2) << std::endl;    // 2
// No matching function for call to 'max'.
// std::cout << max(1, "2") << std::endl;
```

# 类模板

我们也可以定义类模板（class templates），使得一个类可以有基于通用类型的成员，而不需要在类生成的时候定义具体的数据类型。
类模板的原型如下：

```c++
template<class 形参名，class 形参名，…>
class 类名
{
    ... 
};
```

类模板和函数模板都是以 template 开始后接模板形参列表组成，模板形参不能为空，一但声明了类模板就可以用类模板的形参名声明类中的成员变量和成员函数，即可以在类中使用内置类型的地方都可以使用模板形参名来声明。还要注意下面几点：

* 如果在全局域中声明了与模板参数同名的变量，则该变量被隐藏掉。
* 模板参数名不能被当作类模板定义中类成员的名字。
* 同一个模板参数名在模板参数表中只能出现一次。
* 在不同的类模板或声明中，模板参数名可以被重复使用。

下面是一个类模板的例子：

```c++
template<class T>
class A{
public: 
    T a;
    T b; 
    T hy(T c, T &d);
};
```

对于上面的模板类A，使用类模板创建对象的方法为 A\<int\> m; 这样的话类A中凡是用到模板形参的地方都会被int 所代替。当类模板有两个模板形参时创建对象的方法为A\<int, double\> m;类型之间用逗号隔开。

**对于类模板，模板形参的类型必须在类名后的尖括号中明确指定**。如果用 `A<2> m;` 这种方法创建模版对象，则会遇到编译错误：error C2079: 'a' uses undefined class 'A\<int\>'），这是因为**类模板形参不存在实参推演的问题**。也就是说不能把整型值2推演为int 型传递给模板形参，要把类模板形参调置为int 型必须这样指定A\<int\> m。

## 成员函数

类模板的**成员函数可以在类模板的定义中定义(这样就是 inline函数)，也可以在类模板定义之外定义**。要注意的是类模板成员函数本身也是一个模板，类模板被实例化时它并不自动被实例化，只有当它被调用或取地址，才被实例化。

在类模板外部定义成员函数的方法为：

```c++
template<模板形参列表> 函数返回类型 类名<模板形参名>::函数名(参数列表){函数体}
```

比如有两个模板形参T1，T2的类A中含有一个void h()函数，则定义该函数的语法为：

```c++
template<class T1,class T2>
void A<T1,T2>::h(){
}
```

`当在类外面定义类的成员时template后面的模板形参应与要定义的类的模板形参一致`。

# 模板编译

当编译器遇到一个模板定义时，并不生成代码。只有当我们实例化出模版的一个特定版本时，编译器才会生成代码。

**模板的声明和实现是否一定要在同一个头文件中？**

要知道，我们在调用一个函数时，编译器只需要掌握函数的声明。类似的，当**我们使用一个类类型的对象时，类定义必须是可用的，但成员函数的定义不必已经出现**。因此，可以将**类定义和成员函数声明**放在头文件（.h）中，而普通函数和类的成员函数的定义放在源文件中（.cpp）。

这样就可以把源文件编译成目标文件打包成库，然后把库和头文件给客户使用。对客户来说，可以使用相应的功能，但是看不到源文件。这样可以很好地保护商业利益，此外如果想要更改实现的话，可以重新编译自己的库，客户不需要为此更改代码。

但是在使用模板时，这种习惯性做法将变得不再有用。因为**为了生成一个实例化版本，编译器必须要掌握函数模板或类模板成员函数的定义**。因此，与非模版代码不同，模板的头文件通常既包括声明也包括定义。一般做法就是将模板的声明和定义都放置在同一个.h文件中，这就是为什么所有的STL头文件都包含模板定义。

详细来解释的话，主要从这[三个方面](https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl)来理解：

1. A template is not a class or a function. A template is a “pattern” that the compiler uses to generate a family of classes or functions.
2. In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to “fill in” the template. For example, if you’re trying to use a Foo<int>, the compiler must see both the Foo template and the fact that you’re trying to make a specific Foo<int>.
3. Your compiler probably doesn’t remember the details of one .cpp file while it is compiling another .cpp file. It could, but most do not and if you are reading this FAQ, it almost definitely does not. BTW this is called the “`separate compilation model`.”

下面看一个例子，假设一个模板类 Foo 的声明如下：

```c++
template<typename T>
class Foo {
public:
  Foo();
  void someMethod(T x);
private:
  T x;
};
```

成员函数的定义如下：

```c++
template<typename T>
Foo<T>::Foo()
{
  // ...
}
template<typename T>
void Foo<T>::someMethod(T x)
{
  // ...
}
```

现在假设在 `Bar.cpp` 中使用 `Foo<int>`:

```c++
// Bar.cpp
void blah_blah_blah()
{
  // ...
  Foo<int> f;
  f.someMethod(5);
  // ...
}
```

如果我们将Foo 的构造函数以及someMethod成员函数的定义放在Foo.cpp中，编译时会出现链接错误。这是因为编译器在编译 Foo.cpp 时知道了模版的定义代码，在编译 Bar.cpp 时候，知道了 Foo<int>的实例化，但是没法同时掌握模版定义和参数实例化，这样也就无法生成具体的类代码。

为了解决这个问题，通常我们会把模板的声明和定义放在一个头文件中（建议这样做），不过也可以分别放在头文件和源文件中，下面就是一个示例：

* [foo.h](../Coding/C++_Template_foo.h)：函数模版声明，模版类的定义；
* [foo.cpp](../Coding/C++_Template_foo.cpp)：函数模版定义，模板成员函数的定义；
* [main.cpp](../Coding/C++_Template_main.cpp)：使用函数模版和模版类。

这里在模版类的实现文件中放置具体的`模版实例化`，就可以生成具体的实例化对象了。

# 隐式接口和编译期多态

在面向对象编程世界中，总是以显式接口（explicit interfaces）和运行期多态（runtime polymorphism）解决问题。Template 以及泛型编程的世界，与面向对象有根本的不同，这里显式接口和运行期多态依然存在，不过重要性低很多。反而`隐式接口`（implicit interfaces）和`编译期多态`（compile-time polymorphism）重要很多。

下面以一个函数模版的例子来看看什么是隐式接口和编译期多态：

```c++
template <typename T>
void doProcessing(T &w){
    if(w.size() > 10 && w != someType){
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

这里 w 必须支持哪一种接口，是由template 中执行于 w 身上的操作来决定。上面例子看来 w 的类型 T 必须支持 size, normalize 和 swap 成员函数、copy构造函数，不等比较操作符。这一组表达式便是 T 必须支持的一组隐式接口，它们就像面向对象中 class 对象身上的显式接口一样真实，都是在编译期完成检查。

此外，凡是涉及 w 的任何函数调用，例如 operator> 和 operator !=，都有可能造成template 实例化。以不同的 template 参数实例化函数模版，将会导致调用不同的函数，这就是所谓的编译期多态。简单来说，编译期多态和运行期多态的差异类似于**哪一个重载函数被调用（编译期）和哪一个虚函数该被绑定（运行期）**。

# 模板的全特化与偏特化

有时候，对于特定的类型，可以更好地实现模版中的功能，因此需要提供一个专门的实现。以 swap 函数为例，典型实现如下：

```c++
namespace std{
    template <typename T>
    void swap(T &a, T &b){
        T temp(a);
        a = b;
        b = temp;
    }
}
```

只要类型 T 支持拷贝构造函数和拷贝赋值，缺省的 swap 实现代码就会完成置换操作。但是对某些类型来说，这些复制动作无一必要，比如对于`以指针指向一个对象，内含真正数据`的类型（所谓的 pimpl手法），如下例子：

```c++
class WidgetImpl{
    // 针对 Widget 数据而设计的 class
};

class Widget{
private:
    WidgetImpl* pImpl;
};
```

这时候我们可以令 Widget 声明一个名为 swap 的 public 成员函数做真正的置换工作，然后将 **std::swap **特化**，令它调用该成员函数：

```c++
class Widget{
public:
    void swap(Widget &other){
        using std::swap;
        swap(pImpl, other.pImpl);
    }

private:
    WidgetImpl* pImpl;
};

// 全特化版的 std::swap 函数
// 全特化的模板参数列表应当是空的，并且应当给出”模板实参”列表：
namespace std{
    template <>
    void swap<Widget>(Widget &a, Widget &b){
        a.swap(b);
    }
}
```

这里的特化为`全特化`，也就是说限定死模板实现的具体类型，函数模板和类模板都支持全特化。模板的特化必须在同一命名空间下进行，上面例子中 Widget 的swap特化实现必须在 std 命名空间下。在模板实例化时会优先匹配“模板参数”最相符的那个特化版本。下面看一个类模板的全特化：

```c++
template <class T1, class T2>
class A{
    T1 data1;
    T2 data2;
};
// 全特化类模板
template <>
class A<int, double>{
    int data1;
    double data2;
};
```

## 偏特化

类模板还允许`偏特化`，也就是说如果类模板有多个类型，那么只限定其中的一部分。类似于全特化，偏特化也是为了给自定义一个参数集合的模板，但偏特化后的模板需要进一步的实例化才能形成确定的签名。

偏特化也是以template来声明的，需要给出剩余的模板形参和必要的模板实参。例如：

```c++
template <class T2>
class A<int, T2>{
    ...
};
```

**函数模板是不允许偏特化的**，下面的声明会编译错：

```c++
template <class T1, class T2>
void f(){}

template <class T2>
void f<int, T2>(){}
```

这是因为函数允许重载，我们可以声明另一个函数模板即可替代偏特化的需要：

```c++
template <class T2>
void f(){}              // 注意：这里没有"模板实参"
```

多数情况下函数模板重载就可以完成函数偏特化的需要，一个例外便是std命名空间。std是一个特殊的命名空间，用户可以特化其中的模板，但不允许添加模板（其实任何内容都是禁止添加的）。


# 更多阅读

《Effective C++ 模板与泛型编程》  
《Effective C++ 条款 25》  
[Cpp Reference-Templates](http://en.cppreference.com/w/cpp/language/templates)  
[Why can templates only be implemented in the header file?](http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file)  
[Why can’t I separate the definition of my templates class from its declaration and put it inside a .cpp file? ](https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl)  
[类模板定义及实例化](http://www.cnblogs.com/assemble8086/archive/2011/10/02/2198308.html)  
[C++ typename的起源与用法](http://feihu.me/blog/2014/the-origin-and-usage-of-typename/)  
[C++模板的偏特化与全特化](http://harttle.com/2015/10/03/cpp-template.html)    
[C++ 中的模板类声明头文件和实现文件分离后，如何能实现正常编译？](https://www.zhihu.com/question/20630104)  

