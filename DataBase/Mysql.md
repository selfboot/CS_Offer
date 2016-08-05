MySQL 为关系型数据库(Relational Database Management System)，这种所谓的"关系型"可以理解为"表格"的概念, 一个关系型数据库由一个或数个表格组成。

MySQL 主要是由两部分组成，服务器端和客户端。简单的说，服务器端用来保存数据，客户端就是连接服务器端，对服务器进行各种操作的。

OS X 下安装 mysql，然后启动服务的命令如下：

    $ brew install mysql        # 安装mysql
    $ brew info mysql           # 查看mysql信息
    $ mysql.server start        # 启动MySQL服务
    $ mysql —help               # 查看帮助

# 登录

当 MySQL 服务已经运行时，我们可以通过MySQL自带的客户端命令行工具登录到MySQL数据库中：

    $ mysql -h host -u user -p
    Enter password: ********

其中：

- -h：该命令用于指定客户端所要登录的MySQL主机名, 登录当前机器该参数可以省略；
- -u：所要登录的用户名；
- -p：告诉服务器将会使用一个密码来登录，如果所要登录的用户名密码为空，可以忽略此选项。

登录成功，会看到如下信息：

    Welcome to the MySQL monitor.  Commands end with ; or \g.
    Your MySQL connection id is 31 Server version: 5.6.22 Homebrew
    ...
    Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.
    mysql>

