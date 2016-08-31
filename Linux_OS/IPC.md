进程间通信（IPC，Inter-Process Communication），指至少两个进程或线程间传送数据或信号的一些技术或方法。每个进程都有自己的一部分独立的系统资源，彼此是隔离的。为了能使不同的进程互相访问资源并进行协调工作，才有了进程间通信。

进程通信有如下的目的：

1. 数据传输，一个进程需要将它的数据发送给另一个进程，发送的数据量在一个字节到几M之间；
2. 共享数据，多个进程想要操作共享数据，一个进程对数据的修改，其他进程应该立刻看到；
3. 通知事件，一个进程需要向另一个或一组进程发送消息，通知它们发生了某件事情；
4. 资源共享，多个进程之间共享同样的资源。为了做到这一点，需要内核提供锁和同步机制；
5. 进程控制，有些进程希望完全控制另一个进程的执行（如Debug进程），此时控制进程希望能够拦截另一个进程的所有异常，并能够及时知道它的状态改变。

系统进行进程间通信（IPC）的时候，可用的方式包括`管道、命名管道、消息队列、信号量、共享内存、套接字(socket)`等形式。

Linux中，与IPC相关的命令包括：ipcs、ipcrm（释放IPC）。IPCS命令是Linux下显示进程间通信设施状态的工具。

* ipcs -m: 输出有关共享内存(shared memory)的信息
* ipcs -q: 输出有关信息队列(message queue)的信息

# 管道

管道是由内核管理的一个缓冲区，相当于我们放入内存中的一个管子。管道的一端连接一个进程的输出，这个进程会向管道中放入信息，管道的另一端连接一个进程的输入，这个进程取出被放入管道的信息。当管道中没有信息的话，从管道中读取的进程会等待，直到另一端的进程放入信息。当管道被放满信息的时候，尝试放入信息的进程会等待，直到另一端的进程取出信息。当两个进程都终结的时候，管道也自动消失。

![管道][1]

管道是Linux支持的最初Unix IPC形式之一，具有以下特点：

1. 管道是`半双工`的，数据只能向一个方向流动；需要双方通信时，需要建立起两个管道；
2. 只能在具有公共祖先的两个进程之间使用；
3. 一个进程向管道中写的内容被管道另一端的进程读出。写入的内容每次都添加在管道缓冲区的末尾，并且每次都是从缓冲区的头部读出数据。如果读进程不读走管道缓冲区中的数据，那么写操作将阻塞。

管道是通过调用 pipe 函数创建的。

    #include <unistd.h>
    int pipe(int fd[2])
    // 经由参数fd返回两个文件描述符，fd[0]为读而打开，fd[1]为写而打开。 
    
该函数创建的管道的两端处于一个进程中间，在实际应用中没有太大意义，因此，一个进程在由pipe()创建管道后，一般再fork一个子进程，然后通过管道实现父子进程间的通信。

当管道一段关闭时，下列两条规则起作用：

1. 当 read 一个写端已被关闭的管道时，在所有数据都被读取后，read 返回0，表示文件结束。
2. 如果写一个读端已经关闭的管道，则产生信号 SIGPIPE，write返回－1，errno 设置为 EPIPE。

具体示例程序见 [Linux_OS_Pipe.cpp](../Coding/Linux_OS_Pipe.cpp)

# 命名管道

管道只能用于父进程和子进程之间，或者拥有相同祖先的两个子进程之间 (有亲缘关系的进程之间)，这给我们在不相关的的进程之间交换数据带来了不方便。

为了解决这一问题，Linux 提供了`命名管道`（也被称为FIFO文件），它是一种特殊类型的文件，在文件系统中以文件名的形式存在，但是它的行为却和没有名字的管道（匿名管道）类似。写模式的进程向FIFO文件中写入，而读模式的进程从FIFO文件中读出。当删除FIFO文件时，管道连接也随之消失。FIFO的好处在于我们可以通过文件的路径来识别管道，从而让没有亲缘关系的进程之间建立连接。

可以使用下面的函数来创建一个命名管道，原型如下：

```c++
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *filename, mode_t mode);
```

该函数创建一个真实存在于文件系统中的FIFO文件，filename指定了文件名，而mode则指定了文件的读写权限。注意 mkfifo 函数只是创建一个FIFO文件，要使用的话还得将其打开，可以调用 open 函数来打开，通常有4种方式：

