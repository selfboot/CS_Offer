# 基本算法理论

## 渐进记号的性质

［[记号O的定义](http://www.nowcoder.com/questionTerminal/281cab90faae4597a1164e25ea42fd87)］

![][1]

![][2]

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

# 贪心算法

［[加减数字组成一个范围](http://www.nowcoder.com/questionTerminal/1ed7b4017caf4e79ab0621089b4e3d0d)］

# 字符串算法

KMP 算法

［字符串的 next 数组］

# 图算法

## 拓扑排序

对一个有向无环图 (Directed Acyclic Graph, DAG) G 进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前。拓扑排序的结果不唯一。
 
拓扑排序算法主要是循环执行以下两步，直到不存在入度为0的顶点为止。

1. 选择一个入度为0的顶点并输出之；
2. 从图中删除此顶点及所有出边。

循环结束后，若输出的顶点数小于图的顶点数，则有向图中有回路，否则输出的顶点序列就是一种拓扑序列。


［[可能的拓扑序列](http://www.nowcoder.com/questionTerminal/4d323088446d41f69a3868293d0575fe)］



# 算法

[数学之美番外篇：快排为什么那样快](http://mindhacks.cn/2008/06/13/why-is-quicksort-so-quick/)



[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_1.jpg
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_2.jpg

