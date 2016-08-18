算法，即以有限的步骤，解决数学或逻辑上的问题。STL提供了大量操作容器的算法，包括赫赫有名的排序，查找，排列组合算法以及用于数据移动、复制、删除、比较、组合、运算等的算法。这些算法都是采用函数模板来实现的。

STL 中的算法独立于其所处理的数据结构之外，不受数据结构的羁绊。这是因为 STL 将操作对象的型别加以抽象化，把操作对象的标示法和区间目标的移动行为抽象化，于是整个算法就可以在一个抽象层面工作了。整个过程称为算法的泛型化，简称`泛化`。

所有泛型算法的前两个参数都是一对迭代器（iterators），通常称为 first 和 last，用以标示算法的操作区间。STL 习惯采用前闭后开区间表示法，写成[first, last)。不过有一个必要条件就是，必须能够经由 increment（累加）操作符的反复运用，从first到达last。编译器本身无法强求这一点，需要程序员去保证。如果无法确定这点，将导致未可预期的结果。

每一个 STL 算法的声明，都必须表现出它所需要的最低程度的迭代器类型，例如 find() 需要一个 InputIterator ，这是它的最低要求，但是它也可以接受更高类型的迭代器，如 ForwardIterator, BidirectionalIterator 或者 RandomAccessIterator。但是如果给 find 传递一个 OutputIterator，将会出错。此外，将无效的迭代器传递给某个算法，虽然是一种错误，但是不保证编译器就会被捕捉出来。

我们还要知道许多 STL 算法并不只支持一个版本，这一类算法的某个版本采用缺省运算行为，另一个版本提供额外参数，接受外界传入的一个仿函数（functor），以便采用其他策略。

STL算法部分主要由头文`<algorithm>, <numeric>, <functional>`组成。要使用 STL中的算法函数必须包含头文件\<algorithm\>，对于数值算法须包含\<numeric\>，\<functional\>中则定义了一些模板类，用来声明函数对象。

# 常用 STL 算法

STL 涵盖了太多日常可能需要重复使用的算法，这里介绍其中比较常用的一些：

* sort
* lower_bound(upper_bound, binary_search, equal_range)
* reverse
* swap

## [sort](http://www.cplusplus.com/reference/algorithm/sort/)

> Sorts the elements in the range [first,last) into ascending order.  The elements are compared using operator< for the first version, and comp for the second.

sort 是我们用的最多的一个算法，它接受两个 RandomAccessIterators（随机存取迭代器），然后将区间内所有元素以递增方式由大到小重新排列。它的仿函数版本，允许自定义排序标准。关联式容器自动排序，序列式容器中 stack，queue，priority-queue 都是有特定的出入口，因此也不需要 sort。list 的迭代器属于 BidirectionalIterators，因此不能用 sort，剩下的 vector 和 deque 比较适合用sort。

```c++
template <class RandomAccessIterator>
void sort (RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Compare>
void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

一定要注意第二个参数是一个仿函数对象，直接用仿函数类是不可以的。下面是一个简单的示例：

```c++
int myints[] = {32,71,12,45,26,80,53,33};
std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

// using default comparison (operator <):
std::sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33
// using function as comp
std::sort (myvector.begin()+4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)
// print out content:
// using object as comp
std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)
```

## [lower_bound](http://www.cplusplus.com/reference/algorithm/lower_bound/)

> Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.

这是二分查找的一种版本，试图在已经排序的[first, last)中寻找元素 value。它返回一个迭代器，指向第一个`不小于value`的元素。如果 value 大于 [first, last)内的任何一个元素，则返回 last。该函数接受两个版本，版本一采用 operator < 进行比较，版本二采用仿函数 comp，完整的声明如下：

```c++
template <class ForwardIterator, class T>
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                            const T& val);

template <class ForwardIterator, class T, class Compare>
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                            const T& val, Compare comp);
```

此外，还有一个和该函数十分类似的 [upper_bound](http://www.cplusplus.com/reference/algorithm/upper_bound/)，返回的迭代器指向区间内第一个大于 value 的元素。

具体使用例子如下：

```c++
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector

int main () {
    int myints[] = {10,20,30,30,20,10,10,20};
    std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20
    std::sort(v.begin(), v.end());                 // 10 10 10 20 20 20 30 30

    std::vector<int>::iterator low,up;
    low=std::lower_bound (v.begin(), v.end(), 20); //          ^
    up= std::upper_bound (v.begin(), v.end(), 20); //                   ^

    std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
    std::cout << "upper_bound at position " << (up - v.begin()) << '\n';

    return 0;
}
// lower_bound at position 3
// upper_bound at position 6
```

此外，还有一些用到二分查找的其他算法，比如 binary_search 用来检查指定值是否存在于排序后的序列中，equal_range 返回排序后的序列中值等于value的下标范围。

## 其他算法

* `reverse`: Reverses the order of the elements in the range [first,last).
* `swap`: Exchanges the values of a and b.
* `binary_search`: Returns true if any element in the range [first,last) is equivalent to val, and false otherwise.
* `find`: Returns an iterator to the first element in the range [first,last) that compares equal to val. If no such element is found, the function returns last.
* `find_first_of`:  Returns an iterator to the first element in the range [first1,last1) that matches any of the elements in [first2,last2). If no such element is found, the function returns last1.


# 更多阅读  

[how to find the intersection of two std:set in C++?](http://stackoverflow.com/questions/13448064/how-to-find-the-intersection-of-two-stdset-in-c)  
[cplusplus: set_intersection](http://www.cplusplus.com/reference/algorithm/set_intersection/)  
       

