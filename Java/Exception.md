程序运行时，发生的不被期望的事件，它阻止了程序按照程序员的预期正常执行，这就是异常。异常发生时，是任程序自生自灭，立刻退出终止，还是输出错误给用户？或者用C语言风格：用函数返回值作为执行状态？。

Java提供了更加优秀的解决办法：`异常处理机制`。异常处理机制能让程序在异常发生时，按照代码的预先设定的异常处理逻辑，针对性地处理异常，让程序尽最大可能恢复正常并继续执行，且保持代码的清晰。

Java中的异常可以是函数中的语句执行时引发的，也可以是程序员通过throw 语句手动抛出的，只要在Java程序中产生了异常，就会用一个对应类型的异常对象来封装异常，JRE就会试图寻找异常处理程序来处理异常。

# Java 异常的分类和类结构图

Java标准库内建了一些通用的异常，这些类以Throwable为顶层父类。一个对象只有是 Throwable 类的（直接或者间接）实例，他才是一个异常对象，才能被异常处理机制识别。JDK中内建了一些常用的异常类，我们也可以自定义异常。

Throwable派生出Error类和Exception类。

* 错误：Error类以及他的子类的实例，代表了JVM本身的错误。错误不能被程序员通过代码处理，Error很少出现。因此，程序员应该关注Exception为父类的分支下的各种异常类。
* 异常：Exception以及他的子类，代表程序运行时发送的各种不期望发生的事件。可以被Java异常处理机制使用，是异常处理的核心。

根据Javac对异常的处理要求，将异常类分为2类。

* `非检查异常（unchecked exception）`：Error 和 RuntimeException 以及他们的子类。Javac在编译时，不会提示这样的异常，不要求程序处理这些异常。所以如果愿意，我们可以编写代码处理（使用try…catch…finally）这样的异常，也可以不处理。对于这些异常，我们应该修正代码，而不是去通过异常处理器处理。这样的异常发生的原因多半是代码写的有问题，如除0错误ArithmeticException，错误的强制类型转换错误ClassCastException，数组索引越界ArrayIndexOutOfBoundsException，使用了空对象NullPointerException等等。
* `检查异常（checked exception）`：除了Error 和 RuntimeException的其它异常。javac强制要求程序员为这样的异常做预备处理工作。在方法中要么用try-catch语句捕获它并处理，要么用throws子句声明抛出它，否则编译不会通过。这样的异常一般是由程序的运行环境导致的。因为程序可能被运行在各种未知的环境下，而程序员无法干预用户如何使用他编写的程序，于是程序员就应该为这样的异常时刻准备着。如SQLException， IOException，ClassNotFoundException 等。

需要明确的是：检查和非检查是对于javac来说的，这样就很好理解和区分了。


# 异常的链化

在一些大型的，模块化的软件开发中，一旦一个地方发生异常，则如骨牌效应一样，将导致一连串的异常。假设B模块完成自己的逻辑需要调用A模块的方法，如果A模块发生异常，则B也将不能完成而发生异常，但是B在抛出异常时，会将A的异常信息掩盖掉，这将使得异常的根源信息丢失。异常的链化可以将多个模块的异常串联起来，使得异常信息不会丢失。

**异常链化**：以一个异常对象为参数构造新的异常对象。新的异对象将包含先前异常的信息。这项技术主要是通过异常类的一个带Throwable参数的函数来实现的。这个当做参数的异常，我们叫他根源异常（cause）。查看Throwable类源码，可以发现里面有一个Throwable字段cause，就是它保存了构造时传递的根源异常参数。这种设计和链表的结点类设计如出一辙，因此形成链也是自然的了。

![][Throwable]


# 自定义异常




# 函数


[Specifying the Exceptions Thrown by a Method](https://docs.oracle.com/javase/tutorial/essential/exceptions/declaring.html)




# 更多阅读

[The Java™ Tutorials: Exceptions](https://docs.oracle.com/javase/tutorial/essential/exceptions/index.html)  
[When to throw an exception?](https://stackoverflow.com/questions/77127/when-to-throw-an-exception)  
[Java中的异常和处理详解](http://www.cnblogs.com/lulipro/p/7504267.html)  
[Java 异常处理](http://www.runoob.com/java/java-exceptions.html)  


[Throwable]: https://cs-offer-1251736664.cos.ap-beijing.myqcloud.com/Java_Exception_Throwable.jpg







