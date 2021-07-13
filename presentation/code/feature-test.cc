#include <iostream>
#include <version>
#if __has_include(<format>)
  #include <format>
#endif

int main()
{
  #if __cpp_lib_format >= 202106
    std::cout << std::format("{}\n", 42.0);
  #endif
}