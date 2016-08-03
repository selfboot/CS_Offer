/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-03 14:48:18
 */

#include <iostream>
#include "C++_Static_Global.h"

int main(void)
{
    use_it();
    global_variable += 1;
    use_it();
    std::cout << "Increment: " << increment() << "\n";
    return 0;
}
