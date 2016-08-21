/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 15:44:17
*/

#include <iostream>
#include <vector>
class String
{
public:
    String(const char *str=NULL);//普通构造函数
    String(const String &str);//拷贝构造函数
    String & operator =(const String &str);//赋值函数
    ~String();//析构函数
private:
    char* m_data;//用于保存字符串
};

//普通构造函数
String::String(const char *str)
{
    if (str==NULL)
    {
        m_data=new char[1]; //对空字符串自动申请存放结束标志'\0'的空间
        if (m_data==NULL)
        {//内存是否申请成功
            std::cout<<"申请内存失败！"<<std::endl;
            exit(1);
        }
        m_data[0]='\0';
    }
    else
    {
        int length=strlen(str);
        m_data=new char[length+1];
        if (m_data==NULL)
        {//内存是否申请成功
            std::cout<<"申请内存失败！"<<std::endl;
            exit(1);
        }
        strcpy(m_data, str);
    }
}

//拷贝构造函数
String::String(const String &str)
{ //输入参数为const型
    int length=strlen(str.m_data);
    m_data=new char[length+1];
    if (m_data==NULL)
    {//内存是否申请成功
        std::cout<<"申请内存失败！"<<std::endl;
        exit(1);
    }
    strcpy(m_data, str.m_data);
}

// 赋值函数，异常安全的赋值函数
// 创建临时变量，接着将临时变量的 m_pData 和实例自身的做交换
// 临时变量是一个局部栈变量，会自行回收。
String& String::operator =(const String &str)
{
    if(this != &str){   //检查自赋值
        String tmp(str);

        char* data = tmp.m_data;
        tmp.m_data = m_data;
        m_data = data;
    }
    return *this;
}

/*
String& String::operator =(const String &str)
{
    //输入参数为const型
    if (this==&str) //检查自赋值
        return *this;
    delete [] m_data;//释放原来的内存资源
    m_data = NULL;
    m_data = new char[strlen(str.m_data)+1];
    if (m_data==NULL)
    {//内存是否申请成功
        std::cout<<"申请内存失败！"<<std::endl;
        exit(1);
    }
    strcpy(m_data,str.m_data);
    return *this;//返回本对象的引用
}
*/

//析构函数
String::~String()
{
    delete [] m_data;
}

void foo(String x)
{
}

void bar(const String& x)
{
}

String baz()
{
    String ret("world");
    return ret;
}

int main()
{
    String s0;
    String s1("hello");
    String s2(s0);
    String s3 = s1;
    s2 = s1;

    foo(s1);
    bar(s1);
    foo("temporary");
    bar("temporary");
    String s4 = baz();

    std::vector<String> svec;
    svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(baz());
    svec.push_back("good job");
}

