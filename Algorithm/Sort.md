> 人类生活在一个有序的世界中，没有排序，很多事情无法进行。

在计算机科学与数学中，一个排序算法（Sorting algorithm）是一种能将一串数据依照特定排序方式进行排列的一种算法。最常用到的排序方式是`数值顺序`以及`字典顺序`，有效的排序算法在一些算法（例如搜索算法）中是重要的。

虽然排序算法是一个简单的问题，但是从计算机科学发展以来，在此问题上已经有大量的研究。目前有许多排序算法，可以按照下面的一些特征对它们进行分类：

* `稳定性`：稳定排序算法会让原本有相等键值的记录维持相对次序。也就是说如果一个排序算法是稳定的，当有两个相等键值的记录R和S，且在原本的列表中R出现在S之前，在排序过的列表中R也将会在S之前。
* `比较运算`：有的算法通过一个抽象的内容比较操作（通常是“小于或等于”操作）来确定两个元素中哪个应该放在序列前面，这类算法成为比较算法。还有一些则不需要进行比较，成为非比较算法。

下表简单总结了常见的排序算法：

|排序法    |最差时间分析   |平均时间复杂度|空间复杂度 |稳定性| 是比较算法？
|---------|-------------|------------|---------|-----| ----|
|选择排序	|n^2  	  |n^2     |1    |不稳定 | 是 |
|快速排序	|n^2      |nlogn   |logn   |不稳定| 是 |
|希尔排序  |n^2	    | nlogn  |1      |不稳定| 是 |
|堆排序	  |nlogn	  |nlogn   |1     |不稳定| 是 |
|插入排序  |n^2      |n^2     |1     |**稳定**  | 是 |
|冒泡排序  |n^2      |n^2     |1     |**稳定**  | 是 |
|归并排序  |nlogn    | nlogn  | n    | **稳定** | 是 |
|基数排序  |d(r+n)   |d(r+n)  |rd+n  | **稳定** | **否** |
|计数排序  |d(n)   |d(n)  |..  | **不稳定** | **否** |

对于比较排序来说，有很多性能上的根本限制。在最差情況下，任何一种比较排序至少需要O(nlogn)比较操作，这是比较操作所获的信息有限所导致的，或者说是全序集的模糊代数结构所导致的。

从这个意义上讲，归并排序，堆排序在他们必须比较的次数上是渐进最优的，虽然这忽略了其他的操作。而非比较排序算法通过非比较操作能在O(n)完成，这使他们能够回避O(nlogn)这个下界（假设元素是定值）。

不过，比较排序在控制比较函数方面有显著优势，因此比较排序能对各种数据类型进行排序，并且可以很好地控制一个序列如何被排序。例如，如果倒置比较函数的输出结果可以让排序结果倒置。或者可以构建一个按字典顺序排序的比较函数，这样排序的结果就是按字典顺序的。

比较排序可以更好地适应复杂顺序，例如浮点数。并且，一旦比较函数完成，任何比较算法都可以不经修改地使用；而非比较排序对数据类型的要求更严格。

# 冒泡排序

冒泡排序（Bubble Sort）是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。

![][1]

Python 实现如下：

```python
def bubble_sort(L):
    for i in range(len(L) - 1, 0, -1):
        for j in range(0, i):
            if L[j] > L[j + 1]:
                L[j], L[j + 1] = L[j + 1], L[j]
```

尽管这个算法是最简单和最容易实现的排序算法之一，但在最好的情况，也需要O(n^2 )次比较，因此基本不会使用冒泡排序。

# 选择排序

选择排序（Selection sort）是一种简单直观的排序算法。它的工作原理如下：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

![][2]

Python 实现如下：

```python
def selection_sort(L):
    N = len(L)
    for i in range(N - 1):
        min_index = i
        for j in range(i + 1, N):
            if L[min_index] > L[j]:
                min_index = j
        if min_index != i:
            L[min_index], L[i] = L[i], L[min_index]
```
       
选择排序的主要优点与**数据移动**有关。如果某个元素位于正确的最终位置上，则它不会被移动。选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，因此对n个元素的表进行排序总共进行至多n-1次交换。在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。

# 插入排序

