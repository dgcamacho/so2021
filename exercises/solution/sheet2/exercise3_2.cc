#include <iostream>

int main()
{
  // use local scopes (blocks) to overcome "redeclaration" problem.

  { // i
    for (int j = 0; j < 10; ++j) // semicolon instead of comma
      std::cout << j;
  }

  { // ii
    int n, sum = 0;
    do
    { std::cin >> n;  sum += n; }
    while (n > 0);              // semicolon at end of while statement
  }

  { // iii
    int n = 2, m = 0;           // initialization of m
    while (n < 10)
      m *= n, ++n;              // ok, means: "(m *= n), (++n)". statement returns result of "++n"
  }

  { // iv
    unsigned long n = 0;
    int cnt = 1;
    do {                        // curly braces missing
      n += cnt;
      cnt++;
    } while (n < 100);
  }
}