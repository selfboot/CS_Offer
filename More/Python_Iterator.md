# 可迭代对象（Iterable）

给定一个list或tuple，可以通过for循环来遍历这个list或tuple，这种遍历称为迭代（Iteration）。在Python中，迭代是通过for ... in来完成的，而很多语言比如C或者Java，迭代list是通过下标完成的。

可以直接作用于for循环的数据类型有以下几种：

* 集合数据类型，如list / tuple / dict / set / str /等; 
* 生成器表达式和带yield的generator function。

这些可以直接作用于 for 循环的对象统称为可迭代对象：Iterable。可以使用 isinstance() 判断一个对象是否是可迭代对象：

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

迭代器、可迭代对象、生成器之间的关系可以用下图表示：

![][1]

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

## 迭代器协议

迭代器要求支持迭代器协议，支持迭代器协议就是实现对象的`__iter__()`和`next()`方法。其中__iter__()方法返回迭代器对象本身；next()方法返回容器的下一个元素，在结尾时引发StopIteration异常。

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

## 自定义迭代器


# 更多阅读


[Iterables vs. Iterators vs. Generators](http://nvie.com/posts/iterators-vs-generators/)    
[What exactly are Python's iterator, iterable, and iteration protocols?](http://stackoverflow.com/questions/9884132/what-exactly-are-pythons-iterator-iterable-and-iteration-protocols)  
[廖雪峰：迭代器](http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/00143178254193589df9c612d2449618ea460e7a672a366000)  
[Python迭代器和生成器](http://python.jobbole.com/81881/)  
[Python 迭代器小结](http://python.jobbole.com/85240/)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Iterator_1.png

