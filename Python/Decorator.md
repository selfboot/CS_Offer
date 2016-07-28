

# 应用场景

日常开发过程中哪些地方可以用装饰器呢？

* 分析、日志：对于大型应用，我们常常需要记录应用的状态，以及测量不同活动的数量。通过将这些特别的事件包装到函数或方法中，装饰器在满足这些需求的同时，还能保证代码的可读性。
* 验证以及运行时检查：Python 是一种强类型语言，但是变量的类型却是动态变化的。虽然这会带来很多好处，但是同时这也意味着更容易引入 bug。对于静态语言，例如 Java，这些 bug 在编译阶段就可以被发现。因而你可能希望对传入或返回的数据进行一些自定义的的检查，装饰器可以非常容易地实现这个需求。
* 创建框架：一旦掌握了如何写装饰器，就能够从其简单的语法中获益颇丰，你可以为语言添加新的语义使其使用更加简单，甚至可以自己扩展 Python 语法。事实上，很多开源框架都是使用的这样的方式。Web 应用框架 Flask 就是使用装饰器将不同 URL 路由注册到不同处理函数的。

## 类装饰器的使用

### @classmethod

classmethod(fn)表明函数fn是类的函数而非类实例的函数，在语法上，它要求fn的函数签名至少要有1个参数，函数被调用时，解释器会将类作为第1个参数传给fn。

    class C():
        def fn_classmethod(cls, var):
            print cls, var
        fn = classmethod(fn_classmethod)
    
    print C.fn
    C.fn(2)

在Python语法中，@classmethod是一种实现自动调用classsmethod(fn_classmethod)的语法糖，它实现的功能与上述示例代码一致，只是看起来更精简且更pythonic而已：

    class C():
        @classmethod
        def fn_classmethod(cls, var):
            print cls, var
    
    C.fn_classmethod(2)
    # __main__.C, 2

### @staticmethod

staticmethod(fn)表明函数fn是类的静态方法。具体到类定义体内某个函数的定义上，如果该函数想声明称静态成员，则只需在其定义体前加上"@staticmethod"这行，利用装饰器语法糖来实现staticmethod(cls.fun)的目的。示例如下：

    class C(object):  
        @staticmethod  
        def f(arg1, arg2, ...):  
            ...  

与classmethod的装饰器语法糖类似，@staticmethod会自动调用staticmethod(f)。Python中类静态方法的语义跟C++/Java类似，即类的静态成员属于类本身，不属于类的实例，它无法访问实例的属性（数据成员或成员函数）。定义为staticmethod的函数被调用时，解释器不会自动为其隐式传入类或类实例的参数，它的实际参数列表与调用时显式传入的参数列表保持一致。


### @property

C++ 中可以用 set 和 get 函数控制对类的成员变量的访问权限，python 中也有类似的机制，可以控制对属性的访问权限，可以通过 Python内置的@property装饰器来做到这点。

    class Student(object):
    
        @property
        def score(self):
            return self.__score
    
        @score.setter
        def score(self, value):
            if not isinstance(value, int):
                raise ValueError('score must be an integer!')
            if value < 0 or value > 100:
                raise ValueError('score must between 0 ~ 100!')
            self.__score = value

把一个getter方法变成属性，只需要加上@property就可以了，此时，@property本身又创建了另一个装饰器@score.setter，负责把一个setter方法变成属性赋值。于是，我们就拥有一个可控的属性操作：

    >>> s = Student()
    >>> s.score = 60 # OK，实际转化为s.set_score(60)
    >>> s.score # OK，实际转化为s.get_score()
    60
    >>> s.score = 9999
    Traceback (most recent call last):
      ...
    ValueError: score must between 0 ~ 100!

还可以定义只读属性，只定义getter方法，不定义setter方法就是一个只读属性：

    class Student(object):
    
        @property
        def birth(self):
            return self.__birth
    
        @birth.setter
        def birth(self, value):
            self.__birth = value
    
        @property
        def age(self):
            return 2014 - self.__birth

上面的birth是可读写属性，而age就是一个只读属性，因为age可以根据birth和当前时间计算出来。@property广泛应用在类的定义中，可以让调用者写出简短的代码，同时保证对参数进行必要的检查，这样，程序运行时就减少了出错的可能性。


# 更多阅读
[How you implemented your Python decorator is wrong](https://github.com/GrahamDumpleton/wrapt/blob/master/blog/01-how-you-implemented-your-python-decorator-is-wrong.md)  
[python装饰器详解](http://selfboot.cn/2014/08/10/python_decorator/)  
[5个理由告诉你为什么要学习使用Python装饰器](http://python.jobbole.com/85393/)  
[How does the @property decorator work?](http://stackoverflow.com/questions/17330160/how-does-the-property-decorator-work)  
[Python进阶之属性（property）详解](http://python.jobbole.com/80955/)  
[Python @property](http://www.programiz.com/python-programming/property)  





