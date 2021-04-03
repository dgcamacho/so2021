#include <concepts>
#include <vector>

std::vector<double> foo() { return {1.0,2.0,3.0}; }

int main()
{
  std::vector v = foo();
}