/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-04-17 10:57:53
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
    A& operator= (const A& b){
        cout << "4" << endl;
        return *this;
    }
};

void f(A a){        // 3, Copy Constructor.  Create a temp object as parameter.
}                   // 2, Destructors.  Delete the temp object.

A f_2(A a){         // 3, Copy Constructor.  Create a temp object as parameter.
    return a;       // 3, Copy Constructor.  Create a temp object as return value.
}                   // 2, Destructors.  Delete the parameter.

void g(A &a){       // None.
}                   // None.

A & g_2(A &a){
    return a;
}

void h(A *a){       // None.
}                   // None.

int main(void)
{
    A a;            // 1, Constructor
    f(a);           // 3 2
    g(a);           // None
    A c = f_2(a);   // 3 3 2
    // f_2(a);      // 3 3 2 2.  The object returned is destructed here because of no use.
    g_2(a);         // None

    A b=a;          // 3, Copy Constructor.  Same with A b(a)
    b = a;          // 4, Assignment operator.  b is already existing.

    A *d;           // None, just a A * point.
    d = new A();    // 1, Constructor.  Then d point to the temp A object.
    A *e = d;       // None. new A * pointer point to existing A object.
    h(d);           // None

    delete d;       // 2, Destructor.  Delete the A object in heap.
    d = NULL;
    // delete e;    // d, e point to the same A object in heap. Here e is NULL.

    return 0;
    // 2, Destructor a
    // 2, Destructor c
    // 2, Destructor b
}
