虽然运行速度慢是 Python 与生俱来的特点，大多数时候我们用 Python 就意味着放弃对性能的追求。但是，就算是用纯 Python 完成同一个任务，老手写出来的代码可能会比菜鸟写的代码块几倍，甚至是几十倍（这里不考虑算法的因素，只考虑语言方面的因素）。

优化的指导精神：

> Only optimize when there is a proven speed bottleneck. Only optimize the innermost loop.
 
# 优化小技巧

## 选择合适的数据结构

`字典 (dictionary) 与列表 (list)`：Python 字典中使用了 hash table，因此查找操作的复杂度为 O(1)，而 list 实际是个数组，在 list 中，查找需要遍历整个 list，其复杂度为 O(n)，因此对成员的查找访问等操作字典要比 list 更快。

`集合 (set) 与列表 (list)`：set 的 union， intersection，difference 操作要比 list 的迭代要快。因此如果涉及到求 list 交集，并集或者差的问题可以转换为 set 来操作。

* set(list1) | set(list2)：包含 list1 和 list2 所有数据的新集合
* set(list1) & set(list2)：包含 list1 和 list2 中共同元素的新集合
* set(list1) - set(list2)：在 list1 中出现但不在 list2 中出现的元素的集合

## 字符串拼接

python 中的字符串对象是不可改变的，因此对任何字符串的操作如拼接，修改等都将产生一个新的字符串对象，而不是基于原字符串，因此这种持续的 copy 会在一定程度上影响 python 的性能。

**使用 join 而不是 + 连接字符串。**避免类似下面的代码片段：

    s = ""
    for x in list: 
        s += func(x)

而是要使用下面这种：
    
    slist = [func(elt) for elt in somelist] 
    s = "".join(slist)

当对字符串可以使用正则表达式或者内置函数来处理的时候，选择`内置函数`。如 `str.isalpha()，str.isdigit()，str.startswith()，str.endswith()` 等。

对字符进行`格式化操作`比直接串联读取要快，因此要使用

    out = "<html>%s%s%s%s</html>" % (head, prologue, query, tail)

而不是

    out = "<html>" + head + prologue + query + tail + "</html>"


## 列表解析、生成器表达式

列表解析要比在循环中重新构建一个新的 list 更为高效。

    a = [w for w in list]
   
比下面的循环高效：
   
    a = []
    for w in list: 
        a.append(w) 

如果只需要迭代一次，最好使用生成器表达式（generator expression）。

使用 xrange 可以节省大量的系统内存，因为 xrange() 在序列中每次调用只产生一个整数元素。而 range() 將直接返回完整的元素列表，用于循环时会有不必要的开销。在 python3 中 xrange 不再存在，里面 range 提供一个可以遍历任意长度的范围的 iterator。

## 使用内置操作

用 map, reduce 而不是 for、while 循环。
    
    def toUpper(item):
        return item.upper()
    upper_name = map(toUpper, ["hao", "chen", "coolshell"])
    print upper_name
    # 输出 ['HAO', 'CHEN', 'COOLSHELL']

对于map别忘了lambda表达式：可以简单地理解为这是一个inline的匿名函数。下面的lambda表达式相当于：`def func(x): return x*x`

    squares = map(lambda x: x * x, range(9))
    print squares
    # 输出 [0, 1, 4, 9, 16, 25, 36, 49, 64]

下面的lambda表达式中有两个参数，也就是说每次从列表中取两个值，计算结果后把这个值再放回去，下面的表达式相当于：((((1+2)+3)+4)+5) ）

    print reduce(lambda x, y: x+y, [1, 2, 3, 4, 5])
    # 输出 15

Python中的除了map和reduce外，还有一些别的如filter, find, all, any的函数做辅助，可以让代码更简洁，更易读，更高效。（没有了循环体，于是就可以少了些临时变量，以及变量倒来倒去的逻辑。）

## 适时创建局部变量

如果需要在循环中使用全局变量，最好是在循环前创建一个临时的局部变量，然后循环中使用这个局部变量。这是因为 Python 访问局部变量比全局变量快很多。

考虑下面的例子：

    newlist = []
    for word in oldlist:
        newlist.append(word.upper())
    
上面的代码中每次循环都要调用 newlist.append 和 word.upper 两个全局函数。如果改成下面的代码，效率会高很多。

    upper = str.upper
    newlist = []
    append = newlist.append
    for word in oldlist:
        append(upper(word))
    return newlist

这样做的时候要小心，特别是循环体比较长的时候，必须清楚前面局部变量的定义。

# 性能诊断

最直接的想法是在开始 replace 函数之前记录时间，程序结束后再记录时间，计算时间差即为程序运行时间。python提供了模块 time，其中 time.clock() 在Unix/Linux下返回的是CPU时间(浮点数表示的秒数)，Win下返回的是以秒为单位的真实时间(Wall-clock time)。

上面手工插时间断点的方法十分原始，用起来不是那么方便，即使用了上下文管理器实现起来还是略显笨重。还好 Python 提供了timeit模块，用来测试代码块的运行时间。它既提供了命令行接口，又能用于代码文件之中。

更复杂的情况下，可以用标准库里面的profile或者cProfile，它可以统计程序里每一个函数的运行时间，并且提供了可视化的报表。大多情况下，建议使用cProfile，它是profile的C实现，适用于运行时间长的程序。不过有的系统可能不支持cProfile，此时只好用profile。

可以用下面程序测试 timeit_profile() 函数运行时间分配情况。

    import cProfile
    from time_profile import *
    
    cProfile.run("timeit_profile()")

性能诊断的更多详细内容可以看我的博客：[Python 性能分析大全](http://selfboot.cn/2016/06/13/python_performance_analysis/)。
 
# 更多阅读

[My program is too slow. How do I speed it up?](https://docs.python.org/2/faq/programming.html#my-program-is-too-slow-how-do-i-speed-it-up)   
[PerformanceTips](https://wiki.python.org/moin/PythonSpeed/PerformanceTips)  
[Python Patterns - An Optimization Anecdote](https://www.python.org/doc/essays/list2str/)  
[函数式编程](http://coolshell.cn/articles/10822.html)  
[Python 代码性能优化技巧](http://www.ibm.com/developerworks/cn/linux/l-cn-python-optim/)  


