面向对象重要的概念就是类（Class）和实例（Instance），必须牢记类是抽象的模板，比如Student类，而实例是根据类创建出来的一个个具体的“对象”，每个对象都拥有相同的方法，但各自的数据可能不同。

先回顾下 OOP 的常用术语：

* 类：对具有相同数据和方法的一组对象的描述或定义。
* 对象：对象是一个类的实例。
* 实例(instance)：一个对象的实例化实现。
* 实例属性（instance attribute）：一个对象就是一组属性的集合。
* 实例方法(instance method)：所有存取或者更新对象某个实例一条或者多条属性的函数的集合。
* 类属性（classattribute）：属于一个类中所有对象的属性，不会只在某个实例上发生变化
* 类方法（classmethod）：那些无须特定的对象实例就能够工作的从属于类的函数。

# [Class 概述](https://docs.python.org/2/tutorial/classes.html)

在Python中，定义类是通过class关键字：

    class Student(object):
        pass

class后面紧接着是类名，即Student，类名通常是大写开头的单词，紧接着是(object)，表示该类是从哪个类继承下来的。通常，如果没有合适的继承类，就使用object类，这是所有类最终都会继承的类。

定义好了Student类，就可以根据Student类创建出Student的实例，创建实例是通过类名+()实现的：

    >>> bart = Student()
    >>> bart
    <__main__.Student object at 0x10a67a590>
    >>> Student
    <class '__main__.Student'>

可以看到，变量bart指向的就是一个Student的object，后面的0x10a67a590是内存地址，每个object的地址都不一样，而Student本身则是一个类。

可以自由地给一个实例变量绑定属性，比如，给实例bart绑定一个name属性：

    >>> bart.name = 'Bart Simpson'
    >>> bart.name
    'Bart Simpson'

由于类可以起到模板的作用，因此，可以在创建实例的时候，把一些我们认为必须绑定的属性强制填写进去。通过定义一个特殊的__init__方法，在创建实例的时候，就把name，score等属性绑上去。

    class Student(object):
    
        def __init__(self, name, score):
            self.name = name
            self.score = score
        
注意到__init__方法的第一个参数永远是self，表示创建的实例本身，因此，在__init__方法内部，就可以把各种属性绑定到self，因为self就指向创建的实例本身。

有了__init__方法，在创建实例的时候，就不能传入空的参数了，必须传入与__init__方法匹配的参数，但self不需要传，Python解释器自己会把实例变量传进去：

    >>> bart = Student('Bart Simpson', 59)
    >>> bart.name
    'Bart Simpson'
    >>> bart.score
    59
    
和普通的函数相比，在类中定义的对象函数（还有静态方法，类方法）只有一点不同，就是第一个参数永远是实例变量self，并且，调用时不用传递该参数。

## 新式类、旧式类

python的新式类是2.2版本引进来的，之前的类叫做经典类或者旧类。Python 2.x 中如果一个类继承于一个基类（可以是自定义类或者其它类）或者继承自 object，则该类为`新式类`；没有继承的类为`经典类`。Python 3.x 则全部为新式类。

新式类被赋予了很多新的特性（如：统一了types和classes），并改变了以往经典类的一些内容（如：改变了多继承下方法的执行顺序）。

关于统一类(class)和类型(type)，具体看下面的例子

    class OldClass():
        pass
    
    o = OldClass()
    print o.__class__   # __main__.OldClass
    print type(o)       # <type 'instance'>
    
    
    class newClass(object):
        pass
    
    n = newClass()
    print n.__class__   # <class '__main__.newClass'>
    print type(n)       # <class '__main__.newClass'>

