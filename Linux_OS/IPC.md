进程间通信（IPC，Inter-Process Communication），指至少两个进程或线程间传送数据或信号的一些技术或方法。每个进程都有自己的一部分独立的系统资源，彼此是隔离的。为了能使不同的进程互相访问资源并进行协调工作，才有了进程间通信。

进程通信有如下的目的：

1. 数据传输，一个进程需要将它的数据发送给另一个进程，发送的数据量在一个字节到几M之间；
2. 共享数据，多个进程想要操作共享数据，一个进程对数据的修改，其他进程应该立刻看到；
3. 通知事件，一个进程需要向另一个或一组进程发送消息，通知它们发生了某件事情；
4. 资源共享，多个进程之间共享同样的资源。为了做到这一点，需要内核提供锁和同步机制；
5. 进程控制，有些进程希望完全控制另一个进程的执行（如Debug进程），此时控制进程希望能够拦截另一个进程的所有异常，并能够及时知道它的状态改变。

系统进行进程间通信（IPC）的时候，可用的方式包括`管道、命名管道、消息队列、信号、信号量、共享内存、套接字(socket)`等形式。

Linux中，与IPC相关的命令包括：ipcs（显示 IPC 信息）、ipcrm（释放IPC）：

* ipcs -a: 显示所有的IPC设施
* ipcs -m: 输出有关共享内存(shared memory)的信息
* ipcs -q: 输出有关信息队列(message queue)的信息
* ipcrm -m id: 删除共享内存
* ipcrm -s id: 删除共享信号量
* ipcrm -q id: 删除共享队列

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

消息队列实际上就是一个链表，而消息就是链表中具有特定格式和优先级的记录，对消息队列有写权限的进程可以根据一定规则在消息链表中添加消息，对消息队列有读权限的进程则可以从消息队列中获得所需的信息。

在某个进程往一个消息队列写入消息之前，并不需要另外某个进程在该队列上等待消息的到达。这跟命名管道是不同的，对后者来说，除非读端已经存在，否则写端的打开管道操作会一直阻塞。此外，管道和命名管道都是随进程持续的，而消息队列还有后面的信号量、共享内存都是随内核持续的。也就是说当一个管道或FIFO的最后一次关闭发生时，仍在该管道或FIFO上的数据将被丢弃。而对于消息队列来说，除非内核自举或显式删除，否则其一直存在。

对于系统中的每个消息队列，内核维护一个定义在`<sys/msg.h>`头文件中的消息队列结构。

```c++
struct msqid_ds {
    struct ipc_perm msg_perm ;
    struct msg*    msg_first ; //指向队列中的第一个消息
    struct msg*    msg_last ; //指向队列中的最后一个消息
    ...
};
```

Linux 中还提供了一系列消息队列的函数接口来让我们方便地使用它来实现进程间的通信，如下：

```c++
// 创建和访问一个消息队列
int msgget(key_t key, int msgflg);  
// key 用来命名某个特定的消息队列，msgflg是一个权限标志，表示消息队列的访问权限，它与文件的访问权限一样。
// 它返回一个以key命名的消息队列的标识符（非零整数），失败时返回-1.

// 该函数用来把消息添加到消息队列中
int msgsnd(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);  
// msgid是由msgget函数返回的消息队列标识符
// msg_ptr是一个指向消息的指针，这里对消息的数据结构有一定的要求，即必须是一个以长整型成员变量开始的结构体，接收函数将用这个成员来确定消息的类型。
// msg_sz是msg_ptr指向的消息的长度，注意是消息的长度，而不是整个结构体的长度，也就是说msg_sz是不包括长整型消息类型成员变量的长度。
// msgflg用于控制当前消息队列满或队列消息到达系统的限制时将要发生的事情。
// 如果调用成功，消息数据的一分副本将被放到消息队列中，并返回0，失败时返回-1.

// 该函数用来从一个消息队列获取消息
int msgrcv(int msgid, void *msg_ptr, size_t msg_st, long int msgtype, int msgflg);  
// msgid, msg_ptr, msg_st的作用也函数 msgsnd 函数的一样。
// msgtype 可以实现一种简单的接收优先级。如果msgtype为0，就获取队列中的第一个消息。如果它的值大于零，将获取具有相同消息类型的第一个信息。如果它小于零，就获取类型等于或小于msgtype的绝对值的第一个消息。
// msgflg 用于控制当队列中没有相应类型的消息可以接收时将发生的事情。
// 调用成功时，该函数返回放到接收缓存区中的字节数，消息被复制到由msg_ptr指向的用户分配的缓存区中，然后删除消息队列中的对应消息。失败时返回-1.

// 该函数用来控制消息队列
int msgctl(int msgid, int command, struct msgid_ds *buf);  
```

