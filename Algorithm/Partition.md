


    procedure three-way-partition(A : array of values, mid : value):
        i ← 0
        j ← 0
        n ← size of A - 1
    
        while j ≤ n:
            if A[j] < mid:
                swap A[i] and A[j]
                i ← i + 1
                j ← j + 1
            else if A[j] > mid:
                swap A[j] and A[n]
                n ← n - 1
            else:
                j ← j + 1




# 更多阅读

[Algorithms 4.0: DemoPartitioning](http://algs4.cs.princeton.edu/lectures/23DemoPartitioning.pdf)   
[Dutch national flag problem](https://en.wikipedia.org/wiki/Dutch_national_flag_problem)

