# 多线程 —— GIL的限制

在 Python 语言的主流实现 CPython 中，`GIL（Global Interpreter Lock，全局解释器锁）`是一个货真价实的全局线程锁，在解释器解释执行任何 Python 代码时，都需要先获得这把锁才行，在遇到 I/O 操作时会释放这把锁。如果是纯计算的程序，没有 I/O 操作，解释器会每隔一定次数的操作就释放这把锁，让别的线程有机会执行（这个次数可以通过sys.setcheckinterval 来调整）。

所以虽然 CPython 的线程库直接封装操作系统的原生线程，但 CPython 进程做为一个整体，同一时间只会有一个获得了 GIL 的线程在跑，其它的线程都处于等待状态等着 GIL 的释放。官网这样解释 GIL：

> In CPython, the global interpreter lock, or GIL, is a mutex that prevents multiple native threads from executing Python bytecodes at once. This lock is necessary mainly because CPython’s memory management is not thread-safe. (However, since the GIL exists, other features have grown to depend on the guarantees that it enforces.)

下面用例子来理解下 GIL 机制下python 只能运行单线程这一事实。首先看一个简单的死循环片段：

    def dead_loop():
        while True:
            pass
    
    dead_loop()

在双核 CPU 上运行这段代码，会吃掉一个核的工作负荷，也就是说会占用50％左右的CPU。那么如何能在双核机器上占用 100％ 的CPU呢？熟悉操作系统的话，很容易想到，用两个线程并行地各跑一个死循环线程就可以了。用 C++ 的多线程实现的话，确实是这样。但是用Python开两个死循环线程并不能占用 100% CPU。如下代码：

    import threading
    def dead_loop():
        while True:
            pass
    
    # 新起一个死循环线程
    t = threading.Thread(target=dead_loop)
    t.start()
    
    # 主线程也进入死循环
    dead_loop()
    t.join()

上面的代码并没有占用两个核的 CPU 资源，仍然是只占用了50%左右的CPU。这是因为虽然有两个死循环的线程，而且有两个物理 CPU 内核，但因为 GIL 的限制，两个线程只是做着分时切换，同一时间只有一个线程在一个CPU核上运行，总有一个CPU依旧是空闲的。

为了更加直观地理解GIL对于多线程带来的性能影响，这里直接借用的一张测试结果图（见下图）。图中表示的是两个线程在双核CPU上得执行情况，两个线程均为CPU密集型运算线程。绿色部分表示该线程在运行，且在执行有用的计算，红色部分为线程被调度唤醒，但是无法获取GIL导致无法进行有效运算等待的时间。 

![][1]

由图可见，GIL的存在导致多线程无法很好的利用多核CPU的并发处理能力。为了弥补多线程并不能真正并行计算的问题，python在 2.6 里引入了multiprocessing，它完整的复制了一套thread所提供的接口方便迁移，唯一的不同就是它使用了多进程而不是多线程。每个进程有自己的独立的GIL，因此也不会出现进程之间的GIL争抢，但是进程的创建、切换代价会高很多，并且进程间通信也相对复杂。

如果不想用多进程这样重量级的解决方案，可以把关键部分用 C/C++ 写成 Python 扩展，其它部分还是用 Python 来写，让 Python 的归 Python，C 的归 C。一般计算密集性的程序都会用 C 代码编写并通过扩展的方式集成到 Python 脚本里（如 NumPy 模块）。在扩展里就完全可以用 C 创建原生线程，而且不用锁 GIL，充分利用 CPU 的计算资源了。

不过，写 Python 扩展总是让人觉得很复杂。好在 Python 还有另一种与 C 模块进行互通的机制 : ctypes。ctypes 与 Python 扩展不同，它可以让 Python 直接调用任意的 C 动态库的导出函数。你所要做的只是用 ctypes 写些 python 代码即可。最酷的是，ctypes 会在调用 C 函数前释放 GIL。所以，我们可以通过 ctypes 和 C 动态库来让 python 充分利用物理内核的计算能力。

