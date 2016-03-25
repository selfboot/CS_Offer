/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-01 11:33:36
*/

#include <iostream>
using std::cout;

static int a = 20;

static void func_1(){
    cout << "Global variable: " << a << "\n";
}

void func_2(){
    static int a = 1;
    a += 1;
    cout << "Local variable :" << a << "\n";
}

int main ( ) {
    cout <<  "Global variable: " << a << "\n";
    a += 1;
    func_1();
    func_2();
    func_2();
    func_1();
    func_2();
}


/*
 * Global variable: 20
 * Global variable: 21
 * Local variable :2
 * Local variable :3
 * Global variable: 21
 * Local variable :4
 */
