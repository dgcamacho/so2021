
#include <cassert>  // for assert(...)
#include <vector>

void f1 (std::vector<int> arg) {};      // pass-by-value (copy)
void f2 (std::vector<int>& arg) {};     // pass-by-reference

int main()
{
  int n = 100;
  std::vector<double> vec1(n, 0.0);     // construct with size n and default value 0.0
  std::vector vec2{1.0, 2.0, 3.0};      // deduce type and size from initializer list [c++17]
  auto vec3 = vec2;                     // create copy of array
  assert(vec3.size() == 3);             // access number of elements (dynamic information)
}