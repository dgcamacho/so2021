#include <memory>
#include <iostream>

std::shared_ptr<int> create_int_ptr(int value)
{
  return std::shared_ptr<int>( new int{value} );
}

int main()
{
  std::shared_ptr<int> i;
  {
    // create shared_ptr in place of "j" => count = 1
    std::shared_ptr<int> j = create_int_ptr(2);
    std::cout << "#0: count = " << j.use_count() << "\n";
    i = j; // => count = 2
    std::cout << "#1: count = " << j.use_count() << "\n";
  } // j is destroyed

  // => count = 1
  std::cout << "#2: count = " << i.use_count() << "\n";
  return 0;
}
