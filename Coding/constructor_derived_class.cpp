/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-14 11:02:31
 * Refer to
 * https://msdn.microsoft.com/zh-cn/library/s16xw1a8.aspx#order_of_construction
 */

#include <iostream>
using namespace std;

class Contained1 {
public:
    Contained1() {
        cout << "Contained1 constructor." << endl;
    }
    ~Contained1(){
        cout << "Contained1 destructor." << endl;
    }
};

class Contained2 {
public:
    Contained2() {
        cout << "Contained2 constructor." << endl;
    }
    ~Contained2(){
        cout << "Contained2 destructor." << endl;
    }
};

class Contained3 {
public:
    Contained3() {
        cout << "Contained3 constructor." << endl;
    }
    ~Contained3(){
        cout << "Contained3 destructor." << endl;
    }
};

class BaseContainer {
public:
    BaseContainer() {
        cout << "BaseContainer constructor." << endl;
    }
    // virtual destructor is very important here, or will cause resources leak.
    virtual ~BaseContainer(){
        cout << "BaseContainer destructor." << endl;
    }
private:
    Contained1 c1;
    Contained2 c2;
};

class DerivedContainer : public BaseContainer {
public:
    DerivedContainer(){
        cout << "DerivedContainer constructor." << endl;
    }
    ~DerivedContainer(){
        cout << "DerivedContainer destructor." << endl;
    }
private:
    Contained3 c3;
};

int main() {
    DerivedContainer dc;
    cout << "+++++++++++++" << endl;
    BaseContainer *p = new DerivedContainer();
    cout << "*************" << endl;
    /*
     * If baseContainer destructor is not virtual, delete p has undefined behaviour.
     * In most implementations, the call to the destructor will be resolved like any non-virtual code,
     * meaning that the destructor of the base class will be called but not the one of the derived class,
     * resulting in a resources leak.
     * Refer to:
     * http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
     */
    delete p;
    cout << "-------------" << endl;
    return 0;
    // Here dc is destroyed normally no matter whether the base class's destructor is virtual or not.
}

/*
Contained1 constructor.
Contained2 constructor.
BaseContainer constructor.
Contained3 constructor.
DerivedContainer constructor.
+++++++++++++
Contained1 constructor.
Contained2 constructor.
BaseContainer constructor.
Contained3 constructor.
DerivedContainer constructor.
*************
BaseContainer destructor.
Contained2 destructor.
Contained1 destructor.
-------------
DerivedContainer destructor.
Contained3 destructor.
BaseContainer destructor.
Contained2 destructor.
Contained1 destructor.
*/