```c++
open(const char *path, O_RDONLY);//阻塞直到有数据可以读
open(const char *path, O_RDONLY | O_NONBLOCK);//    
open(const char *path, O_WRONLY);//3    
open(const char *path, O_WRONLY | O_NONBLOCK);//4  
```

对于以只读方式（O_RDONLY）打开的FIFO文件，如果open调用是阻塞的（即第二个参数为O_RDONLY），除非有一个进程以写方式打开同一个FIFO，否则它不会返回；如果open调用是非阻塞的的（即第二个参数为O_RDONLY | O_NONBLOCK），则即使没有其他进程以写方式打开同一个FIFO文件，open调用将成功并立即返回。

对于以只写方式（O_WRONLY）打开的FIFO文件，如果open调用是阻塞的（即第二个参数为O_WRONLY），open调用将被阻塞，直到有一个进程以只读方式打开同一个FIFO文件为止；如果open调用是非阻塞的（即第二个参数为O_WRONLY | O_NONBLOCK），open总会立即返回。如果没有其他进程以只读方式打开同一个FIFO文件，open调用将返回-1，并且FIFO也不会被打开。

还要注意下面两点：

1. 程序不能以 O_RDWR 模式打开FIFO文件进行读写操作，而其行为也未明确定义，因为如一个管道以读/写方式打开，进程就会读回自己的输出。
2. 传递给open调用的是FIFO的路径名，而不是正常的文件。

具体示例程序见 [Linux_OS_Pipe_Read.cpp](../Coding/Linux_OS_Pipe_R.cpp) 和 [Linux_OS_Pipe_Write.cpp](../Coding/Linux_OS_Pipe_W.cpp)。两个程序都使用阻塞模式的FIFO，Linux_OS_Pipe_Read 读取匿名管道数据，Linux_OS_Pipe_Write 向管道写数据。

首先运行Linux_OS_Pipe_Write，会阻塞在 open 调用上，因为这时候没有进程以只读模式打开命名管道。

```bash
$./Linux_OS_Pipe_W.o
Open named pipe with pending model...
```

接下来运行 Linux_OS_Pipe_Read，此时上面的Linux_OS_Pipe_Write才会写内容到命名管道中，如下：

```bash
Write data:
1111222233334444
```

Linux_OS_Pipe_Read 接着从命名管道中读取数据，输出如下：

```
Read data as follows:
1111
2222
3333
4444
```

# 消息队列



# 信号量


系统如何在进程间传递信号，参考[Linux_OS_Signal.md](Linux_OS_Signal.md)

# 共享内存

共享内存就是允许两个不相关的进程访问同一个逻辑内存。共享内存是在两个正在运行的进程之间共享和传递数据的一种最有效的方式，不同进程之间共享的内存通常安排为同一段物理内存。进程可以将同一段共享内存连接到它们自己的地址空间中，所有进程都可以访问共享内存中的地址，就好像它们是由用C语言函数malloc分配的内存一样。而如果某个进程向共享内存写入数据，所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。

![][6]

注意共享内存并未提供同步机制，也就是说，在第一个进程结束对共享内存的写操作之前，并无自动机制可以阻止第二个进程开始对它进行读取。所以通常需要用其他的机制来同步对共享内存的访问，例如前面说到的信号量。

采用共享内存通信的一个显而易见的好处是`效率高`，因为进程可以直接读写内存，而不需要任何数据的拷贝。对于像管道和消息队列等通信方式，则需要在内核和用户空间进行四次的数据拷贝，而共享内存则只拷贝两次数据：一次从输入文件到共享内存区，另一次从共享内存区到输出文件。

关于共享内存的更多内容参见 [Linux_OX_SharedMemory.md](More/Linux_OX_SharedMemory.md)

# 套接字


# 更多阅读

[Linux进程间通信之管道(pipe)、命名管道(FIFO)与信号(Signal)](http://www.cnblogs.com/biyeymyhjob/archive/2012/11/03/2751593.html)  
[Linux环境进程间通信（一）](https://www.ibm.com/developerworks/cn/linux/l-ipc/part1/)  
[Linux环境进程间通信（五）: 共享内存（上）](http://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html)  
[Linux环境进程间通信（五）: 共享内存（下）](Linux环境进程间通信（五）: 共享内存（下）)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IPC_1.jpg
[6]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_ProcessThread_6.gif


