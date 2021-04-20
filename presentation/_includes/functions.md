---
class: center, middle
# Functions
---

# Functions
## Function Declaration/Definition
The declaration of a function in C++ follows

```c++
<return_type> <function_name> (<argument_list>...);           // C-style
// or
auto <function_name> (<argument_list>...) -> <return_type>;   // Since [C++11]
```

- When a function does not return a result, then the return type is `void`.
- To return a value from a function, C++ provides the keyword `return`.

```c++
double square (double const x)
{
  return x*x;
}
// or
auto square2 (double const x) -> double
{
  return x*x;
}
```

---

# Functions
## Function Call
A function is called by

```c++
<function_ name>(<argument1>, <argument2>...);
```

### Example:

```c++
double y = square(4.3);

double y2 = square(square(4.3));
```

### Argument passing
Passing an argument to a function is like defining a variable.

```c++
double y = square(4); // passing an int means: conversion
// double const x = 4; return x*x;
```

---

# Functions
## Function Declaration/Definition
Note, one cannot define a function in the body of another function:

```c++
double cube (double const x)
{
  // ERROR
  double square (double const y) { return y*y; }

  return square(x) * x;
}
```

--

**Outlook:** Lambda expressions. Instead of a function, define a "function-object":

```c++
double cube (double const x)
{
  // OK
  auto square = [](double const y) { return y*y; };

  return square(x) * x;
}
```

---

# Functions
## Function Examples
Iterative computation of factorial

```c++
int factorial (int const n)
{
  int  f = 1;

  for (int i = 1; i <= n; ++i)
    f *= i;

  return f;
}
```

> .h3[Coding Principle:] Make all function arguments `const`,
> except when changing value (see later).

---

# Functions
## Function Examples (Cont.)
Power function with positive integer exponents:

```c++
double power (double const x, unsigned int const n)
{
  switch (n) {
    case 0 : return 1;
    case 1 : return x;
    case 2 : return square(x);
    default: {
      double f = x;
      for (int i = 0; i < n; ++i)  f *= x;
      return f;
    }
  }
}
```

> .h3[Coding Principle:] Make sure, that a function has a call to `return` in every execution path.

---

# Functions
## Call by Value
In previous examples, only the *value* of a variable (or
constant) is used as the argument of a function, i.e., changing the value
of the argument does not change the value of the original variable:

```c++
int f (int m)   // non const argument!
{
  m = 4;        // explicitly changing the value of argument m
  return m;
}

int  m = 5;
int  n = f(m);  // m is unchanged by f
int n2 = f(5);  // OK: pass value 5 directly
```

This is known as **call-by-value**.

> .h3[Remark:] It is nevertheless advised to use `const` arguments.

---

# Functions
## Call by Reference
If the original variable should be changed in a
function, a pointer or reference to this variable has to be supplied:

```c++
int f (int& m)  // reference argument
{
  m = 4;        // changing m, changes the variable pointed to
  return m;
}

int  m = 5;
int  n = f(m);  // m is changed by f to 4
assert(m == 4); // Simple error checking

int n2 = f(5);  // ERROR! cannot bind reference to value
```

This is known as **call-by-reference**.

---

# Functions
## Call by Reference
The same function with pointers:

```c++
int f (int* m)    // reference argument
{
  *m = 4;         // changing m, changes the variable pointed to
  return *m;
}

int  m = 5;
int  n = f(&m);   // m is changed by f to 4
```

---

# Functions
## Call by Reference
When using references to *constant* variables, the value can not be changed:

```c++
int f (int const& m)
{
  m = 4;          // ERROR: m is constant
  return m;
}

// Note:
int n2 = f(5);    // OK: const& can 'bind' to rvalues (temporaries)
```

Therefore, this is (almost) equivalent to call-by-value and needed for
advanced datatypes (see later).

For basic datatypes, using call-by-reference, even with `const`, is usually
not advisable, except when changing the original variable.

---

# Functions
## Multiple return values
Returning multiple values could be done by multiple call-by-reference arguments, or by
returning a `std::tuple`

```c++
auto min_max (int const n1, int const n2)
{
  if (n1 < n2)
    return std::tuple{n1,n2};
  else
    return std::tuple{n2,n1};
}
// ...
auto [m1,m2] = min_max(42, 17);   // "Structured binding"
```

> .h3[Remark:] If the return type can be uniquely determined from the *return expressions*, you can
> use the placeholder type `auto` as return type.

---

# Functions
## Recursion
Calling the same function from inside the function body is called a *recursive* function call:

