
#include <array>

void f1 (std::array<int,3> arg) {};      // pass-by-value (copy)
void f2 (std::array<int,3>& arg) {};     // pass-by-reference

int main()
{
  std::array<int, 3> vec1 = {1, 2, 3};  // explicit type and size
  std::array vec2{1.0, 2.0, 3.0};       // deduce type and size from initializer list [c++17]
  auto vec3 = vec2;                     // create copy of array
  static_assert(vec3.size() == 3);      // access number of elements (static information)
}