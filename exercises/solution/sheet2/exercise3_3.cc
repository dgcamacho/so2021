#include <iostream>
#include <limits>
#include <iomanip>

int main()
{
  unsigned int n = 0;

  std::cout << "Type a positive integer number:\n";
  while (std::cin >> n) {
    unsigned int sum = 0;
    for (int i = 1; i <= n; ++i)
      sum += i*i;
    std::cout << "sum(" << n << ") = " << sum << "\n";
  }

}