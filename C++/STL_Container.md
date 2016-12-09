> 容器，置物之所也。

研究数据的特定排列方式，以利于搜寻或者排序或其他特殊目的，这一专门学科称为数据结构。几乎可以说，任何特定的数据结构都是为了实现某种特定的算法。

众所周知，常用的数据结构不外乎数组(array)、链表(list)、树(tree)、栈(stack)、队列(queue)、散列表(hash table)、集合(set)、映射(map)等等。根据数据在容器中的排列特性，这些数据结构分为序列式和关联式两种。STL容器即是将运用最广的一些数据结构实现出来。

![][2]

# 序列式容器

`序列式容器（sequential container）`：其中的元素都可序（ordered），但未必有序（sorted）。C++语言本身提供了一个序列式容器 array，STL 另外提供了 vector，list，deque，stack，queue，priority-queue等序列式容器。其中 stack、queue 只是由 deque 改头换面而成，技术上归为一种配接器（adapter）。`适配器`是标准库中的一个通用概念，容器、迭代器和函数都有适配器。本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。

## [vector](http://www.cplusplus.com/reference/vector/vector/)

> Vectors are sequence containers representing arrays that can change in size.

Vector 是一个拥有扩展功能的数组，我们可以创建任何类型的 vector，通过 vector 创建二维数组，最简单的方式就是创建一个存储 vector 元素的 vector。

    int N＝5, M＝10;
    vector<vector<int>> Matrix(N, vector<int>(M, -1));

我们创建了一个 N * M 的矩阵，**并用 -1 填充所有位置上的值**。再看下面的例子：

    vector<int> v(10, 0);
    int elements_count = v.size();
    bool is_nonempty_ok = !v.empty();
    
这里 V 包含了10 个 int 整数，初始化为0。Vector 最常使用的特性就是获取容器`size`，有两点要注意：首先，**size() 函数返回的值是无符号的，这点有时会引起一些问题**。其次，如果你想知道容器是否为空，把 size() 返回值和0比较不是一个好的做法。最好使用 empty() 函数，因为不是所有容器都能在常量时间内返回自己的大小，而且你绝不应该为了确定链表中至少包含一个节点元素就对一条双链表中的所有元素计数。

另一个 vector 中经常使用的函数是 `push_back`。Push_back 函数永远向 **vector 尾部**添加一个元素，容器长度加 1。当需要调整 vector 的大小时，使用 resize() 函数。如果在使用了 resize() 后又用了 push_back()，那新添加的元素就会位于新分配内存的后面，而不是被放入新分配的内存当中。

    v.resize(15);
    for(int i = 1; i < 5; i++) {
        v.push_back(i*2);
        //把元素写入下标值[15..20), not [10..15)
    }

此外，`erase()函数`从指定容器删除指定位置的元素或某段范围内的元素，如果是删除指定位置的元素时，返回值是一个迭代器，指向删除元素下一个元素；如果是删除某范围内的元素时：返回值也表示一个迭代器，指向最后一个删除元素的下一个元素。下面例子中删除 vector 中指定的某个元素值（删除一个元素后导致后面所有的元素会向前移动一个位置）：

```c++
std::vector<int> array = {1,2,6,6,7,8};
for (std::vector<int>::iterator itor = array.begin(); itor != array.end(); itor++)
{
   if (*itor == 6) {
       array.erase(itor);
       itor--;
   }
}
for(auto n: array) std::cout << n << ", ";
// 1,2,7,8
```

vector 提供了许多元素操作方法，不详细说明，下面简单列出常使用的：

* insert()：在指定的迭代器位置前面插入新的元素或者一组元素，返回指向新插入元素（如果是一组元素的话，返回第一个）的迭代器；
* clear()：清空 vector，使其包含 0 个元素，成为空容器。
* capacity()：返容器占用的内存空间，注意和v.size()的区别（空间的分配和size的关系）；
* pop_back()：删除尾部的数据，size -= 1；
* c.at(index)：传回索引为index的数据，如果index越界，抛出out_of_range异常。
* c.front()：返回第一个数据，在空的 vector 上调用该操作会导致未定义行为。
* c.back()：传回最后一个数据，在空的 vector 上调用该操作会导致未定义行为。