下面是一个具体的例子来展示如何使用消息队列进行进程间通信，进程 [rcv](../Coding/Linux_OS_MsgQ_Rcv.cpp) 用来从消息队列接受消息，进程 [snd](../Coding/Linux_OS_MsgQ_Snd.cpp) 用来发送消息。我们首先运行 Snd 来发送消息，然后运行 Rcv 接受，如下所示：

```bash
$ ./snd.o
Enter some text: This is a demo.
Enter some text: new content
Enter some text: end
$ ./rcv.o
You wrote: This is a demo.

You wrote: new content

You wrote: end

```

注意如果将 rcv 中 msgtype = 2，那么 rcv 将不能接收到 snd 发送的信息。这是因为在调用msgrcv函数时，如果msgtype（第四个参数）大于零，则将只获取具有相同消息类型的第一个消息，修改后获取的消息类型为2，而 snd 发送的消息类型为1，所以不能被 rcv 程序接收。

与命名管道相比，消息队列的优势在于：

1. 消息队列可以独立于发送和接收进程而存在，从而消除了在同步命名管道的打开和关闭时可能产生的困难。
2. 同时通过发送消息还可以避免命名管道的同步和阻塞问题，不需要由进程自己来提供同步方法。
3. 接收程序可以通过消息类型有选择地接收数据，而不是像命名管道中那样，只能默认地接收。

# 信号

信号（Signals）是Unix系统中使用的最古老的进程间通信的方法之一。操作系统通过信号来通知进程系统中发生了某种预先规定好的事件（一组事件中的一个），它也是用户进程之间通信和同步的一种原始机制。一个键盘中断或者一个错误条件（比如进程试图访问它的虚拟内存中不存在的位置等）都有可能产生一个信号。Shell也使用信号向它的子进程发送作业控制信号。目前几乎所有的Unix变种都提供了和Posix标准兼容的信号实现机制。

关于系统如何在进程间传递信号，参考[Linux_OS_Signal.md](Signal.md)

# 共享内存

共享内存就是允许两个不相关的进程访问同一个逻辑内存。共享内存是在两个正在运行的进程之间共享和传递数据的一种最有效的方式，不同进程之间共享的内存通常安排为同一段物理内存。进程可以将同一段共享内存连接到它们自己的地址空间中，所有进程都可以访问共享内存中的地址，就好像它们是由用C语言函数malloc分配的内存一样。而如果某个进程向共享内存写入数据，所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。

![][6]

注意共享内存并未提供同步机制，也就是说，在第一个进程结束对共享内存的写操作之前，并无自动机制可以阻止第二个进程开始对它进行读取。所以通常需要用其他的机制来同步对共享内存的访问，例如前面说到的信号量。

采用共享内存通信的一个显而易见的好处是`效率高`，因为进程可以直接读写内存，而不需要任何数据的拷贝。对于像管道和消息队列等通信方式，则需要在内核和用户空间进行四次的数据拷贝，而共享内存则只拷贝两次数据：一次从输入文件到共享内存区，另一次从共享内存区到输出文件。

Linux中提供了一组函数接口用于使用共享内存，声明在头文件 `sys/shm.h`中。

## shmget 

