# Exercise sheet 2 - 2019/10/23


## Exercise 1 (Floating-point numbers)
1. What is the difference between `float` and `double`?
2. Assume the following program needs 1 second to run:
```c++
int main()
{
  double x = 1.0e8;
  while (x > 0)
  {
    --x;
  }
}
```
How long would it run if you replace `double` by `float`? Why?

3. Look at the following code example:
```c++
#include <cassert>
int main()
{
  using T = float; // a type-alias
  T a = 0.15 + 0.15;
  T b = 0.1 + 0.2;
  assert(a == b);
  assert(a >= b);
}
```
where `assert` is a macro resulting in an error if the argument evaluates to `false`. What is the effect of the
program? What happens if we change `float` to `double`? Why?

### Resources
- https://en.wikipedia.org/wiki/Floating-point_arithmetic
- https://en.wikipedia.org/wiki/IEEE_754


## Exercise 3 (Control structures)
Get familiar with control structures in C++, i.e. `if`, `else`, `for`, `do`, `while`, `switch`, `case`.
1. Rewrite the following `while`-loop by a `for`-loop:
```c++
int log10 = 0;
double num = 12345.0;
while (num >= 10.0) {
  num /= 10.0;
  ++log10;
}
```

2. What is the error in the following statements?

  i.
```c++
  for (int j = 0, j < 10, ++j)
    std::cout << j;
```
  ii.
```c++
int n, sum = 0;
do
{ std::cin >> n; sum += n; }
while (n > 0)
```
  iii.
```c++
int n = 2, m;
while (n < 10)
  m *= n, ++n;
```
  iv.
```c++
unsigned long n = 0;
int cnt = 1;
do
  n += cnt;
  cnt++;
while (n < 100);
```

3. Write a C++-program that calculates and prints the sum of the first $`n`$ positive integers, i.e.
```math
1^2 + 2^2 + 3^2 + 4^2 + ... + n^2
```
while a positive integer is read from the keyboard. Use the standard stream operator `std::cin >> ...` and
`std::cout << ...` from `<iostream>` for reading and writing.

### Resources
- [if-then-else](https://en.cppreference.com/w/cpp/language/if), [switch-case](https://en.cppreference.com/w/cpp/language/switch),
  [for-loop](https://en.cppreference.com/w/cpp/language/for), [while-loop](https://en.cppreference.com/w/cpp/language/while),
  [do-while-loop](https://en.cppreference.com/w/cpp/language/do)
- [std::cout](https://en.cppreference.com/w/cpp/io/cout), [std::cin](https://en.cppreference.com/w/cpp/io/cin)


## Exercise 4 (Kahan Summation Formula) :pencil2:
Calculate the sum $`\sum_{j=0}^{N-1} x_j`$ for a given set of values $`\{x_j\}`$ using the following algorithm:
```
S = x_0
C = 0
for j = 1,..., N-1 do
  Y = x_j - C
  T = S + Y
  C = (T - S) - Y
  S = T
```
What is the difference to a classical summation algorithm?

1. Create a `std::vector` with 100 `float`/`double` values: $`x_k := \bar{x}^k/(k!)`$ with $`\bar{x} = 7`$.
2. Sum up these values using the Kahan-algorithm and a simple summation, with internal value format `float`/`double`.
3. Compare the result of the summation of `float`s to `double`s and compare to the function `std::exp` from `<cmath>`.
4. Compile your program with
- `g++ -std=c++11 SOURCE.cc`
- `g++ -std=c++11 -O3 -ffast-math SOURCE.cc`
- `clang++ -std=c++11 SOURCE.cc`
- `clang++ -std=c++11 -O3 -ffast-math SOURCE.cc`

What is the difference, if any? Why is there a difference in the output?

5. Try again, but reverse the order of the entries of the vector, i.e.
```c++
#include <algorithm>
...
std::reverse(x.begin(), x.end());
```

6. Try again, but first randomly shuffle the entries of the vector, i.e.
```c++
#include <algorithm>
#include <cstdlib>
...
std::srand(12345);               // fixed initial seed
std::random_shuffle(x.begin(), x.end(), [](int n) { return std::rand() % n; });
```


**>> Submit solution until 2019/11/06 ... (10 Points)**

### Note
For a comparison of the computations, print the value with maximal precision to `std::cout`, i.e.
```c++
#include <iomanip>
#include <iostream>
...
std::cout << std::setprecision(std::numeric_limits<T>::max_digits10) << SUM << std::endl;
```
where `T` is a placeholder for the type that is used, and `SUM` for the value calculated.

### Material
- [material/sheet2/exercise4.cc](/exercises/material/sheet2/exercise4.cc)

### Resources
- [Kahan Summation](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
- [std::vector](https://en.cppreference.com/w/cpp/container/vector),
  [std::exp](http://en.cppreference.com/w/cpp/numeric/math/exp)
- [Optimization options](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html),
  [fast-math](http://stackoverflow.com/questions/7420665/what-does-gccs-ffast-math-actually-do)


## Exercise 5 (GotW-86: Slight typos)
See [GotW #86](http://www.gotw.ca/gotw/086.htm). Answer the following question without using a compiler.

What is the output of the following program on a standards-conforming C++ compiler?
```c++
#include <iostream>
#include <iomanip>
int main()
{
  int x = 1;
  for( int i = 0; i < 100; ++i );
  // What will the next line do? Increment???????????/
  ++x;
  std::cout << x << std::endl;
}
```