#include <vector>
#include "NumVector1.hh"

void vectorTest(std::vector<double>& v) {}

int main()
{
  NumVector v(3);
  v.resize(2);    // must be hidden, just like other methods of std::vector!
  vectorTest(v);  // this should also lead to a compiler error!
}
