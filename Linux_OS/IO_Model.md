# I/O 模型

Unix 下有5种可用的 I/O 模型，如下：

* 阻塞式 I/O
* 非阻塞式 I/O
* I/O 复用（select 和 poll）
* 信号驱动 I/O
* 异步I/O

对于一个套接口上的读写操作，其实分成了两个步骤：发起IO请求和实际的IO操作。第一步通常涉及等待数据从网络中到达，当所等待分组到达时，它被拷贝到内核中的某个缓冲区。第二步就是把数据从内核缓冲区拷贝到应用进程缓冲区。

## 阻塞式 I/O

最流行的 I/O 模型是阻塞式I/O模型，默认情况下，所有套接字都是阻塞的。以数据报套接字为例，如下图所示：

![][1]

进程调用recvfrom，其系统调用直到数据报到达且被拷贝到应用进程的缓冲区中或者发生错误才返回。进程从调用recvfrom开始到它返回的整段时间内是`被阻塞`的。recvfrom成功返回后，应用进程开始处理数据。

## 非阻塞式 I/O

进程把一个套接口设置成非阻塞是在通知内核：当所请求的I/O操作导致进程只能 sleep 时，不要让本进程 sleep，而是直接返回一个错误。下图展示了非阻塞I/O模型。

![][2]

前三次调用recvfrom时没有数据可返回，因此内核转而立即返回一个EWOULDBLOCK错误。第四次调用recvfrom时已有数据报准备好，它被拷贝到应用进程缓冲区，recvfrom于是成功返回。我们接着处理数据。

当一个应用进程像这样对一个非阻塞描述字循环调用recvfrom时，我们称之为`轮询（polling）`。应用进程持续轮询内核，以查看某个操作是否就绪。这么做往往耗费大量CPU时间，不过这种模型偶尔也会遇到，通常是在只专门提供某种功能的系统中才有。

## I/O 复用

I/O多路复用就是通过一种机制，一个进程可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作。

IO多路复用适用如下场合：

1. 当客户处理多个描述字时（一般是交互式输入和网络套接口），必须使用I/O复用。
2. 当一个客户同时处理多个套接口时（这种情况是可能的，但很少出现）
3. 如果一个TCP服务器既要处理监听套接口，又要处理已连接套接口，一般也要用到I/O复用。
4. 如果一个服务器即要处理TCP，又要处理UDP，一般要使用I/O复用。
5. 如果一个服务器要处理多个服务或多个协议，一般要使用I/O复用。

I/O 复用并非只限于网络编程，许多重要的应用程序也需要这项技术。有了I/O复用（I/O multiplexing），就可以调用select或poll，阻塞在这两个系统调用中的某一个之上，而不是阻塞在真正的I/O系统调用上，下图展示了I/O复用模型。

![][3]

我们阻塞于select调用，等待数据报套接口变为可读。当select返回套接口可读这一条件时，我们调用recvfrom把所读数据报拷贝到应用进程缓冲区。

比较I/O复用模型和阻塞I/O模型，I/O复用并没有显示出什么优势，事实上由于使用select需要使用两个而不是单个系统调用，I/O复用还稍有劣势。使用select的优势在于我们可以等待多个描述字就绪。

## 信号驱动 I/O

也可以用信号让内核在描述字就绪时发送SIGIO信号通知我们。我们称这种模型为信号驱动I/O（signal-driven I/O），如下图所示

![][4]

首先开启套接口的信号驱动I/O功能，并通过sigaction系统调用设置一个信号处理函数，该系统调用立即返回。进程继续工作，也就是说它没有被阻塞。当数据报准备好读取时，内核就为该进程产生一个SIGIO信号。随后既可以在信号处理函数中调用recvfrom读取数据报，并通知主循环数据已准备好待处理，也可以立即通知主循环，让它读取数据报。

无论如何处理SIGIO信号，这种模型的优势在于等待数据报到达期间，进程不被阻塞。主循环可以继续执行，只要不时等待来自信号处理函数的通知：既可以是数据已准备好被处理，也可以是数据报已准备好被读取。

## 异步I/O

异步I/O（asynchronous I/O）由POSIX规范定义。一般地说，这些函数的工作机制是：告知内核启动某个操作，并让内核在整个操作（包括将数据从内核拷贝到我们自己的缓冲区）完成后通知我们。这种模型与信号驱动模型的主要区别在于：**信号驱动I/O是由内核通知我们何时启动一个I/O操作，而异步I/O模型是由内核通知我们I/O操作何时完成。**

![][5]

我们调用aio_read函数（POSIX异步I/O函数以aio_或lio_开头），给内核传递描述字、缓冲区指针、缓冲区大小（与read相同的三个参数）、文件偏移（与lseek类似），并告诉内核当整个操作完成时如何通知我们。该系统调用立即返回，在等待I/O完成期间，我们的进程不被阻塞。

