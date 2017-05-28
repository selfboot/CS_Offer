Socket 起源于 Unix，而Unix基本哲学之一就是`一切皆文件`，都可以用“`打开open –> 读写write/read –> 关闭close`”模式来操作。Socket就是该模式的一个实现，网络的Socket数据传输是一种特殊的I/O，Socket也是一种文件描述符。

Socket也具有一个类似于打开文件的函数调用：Socket()，该函数返回一个整型的Socket描述符，随后的连接建立、数据传输等操作都是通过该Socket实现的。使用TCP/IP协议的应用程序通常采用应用编程接口：UNIX BSD的套接字（socket）和UNIX System V的TLI（已经被淘汰），来实现网络进程之间的通信。

# Socket 属性

套接字的特性由3个属性确定，它们分别是：域、类型和协议。

1. 套接字的域：它指定**套接字通信中使用的网络介质**，最常见的套接字域是AF_INET，它指的是Internet网络。当客户使用套接字进行跨网络的连接时，它就需要用到服务器计算机的IP地址和端口来指定一台联网机器上的某个特定服务，所以在使用socket作为通信的终点，服务器应用程序必须在开始通信之前绑定一个端口，服务器在指定的端口等待客户的连接。另一个域AF_UNIX表示UNIX文件系统，它就是文件输入/输出，而它的地址就是文件名。

2. 套接字类型：因特网提供了两种通信机制：流（stream）和数据报（datagram），因而套接字的类型也就分为流套接字和数据报套接字。这里主要讲流套接字。

    流套接字由类型SOCK_STREAM指定，它们是在AF_INET域中通过TCP/IP连接实现，同时也是AF_UNIX中常用的套接字类型。流套接字提供的是一个**有序、可靠、双向字节流**的连接，因此发送的数据可以确保不会丢失、重复或乱序到达，而且它还有一定的出错后重新发送的机制。

    与流套接字相对的是由类型SOCK_DGRAM指定的数据报套接字，它不需要建立连接和维持一个连接，它们在AF_INET中通常是通过UDP/IP协议实现的。它对可以发送的数据的长度有限制，数据报作为一个单独的网络消息被传输,它可能会丢失、复制或错乱到达，UDP不是一个可靠的协议，但是它的速度比较高，因为它并一需要总是要建立和维持一个连接。

3. 套接字协议：只要底层的传输机制允许不止一个协议来提供要求的套接字类型，我们就可以为套接字选择一个特定的协议。通常只需要使用默认值。

# Socket 接口函数

既然socket是“open—write/read—close”模式的一种实现，那么socket就提供了这些操作对应的函数接口。下面以TCP为例，介绍几个基本的socket接口函数。

`socket函数`：**使用给定的协议族、套接字类型、协议编号（默认为0）来创建套接字**。

socket函数对应于普通文件的打开操作。普通文件的打开操作返回一个文件描述字，而socket()用于创建一个socket描述符（socket descriptor），它唯一标识一个socket。这个socket描述字跟文件描述字一样，后续的操作都有用到它，把它作为参数，通过它来进行一些读写操作。

    int socket(int domain, int type, int protocol);

socket函数的三个参数分别为：

* domain：`协议域`。常用的协议族有AF_INET、AF_INET6等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合。
* type：`socket类型`。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等。
* protocol：`指定协议`。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP等，它们分别对应TCP传输协议、UDP传输协议。

注意：type和protocol不可以随意组合的，如SOCK_STREAM不可以跟IPPROTO_UDP组合。当protocol为0时，会自动选择type类型对应的默认协议。

我们调用socket创建一个socket后，返回的socket描述符存在于协议族空间中，但没有一个具体的地址。如果想要给它赋值一个地址，就必须调用bind()函数，否则就当调用connect()、listen()时系统会自动随机分配一个端口。

## 服务器端函数

`bind函数`：**将套接字绑定到地址。**

    int bind(int sockfd, struct sockaddr * my_addr, int addrlen);

三个参数分别为：

* sockfd : 即socket描述字，通过socket()函数创建，唯一标识一个socket。
* my_addr : 结构体指针变量，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同。
* addrlen : 对应的是地址的长度。

通常服务器在启动的时候都会绑定一个地址（如ip地址+端口号），用于提供服务，客户就可以通过它来接连服务器；而客户端就不用指定，系统自动分配一个端口号和自身的ip地址组合。这就是为什么通常服务器端在listen之前会调用bind()，而客户端就不会调用，而是在connect()时由系统随机生成一个。

`listen函数`：使服务器的这个端口和IP处于监听状态，等待网络中某一客户机的连接请求。如果客户端有连接请求，端口就会接受这个连接。

    int listen(int sockfd, int backlog);

两个参数分别为：

* sockfd: socket描述字。
* backlog: ~~指定同时能处理的最大连接要求，通常为10或者5。最大值可设至128~~。参见 [Socket_Listen](Socket_Listen.md) 的详细说明。

`accept函数`：接受远程计算机的连接请求，建立起与客户机之间的通信连接。服务器处于监听状态时，如果某时刻获得客户机的连接请求，此时并不是立即处理这个请求，而是将这个请求放在等待队列中，当系统空闲时再处理客户机的连接请求。

    int accept(int sockfd, struct sockaddr * addr,int * addrlen);

三个参数分别为：

* sockfd : socket描述字。
* addr: 为结构体指针变量，和bind的结构体是同种类型的，系统会把远程主机的信息（远程主机的地址和端口号信息）保存到这个指针所指的结构体中。
* addrlen : 表示结构体的长度

