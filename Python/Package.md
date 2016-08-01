简单地说，`模块`就是一个保存了Python代码的文件。模块能定义函数，类和变量，模块里也能包含可执行的代码。使用模块可以更加有逻辑地组织Python代码段，使代码更好用，更易懂。

为了组织好模块，会将多个模块分为`包`。Python 处理包也是相当方便的，简单来说，包就是文件夹，但该文件夹下必须存在 `__init__.py` 文件。最简单的情况下，__init__.py 为空文件即可，当然它也可以执行包的一些初始化代码。

> 每个py文件被称之为模块，每个具有__init__.py文件的目录被称为包。只要模块或者包所在的目录在sys.path中，就可以使用import 模块或import 包来使用。

在使用一个模块中的函数或类之前，首先要导入该模块。模块的导入使用import语句，格式如下：

    import module_name

调用模块的函数或类时，需要以模块名作为前缀，如下：

    module_name.func()

如果不想在程序中使用模块名前缀符，可以使用`from import`语句从模块导入函数，如下：

    from module_name import func
    func()

上面的例子全部基于当前程序能够找到 module_name 这个模块的假设，下面先看几个简单的例子，对模块导入有一个大致的认识，然后深入探究模块导入的机制。

# 模块导入示例

**同级目录下的调用**，程序结构如下：

    -- src
        |-- mod.py
        |-- test.py

若想在模块 test.py 中导入模块 mod， 则使用下面语句即可：

    import mod
    from mod import *

**调用子目录下的模块**，程序结构如下：

    -- src
        |-- lib
        |    |-- mod.py
        |-- test.py

如果想在模块 test.py 中导入模块mod.py，可以在lib件夹中建立空文件__init__.py文件，然后像下面这样调用即可：

    from lib.mod2 import *
    import lib.mod2

**调用上级目录下的文件**，程序结构如下：

    -- src
        |-- mod1.py
        |-- lib
        |    |-- mod2.py
        |-- sub
        |    |-- test.py

如果想在 test.py 中导入模块 mod1和mod2，则先将目录 src 加入到 sys.path，就可以导入mod1模块。然后在lib中建一个空文件__init__.py，就可以导入lib下的mod2模块，如下：

    import sys
    sys.path.append("..")
    import mod1
    import lib.mod2

项目中具体如何设置模块，如何设置导入，要考虑的问题比较多，具体可以参考极客学院的 [模块与包](http://wiki.jikexueyuan.com/project/python3-cookbook/module-and-pack.html) 这篇文章。

# 导入机制探究

Python 提供了 import 语句来实现类库的引用，当我们执行一行 `from package import module as mymodule` 命令时，Python解释器会查找package 这个包的module模块，并将该模块作为 mymodule 引入到当前的工作空间。所以import语句主要是做了二件事：

1. 查找相应的module
2. 加载module到local namespace

在import的第一个阶段，主要是完成了查找要引入模块的功能。查找时首先检查 sys.modules (保存了之前import的类库的缓存），如果module没有被找到，则按照下面的搜索路径查找模块：

1. .py 所在文件的目录
2. PYTHONPATH 中的目录
3. python安装目录，UNIX下，默认路径一般为/usr/local/lib/python/
4. 3.x 中.pth 文件内容

其大致过程可以简化为：

    def import(module_name):
        if module_name in sys.modules:
            return sys.modules[module_name]
        else:
            module_path = find(module_name)

            if module_path:
                module = load(module_path)
                sys.modules[module_name] = module
                return module
            else:
                raise ImportError

# 模块导入错误

在导入模块方面，可能会出现下面的情况：

* 循环导入（circular imports）
* 覆盖导入（Shadowed imports）

## 循环导入

如果你创建两个模块，二者相互导入对方，那么有可能会出现`循环导入`。例如创建 a.py如下：

    import b
    
    def a_test():
        print "in a_test"
        print b.x
    
    a_test()

然后在同个文件夹中创建另一个模块，将其命名为b.py。

    import a
    x = 1
    
    def b_test():
        print 'In test_b'
        a.a_test()
    
    b_test()

当我们导入 a 模块时，会引发AttributeError，这是因为导入a时，在开始时导入 b 模块，而 b 模块调用 b_test 时需要a的 a_test，这时候 a 模块的 a_test 并没有成功加载。

注意不是所有的互相导入都会引发 AttributeError，[官方文档](https://docs.python.org/2/faq/programming.html#what-are-the-best-practices-for-using-import-in-a-module)这样说：

> Circular imports are fine where both modules use the “import <module>” form of import. They fail when the 2nd module wants to grab a name out of the first (“from module import name”) and the import is at the top level. That’s because names in the 1st are not yet available, because the first module is busy importing the 2nd.

继续以上面的两个模块为例，如果将 a.py 和 b.py 改为下面代码，就不会出现循环导入的错误：

a.py

    def a_test():
        import b
        print "in a_test"
        print b.x
    
    a_test()

b.py

    x = 1
    
    def b_test():
        import a
        print 'In test_b'
        a.a_test()
    
    b_test()

这样的话，先导入 a，再导入 b 的结果如下：

    >>> import a
    In test_b
    in a_test
    1
    in a_test
    1
    >>> import b
    >>> 

## 覆盖导入

当创建的模块与标准库中的模块同名时，如果导入这个模块，就会出现覆盖导入。举个例子，创建一个名叫math.py的文件，在其中写入如下代码：

    import math

    def square_root(number):
        return math.sqrt(number)

运行这个文件，你会得到以下信息（traceback）：AttributeError: module 'math' has no attribute 'sqrt'。这是因为运行这个文件的时候，Python解释器首先在当前运行脚本所处的的文件夹中查找名叫math的模块。在这个例子中，解释器找到了我们正在执行的模块，试图导入它。但是我们的模块中并没有叫sqrt的函数或属性，所以就抛出了AttributeError。


# 更多阅读

[Python 101: All about imports](http://www.blog.pythonlibrary.org/2016/03/01/python-101-all-about-imports/)  
[极客学院：模块与包](http://wiki.jikexueyuan.com/project/python3-cookbook/module-and-pack.html)
[Python 的 import 机制](https://loggerhead.me/posts/python-de-import-ji-zhi.html)  
[Import From Parent Folder](https://xxx-cook-book.gitbooks.io/python-cook-book/content/Import/ImportFromParentFolder.html)  
[Python Cookbook：模块与包](http://python3-cookbook.readthedocs.io/zh_CN/latest/chapters/p10_modules_and_packages.html)    
[Python relative imports - the hard way](http://melitamihaljevic.blogspot.jp/2013/04/python-relative-imports-hard-way.html)          
[Attempted relative import in non-package even with init.py](http://stackoverflow.com/questions/11536764/attempted-relative-import-in-non-package-even-with-init-py)    


