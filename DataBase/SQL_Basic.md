SQL (结构化查询语言)是一门 ANSI 的标准计算机语言，用来访问和操作数据库系统。SQL 可与数据库程序协同工作，比如 MS Access、DB2、MS SQL Server、Oracle以及其他数据库系统。不幸地是，存在着很多不同版本的 SQL 语言，但是为了与 ANSI 标准相兼容，它们必须以相似的方式共同地来支持一些主要的关键词（比如 SELECT、UPDATE、DELETE、INSERT、WHERE 等等）。

可以把 SQL 分为两个部分：`数据操作语言 (DML)` 和 `数据定义语言 (DDL)`。DML 提供从数据库中查询信息，以及在数据库中插入、删除、修改元组的能力，DDL 提供定义、删除、修改关系模式的命令。（SQL 语句对大小写不敏感）

SQL 的 DML 部分包括删除、更新、插入、查询操作：

* SELECT - 从数据库表中获取数据
* UPDATE - 更新数据库表中的数据
* DELETE - 从数据库表中删除数据
* INSERT INTO - 向数据库表中插入数据

SQL 的数据定义语言 (DDL) 部分使我们有能力创建或删除表格。我们也可以定义索引（键），规定表之间的链接，以及施加表间的约束：

* CREATE DATABASE - 创建新数据库
* ALTER DATABASE - 修改数据库
* CREATE TABLE - 创建新表
* ALTER TABLE - 变更（改变）数据库表
* DROP TABLE - 删除表
* CREATE INDEX - 创建索引
* DROP INDEX - 删除索引

此外，SQL还包括定义完整性约束的命令，定义视图的命令，定义事务的开始和结束的命令，定义对关系和视图的访问权限的命令等。

# SQL DML：增删查改

## 查询

SELECT 语句用于从表中选取数据，结果被存储在一个结果表中（称为结果集）。SQL 查询基本结构由三个子句构成：select、from 和 where，查询的输入是在 from 子句中列出的关系，在这些关系上进行 where 和 select 子句中指定的运算，然后产出一个关系作为结果。语法如下：

    SELECT column_name,column_name
    FROM table_name
    WHER p

例如下列SQL语句返回所有有定单的客户：

    SELECT OrderID, Customer.customerID   
    FROM Orders, Customers   
    WHERE Orders.CustomerID=Customers.CustomerID 