插入排序（Insertion Sort）是一种简单直观的排序算法。它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中`从后向前`扫描，找到相应位置并插入。插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。

![][3]

Python 实现如下：

```python
def insertion_sort(L):
    for i in xrange(1, len(L)):
        temp = L[i]
        j = i - 1
        while j >= 0 and temp < L[j]:
            L[j + 1] = L[j]
            j -= 1
        L[j + 1] = temp
```

如果目标是把n个元素的序列升序排列，那么采用插入排序存在最好情况和最坏情况。最好情况就是，序列已经是升序排列了，在这种情况下，需要进行的比较操作需(n-1)次即可。最坏情况就是，序列是降序排列，那么此时需要进行的比较共有n(n-1)/2次。插入排序在工业级库中也有着广泛的应用，在STL的sort算法和stdlib的qsort算法中，都将插入排序作为快速排序的补充，用于少量元素的排序（通常为8个或以下）。

# 希尔排序

希尔排序，也称递减增量排序算法，是插入排序的一种更高效的改进版本。它的实质就是分组插入排序，因DL．Shell于1959年提出而得名。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：

* 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率
* 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位

该方法的基本思想是：先将整个待排元素序列分割成若干个子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序，然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序。因为直接插入排序在元素基本有序的情况下（接近最好情况），效率是很高的，因此希尔排序在时间效率上比前两种方法有较大提高。

![][4]

Python 实现如下：

```python
def shell_sort(L):
    N = len(L)
    gap = N >> 1
    while (gap > 0):
        for pos in xrange(gap, N):
            temp = L[pos]
            pre_pos = pos - gap
            while (pre_pos >= 0 and L[pre_pos] > temp):
                L[pre_pos + gap] = L[pre_pos]
                pre_pos -= gap
            L[pre_pos + gap] = temp
        gap >>= 1
```

步长的选择是希尔排序的重要部分，只要最终步长为1任何步长序列都可以工作。Donald Shell最初建议步长选择为 n/2 并且对步长取半直到步长达到1。
    
# 快速排序

快速排序的实现基于分治法，具体分为三个步骤。假设待排序的序列为L。

* `分解`：随机选定一个轴pivot，将序列L划分成两个`可能空的子序列`L1和L2，使L1的每个元素均小于或等于pivot，同时L2的每个元素均大于pivot。
* `解决`：通过递归调用快速排序，对两个子序列进行排序。
* `合并`：由于两个子序列是就地排序的，所以对它们的合并不需要操作，整个序列L[m .. n]已排好序。

快速排序每次将待排序数组分为两个部分，在理想状况下，每一次都将待排序数组划分成等长两个部分，则需要logn次划分。而在最坏情况下，即数组已经有序或大致有序的情况下，每次划分只能减少一个元素，快速排序将不幸退化为冒泡排序，所以快速排序时间复杂度下界为O(nlogn)，最坏情况为O(n^2 )。在实际应用中，快速排序的平均时间复杂度为O(nlogn)。

![][5]

Python 实现如下：

```python
def partition(L, begin, end):
    pivot = L[begin]
    pivot_index = begin
    for i in range(begin + 1, end):
        if L[i] <= pivot:
            pivot_index += 1
            if pivot_index != i:
                L[pivot_index], L[i] = L[i], L[pivot_index]
    L[begin], L[pivot_index] = L[pivot_index], L[begin]
    return pivot_index


def quick_sort(L, begin, end):
    # Sort the L: [start, end).  Here pivot is the first number in L.
    if begin >= end - 1:
        return
    pivot_pos = partition(L, begin, end)
    quick_sort(L, begin, pivot_pos)
    quick_sort(L, pivot_pos + 1, end)
```
    
这里选择序列第一个元素为pivot，不使用新的空间（内部交换）来进行排序。首先用 partition 函数来将整个数组分解为两部分L1 和 L2，两个子部分可以为空。partition 返回轴 pivot 最后的位置，也就是说轴之前的元素（如果有的话）全部小于等于pivot，之后的元素全部大于（如果有的话）pivot。