# 协程 —— 轻量级线程

对于IO密集型任务来说，多线程仍然有一定的效果。因为在I/O请求的时候，当一个线程因I/O请求阻塞，可以调用另一个线程来继续发起对另一个Url的请求。当第一个线程的I/O请求得到回应时，它再次得到运行。（示例程序在 [gist](https://gist.github.com/xuelangZF/fd6d7ace685853945c589285ab2d7b1f) 上）

但是多线程处理 IO 密集问题时仍然不是很完美，当线程多的时候，线程的切换是一件十分耗时的工作。于是python里面提供了另一个比较好玩的东西：`协程（Coroutine）`。

所谓协程就是在同一进程/线程中，利用生成器来同时执行多个函数(routine)。我们知道对于普通的Python函数（或者叫子程序）来说，一般是从函数的第一行代码开始执行，然后结束于return语句、异常或者函数结束（可以看作隐式的返回None）。一旦函数将控制权交还给调用者，就意味着全部结束。函数中做的所有工作以及保存在局部变量中的数据都将丢失，再次调用这个函数时，一切都将从头创建。

而协程看上去也是子程序，但执行过程中，在子程序内部可中断，然后转而执行别的子程序，在适当的时候再返回来接着执行。注意，这里在一个子程序中中断，去执行其他子程序，不是函数调用，有点类似CPU的中断。比如子程序A、B：

    def A():
        print '1'
        print '2'
    
    def B():
        print 'x'
        print 'y'

假设由协程执行，在执行A的过程中，可以随时中断，去执行B，但是在A中是没有调用B的。B也可能在执行过程中中断再去执行A，结果可能是 1 x 2 y 或者 1 x y 2。

看起来A、B的执行有点像多线程，但协程的特点是在一个线程内执行，那和多线程比，协程有何优势？

* 协程有极高的执行效率。因为子程序切换不是线程切换，而且由程序自身控制，因此，没有线程切换的开销。和多线程比，线程数量越多，协程的性能优势就越明显。
* 不需要多线程的锁机制，因为只有一个线程，也不存在同时写变量冲突，在协程中控制共享资源不加锁，只需要判断状态就好了，所以执行效率比多线程高很多。

因为协程是一个线程执行，那怎么利用多核CPU呢？最简单的方法是多进程+协程，既充分利用多核，又充分发挥协程的高效率，可获得极高的性能。

# yield 与生成器

Python 语言内置了对协程的支持，主要是利用了 yield 和 生成器，关于 yield 和生成器的详细解释，可以参考 [Python_Iterator_Generator_Yield.md] (Python_Iterator_Generator_Yield.md)。




# Greenlet, Gevent

生成器本身不是一个完整的协程实现，所以 Python 的第三方库中还有一个优秀的替代品 [greenlet](https://github.com/python-greenlet/greenlet)。


# 更多阅读

[python 线程，GIL 和 ctypes](http://zhuoqiang.me/python-thread-gil-and-ctypes.html)  
[Python GIL以及多线程性能](http://cenalulu.github.io/python/gil-in-python/)  
[Python的多进程、多线程、协程](https://www.zybuluo.com/chyoo1991/note/179220)  
[利用python yielding创建协程将异步编程同步化](http://www.jackyshen.com/2015/05/21/async-operations-in-form-of-sync-programming-with-python-yielding/)  
[Python Doc：Yield expressions](https://docs.python.org/2/reference/expressions.html#yield-expressions)  
[Python yield 使用浅析](http://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/)  
[Greenlet Vs. Threads](http://stackoverflow.com/questions/15556718/greenlet-vs-threads)  
[gevent程序员指南](http://xlambda.com/gevent-tutorial/)  
[用 greenlet 协程处理异步事件](https://blog.tonyseek.com/post/event-manage-with-greenlet/)  





[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Python_Coroutine_1.png

