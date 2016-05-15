面向对象重要的概念就是类（Class）和实例（Instance），必须牢记类是抽象的模板，比如Student类，而实例是根据类创建出来的一个个具体的“对象”，每个对象都拥有相同的方法，但各自的数据可能不同。

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
    
这个self和cls是对类或者实例的绑定，对于一般的函数来说我们可以这么调用foo(x)，这个函数就是最常用的，它的工作跟任何东西(类，实例)无关。

对于实例方法，我们知道在类里每次定义方法的时候都需要绑定这个实例，就是foo(self, x)。为什么要这么做呢？因为实例方法的调用离不开实例，我们需要把实例自己传给函数，调用的时候是这样的a.foo(x)(其实是foo(a, x))。类方法一样，只不过它传递的是类而不是实例，A.class_foo(x)。注意这里的self和cls可以替换别的参，但是python的约定是这俩，还是不要改的好。

对于静态方法其实和普通的方法一样，不需要对谁进行绑定，唯一的区别是调用的时候需要使用a.static_foo(x) 或者 A.static_foo(x)来调用。（Staticmethods are used to group functions which have some logical connection with a class to the class.）

|       | 实例方法 | 类方法           |  静态方法           |
|-------| --------| -------         |  -------          |
|a = A()| a.foo(x)| a.class_foo(x)  |  a.static_foo(x)  |
| A     | 不可用   | A.class_foo(x)  |  A.static_foo(x)  |

参考：  
[What is the difference between @staticmethod and @classmethod in Python?](http://stackoverflow.com/questions/136097/what-is-the-difference-between-staticmethod-and-classmethod-in-python)

# Python 类变量

    class Person:
        name="aaa"
    
    p1=Person()
    p2=Person()
    p1.name="bbb"
    print p1.name  # bbb
    print p2.name  # aaa
    print Person.name  # aaa

类变量就是供类使用的变量，实例变量就是供实例使用的。

这里p1.name="bbb"是实例调用了类变量，p1.name一开始是指向的类变量name="aaa"，但是在实例的作用域里把类变量的引用改变了，就变成了一个实例变量。self.name不再引用Person的类变量name了。

    class Person:
        name=[]
    
    p1=Person()
    p2=Person()
    p1.name.append(1)
    print p1.name  # [1]
    print p2.name  # [1]
    print Person.name  # [1]

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
[A Guide to Python's Magic Methods](http://www.rafekettler.com/magicmethods.html)  
[类和实例——廖雪峰的官方网站](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/00138682004077376d2d7f8cc8a4e2c9982f92788588322000)  


