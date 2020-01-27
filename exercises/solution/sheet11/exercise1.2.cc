#include <cassert>
#include <type_traits>

namespace scprog
{

  template <class T1, class T2>
  T1 min(T1 a, T2 b)
  {
    return a < b ? a : b; // PROBLEM: result-type of ?: is "common_type" of T1, T2, but return type of min() is fixed to T1.
  }

} // end namespace scprog

int main()
{
  int a = -6;
  unsigned b = 5;

  auto erg = scprog::min(a, b);

  assert( erg == -6 );

  // PROBLEM: common_type<int, unsigned int> is unsigned int
}
