# strcpy, strncpy

C语言标准库函数strcpy，把从src地址开始直到'\0'结束符为止（包括 '\0'）的字符串复制到以dest开始的地址空间。其原型为：

```c++
char * strcpy ( char * destination, const char * source );
// Copies the C string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).
```

一个不错的实现如下：

```c++
char* strcpy (char * destination, const char * source ){
    if(destination==NULL || source==NULL){
        return NULL;
    }
    char *des = destination;
    while ((*destination++=*source++) != '\0');
    return des;
}
```

这里对于出现异常的情况 ANSI-C99标准并未定义，故由实现者决定返回值，通常为NULL。要注意以下几个方面：

* 检查指针的有效性（用 NULL 检查）；
* strcpy已经把src的内容复制到dest，但是为了实现**级联操作**，还需要 char *类型的返回值。

使用 strcpy 的例子如下：

```c++     
const char *a = "1234";
char b[5], c[5];        // 长度为5，最后一个保存 \0
strcpy(c, strcpy(b, a));
printf("b: %s\nc: %s\n", b, c);     // 级联操作

char *d = (char *)malloc(5);
strcpy(d, a);
```

## strncpy

不过由于 strcpy 在复制 src 内容时并不检查是否超过了 dest 缓冲区的大小，因此存在缓冲区溢出的安全隐患。所以，推荐使用 `strncpy 函数`来代替所有需要使用 strcpy 的地方，其原型如下：

```c++
char * strncpy ( char * destination, const char * source, size_t num );
```

调用函数时必须指定缓冲区大小，如果复制 n（<num）个source中的字符后遇到 '\0\，那么用 '\0' 填充dest中剩余的空间，如果source中字符大于等于num，会复制num个字符，并不会在 dest 最后隐式的添加 '\0'，也就是不能将 dest 看作一个C风格字符串（否则可能会导致缓冲区溢出）。注意，这里destination 和 source 不能有重叠部分。

strncpy 的不错的实现如下： 

```c++

char* strncpy(char * destination, const char * source, int len)
{
    if(destination==NULL || source==NULL){
        return NULL;
    }
    char* ret=destination;
    int i=0;
    while(i++ < len && (*destination++ = *source++)!='\0');
    while(i++ < len)    *destination++ = '\0';
    return ret;
}
```

**如何确保dest的有效性？**

我们的版本中可以判断 dest 非空，但是对于一个没有初始化的指针，strcpy 还是是会出问题的（C++库中的strcpy也会出问题），这里需要调用者来保证这点。

## 指针重叠

考虑如果 dest 和 src 重合的话，情况会怎么样呢？

```c++
char s[10]="hello";
strcpy(s, s+1);
printf("%s \n", s);     // 返回ello，

char ss[10]="hello";
strcpy(ss+1, ss);
printf("%s \n", ss);    // 应返回hhello，但实际会报错
```

第二种情况中，src 未处理的部分已经被dst给覆盖了，也就是说 `src<=dst<=src+strlen(src)`。要想使得重叠部分的复制也可以完成，可以这样设计 strcpy，代码在 [C++_Strcpy](../Coding/C++_Strcpy.cpp)。

其实标准库中实现了一个 void* 类型的memcpy，实现复制 n 个字节的功能，原型如下：

```c++
void * memcpy ( void * destination, const void * source, size_t num );
```

# String 类

类的构造函数，赋值函数，析构函数。

    class String
    {
    public:
        String(const char *str=NULL);   //普通构造函数
        String(const String &str);      //拷贝构造函数
        String & operator =(const String &str);//赋值函数
        ~String();//析构函数
    private:
        char* m_data;//用于保存字符串w
    };

具体实现（[String.cpp](../Coding/String.cpp)）

# atoi

实现一个 atoi，将字符串转换为整数。[官网文档](http://www.cplusplus.com/reference/cstdlib/atoi/)对 atoi 有规定，注意几个测试用例：

* 不规则输入，但是有效 -3924xbfc。
* 无效格式：++1
* 溢出数据：2147483648

一个可能的实现如下：

```c++
int myAtoi(string str) {
    const int len = str.size();

    int i = 0;
    // Skip starting whitespace as many as possible.
    while (str[i] == ' ' && i < len) i++;

    int sign = 1;
    // Read plus or minus sign.
    if (str[i] == '+') i++;
    else if (str[i] == '-') {
        i++;
        sign = -1;
    }

    int num = 0;
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            break;
        }
        if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
            return sign == -1 ? INT_MIN : INT_MAX;
        }
        num = num * 10 + str[i] - '0';
    }

    return num * sign;
}
```

# 查看文件大小

可以有两种方法：

1. 用标准 C 的文件操作函数（不支持超过2G的文件读取）；
2. 调用 stat 函数获取文件的信息。

主要部分代码如下：

    // 文件读取函数
    unsigned long size;
    FILE* fp = fopen( filename, "rb");
    fseek(fp, SEEK_SET, SEEK_END );
    size=ftell(fp);
    fclose(fp);

    // 库函数 stat 获取文件信息
    struct stat buf;
    auto size ＝ (unsigned long)buf.st_size;

要注意异常的处理，完整部分代码在 [C++_GetFileSize.cpp](../Coding/C++_GetFileSize.cpp)

# 其他实现

* strlen

详细实现在 [C++_Coding](../Coding/C++_Coding.cpp)

# 更多阅读

[strcpy与memcpy的实现](http://hetaotao.net/2015/11/17/strcpy%E4%B8%8Ememcpy%E7%9A%84%E5%AE%9E%E7%8E%B0/)  
[linux下获取文件大小](http://www.vimer.cn/2009/12/linux下获取文件大小.html)  


