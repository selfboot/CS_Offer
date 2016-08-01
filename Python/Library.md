Python 有着大量优秀的三方库，功能十分强大。可以在 [Awesome Python](https://github.com/vinta/awesome-python) 上找自己需要的库，下面列出几个经典的库。

# requests 库

`Requests` 是一个 HTTP 库，用 Python 编写，真正的为人类着想。Python 标准库中的 urllib2 模块提供了你所需要的大多数 HTTP 功能，但是它的 API 太渣了。它需要巨量的工作，甚至包括各种方法覆盖，来完成最简单的任务。

    >>> r = requests.get('https://api.github.com/user', auth=('user', 'pass'))
    >>> r.status_code
    200
    >>> r.headers['content-type']
    'application/json; charset=utf8'
    >>> r.encoding
    'utf-8'
    >>> r.text
    u'{"type":"User"...'

爬过豆瓣的音乐库，还有Coursera的课程下载脚本，还有V2EX的自动登录脚本。

`Beautiful Soup` 是一个可以从 HTML 或 XML 文件中提取数据的Python库。它能够通过你喜欢的转换器实现惯用的文档导航，查找，修改文档的方式。

使用BeautifulSoup解析一段 HTML 代码，得到一个 BeautifulSoup 的对象，然后就可以浏览结构化数据。

# Matplotlib 库

Matplotlib 是Python最流行的绘图库之一，使用起来非常方便，可以高度定制绘图模型，允许用户绘制点线图、条线图/直方图、3D图形，甚至是更复杂的图表。

pylab 是 matplotlib 面向对象绘图库的一个接口，考虑用默认配置在同一张图上绘制正弦和余弦函数图像，如下：

    from pylab import *
    
    X = np.linspace(-np.pi, np.pi, 256,endpoint=True)
    C,S = np.cos(X), np.sin(X)
    
    plot(X,C)
    plot(X,S)
    
    show()

# Numpy

Numpy是Python的一个科学计算的库，提供了矩阵运算的功能，其一般与Scipy、matplotlib一起使用。NumPy 的主要对象是同种元素的多维数组（numpy.ndarray）。在NumPy中维度(dimensions)叫做轴(axes)，轴的个数叫做秩(rank)。

ndarray对象属性有：

* ndarray.ndim：数组的维数（即数组轴的个数），等于秩。最常见的为二维数组（矩阵）。
* ndarray.shape：指示数组在每个维度上大小的整数元组（这个元组的长度就是维度的数目，即ndim属性）。例如一个n排m列的矩阵，它的shape属性将是(n,m)。
* ndarray.size：数组元素的总个数，等于shape属性中元组元素的乘积。
* ndarray.dtype：一个用来描述数组中元素类型的对象，可以通过创造或指定dtype使用标准Python类型。另外NumPy提供它自己的数据类型。
* ndarray.itemsize：数组中每个元素的字节大小。例如，一个元素类型为float64的数组itemsiz属性值为8(float64占用64个bits，每个字节长度为8，所以64/8，占用8个字节）。

### 创建数组

可以使用array函数从常规的Python列表和元组创造数组。所创建的数组类型由原序列中的元素类型推导而来。

    >>> from numpy import *  
    >>> a = array( [2,3,4] )　　　  
    >>> a  
        array([2, 3, 4])  
    >>> a.dtype  
        dtype('int32')  

可使用双重序列来表示二维的数组，三重序列表示三维数组，以此类推。

    >>> b = array( [ (1.5,2,3), (4,5,6) ] )
    >>> b.ndim
    2
    >>> b
    array([[ 1.5,  2. ,  3. ],
           [ 4. ,  5. ,  6. ]])  

通常，刚开始时数组的元素未知，而数组的大小已知。因此，NumPy提供了一些使用占位符创建数组的函数。这些函数有助于满足除了数组扩展的需要，同时降低了高昂的运算开销。

用函数`zeros`可创建一个全是0的数组，用函数ones可创建一个全为1的数组，函数empty创建一个内容随机并且依赖与内存状态的数组。默认创建的数组类型(dtype)都是float64。

    >>> d = zeros((3,4))
    >>> d.dtype
    dtype('float64')
    >>> d
    array([[ 0.,  0.,  0.,  0.],
           [ 0.,  0.,  0.,  0.],
           [ 0.,  0.,  0.,  0.]])
    >>> d.itemsize
    8

也可以制定数组中的元素类型：

    ones( (2,3,4), dtype=int16 )  #手动指定数组中元素类型 

NumPy 还提供一个类似range的函数（arange）返回一个数列形式的数组:

    >>> arange(10,40,5)
    array([10, 15, 20, 25, 30, 35])
    >>> arange(40.1,40.3,0.05)
    array([ 40.1 ,  40.15,  40.2 ,  40.25])

当arange使用浮点数参数时，由于浮点数精度有限，通常无法预测获得的元素个数。因此，最好使用函数`linspace`去接收我们想要的元素个数来代替用range来指定步长。

    >>> linspace(-1, 0, 7)
    array([-1.        , -0.83333333, -0.66666667, -0.5       , -0.33333333,
           -0.16666667,  0.        ])

### 输出数组

当输出一个数组时，NumPy以特定的布局用类似嵌套列表的形式显示： 

* 第一行从左到右输出 
* 每行依次自上而下输出 
* 每个切片通过一个空行与下一个隔开 

一维数组被打印成行，二维数组成矩阵，三维数组成矩阵列表。 

    >>> a = arange(6)          
    >>> print a  
        [0 1 2 3 4 5]  
    >>> b = arange(12).reshape(4,3)  
    >>> print b  
        [[ 0  1  2]  
        [ 3  4  5]  
        [ 6  7  8]  
        [ 9 10 11]]　　　  
  
### 数组运算

数组的算术运算是按元素逐个运算。数组运算后将创建包含运算结果的新数组(有些操作符如+=和*=用来更改已存在数组而不创建一个新的数组)。

    >>> a = array([20,30,40,50])
    >>> b = arange(4)
    >>> a-b
    array([20, 29, 38, 47])
    >>> b ** 2
    array([0, 1, 4, 9])
    >>> 10*sin(a)
    array([ 9.12945251, -9.88031624,  7.4511316 , -2.62374854])
    >>> a < 35
    array([ True,  True, False, False], dtype=bool)  

与其他矩阵语言不同，NumPy中的乘法运算符*按元素逐个计算，矩阵乘法可以使用`dot函数`或创建矩阵对象实现。

    >>> a = arange(10).reshape(2,5)
    >>> b = arange(10).reshape(5,2)
    >>> dot(a,b)
    array([[ 60,  70],
           [160, 195]])

### 索引，切片和迭代

和Python中列表一样，一维数组可以进行索引、切片和迭代操作。多维数组可以每个轴有一个索引，这些索引由一个逗号分割的元组给出。当少于提供的索引数目少于轴数时，已给出的数值按秩的顺序复制，确失的索引则默认为是整个切片：

    >>> d = arange(12).reshape(2,2,3)
    >>> d
    array([[[ 0,  1,  2],
            [ 3,  4,  5]],
    
           [[ 6,  7,  8],
            [ 9, 10, 11]]])
    >>> d[:,:,1]
    array([[ 1,  4],
           [ 7, 10]])
    >>> d[:,1,:]
    array([[ 3,  4,  5],
           [ 9, 10, 11]])
    >>> d[:,1]
    array([[ 3,  4,  5],
           [ 9, 10, 11]])

### 矩阵操作

    >>> m_a = np.matrix('1 2 3; 4 5 6')
    >>> m_b = np.matrix('1 2; 3 4; 5 6')
    >>> m_a * m_b
    matrix([[22, 28],
            [49, 64]])
    >>> m_a
    matrix([[1, 2, 3],
            [4, 5, 6]])
    >>> m_a.T
    matrix([[1, 4],
            [2, 5],
            [3, 6]])


# 更多阅读

[Numpy 学习](https://www.zybuluo.com/tankle/note/51606)  
[DOC: numpy.matrix](http://docs.scipy.org/doc/numpy-1.10.1/reference/generated/numpy.matrix.html)  

