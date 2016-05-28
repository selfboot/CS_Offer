# 函数参数

为了能让一个函数接受任意数量的位置参数，可以使用一个 `* 参数`。例如 

    def avg(first, *args):
        return (first + sum(args)) / (1 + len(args)) 
    # Sample use     avg(1, 2) # 1
    avg(1, 2, 3, 4) # 2

args 是由所有其他位置参数组成的元组。然后我们在代码中把它当成了一个序列来进行后续的计算。 为了接受任意数量的关键字参数，使用一个以 `** 参数`。 

    def get_first(first, **kwargs):
      if first in kwargs:
          return kwargs[first]
      else:
          return "Nope"
       
    print get_first("name", name="John") # John

在这里，kwargs 是一个包含所有被传入进来的关键字参数的字典。 


# 特别注意！

## lambda 匿名函数捕获值

lambda 表达式允许你定义简单函数,但是它的使用是有限制的。你只能指定 单个表达式,它的值就是最后的返回值。也就是说不能包含其他的语言特性了,包括 多个语句、条件表达式、迭代以及异常处理等等。 

    >>> x = 10
    >>> a = lambda y: x + y
    >>> x = 20
    >>> b = lambda y: x + y 

那么 a(10) 和 b(10) 返回的结果是什么? 答案是 30，30。

这其中的奥妙在于**lambda 表达式中的 x 是一个自由变量，在运行时绑定值，而不是定义时就绑定，这跟函数的默认值参数定义是不同的**。因此,在调用这个 lambda 表达式的时候，x 的值是执行时的值。

如果想让某个匿名函数在定义时就捕获到值，可以将那个参数值定义成默认参数即可，就像下面这样: 

    >>> x = 10
    >>> a = lambda y, x=x: x + y
    >>> x = 20
    >>> b = lambda y, x=x: x + y 

这样结果就是 20，30了。下面再看两个例子，加深对lambda变量捕获机制的了解：

    >>> funcs = [lambda x: x+n for n in range(5)] 
    >>> for f in funcs:
    ... print(f(0))
    # 4 4 4 4 4
    >>> funcs = [lambda x, n=n: x+n for n in range(5)]
    >>> for f in funcs:
    ... print(f(0))
    # 0 1 2 3 4

## 默认参数值

定义一个有可选参数的函数是非常简单的，直接在函数定义中给参数指定一个默认值，并放到参数列表最后就行了。但是要注意：`默认参数的值仅仅在函数定义的时候赋值一次`。看下面的例子：

    def f(a, L=[]):
        L.append(a)
        return L
    
    print f(1)  # [1]
    print f(2)  # [1, 2]
    print f(3)  # [1, 2, 3]

关于这点，文档上着重给出警告，如下：

> Important warning: The default value is evaluated only once. This makes a difference when the default is a mutable object such as a list, dictionary, or instances of most classes.

所以，如果默认参数是一个可修改的容器比如一个列表、集合或者字典，最好使用 None 作为默认值。

    # Using a list as a default value
    def spam(a, b=None): 
        if b is None: 
            b = [] 
        ...

如果不想提供一个默认值，而是想仅仅测试下某个默认参数是不是有传递进来，可以像下面这样写: 

    _no_value = object()
    def spam(a, b=_no_value): 
        if b is _no_value: 
            print('No b value supplied')
        ... 

# [内置函数](https://docs.python.org/2/library/functions.html)

Python 自带许多方便的内置函数，如下图：

![][1]

## all

    all(iterable) -> bool

Return True if bool(x) is True for all values x in the iterable.  If the iterable is empty, return True.

    def all(iterable):
        for element in iterable:
            if not element:
                return False
        return True
    
## any
Return True if any element of the iterable is true. If the iterable is empty, return False. Equivalent to:

    def any(iterable):
        for element in iterable:
            if element:
                return True
        return False

## map

    map(function, sequence[, sequence, ...]) -> list

> Return a list of the results of applying the function to the items of the argument sequence(s).  If more than one sequence is given, the function is called with an argument list consisting of the corresponding item of each sequence, substituting None for missing values when not all sequences have the same length.  If the function is None, return a list of the items of the sequence (or a list of tuples if more than one sequence).
    
具体看简单的例子：

    >>> Celsius = [39.2, 36.5, 37.3, 37.8]
    >>> Fahrenheit = map(lambda x: (float(9)/5)*x + 32, Celsius)
    >>> print Fahrenheit
    [102.56, 97.700000000000003, 99.140000000000001, 100.03999999999999]
    >>> a, b, c = [1,2,3,4], [17,12,11,10], [-1,-4,5,9]
    >>> map(lambda x,y,z:x+y+z, a,b,c)
    [17, 10, 19, 23]

## reduce

    reduce(function, sequence[, initial]) -> value

> Apply a function of two arguments cumulatively to the items of a sequence, from left to right, so as to reduce the sequence to a single value.  For example, reduce(lambda x, y: x+y, [1, 2, 3, 4, 5]) calculates ((((1+2)+3)+4)+5).  If initial is present, it is placed before the items of the sequence in the calculation, and serves as a default when the sequence is empty.

具体看简单的例子：

    >>> f = lambda a,b: a if (a > b) else b
    >>> reduce(f, [47,11,42,102,13])
    102
    >>> reduce(lambda x, y: x+y, range(1,101))
    5050

## zip

    zip(seq1 [, seq2 [...]]) -> [(seq1[0], seq2[0] ...), (...)]

> Return a list of tuples, where each tuple contains the i-th element from each of the argument sequences.  The returned list is truncated in length to the length of the shortest argument sequence.

具体看简单的例子：

    >>> z1=[1,2,3]
    >>> z2=[4,5,6]
    >>> result = zip(z1,z2)
    >>> a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    >>> zip(*a)
    [(1, 4, 7), (2, 5, 8), (3, 6, 9)]

## filter

    filter(function or None, sequence) -> list, tuple, or string

> Return those items of sequence for which function(item) is true.  If function is None, return the items that are true.  If sequence is a tuple or string, return the same type, else return a list.

具体看简单的例子：

    >>> def f(x): return x % 2 != 0 and x % 3 != 0 
    >>> filter(f, range(2, 25)) 
    [5, 7, 11, 13, 17, 19, 23]
    >>> filter(lambda x: x!='a', "abcdef") 
    'bcdef'

# 高级用法

## 函数闭包



# 更多阅读

《Python Cookbook 3》  
[Lambda, filter, reduce and map](http://www.python-course.eu/lambda.php)  
[Python 使用 list 作为函数参数时，参数是否会初始化？](http://www.zhihu.com/question/21924859#answer-11532338)    
[More on Defining Functions](https://docs.python.org/2.7/tutorial/controlflow.html#more-on-defining-functions)  
[How can I read python build-in func source code? eg filter, map, reduce](http://stackoverflow.com/questions/6760899/in-eclipse-how-can-i-read-python-build-in-func-source-code-eg-filter-map-red)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Function_1.png