很多时候大量删除数据，或者通过使用reserver()，结果vector占有的空间远远大于实际的需要，这时候需要压缩vector到它的实际大小。在 C++11 中已经提供了`shrink_to_fit()`函数实现vector的压缩。

    std::vector<int> v(1000,1);              // v.capacity()=1000
    v.erase(v.begin(), v.begin()+v.size()/2);// v.capacity()=1000
    v.shrink_to_fit();                       // v.capacity()=500

（空间增长策略*：按照容器现在容量的一倍进行增长。vector容器分配的是一块连续的内存空间，每次容器的增长，并不是在原有连续的内存空间后再进行简单的叠加，而是重新申请一块更大的新内存，并把现有容器中的元素逐个复制过去，然后销毁旧的内存。这时原有指向旧内存空间的迭代器已经失效，所以当操作容器时，迭代器要及时更新。*）

## [list](http://www.cplusplus.com/reference/list/list/)

> Lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence, and iteration in both directions.

相较于 vector 的连续线性空间，list 显得复杂许多，它的好处是每次插入或者删除一个元素，就配置或者释放一个元素空间。因此 list 对于空间的运用有绝对的精准，一点也不浪费。而且对于任何位置的元素插入或元素移除，list 永远是常数时间。

STL list 实现是一个双向链表（SGI list是环状双向链表），迭代器具备前移、后移的能力，所以 list 提供的是 Bidirectional Iterators。list 有个重要的性质：`插入操作和接合操作都不会造成原有的 list 迭代器失效`。这在 vector 是不成立的，因为 vector 的插入操作可能造成记忆体重新配置，导致原有的迭代器全部失效。

![][3]

和 vector 一样，list 也提供了 push_back, pop_back方法，此外由于是双向链表，还可以从头部插入或者删除数据：push_front, push_front。还提供了和 vector 功能相同的front，back，insert，erase，clear 函数。来看几个简单的例子：

```c++
std::list<int> mylist;

mylist.push_back(33);
mylist.push_back(22);
mylist.push_front(11);

mylist.front() -= mylist.back();
mylist.insert(mylist.begin(), 0);
mylist.erase(--mylist.end());

for(auto n: mylist) std::cout << n << " ";  // 0 -11 33 
```

由于 list 数据结构的特殊，也提供了一些 vector 没有的操作，如下：

* splice：将某个连续范围的元素从一个list迁移（transfer）到另一个（或者同一个）list的某个定点。
* remove：删除list中指定值的元素，和 erase 不同，这里是根据值而不是位置去删除。
* merge：合并两个有序链表并使之有序。
* sort：针对 list 的特定排序算法，默认的算法库中的sort需要随机访问迭代器，list并不能提供。

下面看简单的例子：

```c++
std::list<std::string> mylist;
mylist.push_back ("one");
mylist.push_back ("two");
mylist.push_back ("three");
mylist.remove("two");

mylist.sort();
for(auto n: mylist) std::cout << n << " ";  // one three

return 0;
```

## [deque](http://www.cplusplus.com/reference/deque/deque/)

> deque (usually pronounced like "deck") is an irregular acronym of double-ended queue. Double-ended queues are sequence containers with dynamic sizes that can be expanded or contracted on both ends (either its front or its back).

vector 是单向开口的连续线性空间，deque 则是一种双向开口的连续线性空间。所谓双向开口，意思是可以在头尾两端分别做元素的插入和删除工作，如下图所示：

![][4]

deque 和 vector 的差异在于：

* deque 允许常数时间内对起头端进行元素的插入或移除操作
* deque 没有所谓的容量（capacity）概念，因为它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来。

虽然 deque 也提供了 RandomAccessIterator，但是它的迭代器并不是普通指针，复杂度大很多。因此除非必要，应该尽可能使用 vector 而非 deque。对 deque 进行排序操作，为了提高效率，可以先将 deque 完整复制到一个 vector 中，将 vector 排序后（利用 STL sort），再复制回 deque。下面看一个简单的例子：

