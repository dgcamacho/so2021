#include <tuple>
auto min_max (int const n1, int const n2)
{
  if (n1 < n2)
    return std::tuple{n1,n2};
  else
    return std::tuple{n2,n1};
}

int main()
{
  auto [m1,m2] = min_max(42, 17);   // "Structured binding"
}