## 各模型比较

前4种模型主要区别在第一阶段，它们的第二阶段都是一样的：在数据从内核复制到调用者的缓冲区期间，进程阻塞于 recvfrom 调用。

![][6]

POSIX关于同步、异步的定义如下:

1. `同步I/O操作`（synchronous I/O operation）导致请求进程阻塞，直到I/O操作完成。
2. `异步I/O操作`（asynchronous I/O operation）不导致请求进程阻塞。

可以这样理解：

* 阻塞IO和非阻塞IO的区别在于第一步：发起IO请求是否会被阻塞，如果阻塞直到完成那么就是传统的阻塞IO；如果不阻塞，那么就是非阻塞IO
* 同步IO和异步IO的区别就在于第二个步骤是否阻塞，如果实际的IO读写阻塞请求进程，那么就是同步IO，因此阻塞IO、非阻塞IO、IO复用、信号驱动IO都是同步IO；如果不阻塞，而是操作系统帮你做完IO操作再将结果返回给你，那么就是异步IO。

根据上述定义，前4种模型——阻塞I/O模型、非阻塞I/O模型、I/O复用模型和信号驱动I/O模型都是同步I/O模型，因为其中真正的I/O操作（recvfrom）将阻塞进程。只有异步I/O模型与POSIX定义的异步I/O相匹配。

关于同步/异步、阻塞/非阻塞可以这样理解，拿小明下载文件打个比方：

1. 同步阻塞：小明一直盯着下载进度条，到 100% 的时候就完成。
2. 同步非阻塞：小明提交下载任务后就去干别的，每过一段时间就去瞄一眼进度条，看到 100% 就完成。
3. 异步阻塞：小明换了个有下载完成通知功能的软件，下载完成就“叮”一声。不过小明仍然一直等待“叮”的声音（看起来很傻，不是吗）
4. 异步非阻塞：仍然是那个会“叮”一声的下载软件，小明提交下载任务后就去干别的，听到“叮”的一声就知道完成了。

也就是说，同步/异步是下载软件的通知方式，或者说 `API 被调用者的通知方式`。阻塞/非阻塞则是小明的等待方式，或者说 `API 调用者的等待方式`。在不同的场景下，同步/异步、阻塞/非阻塞的四种组合都有应用。

# I/O 多路复用

select，poll，epoll都是IO多路复用的机制，它们本质上都是同步I/O，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。

## select

该函数允许进程指示内核等待多个事件中的任何一个发送，并只在有一个或多个事件发生或经历一段指定的时间后才唤醒。也就是说调用 select 告知内核对哪些描述符（读、写或异常条件）感兴趣以及等待多长时间。

    #include <sys/select.h>
    #include <sys/time.h>
    
    int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
    // 返回值：就绪描述符的数目，超时返回0，出错返回-1

函数参数介绍如下：

1. 第一个参数maxfdp1指定待测试的描述字个数，它的值是待测试的最大描述字加1（因此把该参数命名为maxfdp1），描述字0、1、2...maxfdp1-1 均将被测试，因为文件描述符是从0开始的。
2. 中间的三个参数readset、writeset和exceptset指定我们要让内核测试读、写和异常条件的描述字。如果对某一个的条件不感兴趣，就可以把它设为空指针。struct fd_set可以理解为一个集合，这个集合中存放的是文件描述符。
3. timeout告知内核等待所指定描述字中的任何一个就绪可花多少时间。其timeval结构用于指定这段时间的秒数和微秒数。

timeout 有三种可能：

* 永远等待下去：仅在有一个描述字准备好I/O时才返回。为此，把该参数设置为空指针NULL。
* 等待一段固定时间：在有一个描述字准备好I/O时返回，但是不超过由该参数所指向的timeval结构中指定的秒数和微秒数。
* 根本不等待：检查描述字后立即返回，这称为轮询。为此，该参数必须指向一个timeval结构，而且其中的定时器值必须为0。

select目前几乎在所有的平台上支持，其良好跨平台支持也是它的一个优点。select的一个缺点在于`单个进程能够监视的文件描述符的数量存在最大限制，在Linux上一般为1024`，可以通过修改宏定义甚至重新编译内核的方式提升这一限制，但是这样也会造成效率的降低。

## poll

poll的机制与select类似，本质上没有多大差别，管理多个描述符也是进行`轮询`。根据描述符的状态进行处理，但是poll没有最大文件描述符数量的限制。poll和select同样存在一个缺点就是，包含大量文件描述符的数组被整体复制于用户态和内核的地址空间之间，而不论这些文件描述符是否就绪，它的开销随着文件描述符数量的增加而线性增大。

    # include <poll.h>
    int poll ( struct pollfd * fds, unsigned int nfds, int timeout);

