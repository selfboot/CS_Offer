

# 默认参数值

先来看下面的例子：

    def f(a, L=[]):
        L.append(a)
        return L
    
    print f(1)  # [1]
    print f(2)  # [1, 2]
    print f(3)  # [1, 2, 3]



> Important warning: The default value is evaluated only once. This makes a difference when the default is a mutable object such as a list, dictionary, or instances of most classes.

# 高效函数

## zip

    zip(seq1 [, seq2 [...]]) -> [(seq1[0], seq2[0] ...), (...)]

> Return a list of tuples, where each tuple contains the i-th element from each of the argument sequences.  The returned list is truncated in length to the length of the shortest argument sequence.

具体看下面的例子

    >>> z1=[1,2,3]
    >>> z2=[4,5,6]
    >>> result = zip(z1,z2)

zip()配合*号操作符,可以将已经列表对象解压后进行

    >>> a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    >>> zip(*a)
    [(1, 4, 7), (2, 5, 8), (3, 6, 9)]

参考  
[Python中zip()函数用法举例](http://www.lfyzjck.com/python-zip/)  


# 更多阅读

[Python 使用 list 作为函数参数时，参数是否会初始化？](http://www.zhihu.com/question/21924859#answer-11532338)    
[More on Defining Functions](https://docs.python.org/2.7/tutorial/controlflow.html#more-on-defining-functions)

