template<typename T> struct A { void foo(); };
template<typename T> void bar1();
template<typename T> void bar2();
void bar3();

// include template implementations at the end of the header file
#include "ex11.hh"
