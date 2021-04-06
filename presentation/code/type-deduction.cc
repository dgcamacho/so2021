#include <concepts>
#include <vector>

std::vector<double> foo() { return {1.0,2.0,3.0}; }

int main()
{
  std::integral       auto x{3+4};
  std::floating_point auto y{3.4};

  std::vector v = foo();
}