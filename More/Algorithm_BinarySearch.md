`二分查找算法`（binary search）是一种在有序数组中查找某一特定元素的算法。搜索过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜索过程结束；如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。这种搜索算法每一次比较都使搜索范围缩小一半，因此时间复杂度为 logn。

![][1]

算法看起来十分简单，但要注意几个问题：

* 递归还是迭代？
* 递归实现时，检查参数的有效性（low/high参数）；
* 计算二分查找中的中值时防止溢出；
* 如何查找第一个/最后一个等值？
 
# 简单实现

下面来看下二分查找的两种实现方案，首先是递归实现。



# STL 二分查找



# 参考  
[Binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)  
[数据库中二分查找相关问题](http://hedengcheng.com/?p=595)  



[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_BinarySearch_1.png

