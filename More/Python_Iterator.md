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

迭代器（Iterator）是访问集合内元素的一种方式，提供了一种遍历类序列对象的方法。对于一般的序列，利用索引从0一直迭代到序列的最后一个元素。对于字典、文件、自定义对象类型等，可以自定义迭代方式，从而实现对这些对象的遍历。总之，迭起器就是定义了对对象进行遍历的方式。

迭代器、可迭代对象、生成器之间的关系可以用下图表示：

![][1]


迭代器要求支持迭代器协议，在Python中，支持迭代器协议就是实现对象的`__iter__()`和`next()`方法。其中__iter__()方法返回迭代器对象本身；next()方法返回容器的下一个元素，在结尾时引发StopIteration异常。


# 更多阅读


[Iterables vs. Iterators vs. Generators](http://nvie.com/posts/iterators-vs-generators/)    
[What exactly are Python's iterator, iterable, and iteration protocols?](http://stackoverflow.com/questions/9884132/what-exactly-are-pythons-iterator-iterable-and-iteration-protocols)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Iterator_1.png