`shmget函数` 用来创建共享内存，成功时返回一个与key相关的共享内存标识符（非负整数），用于后续的共享内存函数，调用失败返回-1。它的原型为：

    int shmget(key_t key, size_t size, int shmflg); 

参数说明如下：

* key 为共享内存段命名。
* size 以字节为单位指定需要共享的内存容量。
* shmflg 是权限标志，它的作用与open函数的mode参数一样，如果要想在key标识的共享内存不存在时，创建它的话，可以与IPC_CREAT做或操作。共享内存的权限标志与文件的读写权限一样，举例来说，0644,它表示允许一个进程创建的共享内存被内存创建者所拥有的进程向共享内存读取和写入数据，同时其他用户创建的进程只能读取共享内存。

## shmat

`shmat函数`用来启动对该共享内存的访问，并把共享内存连接到当前进程的地址空间。因为创建完共享内存时，还不能被任何进程访问。调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1。它的原型如下：

```c++
void *shmat(int shm_id, const void *shm_addr, int shmflg);
```

参数说明如下：

* shm_id 是由shmget函数返回的共享内存标识。
* shm_addr 指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
* shm_flg 是一组标志位，通常为0。

## shmdt

`shmdt函数`用于将共享内存从当前进程中`分离（detach）`，调用成功时返回0，失败时返回-1。当进程不再需要共享虚拟内存的时候，它们与之分离。只要仍旧有其它进程在使用这块内存，这种分离就只会影响当前的进程，而不会影响其它进程。当共享这块内存的最后一个进程与之分离时，共享内存页被释放，同时，这块共享内存的数据结构也被释放。它的原型如下：

```c++
int shmdt(const void *shmaddr);
```

其中参数shmaddr是shmat函数返回的地址指针。

## shmctl

`shmctl函数`用来控制共享内存，控制操作包括获得共享内存对象的状态，设置共享内存对象的参数（如uid、gid、mode、ctime等），将共享内存对象在内存中锁定和释放（在对象的mode上增加或去除SHM_LOCKED标志），释放共享内存对象资源等。它的原型如下：

```c++
int shmctl(int shm_id, int command, struct shmid_ds *buf); 
```

主要参数如下：

* shm_id是shmget函数返回的共享内存标识符。
* command是要采取的操作，它可以取下面的三个值 ：
    * IPC_STAT：把shmid_ds结构中的数据设置为共享内存的当前关联值，即用共享内存的当前关联值覆盖shmid_ds的值。
    * IPC_SET：如果进程有足够的权限，就把共享内存的当前关联值设置为shmid_ds结构中给出的值
    * IPC_RMID：删除共享内存段
* buf是一个结构指针，它指向共享内存模式和访问权限的结构。

## 实例分析

下面以两个不相关的进程来说明进程间如何通过共享内存来进行通信。首先 [Shm_Server](../Coding/Linux_OS_Shm_Server.cpp) 进程创建共享内存，并且向共享内存写入字符串。[Shm_Client](../Coding/Linux_OS_Shm_Client.cpp) 进程读取共享内存的字符串，并且更改共享内存的内容，简单的运行如下：

```bash
$ Shm_Server.o&
[1] 11209
$ jobs
[1]  + running    .Shm_Server.o
$ .Shm_Client.o
abcdefghijklmnopqrstuvwxyz
$ 
[1]  + 11209 done       ./Shm_Server.o
```

注意，这里两个进程最后都没有释放共享内存，所以可以使用ipcs命令把共享内存的信息打印出来，使用`ipcs -m`，还可以使用 ipcrm 来释放共享内存中的内容。

```bash
$ Shm_Client.o
*bcdefghijklmnopqrstuvwxyz
$ ipcs -m
IPC status from <running system> as of Thu Sep  1 08:46:52 CST 2016
T     ID     KEY        MODE       OWNER    GROUP
Shared Memory:
m  65536 0x0000162e --rw-rw-rw-  feizhao    staff
$ ipcrm -m 65536
$ ipcs -m
IPC status from <running system> as of Thu Sep  1 08:47:42 CST 2016
T     ID     KEY        MODE       OWNER    GROUP
Shared Memory:

```