［[快排扫描一次结果](http://www.nowcoder.com/questionTerminal/1bed46e1732c47529bf6034cda88603a)］  
［[快排最优原数组特征](http://www.nowcoder.com/questionTerminal/e3065c9dfc694ffeb9b98099fc84f3ee)］
 
# 堆排序

堆（二叉堆）可以视为一棵完全的二叉树，除了最底层之外，每一层都是满的，这使得堆可以利用数组来表示，每一个结点对应数组中的一个元素。二叉堆一般分为两种：最大堆和最小堆。

* 最大（小）堆中的最大（小）元素值出现在根结点（堆顶）；
* 堆中每个父节点的元素值都大（小）于等于其孩子结点（如果存在）。

堆排序就是把堆顶的数取出，将剩余的堆继续调整为最大（小）堆，再次将堆顶的数取出，这个过程持续到剩余数只有一个。在堆中定义以下几种操作：

* 堆调整（Heap_Adjust）：保持堆的性质，即i节点大（小）于孩子节点的值；
* 创建堆（Heap_Build）：将数组中数据重新排序，使其成为堆；
* 堆排序（Heap_Sort）：不断移除堆中的根节点，并作最大（小）堆调整；

Python 实现如下：

```python
def heap_adjust(L, i, size):
    # 调整堆, 使其满足堆约束条件
    parent = i
    while True:
        child = 2 * parent + 1
        if child >= size:
            break
        if child + 1 < size and L[child] < L[child + 1]:
            child += 1
        if L[parent] < L[child]:
            L[parent], L[child] = L[child], L[parent]
            parent = child
        else:
            break

def heap_build(L, size):
    # 创建堆: 将数组中数据重新排序，使其成为堆；
    for i in xrange(size // 2, -1, -1):
        heap_adjust(L, i, size)

def heap_sort(L):
    # 堆排序：不断移除堆中的根节点，并作最大（小）堆调整；
    size = len(L)
    heap_build(L, size)
    print "Big", L
    for i in range(size-1, 0, -1):
        L[i], L[0] = L[0], L[i]
        heap_adjust(L, 0, i)
```


**建堆的时间复杂度 O(N)**

如果从**底部最后的父节点（N/2节点）**开始建堆，假如有N个节点，那么高度为H=logN，最后一层每个父节点最多只需要**下调1次**，倒数第二层最多只需要下调2次，顶点最多需要下调H次，而最后一层父节点共有2^(H-1)个，倒数第二层公有2^(H-2)，顶点只有1( 2^0 )个，所以总共的时间复杂度为

> s = 1 * 2^(H-1) + 2 * 2^(H-2) + ... + (H-1) * 2^1 + H * 2^0 

将H代入后s= 2N - 2 - log2(N)，近似的时间复杂度就是O(N)。

# 归并排序

归并排序是建立在归并操作上的一种有效的排序算法，该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。

归并操作(Merge)，也叫归并算法，指的是将两个已经排序的序列合并成一个序列的操作。归并排序算法依赖归并操作。归并排序有多路归并排序、两路归并排序。

![][6]

算法思路：

1. 把 n 个记录看成 n 个长度为 l 的有序子表；
2. 进行两两归并使记录关键字有序，得到 n/2 个长度为 2 的有序子表；
3. 重复第 2 步直到所有记录归并成一个长度为 n 的有序表为止。
	
Python 实现如下：

```python
def merge_sort(L):
    if len(L) <= 1:
        return L

    mid = len(L) / 2
    left = merge_sort(L[:mid])
    right = merge_sort(L[mid:])
    return merge(left, right)


def merge(left, right):
    result = []
    i, j = 0, 0
    while i < len(left) and j < len(right):
        if (left[i] <= right[j]):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result
```

# 基数排序

基数排序（radix sort）是一种非比较型**稳定**排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。可以采用LSD（Least significant digital）或MSD（Most significant digital）实现，下面以 LSD 为例：将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。

实现如下：

```python
def radix_sort(nums):
    max_num = max(nums)
    bucket = [[] for i in range(10)]
    exp = 1
    while max_num / exp > 0:
        for num in nums:
            bucket[(num / exp) % 10].append(num)
        nums = []
        for each in bucket:
            nums.extend(each)
        bucket = [[] for i in range(10)]
        exp *= 10
```

以排序N个不同整数来举例，假定这些整数以B为底，这样每位数都有B个不同的数字（需要B个不同的桶），每个数字有 k = log<sub>B</sub>(N) 位。所以，一共需要 k 轮处理，在每轮处理中，需要 N 次操作来把整数放到合适的桶中去。排序的平均时间T就是：

> T=log<sub>B</sub>(N)*N

其中前一项是一个与输入数据无关的常数，当然该项不一定小于logN。如果考虑和比较排序进行对照，基数排序的形式复杂度虽然不一定更小，但由于不进行比较，因此其基本操作的代价较小，而且在适当选择的B之下，k一般不大于logn，所以基数排序一般要快过基于比较的排序，比如快速排序。

# 计数排序

计数排序（Counting sort）是一种非比较型稳定排序算法。使用一个额外的数组C，其中第i个元素保存待排序数组A中值等于i的元素的个数，然后根据数组C来将A中的元素排到正确的位置。

```python
def count_sort(L, max_num):
    # 对 [0, max_num) 间的正整数进行排序
    cnt_array = [0] * max_num
    for n in L:
        cnt_array[n] += 1
    ans = []
    for i in range(max_num):
        ans.extend([i]*cnt_array[i])
    return ans

case = [1,4,2,3,4,4,1,2,3,4,1,2,3]
print count_sort(case, 5)
# [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4]
```

当输入的元素是n个0到k之间的整数时，它的运行时间是Θ(n + k)。当然，计数排序算法只能应用于比较特殊的场景。

# 桶排序

桶排序（Bucket sort）将数组分到有限数量的桶里。每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。当要被排序的数组内的数值是均匀分配的时候，桶排序使用线性时间（Θ(n)）。

桶排序以下列程序进行：

1. 设置一个定量的数组当作空桶子。
2. 寻访序列，并且把项目一个一个放到对应的桶子去。
3. 对每个不是空的桶子进行排序。
4. 从不是空的桶子里把项目再放回原来的序列中。

# 混合排序

Introsort（内省排序）是由David Musser在1997年设计的排序算法。这个排序算法首先从快速排序开始，当递归深度超过一定深度（深度为排序元素数量的对数值）后转为堆排序。采用这个方法，内省排序既能在常规数据集上实现快速排序的高性能，又能在最坏情况下仍保持。

introsort的大致思想是：当数据很大时先用quicksort,当递归超过一定深度时改用heapsort，最后每个子序列元素个数小于某个阈值时，就改用insertionsort。由此可知，它乃综合各家之长的算法。
在2000年6月，SGI的C++标准模板库的 [stl_algo.h](http://www.sgi.com/tech/stl/stl_algo.h) 中的不稳定排序算法采用了Musser的introsort算法。在此实现中，切换到插入排序的数据量阈值为16个。

# 更多阅读

[冒泡排序](https://zh.wikipedia.org/wiki/冒泡排序)  
[选择排序](https://zh.wikipedia.org/wiki/冒泡排序)  
[插入排序](https://zh.wikipedia.org/wiki/插入排序)  
[希尔排序](https://zh.wikipedia.org/wiki/希尔排序)  
[快速排序](https://zh.wikipedia.org/wiki/快速排序)  
[常见排序算法：堆排序 (Heap Sort)](http://bubkoo.com/2014/01/14/sort-algorithm/heap-sort/)  
[常见排序算法：快速排序 (Quick Sort)](http://bubkoo.com/2014/01/12/sort-algorithm/quick-sort/)  
[常见排序算法：归并排序](http://bubkoo.com/2014/01/15/sort-algorithm/merge-sort/)   
[数学之美番外篇：快排为什么那样快](http://mindhacks.cn/2008/06/13/why-is-quicksort-so-quick/)  
[八大排序算法的Python实现](http://blog.2liang.me/2015/09/24/%E5%85%AB%E5%A4%A7%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95%E7%9A%84Python%E5%AE%9E%E7%8E%B0/)  
[Sorting Algorithm Animations](http://www.sorting-algorithms.com)

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_1.gif
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_2.gif
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_3.gif
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_4.gif
[5]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_5.gif
[6]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_6.gif


