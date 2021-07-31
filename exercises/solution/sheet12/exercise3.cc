#include <iostream>
#include "exercise3.hh"

int main()
{
  using namespace scprog;

  Sqr sqr_;
  Sqrt sqrt_;
  Exp exp_;

  Plus plus_;

  auto f1 = compose(plus_, sqr_, sqrt_); // sqr(x) + sqrt(x)

  std::cout << f1(2.0) << " ==? " << sqr_(2.0) + sqrt_(2.0) << '\n';

  auto f2 = compose(exp_, f1); // exp(sqr(x) + sqrt(x))

  std::cout << f2(2.0) << " ==? " << exp_(sqr_(2.0) + sqrt_(2.0)) << '\n';
}