```c++
unsigned int factorial (unsigned int const n)
{
  if (n <= 1)   // recursion break condition
    return 1;
  else
    return n * factorial(n-1);
}
// or
unsigned int factorial2 (unsigned int const n)
{
  return n <= 1 ? 1 : n * factorial2(n-1);  // using the ternary operator a ? b : c
}
```

> .h3[Remark:] The recursion depth, i.e., the number of recursive calls, is limited by
> the size of the *stack*, a special part of the memory.

---

# Functions
## Function Naming
A function in C++ is identified by it's name *and* the number and type of it's arguments, i.e., it's
*signature*. Hence, the same name can be used for different argument types:

```c++
int     square (int const    x) { return x*x; }
float   square (float const  x) { return x*x; }
double  square (double const x) { return x*x; }
```

> .h3[Coding Principle:] Functions implementing the same algorithm on different types should be
> named equal.

This can significantly reduce the number of different functions you'll
have to remember und simplifies programming.

---

# Functions
## Function Naming
If only the return type is different between functions, they are identified as equal:

```c++
float  f (int x) { ... }
double f (int x) { ... }  // ERROR: "f" already defined
```

If the function parameter differ only in first-level (outer) constness specifiers, they are identified
as equal:

```c++
float  f (int const x) { ... }
double f (int x) { ... }  // ERROR: "f" already defined
```


> .h3[C++ Standard (n4835) §6.3 (1)] *One-definition rule:* No translation unit shall contain more
> than one definition of any variable, function, class type, enumeration type, or template.

---

# Functions
## Default Arguments
Arguments for a function can have *default* arguments, which then can be omitted at calling the function:

```c++
void f (int n, int m = 10) { ... }

// ...

{
  f(5);    // equivalent to f(5, 10)
  f(5, 8);
}
```

Only limitation: after the first default value, **all** arguments
must have default values:

```c++
void g1 (int n, int m = 10, int k);      // ERROR
void g2 (int n, int m = 10, int k = 20); // Ok
```

---

# Functions
## Default Arguments and Function Names
Two functions with the same name must differ by their arguments *without* default values:

```c++
void f (int n1, int n2, int n3 = 1) { ... }
void f (int n1, int n2)             { ... }

// ...

{
  f(1, 2, 3);   // Ok: call to f(int, int, int)
  f(1, 2);      // Error: call of "f(int, int)" is ambiguous
}
```

---

# Functions
## Function Name Scope
A function can only be called, if it was previously implemented:

```c++
void f (int x) {
  g(x);           // ERROR: function "g" unknown
}

void g (int y) {
  f(y);           // Ok: function "f" already defined
}
```

or *declared*, i.e., definition of function without function body:

```c++
void g (int y);   // forward declaration

void f (int x) {
  g();            // Ok: "g" is declared
}
```

This is known as **forward declaration**.

---

# Functions
## Function Name Scope
Of course, every function with a forward declaration
has to be implemented eventually:

```c++
void g (int y);   // forward declaration
void f (int x) {
  g();
}
// ...
void g (int y) {  // implementation
{
  f(y);           // Note: infinite recursion
}
```

---

# Functions
## Inline Functions
Calling a function involves some overhead. For small
functions, this overhead might exceed the actual computation:

```c++
double  square (double const x) { return x*x; }
// ...
{
  double  x = /*...*/;
  double  f = 0;

  for (int i = 0; i < 100; ++i)
    f += square(x);
}
```

Here, simply calling `square` takes a significant part of the runtime.
Compilers can automatically replace the function call by the function body:

```c++
  for (int i = 0; i < 100; ++i)
    f += x * x;
```

---

# Functions
## Inline Functions
An *inline*-function is a function qualified with the keyword `inline`. Consequences:
- It is allowed to have multiple definitions of the same (inline)-function in the same translation unit,
  as long as all definitions are identical. (Otherwise the **behavior is undefined**)
- The definition must be visible in all translation units

> .h3[Remark:] The keyword `inline` does not necessarily influence the compiler in its decision whether to
> inline a function or not.

---

# Functions
## Functions and `static` Variables
In contrast to standard variables in a function, which are specific to a
specific function call, for `static` variables in all function calls the *same* instance, i.e., memory
position, is referenced:

```c++
double f (double const x, long& cnt) {
  static long counter = 0;                // allocated and initialized
                                          // once per program
  cnt = ++counter;
  return 2.0*x*x - x;
}

int main () {
  long  cnt = 0;
  for (double x = -10; x <= 10.0; x += 0.1)
    f(x, cnt);

  std::cout << cnt << std::endl;          // print number of func. calls
}
```
