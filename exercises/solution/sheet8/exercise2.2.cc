#include <memory>
std::unique_ptr<int> create_int_ptr(int value)
{
  return std::unique_ptr<int>( new int{value} );
}

int main()
{
  std::unique_ptr<int> i;
  {
    std::unique_ptr<int> j = create_int_ptr(2);
    i = j; // ERROR: unique_ptr can not be copied!
  }
  // #1
  return 0;
}
