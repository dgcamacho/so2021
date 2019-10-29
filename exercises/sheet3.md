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


## Exercise 2
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
What is the value of the variables `x`, `y`, and `z` after evaluating the expression?
```c++
int x = 3;
int y = 2;
int z = 5;
```

First, try to evaluate by hand, then check your results by implementing the expressions.

### Material
[material/all/exercise2.cc](/exercises/material/all/exercise2.cc)

### Resources
- [cppreference:expressions](https://en.cppreference.com/w/cpp/language/expressions#Operators),
  [cppreference:operator_precedence](https://en.cppreference.com/w/cpp/language/operator_precedence)
- [Wikibook:Operatoren](https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Operatoren)
