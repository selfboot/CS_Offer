# Python 类

## Python 类方法

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

## Python 类变量

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

## 元类

`Python 中类也是一种对象`。只要你使用关键字class，Python解释器在执行的时候就会创建一个对象。于是乎你可以对它做如下的操作：

1. 你可以将它赋值给一个变量
2. 你可以拷贝它
3. 你可以为它增加属性
4. 你可以将它作为函数参数进行传递

**元类就是用来创建类的“东西”**。你创建类就是为了创建类的实例对象，但是我们已经学习到了Python中的类也是对象。好吧，元类就是用来创建这些类（对象）的，元类就是类的类。

更多详细内容见 [Python_Metaclass.md](More/Python_Metaclass.md)

# python 性能调优

1. 选择合适的数据结构。

    `字典 (dictionary) 与列表 (list)`：Python 字典中使用了 hash table，因此查找操作的复杂度为 O(1)，而 list 实际是个数组，在 list 中，查找需要遍历整个 list，其复杂度为 O(n)，因此对成员的查找访问等操作字典要比 list 更快。
    
    `集合 (set) 与列表 (list)`：set 的 union， intersection，difference 操作要比 list 的迭代要快。因此如果涉及到求 list 交集，并集或者差的问题可以转换为 set 来操作。

    * set(list1) | set(list2)：包含 list1 和 list2 所有数据的新集合
    * set(list1) & set(list2)：包含 list1 和 list2 中共同元素的新集合
    * set(list1) - set(list2)：在 list1 中出现但不在 list2 中出现的元素的集合

2. 使用列表解析（list comprehension）

    列表解析要比在循环中重新构建一个新的 list 更为高效。
    
        a = [w for w in list]
        
    比下面的循环高效：
        
        a = []
        for w in list: 
            a.append(w) 
            
3. 使用生成器表达式（generator expression）
    
    使用 xrange 可以节省大量的系统内存，因为 xrange() 在序列中每次调用只产生一个整数元素。而 range() 將直接返回完整的元素列表，用于循环时会有不必要的开销。在 python3 中 xrange 不再存在，里面 range 提供一个可以遍历任意长度的范围的 iterator。

4. 字符串的优化

    python 中的字符串对象是不可改变的，因此对任何字符串的操作如拼接，修改等都将产生一个新的字符串对象，而不是基于原字符串，因此这种持续的 copy 会在一定程度上影响 python 的性能。

    `使用 join 而不是 + 连接字符串`

    避免类似下面的代码片段：
    
        s = ""
        for x in list: 
            s += func(x)
    
    而是要使用下面这种：
 
        slist = [func(elt) for elt in somelist] 
        s = "".join(slist)

    当对字符串可以使用正则表达式或者内置函数来处理的时候，选择`内置函数`。如 str.isalpha()，str.isdigit()，str.startswith(('x', 'yz'))，str.endswith(('x', 'yz')) 等。

    对字符进行`格式化`比直接串联读取要快，因此要使用

        out = "<html>%s%s%s%s</html>" % (head, prologue, query, tail)

    而不是
    
        out = "<html>" + head + prologue + query + tail + "</html>"

5. 适当地函数式编程

    用 map, reduce 代替循环迭代。

        def toUpper(item):
              return item.upper()
        upper_name = map(toUpper, ["hao", "chen", "coolshell"])
        print upper_name
        # 输出 ['HAO', 'CHEN', 'COOLSHELL']

    对于map别忘了lambda表达式：可以简单地理解为这是一个inline的匿名函数。下面的lambda表达式相当于：`def func(x): return x*x`

        squares = map(lambda x: x * x, range(9))
        print squares
        # 输出 [0, 1, 4, 9, 16, 25, 36, 49, 64]

    下面的lambda表达式中有两个参数，也就是说每次从列表中取两个值，计算结果后把这个值再放回去，下面的表达式相当于：((((1+2)+3)+4)+5) ）

        print reduce(lambda x, y: x+y, [1, 2, 3, 4, 5])
        # 输出 15

    Python中的除了map和reduce外，还有一些别的如filter, find, all, any的函数做辅助，可以让代码更简洁，更易读，更高效。（没有了循环体，于是就可以少了些临时变量，以及变量倒来倒去的逻辑。）
    
