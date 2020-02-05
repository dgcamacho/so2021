#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

// an output function for vectors, by overloading the operator<<
template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> const& vec)
{
  std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(out, " "));
  return out;
}

int main()
{
  // create an empty vector
  std::vector<int> vec;

  // fill it with 10 random values in the range [0,10), using push_back function
  std::generate_n(std::back_inserter(vec), 10, [](){ return std::rand() % 10; });
  std::cout << "vector    = [" << vec << "]\n";

  // exercise 13.2.a
  {
    // variant 1, using std::bind and std::greater
    using namespace std::placeholders; // -> _1
    std::vector<int> result;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), std::bind(std::greater<int>{}, _1, 5));
    std::cout << "result(a) = [" << result << "]\n";

    // variant 2, using lambda and ostream_iterator
    std::cout << "result(a')= [";
    std::copy_if(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "), [](int x) { return x > 5; });
    std::cout << "]\n";
  }

  // exercise 13.2.b
  {
    // a variant using std::for_each
    std::cout << "result(b) = [";
    std::for_each(vec.begin(), vec.end(), [](int x) { if (x != 5) std::cout << x << ' '; });
    std::cout << "]\n";
  }

  // exercise 13.2.c
  {
    std::vector<int> result;
    std::transform(vec.begin(), vec.end(), std::back_inserter(result), [](int x) { return 2*x; });
    std::cout << "result(c) = [" << result << "]\n";

    // variant, scaling in-place
    std::for_each(vec.begin(), vec.end(), [](int& x) { x *= 2; });
    std::cout << "result(c')= [" << vec << "]\n";
  }
}
