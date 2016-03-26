# 冒泡排序

冒泡排序（Bubble Sort）是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。

![][1]

Python 实现如下：

    def bubble_sort(L):
        for j in range(len(L)-1,0,-1):
            for i in range(0,j):
                if L[i]>L[i+1]:
                    L[i],L[i+1]=L[i+1],L[i]

尽管这个算法是最简单和最容易实现的排序算法之一，但在最好的情况，也需要O(n^2 )次比较，因此基本不会使用冒泡排序。

# 选择排序

选择排序（Selection sort）是一种简单直观的排序算法。它的工作原理如下：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

![][2]

Python 实现如下：

    def selection_sort(L):
        N = len(L)
        for i in range(N - 1):
            min_index = i
            for j in range(i + 1, N):
                if L[min_index] > L[j]:
                    min_index = j
            if min_index != i:
                L[min_index], L[i] = L[i], L[min_index]
       
选择排序的主要优点与**数据移动**有关。如果某个元素位于正确的最终位置上，则它不会被移动。选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，因此对n个元素的表进行排序总共进行至多n-1次交换。在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。

# 插入排序

插入排序（Insertion Sort）是一种简单直观的排序算法。它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中`从后向前`扫描，找到相应位置并插入。插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。

![][3]

Python 实现如下：

    def insertion_sort(lst):
        for i in xrange(1, len(L)):
            temp = L[i]
            j = i - 1
            while j >= 0 and temp < L[j]:
                L[j + 1] = L[j]
                j -= 1
            L[j + 1] = temp

如果目标是把n个元素的序列升序排列，那么采用插入排序存在最好情况和最坏情况。最好情况就是，序列已经是升序排列了，在这种情况下，需要进行的比较操作需(n-1)次即可。最坏情况就是，序列是降序排列，那么此时需要进行的比较共有n(n-1)/2次。插入排序在工业级库中也有着广泛的应用，在STL的sort算法和stdlib的qsort算法中，都将插入排序作为快速排序的补充，用于少量元素的排序（通常为8个或以下）。

# 希尔排序

希尔排序，也称递减增量排序算法，是插入排序的一种更高效的改进版本。它的实质就是分组插入排序，因DL．Shell于1959年提出而得名。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：

* 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率
* 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位

该方法的基本思想是：先将整个待排元素序列分割成若干个子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序，然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序。因为直接插入排序在元素基本有序的情况下（接近最好情况），效率是很高的，因此希尔排序在时间效率上比前两种方法有较大提高。

![][4]

Python 实现如下：

    def shell_sort(L):
        N = len(L)
        gap = N >> 1
        while(gap > 0):
            for pos in xrange(gap, N):
                temp = L[pos]
                pre_pos = pos-gap
                while(pre_pos >= 0 and L[pre_pos] > temp):
                    L[pre_pos+gap] = L[pre_pos]
                    pre_pos -= gap
                L[pre_pos+gap] = temp
            gap >>= 1

步长的选择是希尔排序的重要部分，只要最终步长为1任何步长序列都可以工作。Donald Shell最初建议步长选择为 n/2 并且对步长取半直到步长达到1。
    
# 快速排序

快速排序的实现基于分治法，具体分为三个步骤。假设待排序的序列为L[m..n]。

* `分解`：序列L[m .. n]被划分成两个可能为空的子序列L[m .. pivot-1]和L[pivot+1 .. n]，使L[m .. pivot-1]的每个元素均小于或等于L[pivot]，同时L[pivot+1.. n]的每个元素均大于L[pivot]。其中L[pivot]称为这一趟分割中的主元（也称为枢轴、支点）。
* `解决`：通过递归调用快速排序，对子序列L[m .. pivot-1]和L[pivot+1 .. r]排序。
* `合并`：由于两个子序列是就地排序的，所以对它们的合并不需要操作，整个序列L[m .. n]已排好序。