参考：  
[Python 代码性能优化技巧](http://www.ibm.com/developerworks/cn/linux/l-cn-python-optim/)  
[函数式编程](http://coolshell.cn/articles/10822.html)

# Python 思想

## 生成器 与 yeild

当你建立了一个列表，你可以逐项地读取这个列表，这叫做一个可迭代对象。所有可以使用 for .. in .. 的对象都可以看作是一个`迭代器`。链表，字符串，文件都是迭代器，访问迭代器时首先把所有数据读进内存，然后用一个一个读取。

    >>> mylist = [x*x for x in range(3)]
    >>> for i in mylist:
    ...     print i
    ...
    0
    1
    4
    
如果数据量太大，并且只需要一次迭代一次的话，这样做并不合适，因此引入了`生成器`。生成器是可以迭代的，但是`只可以读取它一次`，因为它并不把所有的值放在内存中，它是实时地生成数据。

    >>> mygenerator = (x*x for x in range(3))
    >>> for i in mygenerator:
    ...     print i
    ...
    0
    1
    4
    >>> for i in mygenerator:
    ...     print i
    ...

看起来除了把 [] 换成 () 外没什么不同。但是，你不可以再次使用 for i in mygenerator , 因为生成器只能被迭代一次。

除了生成器表达式，还可以定义`生成器函数`，它的定义很像一个普通的函数，除了当它要生成一个值的时候，使用yield关键字而不是return。

当一个生成器函数调用yield，生成器函数的“状态”会被冻结，所有的变量的值会被保留下来，下一行要执行的代码的位置也会被记录，直到再次调用next()。一旦next()再次被调用，生成器函数会从它上次离开的地方开始。

参考：  
[What does the yield keyword do in Python?](http://stackoverflow.com/questions/231767/what-does-the-yield-keyword-do-in-python)

## 装饰器

python中一切都是对象，这里需要强调函数是对象，那么

* 可以被赋给另一个变量
* 可以被定义在另一个函数里
* 一个函数可以返回另一个函数
* 函数作为参数传递

当你在用某个@decorator来修饰某个函数func时，如下所示:

    @decorator
    def func():
        pass

其解释器会解释成下面这样的语句：

    func = decorator(func)

用装饰器实现缓存机制，避免斐波那契数列递归实现中的重复调用，代码如下：

    def cache(func):
        caches = {}
    
        @wraps(func)
        def wrap(*args):
            if args not in caches:
                caches[args] = func(*args)
    
            return caches[args]
        return wrap
    
    
    @cache
    def fib_cache(n):
        assert n > 0, 'invalid n'
        if n < 3:
            return 1
        else:
            return fib_cache(n - 1) + fib_cache(n - 2)
            
参考：   
[python装饰器详解](http://selfboot.cn/2014/08/10/python_decorator/)  
[Python修饰器的函数式编程](http://coolshell.cn/articles/11265.html)

## lambda 匿名函数

Python使用lambda关键字创造匿名函数。所谓匿名，意即不再使用def语句这样标准的形式定义一个函数。这种语句在调用时绕过函数的栈分配，可以提高效率。其语法是：

    lambda [arg1[, arg2, ... argN]]: expression

其中，参数是可选的，如果使用参数的话，参数通常也会在表达式之中出现。

    # 调用lambda函数
    >>> a = lambda x, y: x + y
    >>> a( 1, 3 )
    4
    >>> b = lambda x, y = 2: x + y
    >>> b( 1 )
    3
    >>> b( 1, 3 )
    4
    >>> c = lambda *z: z
    >>> c( 10, 'test')
    (10, 'test')

# Python 用法

## 排序函数

> `s.sort`：sort the items of s(mutable sequence types) in place.  Starting with Python 2.2, sorts are guaranteed to be stable.

用法如下

    sort([cmp[, key[, reverse]]])

其中：

* cmp：比较两个对象x和y，如果x > y返回正数，x < y 返回负数；x == y，返回0；比较什么由key决定。只适用于 python 2.x;
* key：用列表元素的某个属性和函数进行作为关键字，有默认值，迭代集合中的一项;
* reverse：排序规则, reverse = True(降序) 或者 reverse = False(升序，默认)

例如有一个数组，它的每一个成员是一个字典，然后根据字典中的属性来排序，如下：

    >>> persons=[{'name':'zhang3','age':15},{'name':'li4','age':12}]
    >>> persons.sort(lambda a,b: a['age']-b['age'])
    >>> persons
    [{'age': 12, 'name': 'li4'}, {'age': 15, 'name': 'zhang3'}]

`sorted`：Return a new sorted list from the items in iterable。

    sorted(iterable[, cmp[, key[, reverse]]])

sorted 中cmp, key, reverse 和 sort 的用法一样，不过它返回一个排序后的可迭代对象。例如给一个字典按照value值进行排序，如下：

    >>> d = {"a":1, "c":3, "d":4, "b":2, "e": 5}
    >>> sorted_d = sorted(d.items(), key=lambda i: i[1])
    >>> sorted_d
    [('a', 1), ('b', 2), ('c', 3), ('d', 4), ('e', 5)]

### key 的神级用法

> key parameter to specify a function to be called on each list element prior to making comparisons.  The value of the key parameter should be a function that takes a single argument and returns a key to use for sorting purposes. 

通俗点讲，**key 用来决定在排序算法中 cmp 比较的内容，key 可以是任何可被比较的内容，比如元组（python 中元组是可被比较的）**。

给定一个只包含大小写字母，数字的字符串，对其进行排序，保证：

* 所有的小写字母在大写字母前面，
* 所有的字母在数字前面
* 所有的奇数在偶数前面

像下面这样用 sorted 函数即可。

    >>> s = "Sorting1234"
    >>> "".join(sorted(s, key=lambda x: (x.isdigit(), x.isdigit() and int(x) % 2 == 0, x.isupper(), x.islower(), x)))
    'ginortS1324'

这里，lambda 函数将输入的字符转换为一个元组，然后 `sorted 函数将根据元组`（而不是字符）来进行比较，进而判断每个字符的前后顺序。这里可以理解为，根据字符生成的元组重新定义了排序的依据。

参考  
[Sorting Mini-HOW TO](https://wiki.python.org/moin/HowTo/Sorting)    
[python里方法sort()中cmp参数的用法](https://segmentfault.com/q/1010000000405289)  
[hackerrank: ginortS](https://www.hackerrank.com/challenges/ginorts/forum)  

# 深入 Python 机制
 
## Python 程序执行原理

简单来说，Python先把代码（.py文件）编译成字节码，交给字节码虚拟机，然后虚拟机一条一条执行字节码指令，从而完成程序的执行。这里字节码在Python虚拟机程序里对应的是PyCodeObject对象，.pyc文件是字节码在磁盘上的表现形式。

更多内容参见 [Python_HowToRun.md](More/Python_HowToRun.md)

## Python 垃圾回收机制

Python GC主要使用`引用计数（reference counting）`来跟踪和回收垃圾。在引用计数的基础上，通过“标记-清除”（mark and sweep）解决容器对象可能产生的循环引用问题，通过“分代回收”（generation collection）以空间换时间的方法提高垃圾回收效率。

1. 引用计数

    PyObject是每个对象必有的内容，其中ob_refcnt就是作为引用计数。当一个对象有新的引用时，它的ob_refcnt就会增加，当引用它的对象被删除，它的ob_refcnt就会减少。引用计数为0时，该对象生命就结束了。

    优点：简单、实时性
    缺点：维护引用计数消耗资源、循环引用

2. 标记-清除机制

    基本思路是先按需分配，等到没有空闲内存的时候从**寄存器和程序栈上的引用**出发，遍历以对象为节点、以引用为边构成的图，把所有可以访问到的对象打上标记，然后清扫一遍内存空间，把所有没标记的对象释放。

3. 分代技术

    分代回收的整体思想是：将系统中的所有内存块根据其存活时间划分为不同的集合，每个集合就成为一个“代”，垃圾收集频率随着“代”的存活时间的增大而减小，存活时间通常利用经过几次垃圾回收来度量。Python默认定义了三代对象集合，索引数越大，对象存活时间越长。

    当某些内存块M经过了3次垃圾收集的清洗之后还存活时，我们就将内存块M划到一个集合A中去，而新分配的内存都划分到集合B中去。当垃圾收集开始工作时，大多数情况都只对集合B进行垃圾回收，而对集合A进行垃圾回收要隔相当长一段时间后才进行，这就使得垃圾收集机制需要处理的内存少了，效率自然就提高了。在这个过程中，集合B中的某些内存块由于存活时间长而会被转移到集合A中，当然，集合A中实际上也存在一些垃圾，这些垃圾的回收会因为这种分代的机制而被延迟。

## 浅拷贝、深拷贝

首先需要搞清楚两个概念：赋值和引用，对于操作 target = source:

* 赋值操作：程序先新建对象target，然后将source的值拷贝到target中。这里，target和source值相同，但是它们是两个完全不同的对象。
* 引用操作：程序直接将target指向source，也就是说target和source是同一个对象，target只不过是source的一个别名。

`python中没有赋值，只有引用`。如果我们想拷贝一个对象，而不仅仅是创建一个引用，那么该如何操作呢？万能的python提供了两种拷贝机制`浅拷贝(shallow copy)、深拷贝(deep copy)`供我们选择，浅拷贝和深拷贝的唯一区别在于对嵌套对象的拷贝处理上。

对于嵌套对象比如说source = [1, 2, [3, 4]]，浅拷贝创建新的列表对象target，target中的所有元素均是source中元素的引用，也就是说target中的元素只是source中元素的别名。切片操作[start:end]属于浅拷贝。

深拷贝，其实就是递归拷贝。也就是说对于嵌套对象比如说source = [1, 2, [3, 4]]，深拷贝时创建新的列表对象target，然后递归地将source中的所有对象均拷贝到target中。即如果source中的元素是列表、字典等，那么python将拷贝这些列表、字典中的对象到target中去，就这样迭代下去，直到不存在嵌套结构。

参考  
[操作之灵魂——拷贝](http://selfboot.cn/2014/08/08/python_copy/)
   
## list的实现

类似于 C++ STL中 vector 的实现。在需要的时候扩容，但又不允许过度的浪费，适当地进行内存回收。

空间不够，或者利用率小于 50% 时，用下面计算方式重新分配空间：

    new_allocated = (newsize // 8) + (newsize < 9 and 3 or 6)
    # 调整后大小 (new_allocated) = 新元素数量 (newsize) + 预留空间 (new_allocated)


1. 当 newsize >= allocated，自然按照这个新的长度 "扩容" 内存。
2. 如果 newsize < allocated，且利用率低于一半：

    | allocated  | newsize  | new_size + new_allocated|
    |------------|----------|-------------------------|
    |10          |  4       | 4 + 3       |
    |20          |  9       | 9 + 7       |

参考     
[Python中list的实现](http://www.jianshu.com/p/J4U6rR)

##  Python 运行慢的原因
  
我们知道和 C/C++ 相比，Python效率确实不高，那么有哪些原因导致了Python 的低效呢？

1. Python 是动态类型，C++ 是静态类型；
2. Python 是解释型语言，C++是编译型的。
3. Python 的对象模型导致低效的内存访问。

参考  
[Why Python is Slow: Looking Under the Hood](https://jakevdp.github.io/blog/2014/05/09/why-python-is-slow/)  

# Python 常用库

## requests 库

`Requests` 是一个 HTTP 库，用 Python 编写，真正的为人类着想。Python 标准库中的 urllib2 模块提供了你所需要的大多数 HTTP 功能，但是它的 API 太渣了。它需要巨量的工作，甚至包括各种方法覆盖，来完成最简单的任务。

    >>> r = requests.get('https://api.github.com/user', auth=('user', 'pass'))
    >>> r.status_code
    200
    >>> r.headers['content-type']
    'application/json; charset=utf8'
    >>> r.encoding
    'utf-8'
    >>> r.text
    u'{"type":"User"...'

爬过豆瓣的音乐库，还有Coursera的课程下载脚本，还有V2EX的自动登录脚本。

`Beautiful Soup` 是一个可以从 HTML 或 XML 文件中提取数据的Python库。它能够通过你喜欢的转换器实现惯用的文档导航，查找，修改文档的方式。

使用BeautifulSoup解析一段 HTML 代码，得到一个 BeautifulSoup 的对象，然后就可以浏览结构化数据。

## matplotlib 库：

Matplotlib 是Python最流行的绘图库之一，使用起来非常方便，可以高度定制绘图模型，允许用户绘制点线图、条线图/直方图、3D图形，甚至是更复杂的图表。

pylab 是 matplotlib 面向对象绘图库的一个接口，考虑用默认配置在同一张图上绘制正弦和余弦函数图像，如下：

    from pylab import *
    
    X = np.linspace(-np.pi, np.pi, 256,endpoint=True)
    C,S = np.cos(X), np.sin(X)
    
    plot(X,C)
    plot(X,S)
    
    show()

## Numpy 库

Numpy 是一个用python实现的科学计算包。包括：

- 一个强大的N维数组对象Array；
- 比较成熟的函数库；
- 用于整合C/C++和Fortran代码的工具包；
- 实用的线性代数、傅里叶变换和随机数生成函数。

## SciPy 库

Scipy 是一个开源的Python算法库和数学工具包，SciPy包含的模块有最优化、线性代数、积分、插值、快速傅里叶变换其他科学与工程中常用的计算。

#  Python 中的函数式编程

函数式编程：不依赖于外部的数据，而且也不改变外部数据的值，而是返回一个新的值给你。
    
函数式编程的三大特性：

* immutable data 不可变数据：默认上变量是不可变的，如果你要改变变量，你需要把变量copy出去修改。这样一来，可以让你的程序少很多Bug。因为，程序中的状态不好维护，在并发的时候更不好维护。
* first class functions：这个技术可以让你的函数就像变量一样来使用。也就是说，你的函数可以像变量一样被创建，修改，并当成变量一样传递，返回或是在函数中嵌套函数。
* 尾递归优化：我们知道递归的害处，那就是如果递归很深的话，stack受不了，并会导致性能大幅度下降。所以，我们使用尾递归优化技术——每次递归时都会重用stack，这样一来能够提升性能，当然，这需要语言或编译器的支持。Python就不支持。  

参考

[关于 Python 的最全面试题](http://gold.xitu.io/entry/56010de260b27db45a4f845f)  
[How do I pass a variable by reference?](http://stackoverflow.com/questions/986006/how-do-i-pass-a-variable-by-reference)

