/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-06 08:50:34
 */

#include <iostream>
using namespace std;

class A{
public:
    A(int x): data(x){}
    void print_data() const{
        cout << "Data: " << data << endl;
        // set_data(1);  Error
        // member function 'set_data' not viable: 'this' argument has type 'const A', but function is not marked const
    }
    void set_data(int x){
        data = x;
        print_data();   // no-const function call const function.
    }
    // Here we define a overload function.
    void set_data(int x) const{
        size = x;       // mutable variable can be modified in const func.
        cout << "Size: " << size << endl;
    }

    void update(int x){
        data = x;
        cout << "Data: " << data << endl;
    }

private:
    int data = 0;
    mutable int size = 0;   // Can be modified in const function.

};

int main() {
    A a(2);
    a.set_data(10);
    a.print_data(); // No-const object call const function.
    const A b(-2);
    b.set_data(20); // Here const object call const function.
    // member function 'update' not viable: 'this' argument has type 'const A', but function is not marked const
    // b.update(10);    Error.
}

