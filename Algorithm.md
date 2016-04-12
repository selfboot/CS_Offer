**写在最前面**

能解算法题并不意味着这个人就有能力就能在工作中解决问题，你可以想想，小学奥数题可能比这些题更难，但并不意味着那些奥数能手就能解决实际问题。

对于算法题，我们太喜欢研究算法题的空间和时间复杂度了。我们希望做到空间和时间双丰收，这是算法学术界的风格。所以，习惯于标准答案的我们已经失去思考的能力，只会机械地思考算法之内的性能，而忽略了`算法之外的性能`。

当然，算法很重要，算法题能锻炼我们的思维，而且也有很多实际用处。所以，才有了下面的内容...

# 基本算法理论

## 渐进记号的性质

![][1]

![][2]

［[记号O的定义](http://www.nowcoder.com/questionTerminal/281cab90faae4597a1164e25ea42fd87)］  
［[求算法时间复杂度](http://www.nowcoder.com/questionTerminal/38ec26f251b1471682653e69e17d3f52?source=relative)］  

# 经典排序算法

如果 Ai = Aj，排序前 Ai 在 Aj 前，排序后Ai还是在Aj前，则称排序算法是`稳定`的。

|排序法    |最差时间分析   |平均时间复杂度|空间复杂度 |稳定度|
|---------|-------------|------------|---------|-----|
|冒泡排序  |n^2      |n^2     |1     |**稳定**  |
|选择排序	|n^2  	  |n^2     |1     |不稳定 |
|插入排序  |n^2      |n^2     |1     |**稳定**  |
|快速排序	|n^2      |nlogn   |logn  |不稳定|
|希尔排序  |n^2	    | nlogn  |1      |不稳定|
|二叉树排序|n^2 	     |nlogn   |n     |不稳定|
|堆排序	  |nlogn	  |nlogn   |1     |不稳定|
|归并排序  |nlogn    | nlogn  | n    | **稳定** |
|基数排序  |d(r+n)   |d(r+n)  |rd+n  | **稳定** |

［[5排序函数，最大3位](http://www.nowcoder.com/questionTerminal/7cd79ea790ca4fa1a06dbd93dcf58d7d)］  
［[大量数据中获取前十名](http://www.nowcoder.com/questionTerminal/2ff38817ad074579ae9e07d7d2143fc8)］  
［[加减数字组成一个范围](http://www.nowcoder.com/questionTerminal/1ed7b4017caf4e79ab0621089b4e3d0d)］

# 经典算法思想

## 贪心

## 动态规划

## 分治法

### 二分查找

二分查找算法（binary search）是一种在有序数组中查找某一特定元素的算法。搜索过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜索过程结束；如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。这种搜索算法每一次比较都使搜索范围缩小一半，因此时间复杂度为 logn。

更多内容参见 [BinarySearch.md](C++_Code/Algorithm_BinarySearch.md)

### 相关题目

| 题目简单描述 |  OJ来源  |  Python | C++ |
|---------|---------|----------|---------|
|数组中第 k 大的数 | [LeetCode](https://leetcode.com/problems/kth-largest-element-in-an-array/) | [py](https://github.com/xuelangZF/LeetCode/blob/master/DivideConquer/215_KthLargestElementArray.py) | [cpp](https://github.com/xuelangZF/LeetCode/blob/master/DivideConquer/215_KthLargestElementArray.cpp) |

# 字符串算法

KMP 算法

［[计算 nextval 值](http://www.nowcoder.com/questionTerminal/6bfed2073b48431ea5bfea01684e9ef1)］

# 图算法

## 拓扑排序

对一个有向无环图 (Directed Acyclic Graph, DAG) G 进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前。拓扑排序的结果不唯一。
 
拓扑排序算法主要是循环执行以下两步，直到不存在入度为0的顶点为止。

1. 选择一个入度为0的顶点并输出之；
2. 从图中删除此顶点及所有出边。

循环结束后，若输出的顶点数小于图的顶点数，则有向图中有回路，否则输出的顶点序列就是一种拓扑序列。


［[可能的拓扑序列](http://www.nowcoder.com/questionTerminal/4d323088446d41f69a3868293d0575fe)］



# 参考

[数学之美番外篇：快排为什么那样快](http://mindhacks.cn/2008/06/13/why-is-quicksort-so-quick/)  
[为什么我反对纯算法面试题](http://coolshell.cn/articles/8138.html)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_1.jpg
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_2.jpg

