#include <iostream>
// Function template.
template<typename T>
void foo();

// Class template.
template<typename T>
class Foo {
public:
  void f();
  void g();
};
template<typename T>
inline
void Foo<T>::f()
{
  std::cout << "Inline function f()" << std::endl;
}