关于共享内存的实现原理参见 [SharedMemory.md](SharedMemory.md)

# 信号量

为了防止出现因多个程序同时访问一个共享资源而引发的一系列问题，我们需要一种方法，它可以通过生成并使用令牌来授权，在任一时刻只能有一个执行线程访问代码的临界区域。而信号量就可以提供这样的一种访问机制，让一个临界区同一时间只有一个线程在访问它，也就是说**信号量是用来协调进程对共享资源的访问的**。

信号量是一个特殊的变量，程序对其访问都是原子操作，且只允许对它进行等待和发送操作，也即P(sv)和V(sv)，他们的行为是这样的：

* P(sv)：如果sv的值大于零，就给它减1；如果它的值为零，就挂起该进程的执行；
* V(sv)：如果有其他进程因等待sv而被挂起，就让它恢复运行，如果没有进程因等待sv而挂起，就给它加1。

最简单的信号量是只能取0和1的变量，这也是信号量最常见的一种形式，叫做互斥信号量，可以取多个正整数的信号量被称为通用信号量。

举个例子来说，如果两个进程共享互斥信号量 sv，一旦其中一个进程执行了P(sv)操作，它将得到信号量，并可以进入临界区，使sv减1。而第二个进程将被阻止进入临界区，因为当它试图执行P(sv)时，sv为0，它会被挂起以等待第一个进程离开临界区域并执行V(sv)释放信号量，这时第二个进程就可以恢复执行。

Linux提供了一组精心设计的信号量接口来进行操作，它们声明在头文件sys/sem.h中。

## semget

该函数用于创建一个新信号量或取得一个已有信号量，成功返回一个相应信号标识符（非零），失败返回-1，原型如下：

```c++
int semget(key_t key, int num_sems, int sem_flags); 
```

参数解释如下：

* key 是整数值（唯一非零），不相关的进程可以通过它访问一个信号量，它代表程序可能要使用的某个资源，程序对所有信号量的访问都是间接的，程序先通过调用semget函数并提供一个键，再由系统生成一个相应的信号标识符（semget函数的返回值），只有semget函数才直接使用信号量键，所有其他的信号量函数使用由semget函数返回的信号量标识符。如果多个程序使用相同的key值，key将负责协调工作。
* num_sems 指定需要的信号量数目，它的值几乎总是1。
* sem_flags是一组标志，可以和值IPC_CREAT做按位或操作，这样当想要的信号量不存在时会创建一个新的信号量，如果给出的键是一个已有信号量的键，也不会产生错误。而IPC_CREAT | IPC_EXCL则可以创建一个新的，唯一的信号量，如果信号量已存在，返回一个错误。

## semop

该函数用于改变信号量的值，原型如下：

```c++
int semop(int sem_id, struct sembuf *sem_opa, size_t num_sem_ops); 
```

sem_id是由semget返回的信号量标识符，sembuf结构的定义如下：

```c++
struct sembuf{  
    short sem_num;//除非使用一组信号量，否则它为0  
    short sem_op; //信号量在一次操作中需要改变的数据，
                  // 通常是两个数，一个是-1，即P（等待）操作，一个是+1，即V（发送信号）操作。  
    short sem_flg;//通常为SEM_UNDO,使操作系统跟踪信号，  
                  //并在进程没有释放该信号量而终止时，操作系统释放信号量  
};  
```

## semctl

该函数用来直接控制信号量信息，它的原型为

```c++
int semctl(int sem_id, int sem_num, int command, ...);
```

前两个参数与前面函数中的一样，command通常是下面两个值中的其中一个：

* SETVAL：用来把信号量初始化为一个已知的值。p 这个值通过union semun 中的val成员设置，其作用是在信号量第一次使用前对它进行设置。
* IPC_RMID：用于删除一个已经无需继续使用的信号量标识符。

如果有第四个参数，它通常是一个union semum结构，定义如下：

