# 函数概述

函数是重用的程序段。允许给一块语句一个名称，然后可以在你的程序的任何地方使用这个名称任意多次地运行这个语句块。这被称为`调用函数`。

Python 中通过def关键字定义函数，def关键字后跟一个函数的标识符名称，然后跟一对圆括号。圆括号之中可以包括一些变量名，该行以冒号结尾。接下来是一块语句，它们是函数体。

函数参数在函数定义的圆括号内指定，用逗号分割，当我们调用函数的时候，以同样的方式提供值。函数参数有多种类型，下面会详细说明。

在函数体内声明的变量，与函数外具有相同名称的其他变量没有任何关系，称之为`局部变量`。它的作用域从被定义的点开始，直到定义的块的结束。如果想在函数内部，给全局变量赋值，那么必须用 global 关键字声明该变量是全局的变量。(关于 Python 作用域的 LEGB 解析规则，可以参考 [Short Description of Python Scoping Rules](http://stackoverflow.com/questions/291978/short-description-of-python-scoping-rules))

	l1, l2, l3 = [1, 2, 3], [1, 2, 3], [1, 2, 3]
	
	def test():
	    l1.append(4)
	    l2 = [4]
	    global l3
	    l3 = [4]
	    print "l1->", l1, "l2->", l2, "l3->", l3
	
	test()
	print "l1->", l1, "l2->", l2, "l3->", l3
	# l1-> [1, 2, 3, 4] l2-> [4] l3-> [4]
	# l1-> [1, 2, 3, 4] l2-> [1, 2, 3] l3-> [4]

想明白上面的输出就基本理解了局部变量，以及global 关键字了。

## lambda 匿名函数

如果函数体是一个单独的return expression语句，可以选择使用特殊的lambda表达式：

	lambda parameters: expression

lambda表达式相当于函数体为单个return语句的普通函数的匿名函数。它的使用是有限制的，只能指定单个表达式，它的值就是最后的返回值。也就是说不能包含其他的语言特性了，包括多个语句、条件表达式、迭代以及异常处理等等。但是想要使用一个简单函数作为参数或者返回值时，使用lambda表达式是很方便的：

	>>> aList = [1, 2, 3, 4, 5, 6, 7, 8, 9]
	>>> low, high = 3, 7
	>>> filter(lambda x, l=low, h=high: h>x>l, aList)
	[4, 5, 6]

## 文档字符串

在函数的第一个逻辑行的字符串是这个函数的`文档字符串`。文档字符串的惯例是一个多行字符串，它的首行以大写字母开始，句号结尾。第二行是空行，从第三行开始是详细的描述，在函数中使用文档字符串时尽量遵循这个惯例，一个例子：

	def complex(real=0.0, imag=0.0):
	    """Form a complex number.
	
	    Keyword arguments:
	    real -- the real part (default 0.0)
	    imag -- the imaginary part (default 0.0)
	    """
	    if imag == 0.0 and real == 0.0:
	        return complex_zero
	    ...

DocStrings也适用于模块和类，详细内容参见 [PEP 257](https://www.python.org/dev/peps/pep-0257/)。

# 函数参数

## 参数传递方式

在C++中，函数传递方式有`值传递`和`引用传递`两种方式。python中参数传递类似于引用传递，因为 python中一切都是对象，变量全部是对象的引用。但是要区分参数是不可变对象，还是可变对象。

当函数参数为不可变对象（整数，字符串，元组）时，函数体内的参数在被改变之前，会一直持有该对象的引用，但当参数发生改变时，由于该对象为不可变对象，必须生成一份新的拷贝作为函数的本地变量，函数对该本地变量的修改不会影响函数调用者的变量值，这一点有点类似 C++ 函数的值传递。

    def func_pass_value(x):
        print "before: x=", x, " id=", id(x)
        x = 2
        print "after: x=", x, " id=", id(x)
    >>> x = 1
    >>> func_pass_value(x)
    before: x= 1  id= 5363912
    after: x= 2  id= 5363888
    >>> x, id(x)
    (1, 5363912)

当函数参数为可变对象（列表，字典）时，除非发生赋值操作，函数体类的参数会一直持有该对象的引用，函数对该参数的修改也会影响到函数调用者的变量值，类似于C++函数中的引用传递。但在函数体内发生赋值操作时，也会生成一份新的拷贝作为函数的本地变量，函数对该本地变量的修改不会影响到函数调用者的变量值。

    def func_pass_ref1(list):
        print list
        list = [4, 5]
        print list
    
    def func_pass_ref2(list):
        print list
        list += [4, 5]
        print list
    >>> al = [1, 2, 3]
    >>> func_pass_ref1(al)
    [1, 2, 3]
    [4, 5]
    >>> al
    [1, 2, 3]
    >>> func_pass_ref2(al)
    [1, 2, 3]
    [1, 2, 3, 4, 5]
    >>> al
    [1, 2, 3, 4, 5]

## 函数参数类型

python函数传递参数类型比较多，按照是否确定参数数目可分为定长参数变长参数，按照是否引入关键字分为普通参数和关键字参，可以从以下五个方面进行介绍：

* 定长普通参数
* 定长关键字参数
* 变长普通参数
* 变长关键字参数
* 复合参数

`定长普通参数`为最常见的参数传递方式，参数传递时要求实参和虚参的个数相同，顺序也必须相同，否则会出现错误。**如果要设置默认参数，默认参数应该放在参数链表的尾部, 否则在函数调用时会给默认参数指定实参，从而使默认参数的设置失去意义**。定长普通参数对`参数位置`要求严格，为了摆脱位置对参数的束缚，python引入了关键字参数。

`定长关键字参数`进行参数传递时，必须设定指定参数的名字，函数调用时将以键值对的方式进行传递，若要给某个参数设定缺省值，在函数定义时直接指定缺省键值对即可，且不受位置的束缚，在函数调用时则不需要设定指定参数的键值对。

    def fun2(Name='Tom', Age=20, Sex="Male"):
        print 'Name:', Name
        print 'Age:', Age
        print 'Sex:', Sex
    if __name__ == "__main__":
        fun2(Name="Alice", Sex="Female")
        fun2(Name="Bob", Age=22)

有些情况我们在定义一个函数时，并不能能够确定接受的参数的个数，只是知道需要对所接受的参数依次进行处理，这种情况下需要使用变长参数进行参数传递，python在定义变长参数时引入了`*`，定义变长普通参数时在参数名前面放在 *，如 `*args`，定义变长关键字参数时在参数前面放两个`*`号，如`**kargs`。

`变长普通参数`只需要在参数前面放一个*号即可，在函数体内部把形参当作一个元组来处理。在函数调用时可以把一个元组当作参数，不过需要对元组进行unpack，即在相应参数前面加 * 即可。

    def foo(*args):
        for arg in args:
            print arg
        
    if __name__ == "__main__":
        foo(1, 2, 3, "good")
        arglist = 1, 2, 3, "good"
        foo(*arglist)
    
注意在**函数定义时变长参数（包括后面介绍的变长关键字参数）必须设置在定长参数后面**。

变长关键字长参数类似于变长普通参数，只是变长关键字参数在函数定义时在参数前面加 `**` 号，在函数体内部把参数当作一个参数字典来处理。`在函数调用时可以把一个字典当作参数，不过需要对字典进行unpack，即在字典参数前面加 ** `。

    def foo(**kwargs):
        for k, v in kwargs.items():
            print k, v
    if __name__ == "__main__":
        foo(Name="Jim", Age=22, Sex="Male")
        argDict = {"Name": "Jim", "Age": 22, "Sex": "Male"}
        foo(**argDict)

对于变长关键字参数，我们可以任意指定关键字的名字，函数调用的内部会去获取关键字的名字和值。

在实际编程的过程当中，我们可能面临这样一种情况，函数定义时不能够确定会接受到什么样参数，包括参数的数目，参数的类型等，这个时候，我们就会用到这里介绍的复合参数，复合参数及前面介绍的四种参数的混搭形式。

    def foo(firstname, lastname="John", *args, **kwargs):
        print firstname
        print "LastName: ", lastname
        for arg in args:
            print arg
        for k, v in kwargs.items():
            print k, v
    
    if __name__ == "__main__":
        arglist = 1, 2, 3, "good"
        argDict = {"Name": "Jim", "Sex": "Male"}
        foo("Jim", "Jack", *arglist, **argDict)
    
只是在函数定义时对参数的顺序特定的要求：

* 关键字参数必须在普通参数后面
* 变长普通参数必须放在定长参数的后面
* 变长关键字参数必须放在变长普通参数的后面

函数调用时赋值的过程为：

1. 依次为普通参数赋值  
2. 为关键字参数赋值  
3. 将多余出的零散实参打包成一个元组传递给赋给变长普通参数 *args 
4. 将多余的键值对形式的实参打包成一个字典传递给变长关键字参数 **kargs

此外，我们还可以从一个函数传递变长普通参数和变长关键字参数到另一个函数中去，如下：

    def f(x, *args, **kwargs):
        ...
        kwargs['width'] = '14.3c'
        ...
        g(x, *args, **kwargs)
    
# 特别注意！

## lambda 匿名函数捕获值

lambda 表达式允许你定义简单函数,但是它的使用是有限制的。你只能指定单个表达式,它的值就是最后的返回值。也就是说不能包含其他的语言特性了，包括多个语句、条件表达式、迭代以及异常处理等等。 

    >>> x = 10
    >>> a = lambda y: x + y
    >>> x = 20
    >>> b = lambda y: x + y 

那么 a(10) 和 b(10) 返回的结果是什么? 答案是 30，30。

这其中的奥妙在于**lambda 表达式中的 x 是一个自由变量，在运行时绑定值，而不是定义时就绑定，这跟函数的默认值参数定义是不同的**。因此在调用这个 lambda 表达式的时候，x 的值是执行时的值。

如果想让某个匿名函数在定义时就捕获到值，可以将那个参数值定义成默认参数即可，就像下面这样: 

```python
>>> x = 10
>>> a = lambda y, x=x: x + y
>>> x = 20
>>> b = lambda y, x=x: x + y 
```

这样结果就是 20，30了。下面再看两个例子，加深对lambda变量捕获机制的了解：

```python
>>> funcs = [lambda x: x+n for n in range(5)] 
>>> for f in funcs:
... print(f(0))
# 4 4 4 4 4
>>> funcs = [lambda x, n=n: x+n for n in range(5)]
>>> for f in funcs:
... print(f(0))
# 0 1 2 3 4
```

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

## sorted

```python
sorted(iterable[, cmp[, key[, reverse]]])
```

> Return a new sorted list from the items in iterable.

其中：

* iterable：可迭代对象；
* cmp：比较两个对象x和y，如果x > y返回正数，x < y 返回负数；x == y，返回0；比较什么由key决定。只适用于 python 2.x;
* key：用来决定在排序算法中 cmp 比较的内容，key 可以是任何可被比较的内容，比如元组（python 中元组是可被比较的）;
* reverse：排序规则, reverse = True(降序) 或者 reverse = False(升序，默认)

例如有一个字典，根据字典中的属性值来排序，返回一个排好序的元组：

```python
>>> d = {"a":1, "c":3, "d":4, "b":2, "e": 5}
>>> sorted_d = sorted(d.items(), key=lambda i: i[1])
>>> sorted_d
[('a', 1), ('b', 2), ('c', 3), ('d', 4), ('e', 5)]
```

或者有一个数组，它的每一个成员是一个字典，然后根据字典中的属性值来排序，用cmp参数如下：

```python
>>> persons=[{'name':'zhang3','age':15},{'name':'li4','age':12}]
>>> sorted_d = sorted(persons, lambda a,b: a['age']-b['age'])
>>> sorted_d
[{'age': 12, 'name': 'li4'}, {'age': 15, 'name': 'zhang3'}] 
```

再来看一个稍微复杂的例子。给定一个只包含大小写字母，数字的字符串，对其进行排序，保证：

* 所有的小写字母在大写字母前面，
* 所有的字母在数字前面
* 所有的奇数在偶数前面

像下面这样用 sorted 函数即可。

```python
>>> s = "Sorting1234"
>>> "".join(sorted(s, key=lambda x: (x.isdigit(), x.isdigit() and int(x) % 2 == 0, x.isupper(), x)))
'ginortS1324'
```

这里，lambda 函数将输入的字符转换为一个元组，然后 `sorted 函数将根据元组`（而不是字符）来进行比较，进而判断每个字符的前后顺序。这里可以理解为，根据字符生成的元组重新定义了排序的依据。

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

在计算机科学中，闭包（Closure）是`词法闭包（Lexical Closure）`的简称，**是指引用了自由变量的函数**。这个被引用的自由变量将和这个函数一同存在，即使已经离开了创造它的环境也不例外。所以，有另一种说法认为闭包是由函数和与其相关的引用环境组合而成的实体。

Python中如果调用函数A，它返回函数B。这个返回的函数B就叫做闭包，在调用函数A的时候传递的参数就是`自由变量`。举个例子：

    def func(name):
        def inner_func(age):
            print 'name:', name, 'age:', age
        return inner_func
    
    bb = func('the5fire')
    bb(26)  # name: the5fire age: 26

这里面调用func的时候就产生了一个闭包——inner_func,并且该闭包持有自由变量——name，因此这也意味着，当函数func的生命周期结束之后，name这个变量依然存在，因为它被闭包引用了，所以不会被回收。（闭包并不是Python中特有的概念，所有把函数作为一等公民的语言均有闭包的概念。）

## partial 函数封装

如果需要减少某个函数的参数个数，可以使用 functools.partial() 。 partial() 函数允许给一个或多个参数设置固定的值，减少接下来被调用时的参数个数。假设有下面的函数：

    def spam(a, b, c, d):
        print(a, b, c, d)

现在使用 partial() 函数来固定某些参数值：

    >>> from functools import partial
    >>> s1 = partial(spam, 1) # a = 1
    >>> s1(2, 3, 4)
    1 2 3 4
    >>> s2 = partial(spam, d=42) # d = 42
    >>> s2(1, 2, 3)
    1 2 3 42
    >>> s3 = partial(spam, 1, 2, d=42) # a = 1, b = 2, d = 42
    >>> s3(3)
    1 2 3 42

可以看出，partial() 固定某些参数并返回一个新的callable对象。这个新的callable接受未赋值的参数，然后跟之前已经赋值过的参数合并起来，最后将所有参数传递给原始函数。

# 更多阅读

《Python Cookbook 3》 Chapter 7: Function  
[python参数传递介绍](http://brionas.github.io/2014/03/25/Introduction-python-parameters-pass/)  
[Lambda, filter, reduce and map](http://www.python-course.eu/lambda.php)  
[Python 使用 list 作为函数参数时，参数是否会初始化？](http://www.zhihu.com/question/21924859#answer-11532338)    
[陷阱！python参数默认值](http://selfboot.cn/2014/10/27/python_default_values/)  
[More on Defining Functions](https://docs.python.org/2.7/tutorial/controlflow.html#more-on-defining-functions)  
[How can I read python build-in func source code? eg filter, map, reduce](http://stackoverflow.com/questions/6760899/in-eclipse-how-can-i-read-python-build-in-func-source-code-eg-filter-map-red)   
[Why aren't python nested functions called closures?](http://stackoverflow.com/questions/4020419/why-arent-python-nested-functions-called-closures)  
[Short Description of Python Scoping Rules](http://stackoverflow.com/questions/291978/short-description-of-python-scoping-rules)  
[Sorting Mini-HOW TO](https://wiki.python.org/moin/HowTo/Sorting)    
[python里方法sort()中cmp参数的用法](https://segmentfault.com/q/1010000000405289)  
[hackerrank: ginortS](https://www.hackerrank.com/challenges/ginorts/forum)  
[Python中的闭包](http://www.the5fire.com/closure-in-python.html)   


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Function_1.png

