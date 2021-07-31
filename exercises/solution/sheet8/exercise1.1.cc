#include <iostream>

int allocate(int n)
{
  if (n > 0) {
    int* array = new int[n];
    allocate(n-1);
  }
  return 0;
}

int main()
{
  allocate(10);
}

/**
valgrind:

==34542== HEAP SUMMARY:
==34542==     in use at exit: 220 bytes in 10 blocks
==34542==   total heap usage: 11 allocs, 1 frees, 72,924 bytes allocated
==34542==
==34542== LEAK SUMMARY:
==34542==    definitely lost: 220 bytes in 10 blocks

valgrind --leak-check=full:

==34608== 4 bytes in 1 blocks are definitely lost in loss record 1 of 10
==34608==    at 0x4C3089F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==34608==    by 0x108869: allocate(int) (exercise1.1.cc:6)
==34608==    by 0x108871: allocate(int) (exercise1.1.cc:7)
[...]
==34608==    by 0x108871: allocate(int) (exercise1.1.cc:7)
==34608==    by 0x108871: allocate(int) (exercise1.1.cc:7)
==34608==    by 0x108891: main (exercise1.1.cc:14)
*/
