一般来说，一个描述器是一个有`绑定方法`的对象属性(object attribute)，它的访问控制被描述器协议方法重写。这些方法是 `__get__(), __set__(), 和 __delete__()`，有这些方法的对象叫做描述器。

描述器只对于新式对象和新式类才起作用，它是属性，实例方法，静态方法，类方法和 super 的背后的实现机制。在Python自身中广泛使用了描述器，以实现 Python 2.2 中引入的新式类。

# 描述器协议

一个对象具有下面任一个方法就会成为描述器，从而在被当作对象属性时重写默认的查找行为。

```python
descr.__get__(self, obj, type=None) --> value
descr.__set__(self, obj, value) --> None
descr.__delete__(self, obj) --> None
```

如果一个对象同时定义了 `__get__()` 和 `__set__()`，它叫做**资料描述器(data descriptor)**。仅定义了 `__get__()` 的描述器叫**非资料描述器**(常用于方法，当然其他用途也是可以的)。资料描述器和非资料描述器的区别在于：相对于实例的字典的优先级。如果实例字典中有与描述器同名的属性，如果描述器是资料描述器，优先使用资料描述器，如果是非资料描述器，优先使用字典中的属性。

举个例子来说，如果实例 d 的方法和属性重名时，比如都叫 foo。Python会在访问 d.foo 的时候优先访问实例字典中的属性，因为实例函数的实现是个非资料描述器（后面会说明这点），如下示例：

```python
class Demo(object):
    def __init__(self, x):
        self.foo = x

    def foo(self):
        print "Func"


if __name__ == '__main__':
    d = Demo(10)
    print d.__dict__
    print d.foo

"""
{'foo': 10}
10
"""
```

# 描述器的调用

描述器可以直接调用：`d.__get__(obj)`。然而更常见的情况是描述器在属性访问时被自动调用。举例来说，obj.d 会在 obj 的字典中找 d，如果 d 定义了 `__get__` 方法，那么 d.__get__(obj) 会依据下面的优先规则被调用。

