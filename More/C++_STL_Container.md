# 容器

一个容器就是一些特定类型对象的集合。`顺序容器（sequential container）`为程序员提供了控制元素存储和访问顺序的能力。这种顺序不依赖于元素的值，而是与元素加入容器时的位置相对应。

除了顺序容器外，标准库还定义了三个顺序容器适配器：stack、queue和priority_queue。`适配器`是标准库中的一个通用概念，容器、迭代器和函数都有适配器。本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。

和顺序容器对应的是`关联容器（associative-container）`，关联容器中的元素是按关键字来保存和访问的。关联容器支持高效的关键字查找和访问，STL有两个主要的关联容器：map 和 set。

# 顺序容器

## Vector

最简单的 STL 顺序容器就是 vector。Vector 只是一个拥有扩展功能的数组。

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

向 vector 添加数据的最简单方式是使用 push_back()。但是，万一我们想在除了尾部以外的地方添加数据呢？Insert函数可以实现这个目的，往 vector 中插入一个元素：

    vector<int> v(10,0);
    v.insert(1, 42);    // Insert value 42 after the first

从第二个（下标为1的元素）往后的所有元素都要右移一位，从而空出一个位置给新插入的元素。如果你打算添加很多元素，那多次右移并不可取——明智的做法是单次调用 insert()，指明插入数据的空间范围。

    vector<int> v1(3,0);
    vector<int> v2{1,2,3};
    v1.insert(v1.begin(), v2.begin(), v2.end());

还应该记住另一个非常重要的事情：当 vector 作为参数传给某个函数时，实际上是复制了这个 vector（也就是`值传递`）。在不需要这么做的时候创建新的 vector 可能会消耗大量时间和内存。实际上，很难找到一个任务需要在传递 vector 为参数时对其进行复制。所以，最好使用`引用传递`：

    void some_function(const vector<int>& v) { 
        // Read only!
    }
    void some_function(vector<int>& v) { 
        // Can be Modified!
    }

此外，要知道我们可以创建任何类型的 vector，通过 vector 创建二维数组，最简单的方式就是创建一个存储 vector 元素的 vector。

    int N＝5, M＝10;
    vector< vector<int> > Matrix(N, vector<int>(M, -1));

我们创建了一个 N * M 的矩阵，**并用 -1 填充所有位置上的值**。

`erase()函数`从指定容器删除指定位置的元素或某段范围内的元素，如果是删除指定位置的元素时，返回值是一个迭代器，指向删除元素下一个元素；如果是删除某范围内的元素时：返回值也表示一个迭代器，指向最后一个删除元素的下一个元素。

删除 vector 中指定的某个元素值（删除一个元素后导致后面所有的元素会向前移动一个位置）：

    vector<int> array = {1,2,6,6,7,8};
    for (vector<int>::iterator itor = array.begin(); itor != array.end(); itor++)
    {
        if (*itor == 6) {
            array.erase(itor);
            itor--;
        }
    }
    // 1,2,7,8

其他的一些函数：

* clear()：清空 vector，使其包含 0 个元素，成为空容器。
* capacity()：返容器占用的内存空间，注意和v.size()的区别（空间的分配和size的关系）；
* pop_back()：删除尾部的数据，size -= 1；
* c.at(index)：传回索引为index的数据，如果index越界，抛出out_of_range异常。
* c.front()：返回第一个数据。
* c.back()：传回最后一个数据，不检查这个数据是否存在。

很多时候大量删除数据，或者通过使用reserver()，结果vector占有的空间远远大于实际的需要，这时候需要压缩vector到它的实际大小。在 C++11 中已经提供`了shrink_to_fit()`函数实现vector的压缩。

    std::vector<int> v(1000,1);              // v.capacity()=1000
    v.erase(v.begin(), v.begin()+v.size()/2);// v.capacity()=1000
    v.shrink_to_fit();                       // v.capacity()=500

（空间增长策略*：按照容器现在容量的一倍进行增长。vector容器分配的是一块连续的内存空间，每次容器的增长，并不是在原有连续的内存空间后再进行简单的叠加，而是重新申请一块更大的新内存，并把现有容器中的元素逐个复制过去，然后销毁旧的内存。这时原有指向旧内存空间的迭代器已经失效，所以当操作容器时，迭代器要及时更新。*）

# 关联容器

关联容器用来支持高效的关键字查找和访问，其中的元素是按照关键字来保存和访问的。与之相对，顺序容器中的元素是按它们在容器中的位置来顺序保存和访问的。两个主要的关联容器类型是 map 和 set：

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
    map <string, string> authors = {{"Joyce", "James"},
                                    {"Austen", "Jane"}};

对于有序容器，关键字类型必须定义元素比较的方法。默认情况下，标准库使用关键字类型的 < 运算符来比较两个关键字。

无序容器使用关键字类型的 == 运算符来比较元素，它们还使用一个hash<key_type>类型的对象来生成每个元素的哈希值。标准库为内置类型定义了 hash 模板，还为一些标准库类型，如 string 定义了hash。但是我们不能直接定义关键字类型为自定义类类型的无序容器。因为不能直接使用哈希模板，必须提供我们自己的 hash 模板版本。

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

    map<int, string> test{{1, "1"}};
    auto iter = test.begin();
    cout << iter->first << ", " << iter->second << endl;
    // iter->first = 2;         // 关键字类型是 const 的
    iter -> second = "2";
    cout << iter->first << ", " << iter->second << endl;

与不能改变 map 的关键字一样，一个 set 中的关键字也是 const 的，可以用一个 set 迭代器来读元素的值，但不能修改。

通常不对关联容器使用泛型算法，因为关键字是 const 这一特性意味着不能将关联容器传递给修改或者重排容器元素的算法（这类算法往往需要向元素写入值）。关联容器可用于只读取元素的算法。

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

### 检测 insert 的返回值

insert 返回的值依赖于容器类型和参数，对于不包含重复关键字的容器，添加单一元素的 insert返回一个 pair，告诉我们插入操作是否成功。pair 的 **first 成员是一个迭代器，指向具有给定关键字的元素**，second 成员是一个 bool 值，指出元素是插入成功还是已经存在于容器中。

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

关联容器定义了三个版本的 erase，与顺序容器一样，可以通过传递给 erase 一个迭代器删除一个元素或者一个迭代器对删除一个元素范围。这两个版本和顺序容器的操作类似，指定的元素被删除，返回 void。

此外，关联容器提供额外的 erase 操作，接受一个 key_type 参数，此版本删除所有匹配给定关键字的元素（如果存在的话），返回实际删除的元素的数量。对于保存不重复关键字的容器，erase返回值总是0或者1。

### map 的下标操作

map 和 unordered_map 容器提供了下标运算符和一个对应的at函数。set类型不支持下标，因为set中没有与关键字相关联的值。也不能对 multimap 或 unordered_multimap 进行下标操作，因为这些容器中可能有多个值与一个关键字相关联。

如果关键字不在 map 中，会为它创建一个元素并插入到 map 中，关联值将进行值初始化。由于下标运算符可能插入一个新元素，我们只可以对非 const 的map使用下标操作。

    map<string, int> word_count;
    word_count["test"];
    word_count["give"] = 1;
    // word_count: {{give, 1},{test, 0}}
    
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

    multimap<string, int> authors{{"Alain", 1}, {"Alain", 2}, {"Alain", 3}};
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


# 参考

《C++ Primer》 11章：关联容器  
[标准模板库（STL）使用入门（上）](http://blog.jobbole.com/87586/)  
[标准模板库（STL）使用入门（下）](http://blog.jobbole.com/88310/)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/C++_STL_Container_1.png

