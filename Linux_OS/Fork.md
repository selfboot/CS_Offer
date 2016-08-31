# fork 详解 

题目：请问下面的程序一共输出多少个“-”？

    #include <stdio.h>
    #include <sys/types.h>
    #include <unistd.h>
    
    int main(void)
    {
        int i;
        for(i=0; i<2; i++){
            fork();
            printf("-");
        }
    
        return 0;
    }

如果你对fork()的机制比较熟悉的话，这个题并不难，输出应该是6个“-”，但是，实际上这个程序会很tricky地输出8个“-”。

## fork 实例讲解

为了理解 fork 的工作方式，把上述程序加上一定的脚手架，如下：

    #include <stdio.h>
    #include <sys/types.h>
    #include <unistd.h>
    int main(void)
    {
        int i;
        for(i=0; i<2; i++){
            fork();
            //注意：下面的printf有“\n”
            printf("ppid=%d, pid=%d, i=%d \n", getppid(), getpid(), i);
        }
        sleep(10);
        //让进程停留十秒，这样我们可以用pstree查看一下进程树
        return 0;
    }

于是，上面这段程序会输出下面的结果，（注：编译出的可执行的程序名为fork）

    ppid=8858, pid=8518, i=0
    ppid=8858, pid=8518, i=1
    ppid=8518, pid=8519, i=0
    ppid=8518, pid=8519, i=1
    ppid=8518, pid=8520, i=1
    ppid=8519, pid=8521, i=1
     
    $ pstree -p | grep fork
    |-bash(8858)-+-fork(8518)-+-fork(8519)---fork(8521)

为了更清晰说明问题，看下图：

![][1]

上图中用了几个色彩，相同颜色的是同一个进程。于是，我们的pstree的图示就可以成为下面这个样子：（下图中的颜色与上图对应）

![][2]

## 题目解释

fork()系统调用是Unix下以自身进程创建子进程的系统调用，一次调用，两次返回，如果返回是0，则是子进程，如果返回值>0，则是父进程（返回值是子进程的pid），这是众为周知的。

在fork()的调用处，整个父进程空间会原模原样地复制到子进程中，包括指令，变量值，程序调用栈，环境变量，`缓冲区`，等等。

上面的那个程序为什么会输入8个“-”，这是因为`printf(“-”);`语句有buffer，所以，对于上述程序，把“-”放到了缓存中，并没有真正的输出（参看《[C语言的迷题](http://coolshell.cn/articles/945.html)》中的第一题），在fork的时候，缓存被复制到了子进程空间，所以，就多了两个，就成了8个，而不是6个。

从下图可以清楚地知道，哪个子进程复制了父进程标准输出缓中区里的的内容，而导致了多次输出。（阴影并双边框的那两个子进程）

![][3]

要知道，Unix下的设备有“[块设备](http://en.wikipedia.org/wiki/Device_file#Block_devices)”和“[字符设备](http://en.wikipedia.org/wiki/Device_file#Character_devices)”的概念，所谓块设备，就是以一块一块的数据存取的设备，字符设备是一次存取一个字符的设备。磁盘、内存都是块设备，字符设备如键盘和串口。**块设备一般都有缓存，而字符设备一般都没有缓存**。

对于上面的问题，我们如果修改一下上面的printf的那条语句为：

    printf("-\n");      // 换行符刷新缓冲区
    // 或者下面的语句
    printf("-");        
    fflush(stdout);     // flush 强制刷新

就没有问题了（就是6个“-”了），因为程序遇到“\n”，或是EOF，或是缓冲区满，或是文件描述符关闭，或是主动flush，或是程序退出，就会**把数据刷出缓冲区**。需要注意的是，标准输出是行缓冲，所以遇到“\n”的时候会刷出缓冲区，但对于磁盘这个块设备来说，“\n”并不会引起缓冲区刷出的动作，那是全缓冲，你可以使用setvbuf来设置缓冲区大小，或是用fflush刷缓存。
   
# 更多阅读  
[陈皓：一个 fork 的面试题](http://blog.jobbole.com/24686/)


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_Fork_1.jpg
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_Fork_2.jpg
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Linux_OS_Fork_3.jpg

