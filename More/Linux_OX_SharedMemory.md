共享内存就是允许两个不相关的进程访问同一个逻辑内存。共享内存是在两个正在运行的进程之间共享和传递数据的一种最有效的方式，不同进程之间共享的内存通常安排为同一段物理内存。进程可以将同一段共享内存连接到它们自己的地址空间中，所有进程都可以访问共享内存中的地址，就好像它们是由用C语言函数malloc分配的内存一样。而如果某个进程向共享内存写入数据，所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。

# 共享内存接口

Linux中提供了一组函数接口用于使用共享内存，声明在头文件 `sys/shm.h`中。

## shmget 

`shmget函数` 用来创建共享内存，成功时返回一个与key相关的共享内存标识符（非负整数），用于后续的共享内存函数，调用失败返回-1。它的原型为：

    int shmget(key_t key, size_t size, int shmflg); 

参数说明如下：

* key 为共享内存段命名。
* size以字节为单位指定需要共享的内存容量。
* shmflg是权限标志，它的作用与open函数的mode参数一样，如果要想在key标识的共享内存不存在时，创建它的话，可以与IPC_CREAT做或操作。共享内存的权限标志与文件的读写权限一样，举例来说，0644,它表示允许一个进程创建的共享内存被内存创建者所拥有的进程向共享内存读取和写入数据，同时其他用户创建的进程只能读取共享内存。

## shmat

`shmat函数`用来启动对该共享内存的访问，并把共享内存连接到当前进程的地址空间。因为创建完共享内存时，还不能被任何进程访问。调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1。它的原型如下：

    void *shmat(int shm_id, const void *shm_addr, int shmflg);  

参数说明如下：

* shm_id是由shmget函数返回的共享内存标识。
* shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
* shm_flg是一组标志位，通常为0。

## shmdt

`shmdt函数`用于将共享内存从当前进程中`分离（detach）`，调用成功时返回0，失败时返回-1。当进程不再需要共享虚拟内存的时候，它们与之分离。只要仍旧有其它进程在使用这块内存，这种分离就只会影响当前的进程，而不会影响其它进程。当共享这块内存的最后一个进程与之分离时，共享内存页被释放，同时，这块共享内存的数据结构也被释放。它的原型如下：

    int shmdt(const void *shmaddr); 

其中参数shmaddr是shmat函数返回的地址指针。

## shmctl

`shmctl函数`用来控制共享内存，控制操作包括获得共享内存对象的状态，设置共享内存对象的参数（如uid、gid、mode、ctime等），将共享内存对象在内存中锁定和释放（在对象的mode上增加或去除SHM_LOCKED标志），释放共享内存对象资源等。它的原型如下：

    int shmctl(int shm_id, int command, struct shmid_ds *buf); 

主要参数如下：

* shm_id是shmget函数返回的共享内存标识符。
* command是要采取的操作，它可以取下面的三个值 ：
    * IPC_STAT：把shmid_ds结构中的数据设置为共享内存的当前关联值，即用共享内存的当前关联值覆盖shmid_ds的值。
    * IPC_SET：如果进程有足够的权限，就把共享内存的当前关联值设置为shmid_ds结构中给出的值
    * IPC_RMID：删除共享内存段
* buf是一个结构指针，它指向共享内存模式和访问权限的结构。

# 实例分析

下面以两个不相关的进程来说明进程间如何通过共享内存来进行通信。首先 shm_server 进程创建共享内存，并且向共享内存写入字符串。shm_client 进程读取共享内存的字符串，并且更改共享内存的内容。两个程序的源码如下：

[shm_server.c](C++_Code/shm_server.c)

    #include <sys/shm.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    #define SHMSZ     27
    
    int main()
    {
        char c;
        int shmid;
        key_t key;
        char *shm, *s;
    
        // We'll name our shared memory segment "5678".
        key = 5678;
    
        // Create the segment.
        if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
    
        // Now we attach the segment to our data space.
        if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }
    
        // Now put some things into the memory for the other process to read.
        s = shm;
        for (c = 'a'; c <= 'z'; c++)
            *s++ = c;
        *s = 0;
    
        /*
         * Finally, we wait until the other process changes the first character of our memory
         * to '*', indicating that it has read what we put there.
         */
        while (*shm != '*')
            sleep(1);
    
        exit(0);
    }

[shm_client.c](C++_Code/shm_client.c)

    #include <sys/shm.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    #define SHMSZ     27
    
    int main()
    {
        int shmid;
        key_t key;
        char *shm, *s;
    
        // We need to get the segment named "5678", created by the server.
        key = 5678;
    
        // Locate the segment.
        if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
    
        // Now we attach the segment to our data space.
        if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }
    
        // Now read what the server put in the memory.
        for (s = shm; *s != 0; s++)
            putchar(*s);
        putchar('\n');
    
        /*
         * Finally, change the first character of the segment to '*',
         * indicating we have read the segment.
         */
        *shm = '*';
    
        exit(0);
    }

可以使用ipcs命令把共享内存/信号量/消息队列的信息打印出来，如果只想显示共享内存信息，则使用`ipcs -m`。

    $ ipcs -m
    IPC status from <running system> as of Thu Jun  9 20:35:31 CST 2016
    T     ID     KEY        MODE       OWNER    GROUP
    Shared Memory:
    m  65536 0x0000162e --rw-rw-rw-  feizhao    staff

# 实现原理


（共享内存段被映射进进程空间之后，存在于进程空间的什么位置？共享内存段最大限制是多少？）


# 更多阅读
[IPC:Shared Memory](https://www.cs.cf.ac.uk/Dave/C/node27.html)  
[Linux进程间通信——使用共享内存](http://blog.csdn.net/ljianhui/article/details/10253345)  
[10 IPCS Command Examples (With IPC Introduction)](http://www.thegeekstuff.com/2010/08/ipcs-command-examples/)  

