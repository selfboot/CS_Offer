

# 默认参数值

先来看下面的例子：

    def f(a, L=[]):
        L.append(a)
        return L
    
    print f(1)  # [1]
    print f(2)  # [1, 2]
    print f(3)  # [1, 2, 3]



> Important warning: The default value is evaluated only once. This makes a difference when the default is a mutable object such as a list, dictionary, or instances of most classes.




# 参考
[Python 使用 list 作为函数参数时，参数是否会初始化？](http://www.zhihu.com/question/21924859#answer-11532338)  
