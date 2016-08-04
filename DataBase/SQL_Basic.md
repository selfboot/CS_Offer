SQL 是使用最为广泛的查询语言，有以下几个部分：

* 数据定义语言（DDL）：提供定义、删除、修改关系模式的命令；
* 数据操纵语言（DML）：提供从数据库中查询信息，一集在数据库中插入、删除、修改元组的能力；
* 完整性（Integrity）：定义完整性约束的命令
* 视图定义（View definition）：定义视图的命令
* 事物控制（transaction control）：定义事务的开始和结束的命令
* 嵌入式SQL和动态SQL：定义SQL语句如何嵌入到通用编程语言中
* 授权：定义对关系和视图的访问权限的命令

## SQL 查询基本结构

SQL 查询基本结构由三个子句构成：select、from 和 where，查询的输入是在 from 子句中列出的关系，在这些关系上进行 where 和 select 子句中指定的运算，然后产出一个关系作为结果。


多表连接没有指定连接条件时，对应集合的笛卡尔积连接。

［[多表查询笛卡尔积](http://www.nowcoder.com/questionTerminal/686aa444c67b4f0c9ca774a50caa494a)］  

### 附加的基本运算

`字符串运算`：在字符串上可以使用`like 操作符`来实现模式匹配（大小写敏感）。

* `百分号%`：匹配任意字串
* `下划线_`：匹配任意一个字符

为了使模式中包含特殊模式的字符（％，_），SQL允许转义字符。在like比较运算中使用 escape 关键词来定义转义字符。如下例子：

* like 'ab\%cd%' escape '\': 匹配所有以 'ab%cd' 开头的字符串；
* like '[8,6]_0%'：匹配第一位为8或6，第三位为0的字符串；

所以要查找 student表中所有电话号码(列名：telephone)的第一位为8或6，第三位为0的电话号码，用下面语句即可：

    SELECT telephone FROM student WHERE telephone LIKE ‘[8,6]_0%’

［[查找倒数第三个字符为W](http://www.nowcoder.com/questionTerminal/87a000d6b34d4c82be56d17ad2945a60)］

## 聚集函数

GroupBy语句从英文的字面意义上理解就是“根据(by)一定的规则进行分组(Group)”。它的作用是通过一定的规则将一个数据集划分成若干个小的区域，然后针对若干个小区域进行数据处理。

［[Group By子句作用](http://www.nowcoder.com/questionTerminal/a1403ec16dc245ebbed0f88f7479dd92)］  

标准的 SQL 的解析顺序为: 

1. FROM 子句, 组装来自不同数据源的数据
2. WHERE 子句, 基于指定的条件对记录进行筛选
3. GROUP BY 子句, 将数据划分为多个分组
4. 使用聚合函数进行计算
5. 使用 HAVING 子句筛选分组
6. 计算Select所有的表达式
7. 使用 ORDER BY 对结果集进行排序

［[分组后满足指定条件的查询](http://www.nowcoder.com/questionTerminal/a42d4a67d0b0471a8dfd7e9b3892afee)］  

## 数据库的修改

SQL 支持对数据库的修改操作，包括删除、更新、插入操作。这些操作都可以用 where 指定谓语，where 子句可以包含 select 语句的 where 子句中的任何合法结构（包括嵌套的select）。**where 语句中嵌套的select可以引用待更新的关系**。

### 删除

只能删除整个元组，而不能只删除某些属性上的值。

> delete from r  
> where P;

其中 P 代表一个谓词，r代表一个关系。delete 语句首先从 r 中找出所有使P(t)为真的元组，然后把它们从 r 中删除。如果省略where子句，则r中所有元组将被删除。

delete 请求可以引用包含嵌套的select，该 select 引用待删除元组的关系。假如想删除工资低于大学平均工资的教师记录，可以写出如下语句：

    delete from instructor
    where salary < (select avg(salary)
                    from instructor);

该 delete 语句首先测试 instructor 关系中的每一个元组，检查其工资是否小于大学教师的平均工资，然后再删除所有符合条件的元组。注意，这里在**执行任何删除之前先进行所有元组的测试**至关重要。

### 插入

要往关系中插入数据，可以指定待插入的元组，或者写一条查询语句来生成待插入的元组集合。必须保证待插入元组的属性值必须在相应属性的域中。insert 语句中可以指定属性，也可以不指定，不指定属性时，插入值的排序和关系模式中属性排列的顺序一致。

    insert into course
        values('CS-437','Database System', 'Comp. Sci', 4);
        
    insert into course(course_id, title, dept_name, credits)
        values('CS-437','Database System', 'Comp. Sci', 4);
        
    insert into course(title, course_id, dept_name, credits)
        values('Database System', 'CS-437', 'Comp. Sci', 4);

### 更新

update 语句可以在不改变整个元组的情况下改变其部分属性的值。假如要进行年度工资增长，如下：

    update instructor
    set salary=salary*1.5

上面更新语句将在instructor关系的每个元组上执行一次。update 语句中嵌套的 select 语句可以引用待更新的关系，对工资低于平均工资的教师涨 5% 的工资，可以写成如下形式：

    update instructor
    set salary=salary*1.05
    where salary < (select avg(salary)
                    from instructor);

SQL 语句提供case 语句，可以利用它在一条语句中执行多种更新，避免更新次序发生的问题。

    update instructor
    set salary=case
        when salary = 7000 then salary * 1.05
        when salary < 7000 then salary * 1.15
        else salary * 1.03
        end

SQL 的更多高级内容参见 [DataBase_SQL.md](More/DataBase_SQL.md)


