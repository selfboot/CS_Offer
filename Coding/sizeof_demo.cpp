/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 14:06:39
*/

#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::string;

class A{
public:
    A() {}
    ~A() {}
    int m1;
    int m2;
};

class B:A{
    B() {}
    ~B() {}
    char m2;
    int m1;
    static char m3;
};

class C{
public:
    C() {}
    ~C() {}
    virtual void fun_1(){}
    virtual void fun_2(){}
    int m1;
    short m2;
};

class D{
};

class BU
{
    int number;
    union UBffer
    {
        char buffer[13];
        int number;
    }ubuf;
    void foo(){}
    typedef char*(*f)(void*);
    enum {hdd,ssd,blueray} disk;
};

int main ( ) {
    int *a;
    cout << "Int    " << sizeof *a << "\n";     // 4
    cout << "Point  " << sizeof(a) << "\n";     // 4 (or 8)
    double *arr = new double[10];
    cout << "double " << sizeof(*arr) << "\n";  // 8
    cout << "Point  " << sizeof(arr) << "\n";   // 4(or 8)

    cout << "Char   " << sizeof(char) << "\n";      // 1
    cout << "Short  " << sizeof(short) << "\n";     // 2
    cout << "int    " << sizeof(int) << "\n";       // 4
    cout << "Float  " << sizeof(float) << "\n";     // 4
    cout << "Double " << sizeof(double) << "\n";    // 8
    cout << "long   " << sizeof(long) << "\n";      // 8

    cout << "--- Class ---\n";
    cout << sizeof(A) << ", " << sizeof(B) << "\n"; // 8, 16
    cout << sizeof(C) << ", " << sizeof(D) << "\n"; // 12, 1 or(16, 1)
    cout << sizeof C::m1 << ", " << sizeof C::m2 << "\n"; // 4, 2

    cout << "--- Array ---\n";
    float f[] = {1.0,2.0,3.0,4.0,5.0};
    cout << "Array  " << sizeof(f) << "\n";     // 20
    char str[]="Tencent";
    cout << "Array  " << sizeof(str) << "\n";   // 8

    cout << "--- Vector, String ---\n";
    vector<int> v(10, 0);
    cout << "Vector " << sizeof(v) << "\n";     //24
    string s("1234");
    cout << "String " << sizeof(s) << "\n";     // 24

    cout << sizeof(BU) << std::endl;
    return 0;
}
