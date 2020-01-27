#include <iostream>

#include "exercise2.2.hh"

int main()
{
  using namespace scprog;

  for (int i : range(10))
    std::cout << i << ' ';

  std::cout << std::endl;
}