`mysql> `提示符告诉用户可以输入其他命令了。如果登录出现问题，可以参考： [Section C.5.2, “Common Errors When Using MySQL Programs”](file:///Users/feizhao/Library/Application%20Support/Dash/DocSets/MySQL/MySQL.docset/Contents/Resources/Documents/error-handling.html#common-errors).

# 数据库

可以使用下面的命令创建数据库

    mysql> create database smile;
    Query OK, 1 row affected (0.00 sec)
 
unix下，数据库名称(还有表格名称)是大小写有关的，不像数据库中的create、select等命令大小写无关。新建数据库后，要想使用该数据库必须显式选择，如下：

    mysql> use smile;
    Database changed

我们可以用 show 命令查看已经存在的数据库，如下：

    mysql> show databases;
    
    +--------------------+
    | Database           |
    +--------------------+
    | information_schema |
    | smile              |
    | test               |
    +--------------------+
    2 rows in set (0.02 sec)

删除数据库可以用 DROP 命令，如下：

    mysql> drop database smile;
    Query OK, 0 rows affected (0.01 sec)

# 数据表

创建表格并不难，困难的地方在于决定数据库使用哪些表格，以及这些表格中有哪些字段。下面假设我们有一个student表格，存放学生的一些信息，包括姓名，学号(假设8位)，出生日期。

    mysql> CREATE TABLE student (name VARCHAR(20), student_id INT(8),  birth DATE);

    Query OK, 0 rows affected (0.03 sec)

创建完表格之后，我们就可以使用 SHOW 命令来查看当前数据库的表格，如下：

    mysql> show tables;
    +-----------------+
    | Tables_in_smile |
    +-----------------+
    | student         |
    +-----------------+
    1 row in set (0.00 sec)

我们可以用 DESCRIBE 命令来查看创建好的表格的结构：

    mysql> describe student;
    
    +------------+-------------+------+-----+---------+-------+
    | Field      | Type        | Null | Key | Default | Extra |
    +------------+-------------+------+-----+---------+-------+
    | name       | varchar(20) | YES  |     | NULL    |       |
    | student_id | int(8)      | YES  |     | NULL    |       |
    | birth      | date        | YES  |     | NULL    |       |
    +------------+-------------+------+-----+---------+-------+
    3 rows in set (0.00 sec)

接下来就是向表格中导入数据了，假设我们有下面的学生数据：

| 诸葛亮 | 09383001 | 1993-02-04 |
| --- | --- | --- |
| 赵子龙 | 09383002 | 2989-05-17 |
| 张飞 | 09383003  | 1994-03-17 |

只需要将这些信息放入 info.txt 文件，每个学生占一行，每项信息以 Tab 键隔开，空白项用 \N(NULL) 来占位，注意MySql下日期的格式为xxxx-xx-xx。然后就可以用 LOAD DATA 命令来导入数据，如下：

    mysql> LOAD DATA LOCAL INFILE '~/Destop/info.txt' INTO TABLE student

不过 LOAD DATA 命令可能会被禁止掉，详细内容可以看[Section 6.1.6, “Security Issues with LOAD DATA LOCAL”](file:///Users/feizhao/Library/Application%20Support/Dash/DocSets/MySQL/MySQL.docset/Contents/Resources/Documents/security.html#load-data-local)。当我们插入少量的数据时，可以直接用 INSERT 语句，如下：

    mysql> INSERT INTO student VALUES ('刘备', 09383022, '1988-01-01');
    
    Query OK, 1 row affected (0.00 sec)

删除表格语句如下：

    mysql> drop table student;
    Query OK, 0 rows affected (0.01 sec)
    mysql> show tables;
    
    Empty set (0.00 sec)

### alter 修改表

我们可能会经常修改和改进表结构，但是，每次进行修改时不必都先删除再重新创建表。相反，可以使用alter语句修改表的结构。利用这个语句，可以在必要时删除、修改和增加列。比如在表tb_demo表中插入一列，表示email，如下：

    mysql> alter table tb_demo add column email varchar(45);
    Query OK, 0 rows affected (0.14 sec)
    Records: 0  Duplicates: 0  Warnings: 0

新的列放在表的最后位置。不过，还可以使用适当的关键字（包括first、after和last）来控制新列的位置。如果想修改表，比如，刚刚加的email，想加入一个not null控制，代码可以是这样的：

    mysql> alter table tb_demo change email email varchar(45) not null;
    Query OK, 0 rows affected (0.11 sec)
    Records: 0  Duplicates: 0  Warnings: 0

如果觉的这个email这列没有存在的必要了，可以使用下面的代码删除它，例如：

    mysql> alter table tb_demo drop email;
    Query OK, 0 rows affected (0.09 sec)
    Records: 0  Duplicates: 0  Warnings: 0

# MySQL 数据类型

好比C++中，定义int类型需要多少字节，定义double类型需要多少字节一样，MySQL对表每个列中的数据也会实行严格控制，这是数据驱动应用程序成功的关键。MySQL提供了一组可以赋给表中各个列的数据类型，每个类型都强制数据满足为该数据类型预先确定的一组规则，例如大小、类型及格式。

对于数据库的整体优化来说，正确定义表中的字段是非常关键的。如果事先知道只会用到2个字符的宽度，就不要把字段定义为10个字符宽。MySQL使用的多种数据类型可分为三类：数字、日期与时间，以及字符串类型，这三大类中又更细致的划分了许多子类型:

* 数字类型
    * 整数: tinyint、smallint、mediumint、int、bigint
    * 浮点数: float、double、real、decimal

* 日期和时间: date、time、datetime、timestamp、year
* 字符串类型
    * 字符串: char、varchar
    * 文本: tinytext、text、mediumtext、longtext
    * 二进制(可用来存储图片、音乐等): tinyblob、blob、mediumblob、longblob


## 数字类型

MySQL使用标准的 ANSI SQL 数字类型，支持整型和浮点数。

整型有如下几种子类型：

| MySQL数据类型 | 含义（有符号） |
| --- | --- |
| tinyint(m) | 1个字节  范围(-128~127) |
| smallint(m)<span class="Apple-tab-span" style="white-space:pre"></span> | 2个字节  范围(-32768~32767) |
| mediumint(m) | 3个字节  范围(-8388608~8388607) |
| int(m) | 4个字节  范围(-2147483648~2147483647) |
| bigint(m) | 8个字节  范围(+-9.22*10的18次方) |

浮点型(float和double) 有 float 和 double：

| MySQL数据类型 | 含义 |
| --- | --- |
| float(m,d) | 单精度浮点型，8位精度(4字节)，m总个数，d小数位 |
| double(m,d) | 双精度浮点型，16位精度(8字节)，m总个数，d小数位 |
|decimal(m, d)	 | decimal是存储为字符串的浮点数 |

设一个字段定义为float(5,3)，如果插入一个数123.45678,实际数据库里存的是123.457，但总个数还以实际为准，即6位。

## 日期与时间类型

MySQL 包含以下几种日期与时间类型：

| MySQL数据类型 | 含义 |
| --- | --- |
| date | 日期 '2008-12-2'  |
| time | 时间 '12:25:36'   |
| datetime | 日期时间 '2008-12-2 22:06:44' |
| timestamp | 自动存储记录修改时间 |

若定义一个字段为timestamp，这个字段里的时间数据会随其他字段修改的时候自动刷新，所以这个数据类型的字段可以存放这条记录最后被修改的时间。

## 字符串类型

虽然数字与日期类型都很有趣，但通常我们存储最多的就是字符串了。下面列出了 MySQL 中常见的字符串类型。

| MySQL数据类型 | 含义 |
| --- | --- |
| char(n) | 固定长度，最多255个字符 |
| varchar(n) | 可变长度，最多65535个字符 |
| tinytext | 可变长度，最多255个字符 |
| text | 可变长度，最多65535个字符 |
| mediumtext | 可变长度，最多2的24次方-1个字符 |
| longtext | 可变长度，最多2的32次方-1个字符 |

char（n）和varchar（n）中括号中n代表字符的个数，并不代表字节个数，所以当使用了中文的时候(UTF8)意味着可以插入m个中文，但是实际会占用m*3个字节。

char和varchar相比：

1. char(n) 若存入字符数小于n，则以空格补于其后，查询之时再将空格去掉。所以char类型存储的字符串末尾不能有空格，varchar不限于此。 
2. char(n) 固定长度，char(4)不管是存入几个字符，都将占用4个字节，varchar是存入的实际字符数+1个字节（n<=255）或2个字节(n>255)，所以varchar(4)，存入3个字符将占用4个字节。 
3. char类型的字符串检索速度要比varchar类型的快。

varchar和text相比： 

1. varchar可指定n，text不能指定，内部存储varchar是存入的实际字符数+1个字节（n<=255）或2个字节(n>255)，text是实际字符数+2个字节。 
2. text类型不能有默认值。 
3. varchar可直接创建索引，text创建索引要指定前多少个字符。varchar查询速度快于text。

## 数据类型的属性


`auto_increment` 为新插入的行赋一个唯一的整数标识符，为列赋此属性将为每个新插入的行赋值为上一次插入的ID+1。MySQL要求将auto_increment属性用于作为主键的列。此外，每个表只允许有一个auto_increment列。例如：

    id smallint not null auto_increment primary key

`default` 属性确保在没有任何值可用的情况下，赋予某个常量值，这个值必须是常量，因为MySQL不允许插入函数或表达式值。此外，此属性无法用于BLOB或TEXT列。如果已经为此列指定了NULL属性，没有指定默认值时默认值将为NULL，否则默认值将依赖于字段的数据类型。例如：

    subscribed enum('0', '1') not null default '0'

`index`属性：如果所有其他因素都相同，要加速数据库查询，使用索引通常是最重要的一个步骤。索引一个列会为该列创建一个有序的键数组，每个键指向其相应的表行。以后针对输入条件可以搜索这个有序的键数组，与搜索整个未索引的表相比，这将在性能方面得到极大的提升。

    create table employees
    (
        id varchar(9) not null,
        firstname varchar(15) not null,
        lastname varchar(25) not null,
        email varchar(45) not null,
        phone varchar(10) not null,
        index lastname(lastname),
        primary key(id)
    );

我们也可以利用MySQL的create index命令在创建表之后增加索引：

    create index lastname on employees (lastname(7));

这一次只索引了名字的前7个字符，因为可能不需要其它字母来区分不同的名字。因为使用较小的索引时性能更好，所以应当在实践中尽量使用小的索引。

`not null`：如果将一个列定义为not null，将不允许向该列插入null值。建议在重要情况下始终使用not null属性，因为它提供了一个基本验证，确保已经向查询传递了所有必要的值。

`null`：为列指定null属性时，该列可以保持为空，而不论行中其它列是否已经被填充。记住，null精确的说法是“无”，而不是空字符串或0。

`primary key`：属性用于确保指定行的唯一性，指定为主键的列中，值不能重复，也不能为空。为指定为主键的列赋予auto_increment属性是很常见的，因为此列不必与行数据有任何关系，而只是作为一个唯一标识符。主键又分为以下两种：

* 单字段主键：如果输入到数据库中的每行都已经有不可修改的唯一标识符，一般会使用单字段主键。注意，此主键一旦设置就不能再修改。
* 多字段主键：如果记录中任何一个字段都不可能保证唯一性，就可以使用多字段主键。这时，多个字段联合起来确保唯一性。如果出现这种情况，指定一个auto_increment整数作为主键是更好的办法。

`unique`：被赋予unique属性的列将确保所有值都有不同的值，只是null值可以重复。一般会指定一个列为unique，以确保该列的所有值都不同。例如：

    email varchar(45) unique


# 更多阅读
[MySQL处理数据库和表的常用命令](http://www.jellythink.com/archives/646)  
[MySQL数据类型和属性](http://www.jellythink.com/archives/642)  

