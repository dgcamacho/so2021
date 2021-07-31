#include <cassert>
#include <tuple> // -> std::pair

namespace scprog
{
  template <class T>
  std::pair<T,T> minmax(T const& a, T const& b)
  {
    return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
  }

#define MINMAX(a, b) ( (a) < (b) ? std::make_pair((a), (b)) : std::make_pair((b), (a)) )

} // end namespace scprog

int main()
{
  int a = 5, b = 7;
  int min_ab = std::min(a,b), max_ab = std::max(a,b);

  int m0, m1;
  std::tie(m0, m1) = scprog::minmax(a, b); // assign result to two variables

#if __cplusplus >= 201703L
  // requires c++17
  auto [m2, m3] = scprog::minmax(a, b); // assign result to two new variables with automatic type
#endif

  auto ab = scprog::minmax(a, b);
  assert( min_ab == ab.first && max_ab == ab.second );

  auto AB = MINMAX(a, b);
  assert( min_ab == AB.first && max_ab == AB.second );

  // some comments:
  //   - the macro does not know anything about namespaces!
  //   - you have to use many extra brackets to have the correct replacement behaviour


  // If you call the function with arguments of different type it will give you a compiler error:
#if 0
  int c = 5;
  double d = 7.0;

  auto cd = scprog::minmax(c, d);
  auto CD = MINMAX(c, d);
#endif
}
