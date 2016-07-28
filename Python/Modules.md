

# [itertools](https://docs.python.org/2.7/library/itertools.html)

itertools 模块实现了许多可以创建不同功能迭代器的函数，此模块中的所有函数返回的迭代器都可以与for循环语句以及其他包含迭代器（如生成器和生成器表达式）的函数联合使用，主要有以下函数组成：

![][1]

## 无限迭代器

### itertools.count(start=0, step=1)

创建一个迭代器，生成从n开始的连续整数，如果忽略n，则从0开始计算，经常和 imap()，izip() 一起使用。

    for i in izip(count(1), ['a', 'b', 'c']):
        print i
    
    (1, 'a')
    (2, 'b')
    (3, 'c')

### itertools.cycle(iterable)

创建一个迭代器，对iterable中的元素反复执行循环操作，内部会生成iterable中的元素的一个副本，此副本用于返回循环中的重复项。

    i = 0
    for item in cycle(['a', 'b', 'c']):
        i += 1
        if i == 6:
            break
        print (i, item)
    
    (1, 'a')
    (2, 'b')
    (3, 'c')
    (4, 'a')
    (5, 'b')
    (6, 'c')

### itertools.repeat(object[, times])

创建一个迭代器，重复生成object，times（如果已提供）指定重复计数，如果未提供times，将无止尽返回该对象。

    >>> list(imap(pow, xrange(10), repeat(2)))
    [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]

## 处理输入序列迭代器

### itertools.product(*iterables[, repeat])¶

创建一个迭代器，生成表示item1，item2等中的项目的`笛卡尔积`的元组，repeat是一个关键字参数，指定重复生成序列的次数。

    a = (1, 2)
    b = ('A', 'B')
    c = itertools.product(a,b)
    for elem in c:
        print elem
    
    (1, 'A')
    (1, 'B')
    (2, 'A')
    (2, 'B')

### itertools.permutations(iterable[, r])

创建一个迭代器，返回iterable中任意取r个元素做排列的元组，如果省略了r，那么序列的长度与iterable中的项目数量相同。

    >>> print list(permutations([1,1,2,3], 3))
    [(1, 1, 2), (1, 1, 3), (1, 2, 1), (1, 2, 3), (1, 3, 1), (1, 3, 2), (1, 1, 2), (1, 1, 3), (1, 2, 1), (1, 2, 3), (1, 3, 1), (1, 3, 2), (2, 1, 1), (2, 1, 3), (2, 1, 1), (2, 1, 3), (2, 3, 1), (2, 3, 1), (3, 1, 1), (3, 1, 2), (3, 1, 1), (3, 1, 2), (3, 2, 1), (3, 2, 1)]

### itertools.combinations(iterable, r)

创建一个迭代器，返回iterable中任意取r个元素做组合的元组，如果省略了r，那么序列的长度与iterable中的项目数量相同。

    >>> print list(combinations([1,1,2,3], 3))
    [(1, 1, 2), (1, 1, 3), (1, 2, 3), (1, 2, 3)]

## 组合生成器

### itertools.imap(function, *iterables)

创建一个迭代器，生成项function(i1, i2, ..., iN)，其中i1，i2...iN 分别来自可迭代对象 iter1，iter2 ... iterN，如果function为None，则返回(i1, i2, ..., iN)形式的元组，只要提供的任何一个可迭代对象不再生成值，迭代就会停止。

    print 'Doubles:'
    for i in imap(lambda x:2*x, xrange(5)):
        print i
    
    print 'Multiples:'
    for i in imap(lambda x,y:(x, y, x*y), xrange(5), xrange(5,10)):
        print '%d * %d = %d' % i

### itertools.ifilter(predicate, iterable)

返回一个迭代器，只包括测试函数 predicate 返回true时的项，类似于内置函数 filter()。如果 predicate 为 None，范围 iterable 中为 True 的对象。具体实现等价于下面程序：

    def ifilter(predicate, iterable):
        # ifilter(lambda x: x%2, range(10)) --> 1 3 5 7 9
        if predicate is None:
            predicate = bool
        for x in iterable:
            if predicate(x):
                yield x

### itertools.chain(*iterables)

将多个可迭代对象作为参数，返回单个迭代器，它产生所有可迭代对象的内容，就好像他们是来自于一个单一的序列。

    for i in chain([1, 2, 3], ['a', 'b', 'c']):
        print i
    1
    2
    3
    a
    b
    c

### itertools.compress(data, selectors)

提供一个选择列表，对原始数据进行筛选，实现如下：

    def compress(data, selectors):
        # compress('ABCDEF', [1,0,1,0,1,1]) --> A C E F
        return (d for d, s in izip(data, selectors) if s)

### itertools.groupby(iterable[, key])

返回一个产生按照key进行分组后的值集合的迭代器：

    >>> a = ['aa', 'ab', 'abc', 'bcd', 'abcde']
    >>> for i, k in groupby(a, len):
    ...     print i, list(k)
    ...
    2 ['aa', 'ab']
    3 ['abc', 'bcd']
    5 ['abcde']

再来看一个稍微复杂的例子：

    from itertools import groupby
    
    d = dict(a=1, b=2, c=1, d=2, e=1, f=2, g=3)
    di = sorted(d.iteritems(), key=lambda x: x[1])
    for k, g in groupby(di, key=lambda x: x[1]):
        print k, map(lambda x: x[1], g)
    # 1 [1, 1, 1]
    # 2 [2, 2, 2]
    # 3 [3]

### itertools.islice(iterable, start, stop[, step])

返回的迭代器，包含输入可迭代对象根据索引来选取的项。

    print 'Stop at 5:'
    for i in islice(count(), 5):
        print i
    
    print 'Start at 5, Stop at 10:'
    for i in islice(count(), 5, 10):
        print i

### itertools.izip(*iterables)

返回一个合并了多个可迭代对象为一个元组的迭代器，元组(i1, i2, ... iN)，其中i1，i2 ... iN 分别来自可迭代对象iter1，iter2 ... iterN，只要提供的某个可迭代对象不再生成值，迭代就会停止。类似于内置函数zip()，只是它返回的是一个迭代器而不是一个列表。

    for i in izip([1, 2, 3], ['a', 'b', 'c']):
        print i
    (1, 'a')
    (2, 'b')
    (3, 'c')

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





[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Modules_1.png

