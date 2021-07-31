int foo ( const int& ) {};
int bar ( int& ) {};

int main()
{
  int i = 0;
  int& j = i;
  static const int f = i;
  int* const p = 0;
  p = &i;                 // cannot change pointer address, since pointer is const
  *p = f;
  const int& l = j;
  const int& k = f;
  foo ( j );
  bar ( l );              // binding reference of type 'int&' to 'const int' discards qualifiers
  foo ( k );
}

// see also the CppCon 2019 presentation by Dan Saks: "Back to Basics: Const as a Promise"
// https://www.youtube.com/watch?v=NZtr93iL3R0