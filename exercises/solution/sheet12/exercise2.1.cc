#include <iostream>
#include "exercise2.1.hh"

int main()
{
  using namespace scprog;

  // NOTE: we have to spell out the begin and end iterator and thus have to use classical loops
  for (auto it = range_iterator(0); it != range_iterator(10); ++it)
    std::cout << *it << ' ';

  std::cout << std::endl;
}
