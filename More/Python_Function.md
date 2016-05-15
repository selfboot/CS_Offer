

## 默认参数值

先来看下面的例子：

    def f(a, L=[]):
        L.append(a)
        return L
    
    print f(1)  # [1]
    print f(2)  # [1, 2]
    print f(3)  # [1, 2, 3]



> Important warning: The default value is evaluated only once. This makes a difference when the default is a mutable object such as a list, dictionary, or instances of most classes.

# [内置函数](https://docs.python.org/2/library/functions.html)

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


# 更多阅读

[Lambda, filter, reduce and map](http://www.python-course.eu/lambda.php)  
[Python 使用 list 作为函数参数时，参数是否会初始化？](http://www.zhihu.com/question/21924859#answer-11532338)    
[More on Defining Functions](https://docs.python.org/2.7/tutorial/controlflow.html#more-on-defining-functions)  
[How can I read python build-in func source code? eg filter, map, reduce](http://stackoverflow.com/questions/6760899/in-eclipse-how-can-i-read-python-build-in-func-source-code-eg-filter-map-red)  