pollfd结构体定义如下：

    struct pollfd {
        int fd;              /* 文件描述符 */
        short events;        /* 等待的事件 */
        short revents;       /* 实际发生了的事件 */
    } ; 
    
每一个pollfd结构体指定了一个被监视的文件描述符，可以传递多个结构体，指示poll()监视多个文件描述符。

## epoll 

epoll是在2.6内核中提出的，是之前的select和poll的增强版本。相对于select和poll来说，epoll更加灵活，没有描述符限制。epoll使用一个文件描述符管理多个描述符，将用户关系的文件描述符的事件存放到内核的一个事件表中，这样在用户空间和内核空间的copy只需一次。

epoll操作过程需要三个接口，分别如下：

    #include <sys/epoll.h>
    int epoll_create(int size);
    int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);

三个接口解释如下：

1. int epoll_create(int size);      

    创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/pid/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

2. int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

    epoll的事件注册函数，它不同于select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。
    
    * 第一个参数是epoll_create()的返回值，
    * 第二个参数表示动作，用三个宏来表示：EPOLL_CTL_ADD：注册新的fd到epfd中；EPOLL_CTL_MOD：修改已经注册的fd的监听事件；EPOLL_CTL_DEL：从epfd中删除一个fd；
    * 第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事，

3. int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);

    等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。该函数返回需要处理的事件数目，如返回0表示已超时。

在 epoll_create 的过程中，会创建一个 eventpoll 结构体，这个结构体的部分定义如下：

    struct eventpoll{
        ...  
        struct rb_root rbr; //红黑树，存储了所有添加到 epoll 中的事件
        struct list_head rdllist; // 双向链表保存通过 epoll_wait 返回给用户的满足条件的事件
        ...
    }

这里的红黑树 rbr 存储了所有已经添加到 epoll 中的事件，如果使用 epoll_ctl 进行事件操作的时候，会在红黑树中进行查找，这个效率是很高的。

双向链表 rdllist 则保存将要返回给用户的满足条件的事件。这个准备就绪list链表是怎么维护的呢？当我们执行epoll_ctl时，除了把socket放到epoll文件系统里file对象对应的红黑树上之外，还会给内核中断处理程序注册一个`回调函数`，告诉内核，如果这个句柄的中断到了，就把它放到准备就绪list链表里。所以，当一个socket上有数据到了，内核在把网卡上的数据copy到内核中后就来把socket插入到准备就绪链表里了。

当epoll_wait调用时，仅仅观察这个list链表里有没有数据即可。有数据就返回，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。所以，epoll_wait非常高效。

如此，一颗红黑树，一张准备就绪句柄链表，少量的内核cache，就帮我们解决了大并发下的socket处理问题。执行epoll_create时，创建了`红黑树和就绪链表`，执行epoll_ctl时，如果增加socket句柄，则检查在红黑树中是否存在，存在立即返回，不存在则添加到树干上，然后向内核注册回调函数，用于当中断事件来临时向准备就绪链表中插入数据。执行epoll_wait时立刻返回准备就绪链表里的数据即可。

epoll对文件描述符的操作有两种模式：`LT（level trigger，水平触发）` 和`ET（edge trigger，边缘触发）`。LT模式是默认模式，LT模式与ET模式的区别如下：

* 水平触发模式：当epoll_wait检测到描述符事件发生并将此事件通知应用程序，应用程序可以不立即处理该事件。下次调用epoll_wait时，会再次响应应用程序并通知此事件。
* 边缘触发模式：当epoll_wait检测到描述符事件发生并将此事件通知应用程序，应用程序必须立即处理该事件。如果不处理，下次调用epoll_wait时，不会再次响应应用程序并通知此事件。

水平触发的话，如果某一次没有处理，那么下一次还会返回给用户，但是边缘触发的话，只在事件发生时返回给用户一次，如果用户忽略掉了，那么后面就不会再返回给用户了。

这件事怎么做到的呢？当一个socket句柄上有事件时，内核会把该句柄插入上面所说的准备就绪list链表，这时我们调用epoll_wait，会把准备就绪的socket拷贝到用户态内存，然后清空准备就绪list链表。最后，epoll_wait检查这些socket，如果不是ET模式（就是LT模式的句柄了），并且这些socket上确实有未处理的事件时，又把该句柄放回到刚刚清空的准备就绪链表了。所以，非ET的句柄，只要它上面还有事件，epoll_wait每次都会返回。而ET模式的句柄，除非有新中断到，即使socket上的事件没有处理完，也是不会次次从epoll_wait返回的。

ET 触发模式在很大程度上减少了epoll事件被重复触发的次数，因此效率要比LT模式高。~~epoll工作在ET模式的时候，必须使用非阻塞套接口，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死~~。