参考  
[What is the difference between old style and new style classes in Python?](http://stackoverflow.com/questions/54867/what-is-the-difference-between-old-style-and-new-style-classes-in-python)

# Python 类方法

Python 类其实有3个方法，即静态方法(staticmethod)，类方法(classmethod)和实例方法，如下:

    def foo(x):
        print "executing foo(%s)"%(x)
    
    class A(object):
        def foo(self,x):
            print "executing foo(%s,%s)"%(self,x)
    
        @classmethod
        def class_foo(cls,x):
            print "executing class_foo(%s,%s)"%(cls,x)
    
        @staticmethod
        def static_foo(x):
            print "executing static_foo(%s)"%x
    
    a=A()
    print(a.static_foo)
    # <function static_foo at 0xb7d479cc>
    
对于一般的函数来说我们可以这么调用foo(x)，这个函数就是最常用的，它的工作跟任何东西(类，实例)无关。

对于实例方法，在类里每次定义方法的时候都需要绑定这个实例，就是foo(self, x)。为什么要这么做呢？因为实例方法的调用离不开实例，我们需要把实例自己传给函数，调用的时候是这样的a.foo(x)(其实是foo(a, x))。类方法一样，只不过它传递的是类而不是实例，A.class_foo(x)。注意这里的self和cls可以替换别的参，但是python的约定是self和cls，最好不要改。

对于静态方法其实和普通的方法一样，不需要对谁进行绑定，唯一的区别是调用的时候需要使用a.static_foo(x) 或者 A.static_foo(x)来调用。（Staticmethods are used to group functions which have some logical connection with a class to the class.）

|       | 实例方法 | 类方法           |  静态方法           |
|-------| --------| -------         |  -------          |
|a = A()| a.foo(x)| a.class_foo(x)  |  a.static_foo(x)  |
| A     | 不可用   | A.class_foo(x)  |  A.static_foo(x)  |

参考：  
[What is the difference between @staticmethod and @classmethod in Python?](http://stackoverflow.com/questions/136097/what-is-the-difference-between-staticmethod-and-classmethod-in-python)

# Python 数据属性

下面创建了一个Student的类，并且实现了这个类的初始化函数"`__init__`":

    class Student(object):
        count = 0
        books = []
        def __init__(self, name, age):
            self.name = name
            self.age = age

在上面的Student类中，count, books, name 和 age 都被称为类的数据属性，但是它们又分为`类数据属性`和`实例数据属性`。直接定义在类体中的属性叫类属性，而在类的方法中定义的属性叫实例属性。

首先看下面代码，展示了对类数据属性和实例数据属性的访问：

    Student.books.extend(["python", "javascript"])  
    print "Student book list: %s" %Student.books    
    # class can add class attribute after class defination
    Student.hobbies = ["reading", "jogging", "swimming"]
    print "Student hobby list: %s" %Student.hobbies    
    print dir(Student)
    
    # class instance attribute
    wilber = Student("Wilber", 28) 
    print "%s is %d years old" %(wilber.name, wilber.age)   
    # class instance can add new attribute 
    # "gender" is the instance attribute only belongs to wilber
    wilber.gender = "male"
    print "%s is %s" %(wilber.name, wilber.gender)
       
    # class instance can access class attribute    
    wilber.books.append("C#")
    print wilber.books 

通过内建函数dir()，或者访问类的字典属性`__dict__`，这两种方式都可以查看类或者实例有哪些属性。对于类数据属性和实例数据属性，可以总结为：

* 类数据属性属于类本身，可以通过类名进行访问/修改；
* 类数据属性也可以被类的所有实例访问/修改；
* 在类定义之后，可以通过类名动态添加类数据属性，新增的类属性也被类和所有实例共有；
* 实例数据属性只能通过实例访问；
* 在实例生成后，还可以动态添加实例数据属性，但是这些实例数据属性只属于该实例；

再看下面的程序

    class Person:
        name="aaa"
    
    p1=Person()
    p2=Person()
    p1.name="bbb"
    print p1.name  # bbb
    print p2.name  # aaa
    print Person.name  # aaa

上面程序中，p1.name="bbb"是实例调用了类变量，p1.name一开始是指向的类变量name="aaa"，但是在实例的作用域里把类变量的引用改变了，就变成了一个实例变量。self.name不再引用Person的类变量name了。

    class Person:
        name=[]
    
    p1=Person()
    p2=Person()
    p1.name.append(1)
    print p1.name  # [1]
    print p2.name  # [1]
    print Person.name  # [1]

更加详细的解释看： [关于Python类属性与实例属性的讨论](https://segmentfault.com/a/1190000002671941)  

## 特殊的类属性

对于所有的类，都有一组特殊的属性：

![][3]

通过这些属性，可以得到 Student类的一些信息，如下：

![][4]


# Python 类的继承

Python 是面向对象语言，支持类的继承（包括单重和多重继承），继承的语法如下：

    class DerivedClass(BaseClass1, [BaseClass2...]):
        <statement-1>
        .
        <statement-N>

子类可以覆盖父类的方法，此时有两种方法来调用父类中的函数：

1. 调用父类的未绑定的构造方法。在调用一个实例的方法时，该方法的self参数会被自动绑定到实例上（称为绑定方法）。但如果直接调用类的方法（比如A.__init），那么就没有实例会被绑定。这样就可以自由的提供需要的self参数，这种方法称为`未绑定(unbound)方法`。大多数情况下是可以正常工作的，但是多重继承的时候可能会重复调用父类。
2. 通过 `super(type, obj).method()` 调用父类函数，super函数返回一个super对象，这个对象负责进行方法解析，解析过程其会自动查找所有的父类以及父类的父类。这里基类必须继承自object类，这样才能使用super函数，因为这是python的“`新式类`”支持的特性。当前的类和对象可以作为super函数的参数使用，调用函数返回的对象的任何方法都是调用超类的方法，而不是当前类的方法。

未绑定(unbound)方法调用如下：

    class Base(object):
        def __init__(self):
            print("Base.__init__")
    
    class Derived(Base):
        def __init__(self):
            Base.__init__(self)
            print("Derived.__init__")
  
supper 调用如下：

    class Base(object):
        def __init__(self):
            print "Base.__init__"
    
    
    class Derived(Base):
        def __init__(self):
            super(Derived, self).__init__()
            print "Derived.__init__"
    
    
    class Derived_2(Derived):
        def __init__(self):
            super(Derived_2, self).__init__()
            print "Derived_2.__init__"

## 继承机制 MRO（Method Resolution Order）

在 MRO 中，基类永远出现在派生类后面，如果有多个基类，基类的相对顺序保持不变。

MRO 主要用于在多继承时判断调的属性的路径(来自于哪个类)。在新式类中，查找一个要调用的函数或者属性的时候，是广度优先搜搜的。在旧式类当中，是深度优先搜索的。如下图所示：

![][2]

注意这里的 super，MRO 都是针对 new-style class，如果不是 new-style class，只能老老实实用父类的类名去调用函数。

关于 super，更深入的理解在 [Python’s super() considered super!](https://rhettinger.wordpress.com/2011/05/26/super-considered-super/)。

# 多态

多态即多种形态，在运行时确定其状态，在编译阶段无法确定其类型，这就是多态。Python中的多态和Java以及C++中的多态有点不同，Python中的变量是弱类型的，在定义时不用指明其类型，它会根据需要在运行时确定变量的类型。

Python本身是一种解释性语言，不进行预编译，因此它就只在运行时确定其状态，故也有人说Python是一种多态语言。在Python中很多地方都可以体现多态的特性，比如 内置函数len(object)，len函数不仅可以计算字符串的长度，还可以计算列表、元组等对象中的数据个数，这里在运行时通过参数类型确定其具体的计算过程，正是多态的一种体现。

# 特殊的类方法

类中经常有一些方法用两个下划线包围来命名，下图给出一些例子。合理地使用它们可以对类添加一些“魔法”的行为。

![][1]

## 构造与析构

当我们调用 x = SomeClass() 的时候，第一个被调用的函数是 ` __new__` ，这个方法创建实例。接下来可以用 `__init__` 来指明一个对象的初始化行为。当这个对象的生命周期结束的时候， `__del__` 会被调用。

* `__new__(cls,[...])` 是对象实例化时第一个调用的方法，它只取下 cls 参数，并把其他参数传给init。
* `__init__(self,[...])` 为类的初始化方法。它获取任何传给构造器的参数（比如我们调用 x = SomeClass(10, ‘foo’) ，init 函数就会接到参数 10 和 ‘foo’） 。
* `__del__(self)`：new和init是对象的构造器， del则是对象的销毁器。它并非实现了语句 del x (因此该语句不等同于 `x.__del__()`)，而是定义当对象被回收时的行为。
	
## 操作符

利用特殊方法可以构建一个拥有Python内置类型行为的对象，这意味着可以避免使用非标准的、丑陋的方式来表达简单的操作。在一些语言中，这样做很常见:

    if instance.equals(other_instance):
        # do something

Python中当然也可以这么做，但是这样做让代码变得冗长而混乱。不同的类库可能对同一种比较操作采用不同的方法名称，这让使用者需要做很多没有必要的工作。因此我们可以定义方法`__eq__`，然后就可以像下面这样使用：

    if instance == other_instance:
        # do something

Python 有许多特殊的函数对应到常用的操作符上，比如：

* `__cmp__(self, other)`：定义了所有比较操作符的行为。应该在 self < other 时返回一个负整数，在 self == other 时返回0，在 self > other 时返回正整数。
* `__eq__(self, other)`：定义等于操作符(==)的行为。
* `__ne__(self, other)`：定义不等于操作符(!=)的行为（**定义了 eq 的情况下也必须再定义 ne**！）
* `__le__(self, other)`：定义小于等于操作符(<)的行为。
* `__ge__(self, other)`：定义大于等于操作符(>)的行为。

## 数值操作符

就像可以使用比较操作符来比较类的实例，也可以定义数值操作符的行为。可以分成五类：一元操作符，常见算数操作符，反射算数操作符，增强赋值操作符，和类型转换操作符，下面为一些例子：

* `__pos__(self)` 实现取正操作，例如 +some_object
* `__invert__(self)` 实现取反操作符 ~
* `__add__(self, other)` 实现加法操作
* `__sub__(self, other)` 实现减法操作
* `__radd__(self, other)` 实现反射加法操作
* `__rsub__(self, other)` 实现反射减法操作
* `__floordiv__(self, other)` 实现使用 // 操作符的整数除法
* `__iadd__(self, other)` 实现加法赋值操作。
* `__isub__(self, other)` 实现减法赋值操作。
* `__int__(self)` 实现到int的类型转换。
* `__long__(self)` 实现到long的类型转换。

反射运算符方法和它们的常见版本做的工作相同，只不过是处理交换两个操作数之后的情况。类型转换操作符，主要用于实现类似 float() 这样的内建类型转换函数的操作。

## 类的表示

使用字符串来表示类是一个相当有用的特性。在Python中有一些内建方法可以返回类的表示，相对应的，也有一系列特殊方法可以用来自定义在使用这些内建函数时类的行为。

* `__str__(self)` 定义对类的实例调用 str() 时的行为。
* `__repr__(self)` 定义对类的实例调用 repr() 时的行为。 str() 和 repr() 最主要的差别在于“目标用户”，repr() 的作用是产生机器可读的输出（大部分情况下，其输出可以作为有效的Python代码），而 str() 则产生人类可读的输出。
* `__dir__(self)` 定义对类的实例调用 dir() 时的行为，这个方法应该向调用者返回一个属性列表。如果重定义了 `__getattr__` 或者使用动态生成的属性，以实现类的交互式使用，那么这个方法是必不可少的。

## 属性控制

    __getattr__(self, name)

当用户试图访问一个根本不存在（或者暂时不存在）的属性时，你可以通过这个魔法方法来定义类的行为。

## 自定义序列

有许多办法可以让 Python 类表现得像是内建序列类型（字典，元组，列表，字符串等）。

在Python中实现自定义容器类型需要用到一些协议。首先，不可变容器类型有如下协议：想实现一个不可变容器，你需要定义 `__len__` 和 `__getitem__`。可变容器的协议除了上面提到的两个方法之外，还需要定义 `__setitem__` 和 `__delitem__` 。如果你想让你的对象可以迭代，你需要定义 `__iter__` ，这个方法返回一个迭代器。迭代器必须遵守迭代器协议，需要定义 `__iter__` （返回它自己）和 next 方法。

# 元类

`Python 中类也是一种对象`。只要你使用关键字class，Python解释器在执行的时候就会创建一个对象。于是乎你可以对它做如下的操作：

1. 你可以将它赋值给一个变量
2. 你可以拷贝它
3. 你可以为它增加属性
4. 你可以将它作为函数参数进行传递

**元类就是用来创建类的“东西”**。你创建类就是为了创建类的实例对象，但是我们已经学习到了Python中的类也是对象。好吧，元类就是用来创建这些类（对象）的，元类就是类的类。

更多详细内容见 [Python_Metaclass.md](More/Python_Metaclass.md)

# 更多阅读

[Python @classmethod and @staticmethod for beginner?](http://stackoverflow.com/questions/12179271/python-classmethod-and-staticmethod-for-beginner)  
[Difference between @staticmethod and @classmethod in Python](http://pythoncentral.io/difference-between-staticmethod-and-classmethod-in-python/)  
[Python Object Oriented](http://www.tutorialspoint.com/python/python_classes_objects.htm)  
[A Guide to Python's Magic Methods](http://www.rafekettler.com/magicmethods.html)  
[类和实例——廖雪峰的官方网站](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/00138682004077376d2d7f8cc8a4e2c9982f92788588322000)  
[Python面向对象详解](http://blog.csdn.net/carolzhang8406/article/details/6903556)  
[知乎：supper 方法](https://www.zhihu.com/question/20040039)  
[NewClass Vs ClassicClass](https://wiki.python.org/moin/NewClassVsClassicClass)  
[python类学习以及mro--多继承属性查找机制](http://blog.csdn.net/imzoer/article/details/8737642)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Class_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Class_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Class_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Class_4.png


