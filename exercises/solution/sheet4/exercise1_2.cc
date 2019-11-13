#include <iostream>

// Helper function to inspect the address of some passed variable
template <class T>
void print_addr_of(T&& var)
{
  std::cout << std::hex << static_cast<const void*>(&var) << std::endl;
}


void f(char) {}
void g(char& c) { print_addr_of(c); }
void h(char const& c) { print_addr_of(c); }

int main()
{
  char c = 'c';
  unsigned char uc = 'u';
  signed char sc = 's';

  // print the address of the original variables
  std::cout << "&c = "; print_addr_of(c);
  std::cout << "&uc = "; print_addr_of(uc);
  std::cout << "&sc = "; print_addr_of(sc);

  f('a');
  f(49);
  f(3300);  // warning: overflow in implicit constant conversion
  f(c);
  f(uc);
  f(sc);

  g(c);
#if 0
  g('a');   // error: cannot bind non-const lvalue reference of type 'char&' to an rvalue of type 'char'
  g(49);    // error: cannot bind non-const lvalue reference of type 'char&' to an rvalue of type 'char'
  g(3300);  // error: cannot bind non-const lvalue reference of type 'char&' to an rvalue of type 'char', warning: overflow in implicit constant conversion
  g(uc);    // error: cannot bind non-const lvalue reference of type 'char&' to an rvalue of type 'char'
  g(sc);    // error: cannot bind non-const lvalue reference of type 'char&' to an rvalue of type 'char'
#endif

  /**
   * clang produces a different error message: for the call g(49)
   *
   * error: no matching function for call to 'g'
   * note: candidate function not viable: no known conversion from 'int' to 'char &' for 1st argument
   **/


  h('a');   // temporary variable created
  h(49);    // temporary variable created
  h(3300);  // temporary variable created, warning: overflow in implicit constant conversion
  h(c);
  h(uc);    // temporary variable created
  h(sc);    // temporary variable created

  /**
   * Temporary variables are created whenever data is passed to a T const& variable and
   *  - the type is different from T, or
   *  - it is an pure rvalue and thus does not yet have an address
   **/
}