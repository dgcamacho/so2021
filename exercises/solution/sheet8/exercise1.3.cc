#include <iostream>

int allocate(int n)
{
  if (n == 0)
    return 0;

  int* array = new int[n];
  int m = allocate(n-1);

  return array[n] + m; // memory access out of range
}

int main()
{
  int m = allocate(10);
  std::cout << "m = " << m << std::endl;
}

/*
valgrind:

==34754== Invalid read of size 4
==34754==    at 0x108A3C: allocate(int) (exercise1.3.cc:11)
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
[...]
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
==34754==    by 0x108A57: main (exercise1.3.cc:16)
==34754==  Address 0x5b7dfd4 is 0 bytes after a block of size 4 alloc'd
==34754==    at 0x4C3089F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==34754==    by 0x108A30: allocate(int) (exercise1.3.cc:8)
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
[...]
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
==34754==    by 0x108A3B: allocate(int) (exercise1.3.cc:9)
==34754==    by 0x108A57: main (exercise1.3.cc:16)
*/
