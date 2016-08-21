/*
* @Author: xuelangZF
* @Date:   2016-03-29 10:11:27
* @Last Modified time: 2016-03-29 10:55:33
*/
#include <iostream>
#include <string>
using namespace std;

class CBase {
    string name;
    int age;
public:
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
protected:
    void setName(string s) {
        name = s;
    }
    void setAge(int i) {
        age = i;
    }
};

class CPublicDerive : public CBase {    //用 public 指定公有继承
public:
    void setBase(string s, int i) {
        setName(s);    //调用基类的保护成员
        setAge(i);     //调用基类的保护成员
        //调用基类的私有成员
        //cout << name << "   " << age << endl;    //编译出错
    }
};

class CProtectDerive : protected CBase {    //用 protected 指定保护继承
public:
    void setBase(string s, int i) {
        setName(s);    //调用基类的保护成员
        setAge(i);     //调用基类的保护成员
        //调用基类的私有成员
        //cout << name << "   " << age << endl;    //编译出错
    }
    string getBaseName() {
        return getName();    //调用基类的公有成员
    }
    int getBaseAge() {
        return getAge();     //调用基类的公有成员
    }
};

class CPrivateDerive : private CBase {    //用 private 指定私有继承，private可以省略
public:
    void setBase(string s, int i) {
        setName(s);    //调用基类的保护成员
        setAge(i);     //调用基类的保护成员
        //调用基类的私有成员
        //cout << name << "   " << age << endl;    //编译出错
    }
    string getBaseName() {
        return getName();    //调用基类的公有成员
    }
    int getBaseAge() {
        return getAge();     //调用基类的公有成员
    }
};

int main ( )
{
    // 公有继承
    CPublicDerive cpublic;
    cpublic.setBase("public", 1);
    //调用基类的私有成员
    //cout << cpublic.name << "   " << cpublic.age << endl;    //编译出错
    //调用基类的公有成员
    cout << cpublic.getName() << "   " << cpublic.getAge() << endl;
    //调用基类的保护成员
    //cpublic.setName("xyz");    //编译出错
    //cpublic.setAge(20);        //编译出错

    // 保护继承
    CProtectDerive cprotect;
    cprotect.setBase("protect", 2);
    //调用基类的公有成员
    //cout << cprotect.getName() << "   " << cprotect.getAge() << endl;    //编译出错
    cout << cprotect.getBaseName() << "   " << cprotect.getBaseAge() << endl;
    //调用基类的保护成员
    //cprotect.setName("xyz");    //编译出错
    //cprotect.setAge(20);        //编译出错


    // 私有继承
    CPrivateDerive cprivate;
    cprivate.setBase("private", 3);
    //调用基类的公有成员
    //cout << cprivate.getName() << "   " << cprivate.getAge() << endl;    //编译出错
    cout << cprivate.getBaseName() << "   " << cprivate.getBaseAge() << endl;
    //调用基类的保护成员
    //cprivate.setName("xyz");    //编译出错
    //cprivate.setAge(20);        //编译出错

    // 隐式类型转换
    CBase &cbase = cpublic;
    // cbase.setName("xyz");    //编译出错
    // cbase.setAge(20);        //编译出错
    cout << cbase.getName() << "   " << cbase.getAge() << endl;
    return 0;
}
