

# 应用场景

日常开发过程中哪些地方可以用装饰器呢？

* 分析、日志：对于大型应用，我们常常需要记录应用的状态，以及测量不同活动的数量。通过将这些特别的事件包装到函数或方法中，装饰器在满足这些需求的同时，还能保证代码的可读性。
* 验证以及运行时检查：Python 是一种强类型语言，但是变量的类型却是动态变化的。虽然这会带来很多好处，但是同时这也意味着更容易引入 bug。对于静态语言，例如 Java，这些 bug 在编译阶段就可以被发现。因而你可能希望对传入或返回的数据进行一些自定义的的检查，装饰器可以非常容易地实现这个需求。
* 创建框架：一旦掌握了如何写装饰器，就能够从其简单的语法中获益颇丰，你可以为语言添加新的语义使其使用更加简单，甚至可以自己扩展 Python 语法。事实上，很多开源框架都是使用的这样的方式。Web 应用框架 Flask 就是使用装饰器将不同 URL 路由注册到不同处理函数的。


# 更多阅读
[How you implemented your Python decorator is wrong](https://github.com/GrahamDumpleton/wrapt/blob/master/blog/01-how-you-implemented-your-python-decorator-is-wrong.md)  
[python装饰器详解](http://selfboot.cn/2014/08/10/python_decorator/)  
[5个理由告诉你为什么要学习使用Python装饰器](http://python.jobbole.com/85393/)  






