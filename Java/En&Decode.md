
# Java 编码转换过程

我们通过 Java 类文件和用户进行最直接的交互（输入、输出），这些交互内容包含会包含中文。无论这些java类是与数据库交互，还是与前端页面交互，他们的生命周期总是这样的：

1. 程序员在操作系统上通过编辑器编写程序代码并且以.java的格式保存操作系统中，这些文件我们称之为源文件。
2. 通过JDK中的 javac.exe 编译这些源文件形成.class类。
3. 直接运行这些类或者部署在WEB容器中运行，得到输出结果。

上面周期中，伴随着如下字符的编码和解码过程：


1. 当我们用编辑器编写java源文件，程序文件在保存时会采用一定的编码格式（一般采用系统默认编码，中文的操作系统采用的是GBK编码格式）形成一个.java文件。
2. 当我们使用javac.exe编译java源文件时，JDK首先会根据编译参数encoding来确定源文件的编码。如果不指定该编译参数，JDK首先会获取操作系统默认的`file.encoding`参数，然后把源程序从file.encoding编码格式转化为JAVA内部默认的UNICODE格式放入内存中。
3. JDK将上面编译好的且保存在内存中信息写入class文件中，形成.class文件。此时.class文件是Unicode编码的，也就是说我们常见的.class文件中的内容无论是中文字符还是英文字符，他们都已经转换为Unicode编码格式了。









更多阅读 

[Java: a rough guide to character encoding](http://illegalargumentexception.blogspot.com/2009/05/java-rough-guide-to-character-encoding.html)  
[From compilation to runtime, how does Java String encoding really work](https://stackoverflow.com/questions/2164804/from-compilation-to-runtime-how-does-java-string-encoding-really-work)  


[locale错误导致Java中文乱码错误的总结](http://itindex.net/detail/52017-locale-%E9%94%99%E8%AF%AF-java)   
[Java利用System.getProperty("file.encoding")获取编码分析](http://blog.csdn.net/loongshawn/article/details/50918506)  
[java编码转换过程](http://wiki.jikexueyuan.com/project/java-chinese-garbled-solution/java-code-conversion-process.html)  

