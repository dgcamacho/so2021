#include <type_traits>

// us a macro as shortcut
#define TEST_LITERAL(LITERAL,TYPE) \
  static_assert(std::is_same<decltype( LITERAL ), TYPE >::value, "TYPE is not the type of the literal!")

int main()
{
  TEST_LITERAL(2L, long);             // a
  TEST_LITERAL(1.23456f, float);      // b
  TEST_LITERAL(0302, int);            // c
  TEST_LITERAL('\101', char);         // d
  TEST_LITERAL(100UL, unsigned long); // e
  TEST_LITERAL(.1e-5, double);        // f
  TEST_LITERAL(0x10, int);            // g
  TEST_LITERAL(1.2345678, double);    // h
  TEST_LITERAL(0xFL, long);           // i
}