#include <iostream>

template<typename T>
void A<T>::foo() { std::cout << "foo-T\n"; }

// move template implementation of bar1 to header implementation file
template<typename T> void bar1() { std::cout << "bar1\n"; }
