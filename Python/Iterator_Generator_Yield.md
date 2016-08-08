在了解Python的数据结构时，容器(container)、可迭代对象(iterable)、迭代器(iterator)、生成器(generator)、列表/集合/字典推导式(list,set,dict comprehension)众多概念参杂在一起，让人难以理解。其实完全可以用下面这幅图来理解它们之间的关系：

![][1]

# 容器(container)

容器是一种把多个元素组织在一起的数据结构，容器中的元素可以逐个地迭代获取，可以用in, not in关键字判断元素是否包含在容器中。通常这类数据结构把所有的元素存储在内存中（也有一些特列并不是所有的元素都放在内存）。在Python中，常见的容器对象有：

* list, deque, ....
* set, frozensets, ....
* dict, defaultdict, OrderedDict, Counter, ....
* tuple, namedtuple, …
* str

可以把容器看作是一个盒子、一栋房子、一个柜子，里面可以塞任何东西。从技术角度来说，当可以询问某个元素是否包含在其中时，那么就可以认为这个对象是一个容器，比如 list，set，tuples 都是容器对象：

尽管绝大多数容器都提供了某种方式来获取其中的每一个元素，但这并不是容器本身提供的能力，而是可迭代对象赋予了容器这种能力，当然并不是所有的容器都是可迭代的，比如：[Bloom filter](https://en.wikipedia.org/wiki/Bloom_filter)，虽然Bloom filter可以用来检测某个元素是否包含在容器中，但是并不能从容器中获取其中的每一个值，因为 Bloom filter 压根就没把元素存储在容器中，而是通过一个散列函数映射成一个值保存在数组中。

# 可迭代对象（Iterable）

给定一个list或tuple，可以通过for循环来遍历这个list或tuple，这种遍历称为迭代（Iteration）。在Python中，迭代是通过for ... in来完成的，而很多语言比如C或者Java，迭代list是通过下标完成的。

可以直接作用于for循环的数据类型有以下几种：

* 集合数据类型，如list/tuple/dict/set/str 等； 
* 生成器表达式或者带yield的generator function；
* 处于打开状态的files，sockets等。

这些可以直接作用于 for 循环的对象统称为`可迭代对象`：Iterable。可以使用 isinstance() 判断一个对象是否是可迭代对象：

    >>> from collections import Iterable
    >>> isinstance([], Iterable)
    True
    >>> isinstance({}, Iterable)
    True
    >>> isinstance('abc', Iterable)
    True
    >>> isinstance((x for x in range(10)), Iterable)
    True
    >>> isinstance(100, Iterable)
    False

可迭代对象和容器一样是一种通俗的叫法，并不是指某种具体的数据类型，list是可迭代对象，dict是可迭代对象，set也是可迭代对象。

# 迭代器（Iterator）

迭代器也是一个对象，用来表示一个数据流，可以被next()函数调用并不断返回下一个数据，直到没有数据时抛出StopIteration错误。可以把这个数据流看做是一个有序序列，但我们却不能提前知道序列的长度，只能不断通过next()函数实现按需计算下一个数据，所以Iterator的计算是惰性的，只有在需要返回下一个数据时它才会计算。

Iterator甚至可以表示一个无限大的数据流，例如全体自然数，而使用list是永远不可能存储全体自然数的。不过迭代器是有限制的：

* 不能向后移动
* 不能回到开始
* 无法复制一个迭代器。

因此要再次进行迭代只能重新生成一个新的迭代器对象。

Python 中只要可以被next()函数调用并不断返回下一个值，就是迭代器（Iterator）。可以使用isinstance()判断一个对象是否是 Iterator：

    >>> from collections import Iterator
    >>> isinstance((x for x in range(10)), Iterator)
    True
    >>> isinstance([x for x in range(10)], Iterator)
    False
    >>> isinstance([], Iterator)
    False
    >>> isinstance({}, Iterator)
    False
    >>> isinstance('abc', Iterator)
    False

生成器都是Iterator对象，但list、dict、str虽然是Iterable，却不是Iterator。对于可迭代对象，可以使用内建函数`iter()`来获取它的迭代器对象。

    >>> isinstance(iter([]), Iterator)
    True
    >>> isinstance(iter('abc'), Iterator)
    True

总结下：

* 凡是可作用于for循环的对象都是Iterable类型；
* 凡是可作用于next()函数的对象都是Iterator类型，它们表示一个惰性计算的序列；
* 集合数据类型如list、dict、str等是Iterable但不是Iterator，不过可以通过iter()函数获得一个Iterator对象。

此外，要知道 Python的for循环本质上就是通过不断调用next()函数实现的，例如：

    for x in [1, 2, 3, 4, 5]:
        pass

实际上完全等价于：

    # 首先获得Iterator对象:
    it = iter([1, 2, 3, 4, 5])
    # 循环:
    while True:
        try:
            # 获得下一个值:
            x = next(it)
        except StopIteration:
            # 遇到StopIteration就退出循环
            break

## 自定义迭代器

迭代器要求支持`迭代器协议`，支持迭代器协议就是实现对象的`__iter__()`和`next()`方法（python3中实现 `__next__()`方法），任何支持迭代器协议的对象都是迭代器。其中__iter__()方法返回迭代器对象本身；next()方法返回容器的下一个元素，在结尾时引发StopIteration异常。

**__iter__()返回迭代器对象本身**，如下：

    >>> a = [1, 2, 3, 4]
    >>> a = iter(a)
    >>> a.__iter__()
    <listiterator object at 0x1073ffa50>
    >>> a
    <listiterator object at 0x1073ffa50>
    >>> a is a.__iter__()
    True

**next()方法返回迭代器中的值直到结尾**，如下：

    >>> next(a)
    1
    >>> next(a)
    2
    >>> next(a)
    3
    >>> next(a)
    4
    >>> next(a)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    StopIteration

有很多关于迭代器的例子，比如itertools 中函数返回的都是迭代器对象。下面的例子从有限序列生成一个无限序列：

    >>> from itertools import cycle
    >>> colors = cycle(['red', 'white', 'blue'])
    >>> next(colors)
    'red'
    >>> next(colors)
    'white'
    >>> next(colors)
    'blue'
    >>> next(colors)
    'red'

当然也可以实现自定义的迭代器，以斐波那契数列为例：

    class Fib:
        def __init__(self):
            self.prev = 0
            self.curr = 1
    
        def __iter__(self):
            return self
    
        def __next__(self):
            value = self.curr
            self.curr += self.prev
            self.prev = value
            return value
    from collections import Iterator
    print isinstance(Fib(), Iterator)  # True.

# 生成器（Generator）

生成器其实是一种特殊的迭代器，在每次进行迭代时返回一个值，直到遇到StopIteration 异常结束。生成器的构造有两种方法：

1. 生成器表达式：通列表解析语法，只不过把列表解析的[]换成()。
2. 生成器函数：在函数中如果出现了yield关键字，那么该函数就不再是普通函数，而是生成器函数。

生成器表达式能做的事情列表解析基本都能处理，只不过在需要处理的序列比较大时，列表解析比较费内存。

    gen = (x**2 for x in range(5))
    print gen
    # <generator object <genexpr> at 0x0000000002FB7B40>
    for g in gen:
        print g
    
    # print gen.next()    # StopIteration

除了生成器表达式，还可以用yiled关键字来产生生成器。yield 的作用就是把一个函数变成一个 generator，带有 yield 的函数不再是一个普通函数，Python 解释器会将其视为一个 generator。也就是说，**yield是一个语法糖，内部实现支持了迭代器协议，同时yield内部也是一个状态机，维护着挂起和继续的状态**。

用生成器来实现斐波那契数列的例子是：

    def fib():
        prev, curr = 0, 1
        while True:
            yield curr
            prev, curr = curr, curr + prev
    f = fib()
    from itertools import islice
    print list(islice(f, 0, 10))    # [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
    print isinstance(f, Iterator)   # True
    print type(f)                   # <type 'generator'>

fib和普通的python函数的区别在于函数体中没有return关键字，这里fib的返回值是一个`生成器对象`。当执行f=fib()返回的是一个生成器对象，此时函数体中的代码并不会执行，只有显示或隐示地调用next的时候才会真正执行里面的代码。

当生成器函数 fib 执行yield语句的时候，fib函数的状态被冻结，所有变量值都被保存，下一条要执行的语句被记录下来，直到下一次的next()调用来临。一旦再遇到next()调用，生成器函数就被激活，而如果next()永远不再调用，那么最后记录的状态也就被丢弃了。

生成器是可以迭代的，但是只可以读取它一次 ，因为它并不把所有的值放在内存中，它实时地生成数据。

## yield 与增强生成器

在 python 2.3 中加入了关键字yield，只要包含它的函数即是一个 generator。但在2.3中，generator 不能重入，不能在运行过程中修改，不能引发异常，要么是顺序调用，要么就创建一个新的 generator。到了 2.5 版之后，做了以下改动：

1. yield 被重新定义为一个表达式（Expression），之前是一个语句（statement）。
2. 添加了一个 send() 函数，可以使用它向 generator 发送消息。
3. 增加了 throw() 方法，可以用来从 generator 内部来引发异常，从而控制 generator 的执行。
4. 增加了 close 方法，用来关闭一个 generator。

执行一个 send(msg) 会恢复 generator 的运行，然后发送的值将成为当前 yield 表达式的返回值。然后 send() 会返回下一个被 generator yield 的值，如果没有下一个可以 yield 的值则引发一个异常。

> Add a new send() method for generator-iterators, which resumes the generator and "sends" a value that becomes the result of the current yield-expression.  The send() method returns the next value yielded by the generator, or raises StopIteration if the generator exits without yielding another value.
       
可以看出这其实包含了一次运行，从将 msg 赋给当前被停住的 yield 表达式开始，到下一个 yield 语句结束，然后返回下一个yield语句的参数，然后再挂起，等待下一次的调用。所以，在 2.5 之后，可以将 next() 看作是 send(None) 。

为了精准的理解 send(msg) 函数，可以将 yield 表达式想象成下面的伪代码：

```python
x = yield i <==> put(i); x = wait_and_get()
```

可以理解为先是一个 `put(i)`，这个 i 就是 yield 表达式后面的参数，如果 **yield 没有参数，则表示 None**。它表示将 i 放到一个全局缓冲区中，相当于返回了一个值。 `wait_and_get()` 可以理解为一个阻塞调用，它等待着外界来唤醒它，并且可以返回一个值。这样下面代码的运行结果就很容易理解了：

```python
>>> def g():
...     print 'step 1'
...     x = yield 'hello'
...     print 'step 2', 'x=', x
...     y = 5 + (yield x)
...     print 'step 3', 'y=', y
...
>>> f = g()
>>> print f.next()
step 1
hello
>>> print f.send(5)
step 2 x= 5
5
>>> print f.send(2)
step 3 y= 7
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

此外，文档中下面一段也很重要：

> Because generator-iterators begin execution at the top of the generator's function body, there is no yield expression to receive a value when the generator has just been created. Therefore, calling send() with a non-None argument is prohibited when the generator iterator has just started, and a TypeError is raised if this occurs (presumably due to a logic error of some kind). Thus, before you can communicate with a coroutine you must first call next() or send(None) to advance its execution to the first yield expression.

第一次调用时要么使用 next() ，要么使用 send(None) ，不能使用 send() 来发送一个非 None 的值，原因就是第一次没有一个 yield 表达式来接受这个值，如下示例：

```python
>>> f = g()
>>> f.send(3)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: can't send non-None value to a just-started generator
```

2.5 增加了 throw() 方法，可以用来从 generator 内部来引发异常，从而控制 generator 的执行。

```python
>>> f = g() 
>>> f.send(None) 
step 1 
'hello' 
>>> f.throw(GeneratorExit) 
>>>
>>> ... 
```

这里执行了 f.throw(GeneratorExit)，引发了一个 GeneratorExit 异常，该异常用来在生成器退出前有机会执行一些清理工作。

2.5 还增加了 close() 方法，用来关闭一个 generator ，它的伪代码如下：

```python
def close(self):
    try:
        self.throw(GeneratorExit)
    except (GeneratorExit, StopIteration):
        pass
    else:
        raise RuntimeError("generator ignored GeneratorExit")
        # Other exceptions are not caught
```

## 递归生成器

生成器可以像函数一样进行递归使用，下面看一个简单的例子，对一个序列进行全排列：

    def permutations(li):
        if len(li) == 0:
            yield li
        else:
            for i in range(len(li)):
                li[0], li[i] = li[i], li[0]
                for item in permutations(li[1:]):
                    yield [li[0]] + item
    
    for item in permutations(range(3)):
        print item

    """
    [0, 1, 2]
    [0, 2, 1]
    [1, 0, 2]
    [1, 2, 0]
    [2, 0, 1]
    [2, 1, 0]
    """

# 更多阅读
[Iterables vs. Iterators vs. Generators](http://nvie.com/posts/iterators-vs-generators/)    
[What exactly are Python's iterator, iterable, and iteration protocols?](http://stackoverflow.com/questions/9884132/what-exactly-are-pythons-iterator-iterable-and-iteration-protocols)  
[What does the yield keyword do in Python?](http://stackoverflow.com/questions/231767/what-does-the-yield-keyword-do-in-python)  
[How to make class iterable?](http://stackoverflow.com/questions/19151/how-to-make-class-iterable)    
[Difference between Python's Generators and Iterators](http://stackoverflow.com/questions/2776829/difference-between-pythons-generators-and-iterators)   
[PEP 342: Coroutines via Enhanced Generators](https://www.python.org/dev/peps/pep-0342/)  
[What is the difference between an expression and a statement in Python?](http://stackoverflow.com/questions/4728073/what-is-the-difference-between-an-expression-and-a-statement-in-python)  
[Python 迭代器和生成器](http://python.jobbole.com/81881/)    
[python 核心 - 生成器和yield](http://www.pycoding.com/2015/12/02/python/generator.html)  
[Python天天美味(25) - 深入理解yield](http://www.cnblogs.com/coderzh/articles/1202040.html)   
[2.5版yield之学习心得](http://zoomq.qiniudn.com/ZQScrapBook/ZqFLOSS/data/20061206220831/index.html)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Iterator_1.png