accept的第一个参数为服务器的socket描述字，是服务器开始调用socket()函数生成的，称为`监听socket描述字`；而accept函数返回的是`已连接的socket描述字`。一个服务器通常通常仅仅只创建一个监听socket描述字，它在该服务器的生命周期内一直存在。内核为每个由服务器进程接受的客户连接创建了一个已连接socket描述字，当服务器完成了对某个客户的服务，相应的已连接socket描述字就被关闭。

## 客户端函数

`connect函数`用来请求连接远程服务器.

    int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);

三个参数分别为：

* sockfd : socket描述字，前面socket的返回值；
* serv_addr : 存储着远程服务器的IP与端口号信息；
* addrlen : 表示结构体变量的长度。

## 通用函数

`recv函数`：负责从缓冲区中读取内容。当读成功时，read返回实际所读的字节数，如果返回的值是0表示已经读到文件的结束了，小于0表示出现了错误。

    int recv(int sockfd,void *buf,int len,unsigned int flags);

四个参数分别为：

* sockfd : 为前面accept的返回值.也就是新的套接字。
* buf : 表示缓冲区
* len : 表示缓冲区的长度
* flags : 通常为0

`send函数`：将buf中的n bytes字节内容写入socket描述字。成功时返回写的字节数。失败时返回-1，并设置errno变量。

    int send(int sockfd,const void * msg,int len,unsigned int flags);

* sockfd : 为前面socket的返回值.
* msg : 一般为常量字符串
* len : 表示长度
* flags : 通常为0

`close函数`：关闭套接字。若顺利关闭则返回0，发生错误时返回-1。

    int close(int sockfd);

# TCP 通信

TCP中 Socket 通信的基本步骤如下：

![][1]

一个简单的 C/S 程序如下（客户端发出的数据, 服务器会回显到客户端的终端上。只是一个简单的模型, 没考虑错误处理等问题。）

服务器端如下：

    import socket   # socket模块
    
    BUF_SIZE = 1024  # 设置缓冲区大小
    server_addr = ('127.0.0.1', 8888)  # IP和端口构成表示地址
    
    server = socket.socket(socket.AF_INET,
                           socket.SOCK_STREAM)   # 生成一个新的socket对象
    server.setsockopt(socket.SOL_SOCKET,
                      socket.SO_REUSEADDR, 1)    # 设置地址复用
    server.bind(server_addr)  # 绑定地址
    server.listen(5)          # 监听, 最大监听数为5
    while True:
        client, client_addr = server.accept()  # 接收TCP连接, 并返回新的套接字和地址
        print 'Connected by', client_addr
        while True:
            data = client.recv(BUF_SIZE)       # 从客户端接收数据
            print data
            client.sendall(data)               # 发送数据到客户端
    server.close()

客户端如下：

    import socket
    
    BUF_SIZE = 1024
    server_addr = ('127.0.0.1', 8888)
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(server_addr)
    while True:
        data = raw_input("Please input some string > ")
        client.sendall(data)
        data = client.recv(BUF_SIZE)
        print data
    client.close()

不过真实的网络编程环境中，一定要使用大量的错误处理，可以尽量的发现错误，也能够使代码显得更加严谨。

三次握手
SYN_SENT    connect() 阻塞 --- accept() 阻塞 SYS_RCV
ESTABLISHED connect() 返回 --- accept() 返回 ESTABLISHED

四次挥手
FIN_WAIT1 close() 阻塞 --- read() 读 0 字节 LAST_ACK
FIN_WAIT2 close()

# UDP Socket函数 

`sendto()`函数：发送UDP数据，将数据发送到套接字。返回实际发送的数据字节长度或在出现发送错误时返回-1。

    int sendto(int sockfd, const void *msg,int len,unsigned int flags,const struct sockaddr *to, int tolen);

`recvfrom()`函数：接受UDP套接字的数据, 与recv()类似。返回接收到的字节数或当出现错误时返回-1，并置相应的errno。

    int recvfrom(int sockfd,void *buf,int len,unsigned int flags,struct sockaddr *from,int *fromlen);

UDP通信流程图如下：

![][2]

简单的客户端服务器UDP连接，服务器端：

    #!/usr/bin/env python
    # -*- coding:utf-8 -*-
    
    import socket
    
    BUF_SIZE = 1024                     # 设置缓冲区大小
    server_addr = ('127.0.0.1', 8888)   # IP和端口构成表示地址
        
    # 生成新的套接字对象
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind(server_addr)        # 套接字绑定IP和端口
        
    while True:
      print "waitting for data"
      # 从客户端接收数据
      data, client_addr = server.recvfrom(BUF_SIZE)
      print 'Connected by', client_addr, ' Receive Data : ', data
      # 发送数据给客户端
      server.sendto(data, client_addr)
    server.close()

客户端如下：

    import socket
    
    BUF_SIZE = 1024                     # 设置缓冲区
        server_addr = ('127.0.0.1', 8888)   # IP和端口构成表示地址
        
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    while True:
      data = raw_input('Please Input data > ')
      client.sendto(data, server_addr)  # 向服务器发送数据
      data, addr = client.recvfrom(BUF_SIZE)  # 从服务器接收数据
      print "Data : ", data
    client.close()


# 更多阅读
 
[Socket通信原理简介](http://www.jianshu.com/p/90348ef3f41e)  
[简单理解Socket](http://www.cnblogs.com/dolphinX/p/3460545.html)  
[Python爬虫(三)-Socket网络编程](http://www.jianshu.com/p/e062b3dd110c)  
[Linux Socket编程（不限Linux）](http://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Network_Socket_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Network_Socket_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Network_Socket_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/Network_Socket_4.png


