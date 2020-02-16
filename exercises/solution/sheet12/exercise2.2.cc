#include <iostream>

#include "exercise2.2.hh"

int main()
{
  using namespace scprog;

  // we can use range-for loops to iterator over our integer_range
  for (int i : range(10))
    std::cout << i << ' ';

  std::cout << std::endl;
}
