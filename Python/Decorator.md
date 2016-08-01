# 函数是对象

**python中一切都是对象，这里需要强调[`函数是对象`](id:func_is_obj)。**为了更好地理解函数也是对象，下面结合代码片段来说明这一点。
	
	def shout(word="yes"):
	    return word.capitalize() + "!"
	
	print shout()
	# outputs: Yes!
	
	"""
	As an object, you can assign the function to a variable like any other object.
	Notice we don't use parentheses: we are not calling the function,
	we are putting the function "shout" into the variable "scream".
	"""
	scream = shout
	
	print scream()
	# outputs: Yes!
	
	"""
	More than that, it means you can remove the old name 'shout',
	and the function will still be accessible from 'scream'.
	"""
	del shout
	try:
	    print shout()
	except NameError, e:
	    print e
	    # outputs: name 'shout' is not defined
	
	print scream()
	# outputs: 'Yes!'

因为[函数是对象](#func_is_obj)，所以python中函数还有一个有趣的特性：[`函数可以被定义在另一个函数中`](id:func_in_func)。下面来看一个简单的例子。

	def talk():
	
	    # You can define a function on the fly in "talk"
	    def whisper(word="yes"):
	        return word.lower()+"..."
	    print whisper()
	
	"""
	You call "talk", that defines "whisper" EVERY TIME you call it,
	then "whisper" is called in "talk".
	"""
	talk()
	# outputs: yes...
	
	# But "whisper" DOES NOT EXIST outside "talk".
	try:
	    print whisper()
	except NameError, e:
	    print e
	    # outputs : name 'whisper' is not defined

# 函数作为参数和返回值

[前面](#func_is_obj)已经知道函数是对象。那么：

1. 可以被赋给另一个变量
2. 可以被定义在另一个函数里

这也意味着，`一个函数可以返回另一个函数`，下面看一个简单的例子。

	def get_talk(kind="shout"):
	
	    def whisper(word="yes"):
	        return word.lower() + "..."
	
	    def shout(word="yes"):
	        return word.capitalize() + "!"
	
	    return whisper if kind == "whisper" else shout
	
	# Get the function and assign it to a variable
	talk = get_talk()
	
	# You can see that "talk" is here a function object:
	print talk
	# outputs : <function shout at 0x107ae9578>
	
	print talk()
	# outputs : Yes!
	
	# And you can even use it directly if you feel wild:
	print get_talk("whisper")()
	# outputs : yes...

我们来进一步挖掘一下函数的特性，既然可以`返回函数`，那么我们也可以把`函数作为参数传递`。

	def whisper(word="yes"):
	    return word.lower() + "..."
	
	
	def do_something_before(func):
	    print "I do something before."
	    print "Now the function you gave me:\n", func()
	
	do_something_before(whisper)
	"""outputs
	I do something before.
	Now the function you gave me:
	yes...
	"""

现在，了解装饰器所需要的所有要点我们已经掌握了，通过上面的例子，我们还可以看出，装饰器其实就是`封装器`，可以让我们在不修改原函数的基础上，在执行原函数的前后执行别的代码。

# 手工装饰器

下面我们[手工实现一个简单的装饰器](id:handcrafted_decorator)。

	def my_shiny_new_decorator(a_function_to_decorate):
	
	    """
	    Inside, the decorator defines a function on the fly: the wrapper.
	    This function is going to be wrapped around the original function
	    so it can execute code before and after it.
	    """
	    def the_wrapper_around_the_original_function():
	
	        """
	        Put here the code you want to be executed BEFORE the original
	        function is called
	        """
	        print "Before the function runs"
	
	        # Call the function here (using parentheses)
	        a_function_to_decorate()
	
	        """
	        Put here the code you want to be executed AFTER the original
	        function is called
	        """
	        print "After the function runs"
	
	    """
	    At this point, "a_function_to_decorate" HAS NEVER BEEN EXECUTED.
	    We return the wrapper function we have just created.
	    The wrapper contains the function and the code to execute before
	    and after. It’s ready to use!
	    """
	    return the_wrapper_around_the_original_function
	
	
	# Now imagine you create a function you don't want to ever touch again.
	def a_stand_alone_function():
	    print "I am a stand alone function, don't you dare modify me"
	
	a_stand_alone_function()
	# outputs: I am a stand alone function, don't you dare modify me
	
	"""
	Well, you can decorate it to extend its behavior.
	Just pass it to the decorator, it will wrap it dynamically in
	any code you want and return you a new function ready to be used:
	"""
	
	a_stand_alone_function_decorated = my_shiny_new_decorator(a_stand_alone_function)
	a_stand_alone_function_decorated()
	"""outputs:
	Before the function runs
	I am a stand alone function, don't you dare modify me
	After the function runs
	"""

现在，如果我们想每次调用`a_stand_alone_function`的时候，实际上调用的是封装后的函数`a_stand_alone_function_decorated`，那么只需要用a_stand_alone_function去覆盖my_shiny_new_decorator返回的函数即可。也就是：

```python
a_stand_alone_function = my_shiny_new_decorator(a_stand_alone_function)
```

# 简单装饰器

对于[前面的例子](#handcrafted_decorator)，如果用装饰器语法，可以添加如下：

	@my_shiny_new_decorator
	def another_stand_alone_function():
	    print "Leave me alone"
	
	another_stand_alone_function()
	"""outputs:
	Before the function runs
	Leave me alone
	After the function runs
	"""

对了，这就是装饰器语法，这里的`@my_shiny_new_decorator`是`another_stand_alone_function = my_shiny_new_decorator(another_stand_alone_function)`的简写，是Python的语法糖。

装饰器只是[装饰器设计模式](http://en.wikipedia.org/wiki/Decorator_pattern)的python实现，python还存在其他几个经典的设计模式，以方便开发，例如迭代器iterators。

当然了，我们也可以嵌套装饰器。

	def bread(func):
	    def wrapper():
	        print "</''''''\>"
	        func()
	        print "<\______/>"
	
	    return wrapper
	
	
	def ingredients(func):
	    def wrapper():
	        print "#tomatoes#"
	        func()
	        print "~salad~"
	
	    return wrapper
	
	
	def sandwich(food="--ham--"):
	    print food
	
	sandwich()
	# outputs: --ham--
	sandwich = bread(ingredients(sandwich))
	sandwich()
	"""outputs:
	</''''''\>
	 #tomatoes#
	 --ham--
	 ~salad~
	<\______/>
	"""

用python的装饰器语法，如下：

	@bread
	@ingredients
	def sandwich_2(food="--ham_2--"):
	    print food
	
	sandwich_2()

放置装饰器的位置很关键。

	@ingredients
	@bread
	def strange_sandwich(food="--ham--"):
	    print food
	
	strange_sandwich()
	"""outputs:
	#tomatoes#
	</''''''\>
	 --ham--
	<\______/>
	 ~salad~
	"""

# 装饰器高级用法

**当我们调用装饰器返回的函数时，其实是在调用封装函数，给封装函数传递参数也就同样的给被装饰函数传递了参数。**

	def a_decorator_passing_arguments(function_to_decorate):
	    def a_wrapper_accepting_arguments(arg1, arg2):
	        print "I got args! Look:", arg1, arg2
	        function_to_decorate(arg1, arg2)
	    return a_wrapper_accepting_arguments
	
	"""
	Since when you are calling the function returned by the decorator, you are
	calling the wrapper, passing arguments to the wrapper will let it pass them to
	the decorated function
	"""
	
	
	@a_decorator_passing_arguments
	def print_full_name(first_name, last_name):
	    print "My name is", first_name, last_name
	
	
	print_full_name("Peter", "Venkman")
	"""outputs:
	I got args! Look: Peter Venkman
	My name is Peter Venkman
	"""

## 装饰类方法

python中函数和类方法几乎一样，除了类方法中第一个参数是指向当前对象的引用(self)。这意味着我们可以为类方法创建装饰器，只是要记得考虑self。

	def method_friendly_decorator(method_to_decorate):
	    def wrapper(self, lie):
	        lie = lie - 3
	        return method_to_decorate(self, lie)
	    return wrapper
	
	
	class Lucy(object):
	
	    def __init__(self):
	        self.age = 32
	
	    @method_friendly_decorator
	    def sayYourAge(self, lie):
	        print "I am %s, what did you think?" % (self.age + lie)
	
	l = Lucy()
	l.sayYourAge(-3)
	# outputs: I am 26, what did you think?

我们还可以创建一个通用的装饰器，可以用于所有的方法或者函数，而且不用考虑它的参数情况。这时候，我们要用到`*args, **kwargs`。

	def a_decorator_passing_arbitrary_arguments(function_to_decorate):
	    # The wrapper accepts any arguments
	    def a_wrapper_accepting_arbitrary_arguments(*args, **kwargs):
	        print "Do I have args?:"
	        print args
	        print kwargs
	        # Then you unpack the arguments, here *args, **kwargs
	        # If you are not familiar with unpacking, check:
	        # http://www.saltycrane.com/blog/2008/01/how-to-use-args-and-kwargs-in-python/
	        function_to_decorate(*args, **kwargs)
	    return a_wrapper_accepting_arbitrary_arguments

另外还有一些高级用法，这里不做详细说明，可以在[How can I make a chain of function decorators in Python?](https://stackoverflow.com/questions/739654/how-can-i-make-a-chain-of-function-decorators-in-python)进一步深入了解装饰器。

# 装饰器内置封装 wraps

装饰器封装了函数，这使得调试函数变得困难。不过在python 2.5引入了`functools`模块，它包含了`functools.wraps()`函数，这个函数可以将被封装函数的名称、模块、文档拷贝给封装函数。有趣的是，functools.wraps是一个装饰器。为了更好地理解，看以下代码：

	# For debugging, the stacktrace prints you the function __name__
	def foo():
	    print "foo"
	
	print foo.__name__
	# outputs: foo
	
	
	def bar(func):
	    def wrapper():
	        print "bar"
	        return func()
	    return wrapper
	
	
	@bar
	def foo():
	    print "foo"
	
	print foo.__name__
	# outputs: wrapper
	
	
	import functools
	
	
	def bar(func):
	    # We say that "wrapper", is wrapping "func"
	    # and the magic begins
	    @functools.wraps(func)
	    def wrapper():
	        print "bar"
	        return func()
	    return wrapper
	
	
	@bar
	def foo():
	    print "foo"
	
	print foo.__name__
	# outputs: foo

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
[Python修饰器的函数式编程](http://coolshell.cn/articles/11265.html)