```c++
std::deque<int> mydeque;

// set some initial values:
for (int i=1; i<6; i++) mydeque.push_back(i);   // 1 2 3 4 5
std::deque<int>::iterator it = mydeque.begin();
++it;
it = mydeque.insert (it,10);
mydeque.erase(--mydeque.end());
for(auto n: mydeque) std::cout << n << " ";     // 1 10 2 3 4
```

## 适配器

### [stack](http://www.cplusplus.com/reference/stack/stack/)

> Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container.

stack 是一种先进后出的数据结构，SGI STL以 deque 作为缺省情况下的 stack 底部结构。它主要支持下面的操作：

* empty：判断栈是否为空
* size：取得栈的大小
* top：取得栈顶元素
* push：入栈操作
* pop：出栈操作

stack 所有元素的进出都必须符合“先进后出”的条件，只有 stack 顶端的元素，才有机会被外界取用。因此 **stack 不提供走访功能，不提供迭代器**。简单的使用例子如下：

```c++
std::stack<int> mystack;
for (int i=0; i<5; ++i) mystack.push(i);
std::cout << "Popping out elements...";
while (!mystack.empty())
{
   std::cout << ' ' << mystack.top();
   mystack.pop();
}
std::cout << '\n';
// Popping out elements... 4 3 2 1 0
return 0;
```

### [queue](http://www.cplusplus.com/reference/queue/queue/)

> queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out), where elements are inserted into one end of the container and extracted from the other.

queue 是一种先进先出（FIFO）的数据结构，允许从最底部加入元素，同时取得最顶部元素。SGI STL以 deque 作为缺省情况下的 queue 底部结构。它主要支持下面的操作：

* empty：判断队列是否为空
* size：取得队列的大小
* front：取得队列头部元素
* back：取得队列尾部元素
* push：队列尾部插入元素
* pop：从队列头部取出元素

和 stack 一样， **queue 不提供走访功能，不提供迭代器**。简单的使用例子如下：

```c++
std::queue<int> myqueue;
for (int i=0; i<5; ++i) myqueue.push(i);
std::cout << "Popping out elements...";
while (!myqueue.empty())
{
   std::cout << ' ' << myqueue.front();
   myqueue.pop();
}
std::cout << '\n';
// Popping out elements... 0 1 2 3 4
return 0;
```

### [priority_queue](http://www.cplusplus.com/reference/queue/priority_queue/)

> Priority queues are a type of container adaptors, specifically designed such that its first element is always the greatest of the elements it contains, according to some strict weak ordering criterion.

优先队列（priority queue）允许用户以任何次序将任何元素推入容器内，但取出时一定是从优先权最高的元素开始取。优先队列具有权值观念，其内的元素并非依照被推入的次序排列，而是自动依照元素的权值排列，权值最高者排在最前面。

优先队列完全以底部容器为根据，加上 heap 处理规则，具有`修改某物接口，形成另一种风貌`的性质，因此是配接器。优先队列中的所有元素，进出都有一定的规则，只有queue顶部的元素（权值最高者），才有机会被外界取用。因此并不提供遍历功能，也不提供迭代器。

优先队列的构造函数和其他序列式容器的略有不同，因为需要指定底层容器的类型和优先级比较的仿函数。C++11 中一共有5大种构造函数，下面列出其中一种：

```c++
template <class InputIterator>
priority_queue (InputIterator first, InputIterator last,
                const Compare& comp, const Container& ctnr);
```

下面是具体的构造示例：

```c++
int myints[]= {10,60,50,20};

std::priority_queue<int> first;
std::priority_queue<int> second (myints,myints+4);
std::priority_queue<int, std::vector<int>, std::greater<int>> third (myints,myints+4);
```

# 关联容器

`关联式容器（associative-container）`：观念上类似关联式数据库，每个元素都有一个键值（key）和一个实值（value）。当元素被插入到关联式容器中时，容器内部结构便依照其键值大小，以某种特定规则将这个元素放置于适当位置。标准的 STL 关联式容器分为map（映射表）和 set（集合）两大类，以及衍生体 multiset（多键集合）和多键映射表（multimap），底层均为 RB-Tree（红黑树完成）。