快速排序每次将待排序数组分为两个部分，在理想状况下，每一次都将待排序数组划分成等长两个部分，则需要logn次划分。而在最坏情况下，即数组已经有序或大致有序的情况下，每次划分只能减少一个元素，快速排序将不幸退化为冒泡排序，所以快速排序时间复杂度下界为O(nlogn)，最坏情况为O(n^2 )。在实际应用中，快速排序的平均时间复杂度为O(nlogn)。

![][5]

Python 实现如下：

    def quick_sort(L, start, end):
        # Sort the array: [start, end).  Here pivot is the end number in L.
        if start >= end-1:
            return
        pivot = L[end-1]
        left = start
        right = end - 2
        while left < right:
            while L[left] < pivot and left < right:
                left += 1
            while L[right] >= pivot and left < right:
                right -= 1
            L[left], L[right] = L[right], L[left]
    
        if L[left] >= L[end-1]:
            L[left], L[end-1] = L[end-1], L[left]
        # Worse case: all the number is less than pivot.
        else:
            left += 1
    
        quick_sort(L, start, left)
        quick_sort(L, left+1, end)

这里选择pivot为序列最后一个元素，不使用新的空间（内部交换）。采用双指针做法，left用来保存下一个比pivot小的元素，right用来保存下一个大于等于pivot的元素。然后left从前往后扫，right从后往前扫，交换在错误位置的数字。

［[快排扫描一次结果](http://www.nowcoder.com/questionTerminal/1bed46e1732c47529bf6034cda88603a)］
［[快排最优原数组特征](http://www.nowcoder.com/questionTerminal/e3065c9dfc694ffeb9b98099fc84f3ee)］
 
# 二叉树排序 


# 堆排序

堆（二叉堆）可以视为一棵完全的二叉树，除了最底层之外，每一层都是满的，这使得堆可以利用数组来表示，每一个结点对应数组中的一个元素。二叉堆一般分为两种：最大堆和最小堆。

* 最大（小）堆中的最大（小）元素值出现在根结点（堆顶）；
* 堆中每个父节点的元素值都大（小）于等于其孩子结点（如果存在）。

堆排序就是把堆顶的数取出，将剩余的堆继续调整为最大（小）堆，再次将堆顶的数取出，这个过程持续到剩余数只有一个。在堆中定义以下几种操作：

* 堆调整（Heap_Adjast）：保持堆的性质；
* 创建堆（Heap_Build）：将数组中数据重新排序，使其成为堆；
* 堆排序（Heap_Sort）：不断移除根节点，并作最大（小）堆调整；

Python 实现如下：


**建堆的时间复杂度 O(N)**

如果从底部最后的父节点开始建堆，假如有N个节点，那么高度为H=logN，最后一层每个父节点最多只需要下调1次，倒数第二层最多只需要下调2次，顶点最多需要下调H次，而最后一层父节点共有2^(H-1)个，倒数第二层公有2^(H-2)，顶点只有1( 2^0 )个，所以总共的时间复杂度为

> s = 1 * 2^(H-1) + 2 * 2^(H-2) + ... + (H-1) * 2^1 + H * 2^0 

将H代入后s= 2N - 2 - log2(N)，近似的时间复杂度就是O(N)。

# 归并排序

# 基数排序

# 参考

[冒泡排序](https://zh.wikipedia.org/wiki/冒泡排序)  
[选择排序](https://zh.wikipedia.org/wiki/冒泡排序)  
[插入排序](https://zh.wikipedia.org/wiki/插入排序)  
[希尔排序](https://zh.wikipedia.org/wiki/希尔排序)  
[快速排序](https://zh.wikipedia.org/wiki/快速排序)  
[常见排序算法 - 堆排序 (Heap Sort)](http://bubkoo.com/2014/01/14/sort-algorithm/heap-sort/)  

[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_1.gif
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_2.gif
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_3.gif
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_4.gif
[5]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_Sort_5.gif

