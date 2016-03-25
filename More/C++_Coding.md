# C++ 代码试水


# 接口了解程度

### 查看文件大小

可以有两种方法：

1. 用标准C 的文件操作函数（不支持超过2G的文件读取）；
2. 调用 stat 函数获取文件的信息。

主要部分代码如下：

    // 文件读取函数
    unsigned long size;
    FILE* fp = fopen( filename, "rb");
    fseek(fp, SEEK_SET, SEEK_END );
    size=ftell(fp);
    fclose(fp);

    // 库函数 stat获取文件信息
    struct stat buf;
    auto size ＝ (unsigned long)buf.st_size;

要注意异常的处理，完整部分代码在 [C++_GetFileSize.cpp](C++_Code/C++_GetFileSize.cpp)

参考：[linux下获取文件大小](http://www.vimer.cn/2009/12/linux下获取文件大小.html)

