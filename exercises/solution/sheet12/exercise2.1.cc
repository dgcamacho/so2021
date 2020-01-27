#include <iostream>
#include "exercise2.hh"

int main()
{
  using namespace scprog;

  for (auto it = range_iterator(0); it != range_iterator(10); ++it)
    std::cout << *it << ' ';

  std::cout << std::endl;
}
