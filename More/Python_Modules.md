

# [itertools](https://docs.python.org/2.7/library/itertools.html)



# [collections](https://docs.python.org/2.7/library/collections.html)

Python拥有一些内置的数据类型，比如str, int, list, tuple, dict等，collections 模块在这些内置数据类型的基础上，提供了几个额外的数据容器：

* Counter：计数器，主要用来计数
* defaultdict：带有默认值的字典
* deque：双端队列，可以快速的从两边 append 和 pop 对象
* namedtuple：生成可以使用名字来访问元素内容的tuple子类
* OrderedDict：有序字典

### [Counter](https://docs.python.org/2.7/library/collections.html#counter-objects)

Counter 提供了一种方便、快速的计数工具。Counter 类是dict的子类，主要用来统计hashable对象的出现次数。如果访问没有出现的元素，不抛出意外，只返回0。

    collections.Counter([iterable-or-mapping])

下面是一些简单的例子：

    >>> c = Counter()                           # a new, empty counter
    >>> c = Counter('gallahad')                 # a new counter from an iterable
    >>> c = Counter({'red': 4, 'blue': 2})      # a new counter from a mapping
    >>> c = Counter(cats=4, dogs=8)             # a new counter from keyword args
    >>> c = Counter(['eggs', 'ham'])
    >>> c['bacon']                              # count of a missing element is zero
    0

下面列出一些常用的方法：

    sum(c.values())                 # total of all counts
    c.clear()                       # reset all counts
    list(c)                         # list unique elements
    set(c)                          # convert to a set
    dict(c)                         # convert to a regular dictionary
    c.items()                       # convert to a list of (elem, cnt) pairs
    Counter(dict(list_of_pairs))    # convert from a list of (elem, cnt) pairs
    c.most_common()[:-n-1:-1]       # n least common elements
    c += Counter()                  # remove zero and negative counts

### [defaultdict](https://docs.python.org/2.7/library/collections.html#defaultdict-objects)

在使用Python原生的数据结构dict的时候，如果用 d[key] 这样的方式访问，当指定的key不存在时，是会抛出KeyError异常的。但是，如果使用defaultdict，只要你传入一个默认的工厂方法，那么请求一个不存在的key时，便会调用这个工厂方法使用其结果来作为这个key的默认值。

    collections.defaultdict([default_factory[, ...]])

下面是一个简单的例子：

    >>> s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
    >>> d = defaultdict(list)
    >>> for k, v in s:
    ...     d[k].append(v)
    ...
    >>> d.items()
    [('blue', [2, 4]), ('red', [1]), ('yellow', [1, 3])]


### [deque](https://docs.python.org/2.7/library/collections.html#deque-objects)

deque（double-ended queue），双端队列实现了从队列头部 O(1) 时间追加和取出对象: .popleft(), .appendleft() 。

    collections.deque([iterable[, maxlen]])

maxlen 用来声明 deque 的最长长度。没有给定 maxlen 时，deque 可以为任意长度。当给定 maxlen 时，deque 中元素个数最多为 maxlen个，当队列满后，在队列一端添加元素导致队列另一段头部被弹出。下面是一个简单的示例：

>>> from collections import deque
>>> d = deque('ghi')                 # make a new deque with three items
>>> d.append('j')                    # add a new entry to the right side
>>> d.appendleft('f')                # add a new entry to the left side
>>> d                                # show the representation of the deque
deque(['f', 'g', 'h', 'i', 'j'])
>>> d.pop()                          # return and remove the rightmost item
'j'
>>> d.popleft()                      # return and remove the leftmost item
'f'
>>> list(d)                          # list the contents of the deque
['g', 'h', 'i']

### [namedtuple](https://docs.python.org/2.7/library/collections.html#namedtuple-factory-function-for-tuples-with-named-fields)

namedtuple主要用来产生可以使用名称来访问元素的数据对象，通常用来增强代码的可读性，在访问一些tuple类型的数据时尤其好用。

    collections.namedtuple(typename, field_names[, verbose=False][, rename=False])

下面是一个简单的示例：

    >>> Point = namedtuple('Point', ['x', 'y'])
    >>> p = Point(11, y=22)     # instantiate with positional or keyword arguments
    >>> p[0] + p[1]             # indexable like the plain tuple (11, 22)
    33
    >>> p.x + p.y               # fields also accessible by name
    33
    >>> p                       # readable __repr__ with a name=value style
    Point(x=11, y=22)
    >>> x, y = p                # unpack like a regular tuple
    >>> x, y
    (11, 22)

当我们使用csv 或者 sqlite3 模块读取数据时，命名元祖特别有用，比如下面的例子：

    EmployeeRecord = namedtuple('EmployeeRecord', 'name, age, title, department, paygrade')
    
    import csv
    for emp in map(EmployeeRecord._make, csv.reader(open("employees.csv", "rb"))):
        print emp.name, emp.title

### [OrderedDict](https://docs.python.org/2.7/library/collections.html#ordereddict-objects)

有序字典和普通字典一样，除此之外它还会记录 `items 插入`的顺序。

下面是一些简单的例子：

    >>> # regular unsorted dictionary
    >>> d = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}
    
    >>> # dictionary sorted by key
    >>> OrderedDict(sorted(d.items(), key=lambda t: t[0]))
    OrderedDict([('apple', 4), ('banana', 3), ('orange', 2), ('pear', 1)])
    
    >>> # dictionary sorted by value
    >>> OrderedDict(sorted(d.items(), key=lambda t: t[1]))
    OrderedDict([('pear', 1), ('orange', 2), ('banana', 3), ('apple', 4)])
    
    >>> # dictionary sorted by length of the key string
    >>> OrderedDict(sorted(d.items(), key=lambda t: len(t[0])))
    OrderedDict([('pear', 1), ('apple', 4), ('orange', 2), ('banana', 3)])


# 更多阅读
[heapq – In-place heap sort algorithm](https://pymotw.com/2/heapq/)  
[itertools – Iterator functions for efficient looping](https://pymotw.com/2/itertools/index.html#module-itertools)  
[collections – Container data types](https://pymotw.com/2/collections/index.html#module-collections)  
[不可不知的Python模块: collections](http://www.zlovezl.cn/articles/collections-in-python/)  
[PYTHON-进阶-ITERTOOLS模块小结](http://wklken.me/posts/2013/08/20/python-extra-itertools.html)  





