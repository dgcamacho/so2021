#include <cassert>
#include <vector>

namespace scprog
{
  template <class InputIt1, class InputIt2>
  bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
  {
    for (; first1 != last1; ++first1, ++first2) {
      if (!(*first1 == *first2)) {
        return false;
      }
    }
    return true;
  }

} // end namespace scprog

int main()
{
  std::vector<int> v1{1,2,3,4,5,6,7};
  std::vector<int> v2{2,3,4,5,6,7,8};

  assert(!scprog::equal(v1.begin(), v1.end(), v2.begin()));
  assert( scprog::equal(v1.begin(), v1.end(), v1.begin()));
}
