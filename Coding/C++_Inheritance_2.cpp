/*
* @Author: xuelangZF
* @Date:   2016-03-29 10:11:27
* @Last Modified time: 2016-03-29 10:55:33
*/

#include <iostream>
using namespace std;

class A
{
public:
    A() : p1(1), p2(2), p3(3) {}
public:
    int p1;
private:
    int p2;
protected:
    int p3;
};

class B: public A {};

int main()
{
    A a;
    std::cout << *(int *)&a << std::endl;       // 1
    std::cout << *((int *)&a + 1) << std::endl; // 2
    std::cout << *((int *)&a + 2) << std::endl; // 3
    B b;
    std::cout << *(int *)&b << std::endl;       // 1
    std::cout << *((int *)&b + 1) << std::endl; // 2
    std::cout << *((int *)&b + 2) << std::endl; // 3
    return 0;
}
