#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

#include "version1.hh"

int main()
{
  using namespace scprog;

  // placeholder for first and second argument
  Arg<0> _0;
  Arg<1> _1;

  // create a functor by composition, using generators
  auto f1 = sqr(_0) + sqrt(_0); // sqr(x) + sqrt(x)
  std::cout << f1(2.0) << " ==? " << Sqr{}(2.0) + Sqrt{}(2.0) << '\n';

  auto f2 = exp(f1); // exp(sqr(x) + sqrt(x))
  std::cout << f2(2.0) << " ==? " << Exp{}(Sqr{}(2.0) + Sqrt{}(2.0)) << '\n';

  // generate some data, to be used in std algorithms
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
  std::vector<int> w{10,1,2,3,4,5,6,7,8,9};

  // the functor _0 + _1 is equal to compose(Plus{}, Arg<0>{}, Arg<1>{})
  std::cout << "sum = " << std::accumulate(v.begin(), v.end(), 0, _0 + _1) << std::endl;

  // the functor _0 + sqr(_1) is equal to compose(Plus{}, Arg<0>{}, compose(Sqr{}, Arg<1>{}))
  std::cout << "norm2 = " << std::accumulate(v.begin(), v.end(), 0, _0 + sqr(_1)) << std::endl;

  // define the functors plus and multiplies inline, like lambda expressions
  std::cout << "dot = " << std::inner_product(v.begin(), v.end(), w.begin(), 0, _0 + _1, _0 * _1) << std::endl;
}