* map中的元素是一些关键字-值对（key-value）对：关键字起到索引的作用，值则表示与索引相关联的数据。
* set中每个元素只包含一个关键字，set支持高效的关键字查询操作——检查一个给定关键字是否在 set 中。

标准库提供了8个关联容器，体现在三个不同的维度：

1. 或者是一个 map，或者是一个 set；
2. 允许关键字重复，或者不允许；
3. 按照顺序保存元素，或者无序保存。

具体情况如下表：

![][1]

## 定义关联容器

定义 map 必须指明关键字类型和值类型，而定义一个set时，只需要指明关键字类型。

    map <string, size_t> word_count; // 空容器
    set <string> exclude = {"the", "but", "and"}; // 列表初始化
    map <string, string> authors = { {"Joyce", "James"},
                                    {"Austen", "Jane"} };

**对于有序容器，关键字类型必须定义元素比较的方法**。默认情况下，标准库使用关键字类型的 `< 运算符` 来比较两个关键字。

无序容器使用关键字类型的 == 运算符来比较元素，它们还使用一个hash<key_type>类型的对象来生成每个元素的哈希值。标准库为内置类型定义了 hash 模板，还为一些标准库类型，如 string 定义了hash。但是我们**不能直接定义关键字类型为自定义类类型的无序容器。因为不能直接使用哈希模板**，必须提供我们自己的 hash 模板版本。

### pair类型

标准库类型 pair 是用来生成特定类型的模板，创建一个 pair 时必须提供两个类型名，pair的数据成员将具有对应的类型。

    pair<string, string> anon{"James", "Joyce"};
    pair<string, vector<int>> line;

与其他标准库类型不同，pair的数据成员是 public 的，两个成员分别命名为 first 和 second，使用普通的成员访问符来访问它们。

    cout << anon.first << anon.second;

## 关联容器操作

关联容器的类型有如下三个：

|类型        |        解释      |
|----       |----              |
|key_type   | 对应容器类型的关键字类型 |
|mapped_type| map 关键字关联的类型    |
|value_type | 对于 set，与 key_type 相同，对于map，为 `pair<const key_type, mapped_type>` |

解引用关联容器迭代器时，得到一个类型为容器的 value_type 的值的引用。对于map而言，value_type 是一个 pair 类型，其 first 成员保存 `const 的关键字`，second 成员保存值。

    map<int, string> test{ {1, "1"} };
    auto iter = test.begin();
    cout << iter->first << ", " << iter->second << endl;
    // iter->first = 2;         // 关键字类型是 const 的
    iter -> second = "2";
    cout << iter->first << ", " << iter->second << endl;

与不能改变 map 的关键字一样，一个 **set 中的关键字也是 const 的，可以用一个 set 迭代器来读元素的值，但不能修改**（因为 set 元素值就是其键值，关系到 set 元素的排列规则，如果任意改变set元素值，会破坏set组织）。

**通常不对关联容器使用泛型算法**，因为关键字是 const 这一特性意味着不能将关联容器传递给修改或者重排容器元素的算法（这类算法往往需要向元素写入值）。关联容器可用于只读取元素的算法。

### 添加元素

关联容器的 insert 成员向容器添加一个元素或一个元素的范围。insert 有两个版本，分别接受一对迭代器，或者是一个初始化器列表。注意，由于map 和 set 包含不重复的关键字，因此插入一个已经存在的元素对容器没有任何影响。

    vector <int> ivec = {4,3,2,1,1,2,3,4};
    set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    // set2 = {1, 2, 3, 4} 有四个元素

对 map 进行 insert 操作时，必须记住元素类型是 pair，一般在insert 参数列表中创建一个 pair：

    map<string, int> word_count;
    word_count.insert({"or", 1});
    word_count.insert(make_pair("the", 1));
    word_count.insert(pair<string, int>("and", 1));
    word_count.insert(map<string, int>::value_type("text", 1));

insert 返回的值依赖于容器类型和参数，对于不包含重复关键字的容器，添加单一元素的 insert返回一个 pair。pair 的 **first 成员是一个迭代器，指向插入妥当的新元素或指向插入失败点（键值重复）的旧元素**，second 成员是一个 bool 值，指出元素是插入成功（返回1）还是已经存在于容器中（没有插入，因此返回0）。

    map<string, int> word_count;
    word_count.insert({"or", 1});
    auto ret = word_count.insert(make_pair("or", 1));
    if(!ret.second){
        ret.first->second += 1;
    }
    // {"or", 2}

