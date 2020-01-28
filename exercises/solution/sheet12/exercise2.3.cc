#include <iostream>
#include <ranges>

// requires c++20, compile with -std=c++2a or -std=c++20

int main()
{
  for (int i : std::view::iota{0,10})
    std::cout << i << ' ';

  std::cout << std::endl;
}
