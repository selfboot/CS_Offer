共享内存就是允许两个不相关的进程访问同一个逻辑内存。共享内存是在两个正在运行的进程之间共享和传递数据的一种最有效的方式，不同进程之间共享的内存通常安排为同一段物理内存。

进程可以将同一段共享内存连接到它们自己的地址空间中，所有进程都可以访问共享内存中的地址，就好像它们是由用C语言函数malloc分配的内存一样。而如果某个进程向共享内存写入数据，所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。

# 实现原理

共享内存可以通过mmap()映射普通文件 （特殊情况下还可以采用匿名映射）机制实现，也可以通过系统V共享内存机制实现。


（共享内存段被映射进进程空间之后，存在于进程空间的什么位置？共享内存段最大限制是多少？）


# 更多阅读
[IPC:Shared Memory](https://www.cs.cf.ac.uk/Dave/C/node27.html)  
[Linux进程间通信——使用共享内存](http://blog.csdn.net/ljianhui/article/details/10253345)  
[10 IPCS Command Examples (With IPC Introduction)](http://www.thegeekstuff.com/2010/08/ipcs-command-examples/)  