## 优缺点比较

select的几大缺点：

1. 每次调用select，都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时会很大。
2. select 会对所有的感兴趣的 fd 一个个去检查是否就绪，这样就行成了一个`轮询`，这个是比较慢的，而 epoll 则通过设置回调函数，在有事件发生的时候，将事件添加到双向链表中，最后只需要检查双向链表是否为空即可，这个也是很高效的。
3. select 用的是 FD_SET 进行操作，而 FD_SET 有上限限制（可以通过自己改源码进行修改），但是 epoll 没有这个限制。

epoll是对select和poll的改进，避免了上述的三个缺点。我们先看一下epoll和select和poll的调用接口上的不同，select和poll都只提供了一个函数——select或者poll函数。而epoll提供了三个函数，epoll_create, epoll_ctl和epoll_wait，epoll_create是创建一个epoll句柄；epoll_ctl是注册要监听的事件类型；epoll_wait则是等待事件的产生。

对于第一个缺点，epoll的解决方案在epoll_ctl函数中。每次注册新的事件到epoll句柄中时，会把所有的fd拷贝进内核，而不是在epoll_wait的时候重复拷贝。epoll保证了每个fd在整个过程中只会拷贝一次。

对于第二个缺点，epoll的解决方案不像select或poll一样每次都把current轮流加入fd对应的设备等待队列中，而只在epoll_ctl时把current挂一遍（这一遍必不可少）并为每个fd指定一个回调函数，当设备就绪，唤醒等待队列上的等待者时，就会调用这个`回调函数`，而这个回调函数会把就绪的fd加入一个就绪链表。

epoll_wait的工作实际上就是在这个就绪链表中查看有没有就绪的fd。而且，通常情况下即使我们要监控百万计的句柄，大多一次也只返回很少量的准备就绪句柄而已，所以，epoll_wait仅需要从内核态copy少量的句柄到用户态而已，所以很高效！

对于第三个缺点，epoll没有这个限制，它所支持的FD上限是最大可以打开文件的数目，这个数字一般远大于2048，举个例子，在1GB内存的机器上大约是10万左右，具体数目可以cat /proc/sys/fs/file-max 查看，一般来说这个数目和系统内存关系很大。

总结如下：

1. select，poll实现需要自己不断轮询所有fd集合，直到设备就绪，期间可能要睡眠和唤醒多次交替。而epoll其实也需要调用epoll_wait不断轮询就绪链表，期间也可能多次睡眠和唤醒交替，**但是它是设备就绪时，调用回调函数，把就绪fd放入就绪链表中，并唤醒在epoll_wait中进入睡眠的进程。**虽然都要睡眠和交替，但是select和poll在“醒着”的时候要遍历整个fd集合，而epoll在“醒着”的时候只要判断一下就绪链表是否为空就行了，这节省了大量的CPU时间。这就是`回调机制`带来的性能提升。
2. select，poll每次调用都要把fd集合从用户态往内核态拷贝一次，并且要把current往设备等待队列中挂一次，而epoll只要一次拷贝，而且把current往等待队列上挂也只挂一次（在epoll_wait的开始，注意这里的等待队列并不是设备等待队列，只是一个epoll内部定义的等待队列）。这也能节省不少的开销。

## 多线程阻塞式I/O

与 I/O 复用密切相关的另一种 I/O 模型是在多线程中使用阻塞式 I/O。这种模型与上述模型极为相似，但它没有使用 select 阻塞在多个描述符上，而是使用多个线程，每个线程阻塞在一个描述符上。

# 更多阅读

[Unix五种I/O模型对比](http://sukai.me/linux-five-io-models/)  
[IO多路复用之select总结](http://www.cnblogs.com/Anker/archive/2013/08/14/3258674.html)  
[IO多路复用之epoll总结](http://www.cnblogs.com/Anker/archive/2013/08/17/3263780.html)  
[select、poll和epoll简介](http://blog.arganzheng.me/posts/select-poll-and-epoll.html)  
[Linux IO模式及 select、poll、epoll详解](https://segmentfault.com/a/1190000003063859)  
[使用事件驱动模型实现高效稳定的网络服务器程序](http://www.ibm.com/developerworks/cn/linux/l-cn-edntwk/index.html?ca=drs-)  
[聊聊 Linux 中的五种 IO 模型](http://blog.jobbole.com/99905/)  
[大话同步/异步、阻塞/非阻塞](https://ring0.me/2014/11/sync-async-blocked/)  
[处理大并发之一 对异步非阻塞的理解](http://blog.csdn.net/feitianxuxue/article/details/8936802)  
[阻塞、非阻塞、同步、异步](http://ajucs.com/2016/09/20/blocking-nonblocking-sync-async.html)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_4.png
[5]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_5.png
[6]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IO_Model_6.png


