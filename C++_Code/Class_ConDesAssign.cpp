/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-04-16 23:02:28
 */

#include <iostream>

using namespace std;

class A{
public:
    A(){
        cout << "1" << endl;
    }
    ~A(){
        cout << "2" << endl;
    }
    A(const A&b){
        cout << "3" << endl;
    }
    A& operator= (A& b){
        cout << "4" << endl;
        return b;
    }
};

void fun(A a){
    return;
}

int main(void)
{
    A a;            //  Constructor
    A b=a;
    A c(b);
    A *d;
    d = new A();
    A *e = d;
    fun(a);
    return 0;
}
