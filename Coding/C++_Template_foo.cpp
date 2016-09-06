/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-06 11:32:32
 */

#include <iostream>
#include "C++_Template_foo.h"
template<typename T>
void foo()
{
  std::cout << "Here I am!\n";
}

template<typename T>
void Foo<T>::g()
{
  std::cout << "Foo<T>::g()" << std::endl;
}

// Important here,  define the template function and class.
template void foo<int>();
template class Foo<int>;
