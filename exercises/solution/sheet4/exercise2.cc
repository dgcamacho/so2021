#include <iostream>

struct A0
{
  bool b;
  char c;
  int i;
  long l;
  double d;
  long double ld;
};

// due to alignment restrictions the mixed small-large packing results in the largest
// overall size
struct A1
{
  bool b;
  long double ld;
  char c;
  double d;
  int i;
  long l;
};

// force the compiler to packe the data as dense as possible
// Don't do that if you do not exactly know the consequences
struct __attribute__((packed)) A2
{
  bool b;
  char c;
  int i;
  long l;
  double d;
  long double ld;
};

int main()
{
  std::cout << "sizeof(A0) = " << sizeof(A0) << std::endl; // 48
  std::cout << "sizeof(A1) = " << sizeof(A1) << std::endl; // 64
  std::cout << "sizeof(A2) = " << sizeof(A2) << std::endl; // 38

  // show the alignment of the types
  std::cout << "Alignment of 'bool': " << alignof(bool) << std::endl;
  std::cout << "Alignment of 'char': " << alignof(char) << std::endl;
  std::cout << "Alignment of 'int': " << alignof(int) << std::endl;
  std::cout << "Alignment of 'long': " << alignof(long) << std::endl;
  std::cout << "Alignment of 'double': " << alignof(double) << std::endl;
  std::cout << "Alignment of 'long double': " << alignof(long double) << std::endl;

  std::cout << "Alignment of 'struct A0': " << alignof(A0) << std::endl;
  std::cout << "Alignment of 'struct A1': " << alignof(A1) << std::endl;
  std::cout << "Alignment of 'struct A2': " << alignof(A2) << std::endl;
}