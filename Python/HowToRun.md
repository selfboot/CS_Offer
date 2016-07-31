简单来说，Python先把代码（.py文件）编译成字节码，交给字节码虚拟机，然后虚拟机一条一条执行字节码指令，从而完成程序的执行。这里字节码在Python虚拟机程序里对应的是`PyCodeObject对象`，.pyc文件是字节码在磁盘上的表现形式。

# PyCodeObject

PyCodeObject 对象的创建时机是模块加载的时候，即import。例如执行 Python test.py 会对test.py进行编译成字节码并解释执行，但是不会生成test.pyc。如果test.py加载了其他模块，如import util，Python会对util.py进行编译成字节码，生成util.pyc，然后对字节码解释执行。

如果想生成test.pyc，我们可以使用Python内置模块py_compile来编译。加载模块时，如果同时存在.py和.pyc，Python会尝试使用.pyc，如果.pyc的编译时间早于.py的修改时间，则重新编译.py并更新.pyc。


## 解析PyCodeObject

Python提供了内置函数compile可以编译Python代码和查看PyCodeObject对象，如下：


# Python 运行慢的原因
  
我们知道和 C/C++ 相比，Python效率确实不高，那么有哪些原因导致了Python 的低效呢？

1. Python 是动态类型，C++ 是静态类型；
2. Python 是解释型语言，C++是编译型的。
3. Python 的对象模型导致低效的内存访问。

# 更多阅读

[Python程序的执行原理](http://tech.uc.cn/?p=1932)  
[谈谈 Python 程序的运行原理](http://www.restran.net/2015/10/22/how-python-code-run/)  
[Why Python is Slow: Looking Under the Hood](https://jakevdp.github.io/blog/2014/05/09/why-python-is-slow/)  

