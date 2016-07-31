Python的3​​.0版本，常被称为Python 3000，或简称Py3k。相对于Python的早期版本，这是一个较大的升级。为了不带入过多的累赘，Python 3.0在设计的时候没有考虑向下相容。

许多针对早期Python版本设计的程式都无法在Python 3.0上正常执行。为了照顾现有程式，Python 2.6 2.7作为过渡版本，基本使用了Python 2.x的语法和库，同时考虑了向Python 3.0的迁移，允许使用部分Python 3.0的语法与函数。

python 2.x 和 3.x 有着许多区别，整理如下。

# print 语法

print语句没有了，取而代之的是print()函数。 Python 2.6与Python 2.7部分地支持这种形式的print语法。如果我们按照 Python 2 的方式不使用小括号调用 print 函数，Python 3 将抛出一个语法异常（SyntaxError）。

2.x

    print 'Python', python_version()
    print 'Hello, World!'
    print('Hello, World!')

3.x

    print('Python', python_version())
    print('Hello, World!')
    print("some text,", end="") 

# 除法运算

Python中的除法较其它语言显得非常高端，有套很复杂的规则。Python中的除法有两个运算符，`/` 和 `//`

/ 除法

* 在python 2.x中 / 除法就跟我们熟悉的大多数语言，比如Java啊C啊差不多，整数相除的结果是一个整数，把小数部分完全忽略掉，浮点数除法会保留小数点的部分得到一个浮点数的结果。
* 在python 3.x中/除法不再这么做了，对于整数之间的相除，结果也会是浮点数。

Python 2.x:

    >>> 1 / 2
    0
    >>> 1.0 / 2.0
    0.5

Python 3.x:
    
    >>> 1/2
    0.5

//除法：这种除法叫做floor除法，会对除法的结果自动进行一个floor操作，在python 2.x和python 3.x中是一致的。

    >>> -1 // 2
    -1

# 比较操作的异常抛出

当对不可排序类型做比较时，会抛出一个类型错误(TypeError)。

2.x

    >>> print None < None
    False
    >>> print 1 < ''
    True
    >>> print len <= len
    True

3.x 中将导致 `TypeError: unorderable types`

# xrange

xrange 不再存在，range函数代替了以前的 xrange 函数。

同时更改的还有一系列内置函数及方法, 都返回迭代器对象, 而不是列表或者元组, 比如 filter, map, zip 等

2.x

    print range(3) 
    print type(range(3))
    
    # [0, 1, 2]
    # <type 'list'>

3.x

    print(range(3))
    print(type(range(3)))
    print(list(range(3)))
    
    range(0, 3)
    <class 'range'>
    [0, 1, 2]

# 字符编码

Python中，不论是Python 2.x还是Python 3.x中，总体上说，字符都只有2大类：

* 通用的Unicode字符；
* Unicode被编码后的某种编码类型的字符，比如UTF-8，GBK等等类型的字符；

python 2.x 中普通的用引号括起来的字符串就是`str类型`，此时字符串的编码类型，对应着Python文件本身保存的编码方式，最常见的Windows平台中，默认用的是GBK。在普通字符串前面加上前缀u后，就表示字符串是`Unicode类型`。当然，也可以用 unicode()强制转换。

Python 3.x中，普通的用引号括起来的字符已经是Unicode类型的str了。普通字符串加上字母b作为前缀，就是表示`bytes字符串`，即为某种编码（UTF-8，GBK等）类型的字节序列。

3.x 中源码文件默认 UTF-8，因此下面语句合法：

    >>> 中国 = 'china' 
    >>> print(中国) 
    china

2.x

    >>> str = "测试"
    >>> str
    '\xe6\xb5\x8b\xe8\xaf\x95'
    >>> str = u"测试"
    >>> str
    u'\u6d4b\u8bd5'

3.x

    >>> str = "测试"
    >>> str
    '测试'

# 其它改动

* Python 3中，没有旧式类，只有新式类，也就是说不用再像这样 class Foobar(object): pass 显式地子类化object。
* Python 2.x中不等于有两种写法 != 和 <>，Python 3.x中去掉了<>, 只有!=一种写法。
* Py3.X去除了long类型，现在只有一种整型——int，但它的行为就像2.X版本的long



# 更多阅读

[What’s New In Python 3.0](https://docs.python.org/3/whatsnew/3.0.html)  
[2to3 - Automated Python 2 to 3 code translation](https://docs.python.org/3/library/2to3.html)  


