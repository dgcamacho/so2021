#include <iostream>

void foo(int a) { std::cout << "(a)\n"; };           // (a)
void foo(int& a) { std::cout << "(b)\n"; };          // (b)
void foo(int* a) { std::cout << "(c)\n"; };          // (c)
void foo(double a) { std::cout << "(d)\n"; };        // (d)
void bar(int a, int b) { std::cout << "(e)\n"; };    // (e)
void bar(float a, float b) { std::cout << "(f)\n"; };// (f)

int main() {
  int a = 1;
  float b = 1.0f;
  double c = 1.0;

//   foo(a);         // (1) ambiguous call to (a) or (b)
  foo(&a);        // (2) -> (c)
  foo(1.0);       // (3) -> (d)
  foo(b);         // (4) -> (d)
//   foo(&b);        // (5) no condidate found
  foo(c);         // (6) -> (d)

  bar(a, a);      // (7) -> (e)
  bar(1.0, a);    // (8) -> (e)
//   bar(&a, a);     // (9) no candidate found
  bar(b, b);      // (10) -> (f)
//   bar(c, c);      // (11) ambiguous call to (e) or (f)
  bar(b, c);      // (12) -> (f)
//   bar(a, b);      // (13) ambiguous call to (e) or (f)
}
