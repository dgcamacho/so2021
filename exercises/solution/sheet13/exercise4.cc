#include <algorithm>
#include <iostream>

#include "exercise4.hh"

int main()
{
  using namespace scprog;

  vector<int> vec(6, 1);
  int i = 2;
  for (int& v : vec) {
    v = ++i;
    std::cout << v << '\n';
  }

  std::sort(std::begin(vec), std::end(vec));

  return 0;
}
