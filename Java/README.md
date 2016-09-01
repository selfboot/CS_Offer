# TODO

Java是一个支持并发、基于类和面向对象的计算机编程语言。



String 是最基本的数据类型吗？ 

Java中的基本数据类型只有8个：byte、short、int、long、float、double、char、boolean；除了基本类型（primitive type）和枚举类型（enumeration type），剩下的都是引用类型（reference type）。

# 数据类型

Java是一个近乎纯洁的面向对象编程语言，但是为了编程的方便还是引入了基本数据类型，但是为了能够将这些基本数据类型当成对象操作，Java为每一个基本数据类型都引入了对应的包装类型（wrapper class），int的包装类就是Integer，从Java 5开始引入了自动装箱/拆箱机制，使得二者可以相互转换。 

Java 为每个原始类型提供了包装类型： 

- 原始类型: boolean，char，byte，short，int，long，float，double 
- 包装类型：Boolean，Character，Byte，Short，Integer，Long，Float，Double

看下面简单的示例：

```Java
class AutoUnboxingTest {
    public static void main(String[] args) {
        Integer a = new Integer(3);
        Integer b = 3;                  // 将3自动装箱成Integer类型
        int c = 3;
        System.out.println(a == b);     // false 两个引用没有引用同一对象
        System.out.println(a == c);     // true a自动拆箱成int类型再和c比较
        
        Integer f1 = 100, f2 = 100, f3 = 150, f4 = 150;
        System.out.println(f1 == f2);   // true
        System.out.println(f3 == f4);   // false
    }
}
```

需要注意的是f1、f2、f3、f4四个变量都是Integer对象引用，所以下面的 == 运算比较的不是值而是引用。如果整型字面量的值在-128到127之间，那么不会new新的Integer对象，而是直接引用常量池中的Integer对象，所以上面的面试题中`f1==f2`的结果是true，而`f3==f4`的结果是false。

String和StringBuilder、StringBuffer的区别？ 

Java平台提供了两种类型的字符串：String和StringBuffer/StringBuilder，它们可以储存和操作字符串。其中String是只读字符串，也就意味着String引用的字符串内容是不能被改变的。而StringBuffer/StringBuilder类表示的字符串对象可以直接进行修改。StringBuilder是Java 5中引入的，它和StringBuffer的方法完全相同，区别在于它是在单线程环境下使用的，因为它的所有方面都没有被synchronized修饰，因此它的效率也比StringBuffer要高


# 常用函数

```Java
System.out.println(Math.round(11.5));   // 12
System.out.println(Math.round(-11.5));  // -11
```

round() 在参数上加0.5然后进行下（小）取整。


# JVM 机制


# 更多阅读

[Java面试题全集（上）](http://blog.csdn.net/jackfrued/article/details/44921941)  

