#include <iostream>
#include "NumVector1.hh"

int main()
{
  NumVector v(3);
  v[0] = 1; v[1] = 3, v[2] = 4;
  NumVector const& w = v;
  std::cout << "norm is " << w.norm() << std::endl;
  std::cout << "vector is [" << w[0] << ", " << w[1] << ", " <<w [2] << "]" << std::endl;
}