［[多表查询笛卡尔积](http://www.nowcoder.com/questionTerminal/686aa444c67b4f0c9ca774a50caa494a)］  

## 插入

INSERT INTO 语句用于向表中插入新记录。要往关系中插入数据，可以指定待插入的元组，或者写一条查询语句来生成待插入的元组集合。必须保证待插入元组的属性值必须在相应属性的域中。

insert 语句中可以指定属性，也可以不指定，不指定属性时，插入值的排序和关系模式中属性排列的顺序一致。

    insert into course
        values('CS-437','Database System', 'Comp. Sci', 4);
        
    insert into course(course_id, title, dept_name, credits)
        values('CS-437','Database System', 'Comp. Sci', 4);
        
    insert into course(title, course_id, dept_name, credits)
        values('Database System', 'CS-437', 'Comp. Sci', 4);


## 更新

update 语句可以在不改变整个元组的情况下改变其部分属性的值。假如要进行年度工资增长，如下：

    update instructor
    set salary=salary*1.5

上面更新语句将在instructor关系的每个元组上执行一次。update 语句中嵌套的 select 语句可以引用待更新的关系，对工资低于平均工资的教师涨 5% 的工资，可以写成如下形式：

    update instructor
    set salary=salary*1.05
    where salary < (select avg(salary)
                    from instructor);

SQL 语句提供case 语句，可以利用它在一条语句中执行多种更新，避免因为更新次序可能引发的问题。

    update instructor
    set salary=case
        when salary = 7000 then salary * 1.05
        when salary < 7000 then salary * 1.15
        else salary * 1.03
        end

## 删除

DELETE 语句用于删除表中的记录。只能删除整个元组，而不能只删除某些属性上的值。

    DELETE FROM r
    WHERE p;

其中 P 代表一个谓词，r代表一个关系。delete 语句首先从 r 中找出所有使P(t)为真的元组，然后把它们从 r 中删除。如果省略where子句，则r中所有元组将被删除。

delete 请求可以引用包含嵌套的select，该 select 引用待删除元组的关系。假如想删除工资低于大学平均工资的教师记录，可以写出如下语句：

    delete from instructor
    where salary < (select avg(salary)
                    from instructor);

该 delete 语句首先测试 instructor 关系中的每一个元组，检查其工资是否小于大学教师的平均工资，然后再删除所有符合条件的元组。注意，这里在**执行任何删除之前先进行所有元组的测试**至关重要。

# SQL 子句、函数

## WHERE 子句

WHERE 子句用于提取那些满足指定标准的记录。语法如下：

```SQL
SELECT column_name,column_name
FROM table_name
WHERE column_name operator value;
```

下面的 SQL 语句从 "Websites" 表中选取国家为 "CN" 的所有网站：

```SQL
SELECT * FROM Websites WHERE country='CN';
```

下面的运算符可以在 WHERE 子句中使用：

* =：等于。
* <>：不等于。（在 SQL 的一些版本中，该操作符可被写成 !=）
* >：大于
* <：小于
* >=：大于等于
* <=：小于等于
* BETWEEN：在某个范围内
* LIKE：**搜索某种模式**
* IN：指定针对某个列的多个可能值

可以在字符串上可以使用`like 操作符`来实现模式匹配（大小写敏感）。

* `百分号%`：匹配任意字符串
* `下划线_`：匹配任意一个字符

为了使模式中包含特殊模式的字符（％，_），SQL允许转义字符。在like比较运算中使用`escape 关键词`来定义转义字符。如下例子：

* like 'ab\%cd%' escape '\': 匹配所有以 'ab%cd' 开头的字符串；
* like '[8,6]_0%'：匹配第一位为8或6，第三位为0的字符串；

所以要查找 student表中所有电话号码(列名：telephone)的第一位为8或6，第三位为0的电话号码，用下面语句即可：

    SELECT telephone FROM student WHERE telephone LIKE ‘[8,6]_0%’

［[查找倒数第三个字符为W](http://www.nowcoder.com/questionTerminal/87a000d6b34d4c82be56d17ad2945a60)］

## GROUP BY 子句

Group By 语句从英文的字面意义上理解就是根据(by)一定的规则进行分组(Group)。它的作用是通过一定的规则将一个数据集划分成若干个小的区域，然后针对若干个小区域进行数据处理。

GROUP BY 语句用于结合聚合函数，根据一个或多个列对结果集进行分组。比如统计 access_log 各个 site_id 的访问量：

```SQL
SELECT site_id, SUM(access_log.count) AS nums
FROM access_log GROUP BY site_id;
```

［[Group By子句作用](http://www.nowcoder.com/questionTerminal/a1403ec16dc245ebbed0f88f7479dd92)］  
［[分组后满足指定条件的查询](http://www.nowcoder.com/questionTerminal/a42d4a67d0b0471a8dfd7e9b3892afee)］

## HAVING 子句

在 SQL 中增加 HAVING 子句原因是，**WHERE 关键字无法与聚合函数一起使用**。HAVING 子句可以让我们筛选分组后的各组数据。假设我们想要查找总访问量大于 200 的网站，可以使用下面的 SQL 语句：

```SQL
SELECT Websites.name, Websites.url, SUM(access_log.count) AS nums FROM (access_log
INNER JOIN Websites
ON access_log.site_id=Websites.id)
GROUP BY Websites.name
HAVING SUM(access_log.count) > 200;
```

现在假设想要查找总访问量大于 200 的网站，并且 alexa 排名小于 200。我们在 SQL 语句中增加一个普通的 WHERE 子句：

    SELECT Websites.name, SUM(access_log.count) AS nums FROM Websites
    INNER JOIN access_log
    ON Websites.id=access_log.site_id
    WHERE Websites.alexa < 200 
    GROUP BY Websites.name
    HAVING SUM(access_log.count) > 200;

## ORDER BY 子句

ORDER BY 关键字用于对结果集按照一个列或者多个列进行排序，默认按照升序对记录进行排序。如果需要按照降序对记录进行排序，您可以使用 `DESC` 关键字。


```SQL
SELECT column_name,column_name
FROM table_name
ORDER BY column_name,column_name ASC|DESC;
```

如果想从 "Websites" 表中选取所有网站，并按照 "country" 和 "alexa" 列排序：


```SQL
SELECT * FROM Websites
ORDER BY country,alexa;
```

## 聚合函数

SQL 拥有很多可用于计数和计算的内建函数，`聚合函数`计算从列中取得的值，返回一个单一的值，常用的聚合函数如下：

| 函数 | 用处 |
| --- | --- |
| AVG()  | AVG() 函数返回数值列的平均值。 |
| COUNT() | 返回匹配指定条件的行数。|
| FIRST() | 返回指定的列中第一个记录的值。 |
| LAST() | 返回指定的列中最后一个记录的值。 |
| MAX() | 返回指定列的最大值。 |
| MIN() | 返回指定列的最小值。 |
| SUM()  |返回数值列的总数。 |

## 执行顺序

SQL 语句的语法顺序和其执行顺序并不一致，标准的 SQL 的解析顺序为:

1. FROM 子句, 组装来自不同数据源的数据
2. WHERE 子句, 基于指定的条件对记录进行筛选
3. GROUP BY 子句, 将数据划分为多个分组
4. 使用聚合函数进行计算
5. 使用 HAVING 子句筛选分组
6. 计算 SELECT 等表达式
7. 使用 ORDER BY 对结果集进行排序

FROM 是 SQL 语句执行的第一步，并非 SELECT。数据库在执行 SQL 语句的第一步是将数据从硬盘加载到数据缓冲区中，以便对这些数据进行操作。

SELECT 是在大部分语句执行了之后才执行的，严格的说是在 FROM 和 GROUP BY 之后执行的。理解这一点是非常重要的，这就是你不能在 WHERE 中使用在 SELECT 中设定别名的字段作为判断条件的原因。

    SELECT A.x + A.y AS z
    FROM A
    WHERE z = 10 // z 在此处不可用，因为SELECT是最后执行的语句！

# SQL DDL

`CREATE DATABASE` 语句用于创建数据库，DROP DATABASE 语句用于删除数据库。下面的 SQL 语句创建一个名为 "my_db" 的数据库：


```SQL
CREATE DATABASE my_db;
```

`CREATE TABLE` 语句用于创建数据库中的表，表由行和列组成，每个表都必须有个表名。使用 DROP TABLE 语句来删除表。假设想要创建一个名为 "Persons" 的表，包含五列：PersonID、LastName、FirstName、Address 和 City。

```SQL
CREATE TABLE Persons
(
    PersonID int,
    LastName varchar(255),
    FirstName varchar(255),
    Address varchar(255),
    City varchar(255)
);
```

`ALTER TABLE` 语句用于在已有的表中添加、删除或修改列。

```SQL
ALTER TABLE table_name
---
ADD column_name datatype
DROP COLUMN column_name
MODIFY COLUMN column_name datatype // ALTER COLUMN column_name datatype
```

假设想要想要删除 "Person" 表中的 "DateOfBirth" 列，可以使用下面的 SQL 语句：

    ALTER TABLE Persons
    DROP COLUMN DateOfBirth

CREATE INDEX 语句用于在表中创建索引，在不读取整个表的情况下，索引使数据库应用程序可以更快地查找数据。CREATE UNIQUE INDEX 在表上创建一个唯一的索引，不允许使用重复的值。DROP INDEX 语句用于删除表中的索引。

假设在 "Persons" 表的 "LastName" 列上创建一个名为 "PIndex" 的索引：

```SQL
CREATE INDEX PIndex
ON Persons (LastName)
```


# 更多阅读
[十步完全理解 SQL](http://blog.jobbole.com/55086/)  
[SQL逻辑查询语句执行顺序](http://www.jellythink.com/archives/924)  