```c++
union semun{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry;  
};  
```

## 实例分析

下面使用一个例子来说明进程间如何使用信号量来进行通信，这个例子是两个相同的程序 [Sem](../Coding/Linux_OS_Sem.cpp)  同时向屏幕输出数据，我们可以看到如何使用信号量来使两个进程协调工作，使同一时间只有一个进程可以向屏幕输出数据。


```bash
./Linux_OS_Sem.o Y & ./Sem.o
[1] 12340
XXYYXXXXYYYY
12341 - finished
$
12340 - finished

[1]  + 12340 done       ./Sem.o Y
```

注意，如果程序是第一次被调用（为了区分，第一次调用程序时带一个要输出到屏幕中的字符作为一个参数），则需要调用set_semvalue函数初始化信号并将message字符设置为传递给程序的参数的第一个字符，同时第一个启动的进程还负责信号量的删除工作。如果不删除信号量，它将继续在系统中存在，即使程序已经退出，它可能在你下次运行此程序时引发问题，而且信号量是一种有限的资源。

仔细观察的话会发现上面‘X’和‘Y’总是成对出现，这是因为每次进入临界区内都会输出两个字符。如果没有使用临界区，那么字符就可能不会成对出现，[Sem_No](../Coding/Linux_OS_Sem_No.cpp) 为不用信号量的程序，如下：

```bash
$ ./Sem_No.o Y & ./Sem_No.o
[1] 12909
YXYXYXXYXYXY
12909 - finished

12910 - finished
[1]  + 12909 done       ./Sem_No.o Y
```

# 套接字

前面说到的进程间的通信，所通信的进程都是在同一台计算机上的，而使用socket进行通信的进程可以是同一台计算机的进程，也是可以是通过网络连接起来的不同计算机上的进程，通常我们使用socket进行网络编程。

下面用多个客户程序和一个服务器程序来展示进程间如何利用套接字进行通信。

[Socket_S](../Coding/Linux_OS_Socket_S.cpp) 是一个服务器程序，它首先创建套接字，然后绑定一个端口监听套接字，忽略子进程的停止消息等，然后它进入循环，一直循环检查是否有客户连接到服务器，如果有，则调用fork创建一个子进程来处理请求。利用read系统调用来读取客户端发来的信息，利用write系统调用来向客户端发送信息。这个服务器的工作非常简单，就是把客户发过来的字符+1，再发送回给客户。

[Socket_C](../Coding/Linux_OS_Socket_C.cpp) 是一个客户程序，它同样要先创建套接，然后连接到指定服务器的端口，如果连接成功，就用write来发送信息给服务器，再用read获取服务器处理后的信息，再输出。

运行结果如下：

```bash
$ ./Socket_S.o&
[1] 13903
Server waiting
$ ./Socket_C.o& ./Socket_C.o& ./Socket_C.o
[2] 13984
[3] 13985
Server waiting
Server waiting
Server waiting
char form server = B
[2]  - 13984 done       ./Socket_C.o
char form server = B
char form server = B
[3]  + 13985 done       ./Socket_C.o
```

关于 Socket 的更多内容，参考 [Socket.md](../Network/Socket.md)

# 更多阅读

[Linux进程间通信之管道(pipe)、命名管道(FIFO)与信号(Signal)](http://www.cnblogs.com/biyeymyhjob/archive/2012/11/03/2751593.html)  
[Linux环境进程间通信（一）](https://www.ibm.com/developerworks/cn/linux/l-ipc/part1/)  
[Linux环境进程间通信（五）: 共享内存（上）](http://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html)  
[Linux环境进程间通信（五）: 共享内存（下）](Linux环境进程间通信（五）: 共享内存（下）)  
[Linux进程间通信——使用消息队列](http://blog.csdn.net/ljianhui/article/details/10287879)  
[Linux进程间通信——使用信号量](http://blog.csdn.net/ljianhui/article/details/10243617)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_IPC_1.jpg
[6]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_ProcessThread_6.gif


