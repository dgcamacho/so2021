#include <iostream>

int allocate(int n)
{
  if (n == 0)
    return 0;

  int* array = new int[n];
  int m = allocate(n-1);

  return array[n-1] + m;  // array values are not initialized
}

int main()
{
  int m = allocate(10);
  std::cout << "m = " << m << std::endl;
}

/*
valgrind:

==34640== Conditional jump or move depends on uninitialized value(s)
==34640==    at 0x4F43C0A: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.25)
==34640==    by 0x4F501A4: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.25)
==34640==    by 0x108A83: main (exercise1.2.cc:17)

valgrind --track-origins=yes:

==34711==  Uninitialized value was created by a heap allocation
==34711==    at 0x4C3089F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==34711==    by 0x108A33: allocate(int) (exercise1.2.cc:8)
==34711==    by 0x108A3E: allocate(int) (exercise1.2.cc:9)
[...]
==34711==    by 0x108A3E: allocate(int) (exercise1.2.cc:9)
==34711==    by 0x108A3E: allocate(int) (exercise1.2.cc:9)
==34711==    by 0x108A5B: main (exercise1.2.cc:16)
*/
