# Exercise sheet 2 - 2019/10/23

## Exercise 1 (Literals)
What is the type of the following literals
```c++
(a) 2L       (d) 1.23456f    (g) 0302
(b) '\101'   (e) 100UL       (h) .1e-5
(c) 0x10     (f) 1.2345678   (i) 0xFL
```

### Hints
To check the type, you can use `delctype` and `static_assert`:
```c++
#include <type_traits>
// ...
static_assert(std::is_same<decltype(LITERAL), TYPE>::value, "Wrong type");
```
(You have to compile this code with `-std=c++11` flag)

### Resources
- [cppreference:literals](https://en.cppreference.com/w/cpp/language/expressions#Literals)


## Exercise 2 (Variable declaration)
What is the error in the following variable definitions?
```c++
(a) int n, int i;              (c) double side length;   (e) Short min(0);
(b) int m; double result{.5}   (d) char c['a'];          (f) double slow_down = "1.E-4";
```


## Exercise 3 (Operators)
What is the meaning of the following arithmetic expressions? To illustrate which sub-expression is evaluated first, add brackets!
```c++
(a) x / y * z             (g) z-y-x?x+y+z:x-y-z
(b) x * y++ / -z          (h) z<<x>>y
(c) x^2 + y^2             (i) z>>x<<y
(d) ++x * x++             (j) x||y||z
(e) *&x*y&&z              (k) ++x*=y++
(f) x+++x                 (l) -~x^x
```

What is the value of the expressions with the following value of the variables?
```c++
int x = 3;
int y = 2;
int z = 5;
```

What is the value of the variables `x`, `y`, and `z` after evaluating the expression?

First, try to evaluate by hand, then check your results by implementing the expressions.

### Resources
- [cppreference:expressions](https://en.cppreference.com/w/cpp/language/expressions#Operators),
  [cppreference:operator_precedence](https://en.cppreference.com/w/cpp/language/operator_precedence)
- [Wikibook:Operatoren](https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Operatoren)



## Exercise 4 (Recursion) :pencil2:
To calculate the square-root of a real number $`a > 0`$ you can use the Newton-method, by getting the root (zero-point) of the function $`f(x)`$,
defined by:
```math
  f(x) := x^2 - a,
```
i.e., $`f(x) = 0 \Leftrightarrow |x|=\sqrt{a}`$.

The Newton-method introduces an iteration $`x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}`$ starting from some initial value $`x_0`$.

This calculation rule can be interpreted as a recursion in the sense:
```math
  T: x\mapsto x - f(x)/f'(x),\quad
  x_n = T(x_{n-1}),\;
  x_0 = \text{\texttt{x0}}
```
or it can be interpreted as in iteration starting from $`x_0`$ and iteratively calculating the next value.

Implement the functions
```c++
  double sqrt_recu(double a, double x0, int N); // returns x_N
  double sqrt_iter(double a, double x0, int N); // returns x_N
```
by realizing this code _recursively_ and _iteratively_. Use `x0` as recursion break condition or initial value $`x_0`$ and return the value `x_N`
as your approximation of the square-root of `a`.

Try your code with a recursion depth of $`N=5, 10, 100`$ for $`a=10`$ and initial value $`x_0=3`$.

How to check the error you have made? How to choose the initial value `x0` and the iteration count `N`? How would you design your implementation
`double sqrt(double a)` of a square-root function and which version of the implementation above would you choose?

**>> Submit solution until 2019/11/13 ... (10 Points)**

### Notes and additional questions:
- You can use the `std::sin` function from `<cmath>` as a comparison.
- Measure the time of your implementation and compare it against the time of the `std::sin` implementation. Therefore, either use the `Timer`
  in the lecture material folder, or user the Google micro benchmarking suite: https://github.com/google/benchmark
- What happens if your change your type from `double` to `float`. Do you see any difference in accuracy and performance?

## Exercise 5 (GotW-78: Operators, Operators Everywhere)
See [GotW #78](http://www.gotw.ca/gotw/078.htm).

1. What is the greatest number of plus signs (`+`) that can appear consecutively, without whitespace, in a
valid C++-program?

*Note:* Of course, plus signs in comments, preprocessor directives and macros, and literals don't count.
That would be too easy.

2. **Guru Question**: Similarly, what is the greatest number of each the following characters that can appear
consecutively, without whitespace, outside comments in a valid C++-program?
  - `&`,
  - `<`,
  - `|`.

For example, the code `if( a && b )` trivially demonstrates two consecutive `&` characters in a
valid C++-program.
