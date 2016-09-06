# Posix 和 System V

POSIX(Portable Operating System Interface for Computing Systems)是由IEEE 和ISO/IEC 开发的一簇标准。该标准是基于现有的UNIX 实践和经验，描述了操作系统的调用服务接口，用于保证编制的应用程序可以在源代码一级上在多种操作系统上移植运行。

Unix System V，是Unix操作系统众多版本中的一支。它最初由AT&T开发，在1983年第一次发布，因此也被称为AT&T System V。一共发行了4个System V的主要版本：版本1、2、3和4。System V Release 4，或者称为SVR4，是最成功的版本，成为一些UNIX共同特性的源头。

# Linux 启动流程

每个平台的启动细节不同，但整体来说启动过程如下。

首先 BIOS 加电自检，对硬件（内存，CPU，主板等）进行检测（POST: Power-On Self-Test）和初始化，因为操作系统的启动过程中可能会依赖于磁盘访问、屏幕、键盘等。（上个世纪70年代初，"只读内存"（read-only memory，缩写为ROM）发明，开机程序被刷入ROM芯片，计算机通电后，第一件事就是读取它。这块芯片里的程序叫做"基本输入输出系统"（Basic Input/Output System），简称为`BIOS`）

接下来BIOS按照"启动顺序"，把控制权转交给排在第一位的储存设备，读取该设备的第一个扇区（最前面的512个字节），即`主引导记录（MBR）`。主引导记录的主要作用是，告诉计算机到硬盘的哪一个位置去找操作系统。

主引导记录由三个部分组成：

1. 第1-446字节：调用操作系统的机器码（boot）。
2. 第447-510字节：分区表（Partition table）。
3. 第511-512字节：主引导记录签名（0x55和0xAA）。

MBR 中的 Boot Loader 程序被读入内存（0x7C00）后，首先将自身复制到高地址的内存（0x9000）当中从而为操作系统释放低地址的内存。Boot Loader 读取启动设备的根目录（这个工作通常由引导程序，如GRUB完成），读入操作系统，并把控制权交给内核。

内核的开始代码是用汇编语言写的，具有较高的机器依赖性。系统首先进行自动配置，一旦所有硬件配置完毕，就运行进程0，建立它的堆栈，运行它。进程0继续进行初始化：配置实时时钟，挂载根文件系统，创建 init 进程（进程1）和页面守护进程（进程2）。

然后，init线程加载系统的各个模块，比如窗口程序和网络程序，直至执行/bin/login程序，跳出登录界面，等待用户输入用户名和密码。

# Linux core文件
 
一个程序崩溃时，它一般会在`当前工作目录`（或者指定目录）下生成一个core文件。core文件仅仅是一个内存映象(同时加上调试信息)，主要是用来调试的。下面的命令可以检查生成core文件的选项是否打开:

    $ ulimit -a
    -c: core file size (blocks)         0

注意core file size是0，程序出错时不会产生core文件。可以用以下命令来允许系统生成core文件，并设定core文件最大大小:

    $ulimit -c 1024

* 使用`ulimit -c`命令可查看core文件的生成开关。若结果为0，则表示关闭了此功能，不会生成core文件。
* 使用`ulimit -c filesize`命令，可以限制core文件的大小（filesize的单位为kbyte）。
* 若`ulimit -c unlimited`则表示core文件的大小不受限制。如果生成的信息超过此大小，将会被裁剪，最终生成一个不完整的core文件，在调试此core文件的时候，gdb会提示错误。

发生core dump之后, 用gdb进行查看core文件的内容, 以定位文件中引发core dump的行。

# 数值的存储

正数的原码、反码、补码形式一致，负数的反码为原码的`数值位取反`，补码为反码+1也即是原码的数值位取反再+1，计算机中以补码表示数据和运算，而32位最小负整数的补码为 1000 0000 0000 0000 0000 0000 0000 0000。

对一个数值执行单目运算符 `-` 表示的是对该数取反然后再+1，也即是我们常说的`求补运算`，注意这里取反+1与原码求补码的区别！也就是求补运算与求补码是不一样的！

例子（4位有符号整数）：

x=-4  1100（补码）   
-x=~x+1 也即是 0011+0001=0100（4）

而1100再求补码应是先数值位取反，即1011，然后+1，变成1100！注意这两者（求补与求补码）之间的区别。

［[－2^31 -1 的各种计算](http://www.nowcoder.com/questionTerminal/5f5f30bea94748fe903ff5616e73de00)］  
［[unsigned 取值](http://www.nowcoder.com/questionTerminal/3327439779e146dc9035b0977d9469eb)］

# 可执行链接格式 ELF

ELF(Executable and Linking Format)是一种对象文件的格式，用于定义不同类型的对象文件(Object files)中都放了什么东西、以及都以什么样的格式去放这些东西。它最早在 System V 系统上出现后，被 xNIX 世界所广泛接受，作为缺省的二进制文件格式来使用。

ELF文件有三种类型： 

* 可重定位文件：也就是通常称的目标文件，后缀为.o。
* 共享文件：也就是通常称的库文件，后缀为.so。
* 可执行文件：


# 更多阅读
  
[你不知道的按位运算](http://selfboot.cn/2015/09/23/something_about_bit_operation/)  
[计算机是如何启动的？](http://www.ruanyifeng.com/blog/2013/02/booting.html)    
[Linux 的启动流程](http://www.ruanyifeng.com/blog/2013/08/linux_boot_process.html)  
[线程安全和线程不安全理解](http://blog.csdn.net/ghevinn/article/details/37764791)  
[Linux生成core文件、core文件路径设置](http://www.nginx.cn/1521.html)