* 对于对象来讲，方法 `object.__getattribute__()` 把 b.x 变成 `type(b).__dict__['x'].__get__(b, type(b))` 。具体实现是依据这样的优先顺序：资料描述器优先于实例变量，实例变量优先于非资料描述器，__getattr__()方法(如果对象中包含的话)具有最低的优先级。完整的C语言实现可以在 [Objects/object.c](https://hg.python.org/cpython/file/2.7/Objects/object.c) 中 [PyObject_GenericGetAttr()](https://docs.python.org/2/c-api/object.html#c.PyObject_GenericGetAttr) 查看。
* 对于类来讲，方法 `type.__getattribute__()` 把 B.x 变成 `B.__dict__['x'].__get__(None, B)` 。用Python来描述就是:

    ```python
    def __getattribute__(self, key):
        "Emulate type_getattro() in Objects/typeobject.c"
        v = object.__getattribute__(self, key)
        if hasattr(v, '__get__'):
           return v.__get__(None, self)
        return v
    ```

其中重要的几点：

* 描述器的调用是因为 `__getattribute__()`，重写 `__getattribute__()` 方法会阻止正常的描述器调用；
* `__getattribute__()` 只对新式类的实例可用；
* `object.__getattribute__()` 和 `type.__getattribute__()` 对 `__get__()` 的调用不一样；
* 资料描述器总是比实例字典优先，非资料描述器可能被实例字典重写。(非资料描述器不如实例字典优先)

super() 返回的对象同样有一个定制的 `__getattribute__()` 方法用来调用描述器。调用 super(B, obj).m() 时会先在 `obj.__class__.__mro__` 中查找与B紧邻的基类A，然后返回 `A.__dict__['m'].__get__(obj, A)` 。如果不是描述器，原样返回 m 。如果实例字典中找不到 m ，会回溯继续在 `__mro__` 中的下一个基类中查找查找。

以上展示了描述器的机理是在 object, type, 和 super 的 `__getattribute__()` 方法中实现的。由 object 派生出的类自动的继承这个机理，或者它们有个有类似机理的元类。同样，可以重写类的 `__getattribute__()` 方法来关闭这个类的描述器行为。

## 简单例子

下面的代码中定义了一个资料描述器，每次 get 和 set 都会打印一条消息。当然重写 `__getattribute__()` 是另一个可以使所有属性拥有这个行为的方法。但是，描述器在监视特定属性的时候是很有用的。

```python
class RevealAccess(object):
    """A data descriptor that sets and returns values
       normally and prints a message logging their access.
    """

    def __init__(self, initval=None, name='var'):
        self.val = initval
        self.name = name

    def __get__(self, obj, objtype):
        print 'Retrieving', self.name
        return self.val

    def __set__(self, obj, val):
        print 'Updating' , self.name
        self.val = val

>>> class MyClass(object):
        x = RevealAccess(10, 'var "x"')
        y = 5

>>> m = MyClass()
>>> m.x
Retrieving var "x"
10
>>> m.x = 20
Updating var "x"
>>> m.x
Retrieving var "x"
20
>>> m.y
5
```

这个协议非常简单，并且提供了令人激动的可能。一些用途实在是太普遍以致于它们被打包成独立的函数。像属性(property), 方法(bound和unbound method), 静态方法和类方法都是基于描述器协议的。

# 属性

调用 `property()` 是建立资料描述器的一种简洁方式，从而可以在访问属性时触发相应的方法调用。这个函数的原型:

```python
property(fget=None, fset=None, fdel=None, doc=None) -> property attribute
```

下面展示了一个典型应用，定义一个托管属性(Managed Attribute) x 。

```python
class C(object):
    def getx(self): return self.__x
    def setx(self, value): self.__x = value
    def delx(self): del self.__x
    x = property(getx, setx, delx, "I'm the 'x' property.")
```

当用户接口已经被授权访问属性之后，需求发生一些变化，属性需要进一步处理才能返回给用户，这时 property() 能够提供很大帮助。例如，一个电子表格类提供了访问单元格的方式: Cell('b10').value。 之后，对这个程序的改善要求在每次访问单元格时重新计算单元格的值。然而，程序员并不想影响那些客户端中直接访问属性的代码。那么解决方案是将属性访问包装在一个属性资料描述器中:

```python
class Cell(object):
    . . .
    def getvalue(self, obj):
        "Recalculate cell before returning value"
        self.recalc()
        return obj._value
    value = property(getvalue)
```

property的纯Python的等价实现如下，这里就是用到了描述器:

```python
class Property(object):
    "Emulate PyProperty_Type() in Objects/descrobject.c"

    def __init__(self, fget=None, fset=None, fdel=None, doc=None):
        self.fget = fget
        self.fset = fset
        self.fdel = fdel
        self.__doc__ = doc

    def __get__(self, obj, objtype=None):
        if obj is None:
            return self
        if self.fget is None:
            raise AttributeError, "unreadable attribute"
        return self.fget(obj)

    def __set__(self, obj, value):
        if self.fset is None:
            raise AttributeError, "can't set attribute"
        self.fset(obj, value)

    def __delete__(self, obj):
        if self.fdel is None:
            raise AttributeError, "can't delete attribute"
        self.fdel(obj)

    def getter(self, fget):
        return type(self)(fget, self.fset, self.fdel, self.__doc__)

    def setter(self, fset):
        return type(self)(self.fget, fset, self.fdel, self.__doc__)

    def deleter(self, fdel):
        return type(self)(self.fget, self.fset, fdel, self.__doc__)
```

# 函数和方法

Python中对类方法，实例方法，静态方法的支持是建立在基于函数的环境之上的。类的字典把方法当做函数存储，在定义类的时候，方法通常用关键字 def 和 lambda 来声明，这和创建函数是一样的。唯一的不同之处是类方法的第一个参数用来表示对象实例。

**为了支持方法调用，函数包含一个 `__get__()` 方法以便在属性访问时绑定方法。** 这就是说所有的函数都是非资料描述器，它们返回绑定(bound)还是非绑定(unbound)的方法取决于他们是被实例调用还是被类调用。用Python代码来描述就是:


```python
class Function(object):
    . . .
    def __get__(self, obj, objtype=None):
        "Simulate func_descr_get() in Objects/funcobject.c"
        return types.MethodType(self, obj, objtype)
```

下面以一个简单的例子来看下函数描述器是如何工作的:

```python
class D(object):
    def f(self, x):
        return x

d = D()
print D.__dict__['f']
print D.f
print d.f
"""
<function f at 0x1048cd0c8>
<unbound method D.f>
<bound method D.f of <__main__.D object at 0x1048d1050>>
"""
```

从输出来看，绑定方法和非绑定方法是两个不同的类型。它们是在文件 [Objects/classobject.c](http://svn.python.org/view/python/trunk/Objects/classobject.c?view=markup) 中用C实现的， PyMethod_Type 是一个对象，但是根据 im_self 是否是 NULL (在C中等价于 None ) 而表现不同。

# 静态方法和类方法

非资料描述器为将函数绑定成方法这种常见模式提供了一个简单的实现机制。简而言之，函数有个方法 `__get__()` ，当函数被当作属性访问时，它就会把函数变成一个实例方法。非资料描述器把 `obj.f(*args)` 的调用转换成 `f(obj, *args)`。

此外，还有两个变种，静态方法和类方法。静态方法原样返回函数，调用 c.f 或者 C.f 分别等价于 `object.__getattribute__(c, "f")` 或者 `object.__getattribute__(C, "f")`。也就是说，无论是从一个对象还是一个类中，这个函数都会同样地访问到。

那些不需要 self 变量的方法适合用做静态方法。staticmethod将函数原封不动的返回，如下例子（当然也可以用 `@staticmethod` 语法糖）：

```python
class E(object):
    def f(x):
        print x
    f = staticmethod(f)


E.f(3)
E().f(3)
# 3
# 3
```

利用非资料描述器， `staticmethod` 的纯Python版本看起来像这样:

```python
class StaticMethod(object):
 "Emulate PyStaticMethod_Type() in Objects/funcobject.c"

 def __init__(self, f):
      self.f = f

 def __get__(self, obj, objtype=None):
      return self.f
```

不像静态方法，类方法需要在调用函数之前会在参数列表前添上class的引用作为第一个参数。不管调用者是对象还是类，这个格式是一样的:

```python

class E(object):
     def f(cls, x):
          print cls.__name__, x
     f = classmethod(f)

E.f(3)
# ('E', 3)
E().f(3)
# ('E', 3)
```

当一个函数不需要相关的数据做参数而只需要一个类的引用的时候，这个特征就显得很有用了，类方法的一个用途是用来创建不同的`类构造器`。在Python 2.3中, dict.fromkeys() 可以依据一个key列表来创建一个新的字典，等价的Python实现就是:

```python
class Dict(dict):
    def fromkeys(klass, iterable, value=None):
        "Emulate dict_fromkeys() in Objects/dictobject.c"
        d = klass()
        for key in iterable:
            d[key] = value
        return d
    fromkeys = classmethod(fromkeys)

print Dict.fromkeys('abracadabra')  # 构造了一个字典
# {'a': None, 'r': None, 'b': None, 'c': None, 'd': None}
```

用非资料描述器协议， classmethod() 的纯Python版本实现看起来像这样:

```python
class ClassMethod(object):
     "Emulate PyClassMethod_Type() in Objects/funcobject.c"
     def __init__(self, f):
          self.f = f

     def __get__(self, obj, klass=None):
          if klass is None:
               klass = type(obj)
          def newfunc(*args):
               return self.f(klass, *args)
          return newfunc
```

# 更多阅读

[Descriptor HowTo Guide](https://docs.python.org/2/howto/descriptor.html)  
[Python描述器引导](http://pyzh.readthedocs.io/en/latest/Descriptor-HOW-TO-Guide.html)  
[python描述器与属性查找](http://strawhatfy.github.io/2015/04/21/python-attribute-lookup/)  
[Python描述器的理解](http://beginman.cn/python/2016/02/16/python-descriptor-guide/)  
[Python中的属性管理](http://blog.chinaunix.net/uid-21633169-id-4614666.html)   
[Python描述符（descriptor）解密](http://www.geekfan.net/7862/)  


