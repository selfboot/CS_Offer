/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-03 14:47:58
 */
#include <iostream>
#include "C++_Static_Global.h"

// Declaration made available here

// Variable defined here
int global_variable = 37;
int increment(void) {
    return global_variable++;
}
void use_it(void)
{
    std::cout << "Global variable: " << global_variable << "\n";
}
