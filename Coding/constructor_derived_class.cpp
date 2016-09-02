/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-02-29 20:51:22
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
};

class Contained2 {
public:
    Contained2() {
        cout << "Contained2 constructor." << endl;
    }
};

class Contained3 {
public:
    Contained3() {
        cout << "Contained3 constructor." << endl;
    }
};

class BaseContainer {
public:
    BaseContainer() {
        cout << "BaseContainer constructor." << endl;
    }
private:
    Contained1 c1;
    Contained2 c2;
};

class DerivedContainer : public BaseContainer {
public:
    DerivedContainer() : BaseContainer() {
        cout << "DerivedContainer constructor." << endl;
    }
private:
    Contained3 c3;
};

int main() {
    DerivedContainer dc;
    /*
    Contained1 constructor.
    Contained2 constructor.
    BaseContainer constructor.
    Contained3 constructor.
    DerivedContainer constructor.
    */
    return 0;
}
