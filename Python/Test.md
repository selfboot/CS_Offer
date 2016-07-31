单元测试是用来对一个模块、一个函数或者一个类来进行正确性检验的测试工作。比如我们自己编写了一个Dict类，这个类的行为和dict一致，但是可以通过属性来访问，那么可以编写出以下几个测试函数：

    def test_init(self):
    def test_key(self):
    def test_attr(self):
    def test_keyerror(self):
    def test_attrerror(self):

把上面的测试用例放到一个测试模块里，就是一个完整的单元测试。如果单元测试通过，说明我们测试的这个函数能够正常工作。如果单元测试不通过，要么函数有bug，要么测试条件输入不正确，总之，需要修复使单元测试能够通过。

单元测试通过后有什么意义呢？如果我们对代码做了修改，只需要再跑一遍单元测试，如果通过，说明我们的修改不会对函数原有的行为造成影响，如果测试不通过，说明我们的修改与原有行为不一致，要么修改代码，要么修改测试。

为了编写单元测试，我们需要引入Python自带的 `unittest` 模块，编写mydict_test.py 如下：

    import unittest
    
    from mydict import Dict
    
    class TestDict(unittest.TestCase):
    
        def test_init(self):
            d = Dict(a=1, b='test')
            self.assertEquals(d.a, 1)
            self.assertEquals(d.b, 'test')
            self.assertTrue(isinstance(d, dict))

编写单元测试时，我们需要编写一个测试类，从unittest.TestCase继承。
以test开头的方法就是测试方法，不以test开头的方法不被认为是测试方法，测试的时候不会被执行。

对每一类测试都需要编写一个test_xxx()方法。由于unittest.TestCase提供了很多内置的条件判断，我们只需要调用这些方法就可以断言输出是否是我们所期望的。最常用的断言就是 `assertEquals()`：

    self.assertEquals(abs(-1), 1) # 断言函数返回的结果与1相等

另一种重要的断言就是期待抛出指定类型的Error，比如通过d['empty']访问不存在的key时，断言会抛出KeyError：

    with self.assertRaises(KeyError):
        value = d['empty']

一旦编写好单元测试，我们就可以运行单元测试。最简单的运行方式是在mydict_test.py的最后加上两行代码：

    if __name__ == '__main__':
        unittest.main()
    
这样就可以把mydict_test.py当做正常的python脚本运行：

    $ python mydict_test.py

# mock

 
# 更多阅读

[单元测试：廖雪峰的官方网站](http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/00140137128705556022982cfd844b38d050add8565dcb9000)  