我们要知道这里 ret 的类型为：

    pair<map<string, int>::iterator, bool> 

对允许重复关键字的容器，接受单个元素的 insert 操作返回一个指向新元素的迭代器，这里无需返回一个 bool值，因为 insert 操作总是向这类容器中加入一个新元素。

### 删除元素

关联容器定义了三个版本的 erase，与序列式容器一样，可以通过传递给 erase 一个迭代器删除一个元素或者一个迭代器对删除一个元素范围。这两个版本和序列式容器的操作类似，指定的元素被删除，返回 void。

此外，关联容器提供额外的 erase 操作，接受一个 key_type 参数，此版本删除所有匹配给定关键字的元素（如果存在的话），返回实际删除的元素的数量。对于保存不重复关键字的容器，erase返回值总是0或者1。

### map 的下标操作

map 和 unordered_map 容器提供了下标运算符和一个对应的at函数。set类型不支持下标，因为set中没有与关键字相关联的值。也不能对 multimap 或 unordered_multimap 进行下标操作，因为这些容器中可能有多个值与一个关键字相关联。

如果关键字不在 map 中，会为它创建一个元素并插入到 map 中，关联值将进行值初始化。由于下标运算符可能插入一个新元素，我们只可以对非 const 的map使用下标操作。

    map<string, int> word_count;
    word_count["test"];
    word_count["give"] = 1;
    // word_count: { {give, 1},{test, 0} }
    
上面最后一句执行的操作如下：

1. 在 word_count 中搜索关键字为 give 的元素，未找到；
2. 将一个新的`关键字-值`对插入到 word_count 中，关键字是一个 const string，保存 give，值进行初始化为0；
3. 提取出新插入的元素，并将值 1 赋予它。

对一个 map 进行下标操作时，会获得一个 mapped_type 对象。

### 访问元素

关联容器提供多种查找一个指定元素的方法，如果只关心一个特定元素是否已在容器中， find 是最佳选择。

|    操作     |   含义   |
|----------- |----------|
|  c.find(k) | 返回一个迭代器，指向第一个关键字为 k 的元素，若 k 不在容器中，则返回尾后迭代器 |
| c.count(k) | 返回关键字等于k的元素的数量，对于不允许重复关键字的容器，返回值永远是0或1    |
| c.lower_bound(k) | 返回一个迭代器，指向第一个关键字不小于 k 的元素| 
| c.upper_bound(k) | 返回一个迭代器，指向第一个关键字大于 k 的元素 |
| c.equal_range(k) | 返回一个迭代器 pair，表示关键字等于 k 的元素的范围。若 k 不存在，pair 的两个成员均等于 c.end() |

在一个不允许重复关键字的关联容器中查找一个元素是一件很简单的事情，元素要么在容器中，要么不在。但对于允许重复关键字的容器来说，过程更为复杂：容器中可能有很多元素具有给定的关键字。如果一个 multimap 或 multiset 中有多个元素具有给定关键字，则这些元素在容器中会`相邻存储`。

    multimap<string, int> authors{ {"Alain", 1}, {"Alain", 2}, {"Alain", 3} };
    string search_item("Alain");
    auto iter = authors.find(search_item);
    auto entries = authors.count(search_item);
    while(entries){
        cout << iter->second << endl;
        iter++;
        entries--;
    }

此外，可以用 lower_bound 和 upper_bound 来解决此类问题。 

    for(auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item);
        beg != end; beg++){
        cout << beg->second << endl;
    }

# 更多阅读

《STL 源码剖析》  
《C++ Primer》 11章：关联容器  
[标准模板库（STL）使用入门（上）](http://blog.jobbole.com/87586/)  
[标准模板库（STL）使用入门（下）](http://blog.jobbole.com/88310/)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_Container_1.png
[2]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_Container_2.png
[3]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_Container_3.png
[4]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_Container_4.png

