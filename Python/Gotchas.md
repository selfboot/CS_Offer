Python 简单，但又危机四伏，充满陷阱，下面列出一些常见的陷阱，来更好地理解 Python。

# 函数参数带默认值

下面一段代码：

    >>> def append(list=[]):
    ...     # append the length of a list to the list
    ...     list.append(len(list))
    ...     return list
    ...
    >>> append(['a','b'])
    ['a', 'b', 2]
    >>>
    >>> append()  # calling with no arg uses default list value of []
    [0]
    >>>
    >>> append()  # but what happens when we AGAIN call append with no arg?

关于这点，[文档](https://docs.python.org/2.7/tutorial/controlflow.html#default-argument-values)上着重给出警告，如下：

> Important warning: The default value is evaluated only once. This makes a difference when the default is a mutable object such as a list, dictionary, or instances of most classes.

这是因为：

> Default parameter values are evaluated when the function definition is executed. This means that the expression is evaluated once, when the function is defined, and that the same “pre-computed” value is used for each call. 

    >>> append()  # first call with no arg uses default list value of []
    [0]
    >>> append()  # but then look what happens...
    [0, 1]
    >>> append()  # successive calls keep extending the same default list!
    [0, 1, 2]
    >>> append()  # and so on, and so on, and so on...
    [0, 1, 2, 3]

理解了？再来看一个例子：

    >>>import time
    >>> def report(when=time.time()):
    ...     print when
    ...
    >>> report()
    1210294387.19
    >>> time.sleep(5)
    >>> report()
    1210294387.19

# 类变量的使用

对于下面的程序

    class AAA(object):
        x = 1
    
    class BBB(AAA):
        pass
    
    class CCC(AAA):
        pass

    # AAA: {'x': 1}, BBB: {}, CCC: {}
    >>> print AAA.x, BBB.x, CCC.x
    1 1 1

一切正常，BBB, CCC 继承了 AAA 的属性。

    >>> BBB.x = 2
    # AAA: {'x': 1}, BBB: {'x': 2}, CCC: {}
    >>> print AAA.x, BBB.x, CCC.x
    1 2 1

这里改变 B 的属性值，然后进行下面的操作：

    >>> AAA.x = 3
    # AAA: {'x': 3}, BBB: {'x': 2}, CCC: {}
    >>> print AAA.x, BBB.x, CCC.x
    3 2 3

这是因为在Python里，类变量通常在内部被当做字典来处理并遵循通常所说的方法解析顺序（Method Resolution Order (MRO)）。因此在上面的代码中，因为属性x在类C中找不到，因此它会往上去它的基类中查找（在上面的例子中只有A这个类，当然Python是支持多重继承的）。

换句话说，C没有它自己独立于A的属性x。因此对C.x的引用实际上是对A.x的引用。B.x不是对A.x的引用是因为在第二步里B.x=2将B.x引用到了2这个对象上，倘若没有如此，B.x仍然是引用到A.x上的。

结合下面的例子来更好地理解：

    class AAA(object):
        x = [1]
    
    ...
    
    >>> AAA.x, BBB.x, CCC.x
    [1], [1], [1]
    >>> CCC.x.append(2)
    >>> AAA.x, BBB.x, CCC.x
    ([1, 2], [1, 2], [1, 2])
    >>> BBB.x = ['a']
    >>> AAA.x, BBB.x, CCC.x
    ([1, 2], ['a'], [1, 2])

# lambda 参数捕获

    >>> flist = []
    >>> for i in range(3):
    ...     flist.append(lambda: i)
    ...
    >>> [f() for f in flist]   
    # what will this print out?
    
输出结果为 [2, 2, 2]，这其中的奥妙在于**lambda 表达式中的 x 是一个自由变量，在运行时绑定值，而不是定义时就绑定，这跟函数的默认值参数定义是不同的**。因此在调用这个 lambda 表达式的时候，x 的值是执行时的值。

如果想让某个匿名函数在定义时就捕获到值，可以将那个参数值定义成默认参数即可，如下：

    >>> flist = []
    >>> for i in range(3):
    ...     flist.append(lambda i = i : i)
    ...
    >>> [f() for f in flist]
    [0, 1, 2]

# 创建嵌套数组

    >>> # INITIALIZING AN ARRAY -- METHOD 1
    ...
    >>> x = [[1,2,3,4]] * 3
    >>> x
    [[1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]]
    >>>
    >>>
    >>> # INITIALIZING AN ARRAY -- METHOD 2
    ...
    >>> y = [[1,2,3,4] for _ in range(3)]
    >>> y
    [[1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]]
    >>>
    >>> # WHICH METHOD SHOULD YOU USE AND WHY?

结论：第一种方法，列表x的3个元素指向同一个对象，第二种方法，列表y有3个元素，每个是一个独立的列表。

    >>> # MODIFYING THE x ARRAY FROM THE PRIOR CODE SNIPPET:
    >>> x[0][3] = 99
    >>> x
    [[1, 2, 3, 99], [1, 2, 3, 99], [1, 2, 3, 99]]
    >>> # UH-OH, DON’T THINK YOU WANTED THAT TO HAPPEN!
    ...
    >>>
    >>> # MODIFYING THE y ARRAY FROM THE PRIOR CODE SNIPPET:
    >>> y[0][3] = 99
    >>> y
    [[1, 2, 3, 99], [1, 2, 3, 4], [1, 2, 3, 4]]
    >>> # THAT’S MORE LIKE WHAT YOU EXPECTED!

这是因为：

> When building a new list by multiplying, Python copies each item by reference. This poses a problem for mutable items, for instance in a multidimensional array where each element is itself a list.   
>  From [The section "List creation shortcuts" on the Python Programming/Lists wikibook](https://en.wikibooks.org/wiki/Python_Programming/Lists#List%5Fcreation%5Fshortcuts) 

# 捕捉多个异常

如果想捕捉多个异常，假如下面的代码：

    >>> try:
    ...     int("z")
    ... except IndexError, ValueError:
    ...     pass
    ...
    Traceback (most recent call last):
      File "<stdin>", line 2, in <module>
    ValueError: invalid literal for int() with base 10: 'z'

这里的问题在于except语句不会像这样去接受一系列的异常。并且，在Python 2.x里面，语法except Exception, e是用来将异常和这个可选的参数绑定起来（即这里的e），以用来在后面查看的。因此，在上面的代码中，IndexError异常不会被except语句捕捉到；而最终ValueError这个异常被绑定在了一个叫做IndexError的参数上。

在except语句中捕捉多个异常的正确做法是将所有想要捕捉的异常放在一个元组（tuple）里并作为第一个参数给except语句。并且，为移植性考虑，使用as关键字，因为Python 2和Python 3都支持这样的语法，例如：

    >>> try:
    ...     int("z")
    ... except (IndexError, ValueError) as e:
    ...     print e
    ...

# LEGB 作用域解析

Python的作用域解析是基于叫做LEGB（Local（本地），Enclosing（封闭），Global（全局），Built-in（内置））的规则进行操作的。看下面的例子

    >>> x = 10
    >>> def foo():
    ...     x += 1
    ...     print x
    ...
    >>> foo()
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "<stdin>", line 2, in foo
    UnboundLocalError: local variable 'x' referenced before assignment

这是因为，在**一个作用域里面给一个变量赋值的时候，Python自动认为这个变量是这个作用域的本地变量，并屏蔽作用域外的同名的变量。**很多时候可能在一个函数里添加一个赋值的语句会让你从前本来工作的代码得到一个`UnboundLocalError`。

下面的是文档中的解释：

> This is because when you make an assignment to a variable in a scope, that variable becomes local to that scope and shadows any similarly named variable in the outer scope. 

在使用列表（lists）的时候，很容易就触发这种错误。看下面这个例子：

    >>> lst = [1, 2, 3]
    >>> def foo1():
    ...     lst.append(5)   # 这没有问题...
    ...
    >>> foo1()
    >>> lst
    [1, 2, 3, 5]
     
    >>> lst = [1, 2, 3]
    >>> def foo2():
    ...     lst += [5]      # ... 这就有问题了！
    ...
    >>> foo2()
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "<stdin>", line 2, in foo
    UnboundLocalError: local variable 'lst' referenced before assignment

# 遍历同时修改列表

这个错误应该比较明显：

    >>> odd = lambda x : bool(x % 2)
    >>> numbers = [n for n in range(10)]
    >>> for i in range(len(numbers)):
    ...     if odd(numbers[i]):
    ...         del numbers[i]  # 这不对的：在遍历列表时删掉列表的元素。
    ...
    Traceback (most recent call last):
      	  File "<stdin>", line 2, in <module>
    IndexError: list index out of range

遍历一个列表或者数组的同时又删除里面的元素，对任何有经验的软件开发人员来说这是个很明显的错误。但是像上面的例子那样明显的错误，也可能不经意间在更加复杂的程序中出现。可以使用内置函数 filter 来避免上面的问题：

    >>> numbers = [n for n in range(10)]
    >>> odd = list(filter(lambda x: x % 2==0, numbers))
    >>> odd
    [0, 2, 4, 6, 8]

# 循环加载模块

假设你有两个文件，a.py和b.py，在这两个文件中互相加载对方，例如：

在a.py中：

    import b
    def f():
        return b.x
    print f()

在b.py中：

    import a
    x = 1
    def g():
        print a.f()

首先，我们试着加载a.py：

    >>> import a
    1

**没有问题**。事实上在Python中仅仅是表面上的出现循环加载并不是什么问题。如果一个模块已经被加载了，Python不会傻到再去重新加载一遍。但是，当每个模块都想要互相访问定义在对方里的函数或者变量时，问题就来了。

回到之前的例子，当我们加载a.py时，它再加载b.py不会有问题，因为在加载b.py时，它并不需要访问a.py的任何东西。b.py中唯一的引用就是调用a.f()，这个调用是在函数g()中完成的，但是a.py或者b.py中没有人调用g()，所以并没有导致错误。

但是当我们首先试图加载b.py时（之前没有加载a.py），会发生什么呢：

    >>> import b
    Traceback (most recent call last):
      	  File "<stdin>", line 1, in <module>
      	  File "b.py", line 1, in <module>
        import a
      	  File "a.py", line 6, in <module>
    	print f()
      	  File "a.py", line 4, in f
    	return b.x
    AttributeError: 'module' object has no attribute 'x'

这里问题出在加载b.py的过程中，Python试图加载a.py，并且在a.py中需要调用到f()，而函数f()又要访问到b.x，但是这个时候b.x却还没有被定义。这就产生了`AttributeError异常`。

解决的方案可以做一点细微的改动。改一下b.py，使得它在g()里面加载a.py：

    x = 1
    def g():
        import a	# 只有当g()被调用的时候才加载
        print a.f()

这会儿当我们加载b.py的时候，一切正常：

    >>> import b
    >>> b.g()
    1	# 第一次输出，因为模块a在最后调用了‘print f()’
    1	# 第二次输出，这是我们调用g

# 不可变对象 tuple 的赋值

我们知道 tuple 是不可变对象，所以下面的程序运行正常：

    >>> a_tuple = (1, 2)
    >>> a_tuple[0] += 1
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'tuple' object does not support item assignment
    >>> a_tuple
    (1, 2)

`a_tuple[0] += 1` 理所当然地引起异常，它实际上和下面的语句等效：

    >>> result = a_tuple[0] + 1
    >>> a_tuple[0] = result
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'tuple' object does not support item assignment

那么，再来看下面的代码：

    >>> a_tuple = (['foo'], 'bar')
    >>> a_tuple[0] += ['item']
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'tuple' object does not support item assignment

到这里也没有问题，tuple 不可变，对其进行赋值会引起异常。但是，当我们读取 a_tuple 的值时，发现它被改变了，如下：

    >>> a_tuple
    (['foo', 'item'], 'bar')

为了解释这里的怪异现象，需要知道以下两点：

1. 如果一个对象实现了 Magic Method: `__iadd__`，当使用 += 操作符时实际调用了该函数，`然后返回值被用于赋值操作`；
2. 对于 list 来说，`__iadd__` 等同于 extend 方法。

所以

    >>> a_list = []
    >>> a_list += [1]
    >>> a_list
    [1]

等同于下面的句子：

    >>> result = a_list.__iadd__([1])
    >>> a_list = result     # 赋值操作

这里 a_list 指向的对象已经被改变，result 指向改变后的对象，然后 a_list 又指向 result。这里 `a_list = result` 其实没有任何意义，因为 a_list 和 result 本来就是指向同一个对象。但是，这个赋值操作确实存在。这就可以解释上面的错误了：

    >>> result = a_tuple[0].__iadd__(['item'])
    >>> a_tuple[0] = result
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    TypeError: 'tuple' object does not support item assignment

__iadd__ 操作没有问题，成功了添加了元素。接着，虽然 result 和 a_tuple[0] 已经指向了同一个对象，不过赋值操作依旧存在，又因为 tuple 是不可变对象，所以导致抛出异常。

如果改用 extend 就不会有这个问题，如下：

    >>> a_tuple = (['foo'], 'bar')
    >>> a_tuple[0].extend(['item'])
    >>> a_tuple
    (['foo', 'item'], 'bar')

# 更多阅读
[Python 2.x gotcha's and landmines](http://stackoverflow.com/questions/530530/python-2-x-gotchas-and-landmines)  
[The Vital Guide to Python Interviewing](https://www.toptal.com/python)  
[Python函数参数默认值的陷阱和原理深究](http://cenalulu.github.io/python/default-mutable-arguments/)  
[Default Parameter Values in Python](http://effbot.org/zone/default-values.htm)  
[Python Gotchas](http://www.ferg.org/projects/python_gotchas.html)  
[Python程序员的10个常见错误](http://python.jobbole.com/68256/)  
[Why am I getting an UnboundLocalError when the variable has a value?](https://docs.python.org/2/faq/programming.html#why-am-i-getting-an-unboundlocalerror-when-the-variable-has-a-value)  
[Programming FAQ](https://docs.python.org/2/faq/programming.html)  

