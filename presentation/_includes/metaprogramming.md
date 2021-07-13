---
class: center, middle
# Metaprogramming
---

# Metaprogramming
## The Compiler can Compute

In 1994 the Developer *Erwin Unruh* from Siemens-Nixdorf presented his prime-number program to
the C++ standard committee - probably the most famous C++ program that **does not compile**.

The **error-messages** of this program contain the result of the computa-
tion: the first 30 prime numbers. This side-effect of the compiling process has clearly shown
that the compile can do computing:
```bash
  error: no suitable constructor exists to convert from "int" to "D<17>"
  error: no suitable constructor exists to convert from "int" to "D<13>"
  error: no suitable constructor exists to convert from "int" to "D<11>"
  error: no suitable constructor exists to convert from "int" to "D<7>"
  error: no suitable constructor exists to convert from "int" to "D<5>"
  error: no suitable constructor exists to convert from "int" to "D<3>"
  error: no suitable constructor exists to convert from "int" to "D<2>"
```

see https://godbolt.org/z/sPGM966s6

---

# Metaprogramming
## Overview

- Techniques to transform, inspect, generate data-types
- Represent numbers as types
- Perform static "computation" (i.e., computation at compile time)

## Template Metaprogramming

1. Templates that calculate values (metafunctions)
2. Templates that define or transform types (type-traits)

---

# Metaprogramming
## General Principles and Techniques
- Properties associated to class (template) types are "compile time properties"
- Static integral constants mus have a value when a class template is instantiated
- Associated types must define a data type when the class template is instantiated

## Constexpr
Keyword `constexpr` specifies that the value of a variable or function can appear in constant expressions,
i.e., an expression that can be evaluated at compile time.

---

# Metaprogramming
## Represent values in types

```c++
template <class T, T v>
struct integral_constant
{
  using value_type = T;
  static constexpr value_type value = v;
};
```

The associated type `value_type` and static constant `value` are available once the template gets instantiated:

```c++
// access the value
static_assert( integral_constant<int, 42>::value == 42 );

// extract the type
integral_constant<int, 42>::value_type var = 42;
```

---

# Metaprogramming
## Metafunctions

- Classical functions are invoked by function parameters and return their result by `return` statement
- Metafunctions get their arguments in form of template parameters and return their result in forma of
  a static constant or a typedef (type alias)

### Initial Example: identity function
```c++
template <class X>
struct identity_value
{
  using value_type = typename X::value_type;
  static constexpr value_type value = X::value;
};

using A = integral_constant<int, 42>;
using B = identity_value<A>;

static_assert(A::value == B::value);
```

---

# Metaprogramming
## Direct calculations with template parameters
- `integral_constant` is the analogue of a data type to store a value
- type alias `using A = integral_constant<...>` is analogue of variable definition
- Instead of using `integral_constants` as template parameters, also directly non-type template parameter can be passed

Example with direct template parameter values
```c++
template <int a, int b>
struct plus
{
  static constexpr int value = a + b;
};

static_assert(plus<13, 29>::value == 42);
```

---

# Metaprogramming
## Direct calculations with template parameters
- `integral_constant` is the analogue of a data type to store a value
- type alias `using A = integral_constant<...>` is analogue of variable definition
- Instead of using `integral_constants` as template parameters, also directly non-type template parameter can be passed

Example with `integral_constant`

```c++
template <class A, class B>
struct plus
{
  static constexpr auto value = A::value + B::value;
};
using A = integral_constant<int,13>;
using B = integral_constant<int,29>;
static_assert(plus<A, B>::value == 42);
```

---

# Metaprogramming
## Recursive programming

Template metaprogramming typically works with recursion, since:
- type of a variable or type alias cannot be changed once it is set
- Value of a static constant cannot be changed (since it is constant)

### Example: Factorial Computation

\[
  \operatorname{factorial}(n) := \left\{\begin{array}{ll} 1 & \text{if }n = 0 \\ n \cdot \operatorname{factorial}(n-1) & \text{otherwise} \end{array}\right.
\]

In a classical function, we would write

.pure-g[.pure-u-1-2[.padding-5[
```c++
int factorial (int const n) {
  return n <= 0 ? 1 : n * factorial(n - 1);
}
```
]].pure-u-1-2[.padding-5[
```c++
int main() {
  int x = factorial(3); // = 3*2*1 = 6
  int y = factorial(0);
}
```
]]]

---

# Metaprogramming
```asm
  _Z3factoriali:
  // ...
      movl    %edi, -4(%rbp)    // n := m
      cmpl    $0, -4(%rbp)
      je  .L2                   // n == 0 ? jump to .L2 : continue
      movl    -4(%rbp), %eax    // \
      subl    $1, %eax          //  } m := n-1
      movl    %eax, %edi        // /
      call    _Z3factoriali     // factorial(m)
      imull   -4(%rbp), %eax    // n * factorial(m)
      jmp     .L3
  .L2:
      movl    $1, %eax          // return_value = 1
  .L3:
      leave                     // return
  // ...
  main:
  //...
      movl    $3, %edi          // m := 3
      call    _Z3factoriali     // factorial(m)
  // ...
```

---

# Metaprogramming
## Recursive programming
### Example: Factorial Computation
Now, the same program implemented using templates, static constants, recursive instantiation
and template specialization for the break condition

```c++
template <int N>
struct factorial_meta { // recursion
  static constexpr int value = N * factorial_meta<N-1>::value;
};
template <>
struct factorial_meta<0> { // break condition
  static constexpr int value = 1;
};
int main() {
  int x = factorial_meta<3>::value;
  int y = factorial_meta<0>::value;
}
```

---

# Metaprogramming
## Recursive programming
### Example: Factorial Computation
Now, the same program implemented using templates, static constants, recursive instantiation
and template specialization for the break condition

.pure-g[.pure-u-13-24[
```c++
template <int N>
struct factorial_meta { // recursion
  static constexpr int value
    = N * factorial_meta<N-1>::value;
};
template <>
struct factorial_meta<0> { // break condition
  static constexpr int value = 1;
};
int main() {
  int x = factorial_meta<3>::value;
  int y = factorial_meta<0>::value;
}
```
].pure-u-1-24[
].pure-u-10-24[
```asm
// assembler output:
main:
// ...
  movl $6, -8(%rbp) // explicit value
  movl $1, -4(%rbp)
// ...
```
]]

---

# Metaprogramming
## Recursive programming
### Remark
When writing an expression involving template instantiations, like
```c++
N <= 0 ? 1 : factorial_meta<N-1>::value;
```
All templates first get instantiated, second the arithmetic expression is evaluated. Meaning,
even for the case `N == 0` the `factorial_meta<N-1>` gets instantiated, thus `factorial<-1>`.
So we would get an infinite recursion and template instantiation. This can only be overcome
by providing another specialization of the template that kicks in instead of the recursive call.

---

# Metaprogramming
## Value and type aliases
- Instead of accessing `value` static constant directly, use a short alias
- Some convention in naming constants and types

```c++
template <int N>
constexpr int factorial_v = factorial_meta<N>::value;

template <class X>
constexpr auto identity_value_v = identity_value<X>::value;
```

Later: introduce type-aliases with postfix `_t`

---

# Metaprogramming
## Constexpr Metafunctions
- Use the keyword `constexpr` not only to define static constant variables
- It marks functions to be evaluable at compile time

```c++
constexpr int factorial (int n)
{
  return n <= 0 ? 1 : n * factorial(n - 1);
}
int main() {
  // runtime computation
  int x = factorial(3); // = 3*2*1 = 6
  int y = factorial(0);

  // compile time evaluation
  constexpr int z = factorial(4);

  // function as template argument
  std::array<int, factorial(5) + 1> arr;
}
```

---

# Metaprogramming
## Constexpr Metafunctions
- Use the keyword `constexpr` not only to define static constant variables
- It marks functions to be evaluable at compile time

.pure-g[.pure-u-13-24[
```c++
constexpr int factorial (int n)
{
  return n <= 0 ? 1 : n * factorial(n - 1);
}
int main() {
  // runtime computation
  int x = factorial(3); // = 3*2*1 = 6
  int y = factorial(0);

  // compile time evaluation
  constexpr int z = factorial(4);

  // function as template argument
  std::array<int, factorial(5) + 1> arr;
}
```
].pure-u-1-24[
].pure-u-10-24[
```asm
// assembler output:
main:
// ...
  movl    $6, -4(%rbp)
// ...
```
]]

---

# Metaprogramming
## Type Traits

- Template metafunctions produce values in form of static constants, depending on
  arguments that (somehow) represent values
- *Type traits* produce either types or values and might depend on types or values as
  input.
- Sometimes calles *typefunctions* or *traits classes*

### Initial example
An identity traits class

```c++
template <typename T>
struct identity
{
  using type = T;
};
```

Usage: `identity<T>::type var = T(value);`

---

# Metaprogramming
## Type Traits

- Template metafunctions produce values in form of static constants, depending on
  arguments that (somehow) represent values
- *Type traits* produce either types or values and might depend on types or values as
  input.
- Sometimes calles *typefunctions* or *traits classes*

### Initial example
An identity traits class

.pure-g[.pure-u-10-24[
```c++
template <typename T>
struct identity
{
  using type = T;
};
```
].pure-u-1-24[
].pure-u-13-24[
```c++
// type alias by convention
template <typename T>
using identity_t = typename identity<T>::type;
```
]]

Usage: `identity<T>::type var = T(value);`


---

# Metaprogramming
## Type Traits
- Type transformations: `(types...)` \(\mapsto\) `type`
- Type generation: `(values...)` \(\mapsto\) `type`
- Type inspection: `(types...)` \(\mapsto\) `value`

--

### 1. Type transformation / modifications
Take one or more input types and define a new type depending on the input

```c++
// Example: Remove constness from type
template <typename T>
struct remove_const { // primary template
  using type = T;
};
template <typename T>
struct remove_const<T const> { // specialization for type qualified with const
  using type = T;
};
```

---

# Metaprogramming
## Type Traits
### 1. Type transformation / modifications
Important type transformations from the std library, defined in `<type_traits>`:
- `std::decay` (convert type as if passed-by-value to function)
- `std::remove_cvref` (remove `const`, `volatile` and ref. `&` qualifiers) *c++20 only*
- `std:common_type` (The type all passed types can be implicitly converted to)

```c++
template <class Iter>
auto sum_elements (Iter first, Iter last)
{
  using type = std::decay_t<decltype(*first)>; // Get the raw type of the elements
  type sum(0)
  while (first != last)
    sum += *first++;
  return sum;
}
```

---

# Metaprogramming
## Type Traits
### 2. Type properties - Relation between types

Are two types the same, is one larger than the other one, can a type be used in a vector
expressions... All these are properties of types that can be tested for using typefunctions,
that return a `bool` constant.

Example: Are two types exactly the same:
```c++
template <typename T1, typename T2>
struct is_same { // primary template
  static constexpr bool value = false;
};
template <typename T>
struct is_same<T,T> { // specialization for same types
  static constexpr bool value = true;
};
```

---

# Metaprogramming
## Type Traits
### 2. Type properties

Important type property traits from the std library, defined in `<type_traits>`:
- `std::is_same` (Two types are identical)
- `std::is_convertible<From,To>` (type `From` is implicitly convertible to `To`)
- `std::is_floating_point` (type is a *fundamental* floating-point type)
- `std::is_invocable` (type is a functor or a function pointer)

Some special classes:
- `std::bool_constant<bool>` and `std::true_type`, `std::false_type`

---

# Metaprogramming
## Example `std::is_floating_point`

.pure-g[.pure-u-12-24[
```c++
template <typename T>
struct is_floating_point {
  // primary template
  static constexpr bool value = false;
};
template <>
struct is_floating_point<double> {
  // Template-specialization for double
  static constexpr bool value = true;
};
template <>
struct is_floating_point<float> {
  // Template-specialization for float
  static constexpr bool value = true;
};
template <>
struct is_floating_point<long double> {
  // Template-specialization for long double
  static constexpr bool value = true;
};
```
].pure-u-1-24[
].pure-u-11-24[
```c++
int main()
{
  using T1 = double;
  using T2 = int;
  if (is_floating_point<T1>::value)
    std::cout << "double is FP\n";
  if (is_floating_point<T2>::value)
    std::cout << "int is FP (???)\n";
}
```
]]

---

# Metaprogramming
## Type Traits
### 3. Type meta functions
Define a type depending on a value. This value can of any integral type

Example: Define a type depending on a boolean condition
```c++
template <bool condition, typename T1, typename T2>
struct conditional {
  using type = T1;    // default: condition==true
};
template <typename T1, typename T2>
struct conditional<false, T1, T2> {
  using type = T2;    // specialization for condition==false
};
```

---

# Metaprogramming
## Constexpr If
If parts of the code depent on template parameters and can only compile successfully in some situations
one has to conditionally activate/deactivate these parts.

### Example: Factorial
```c++
template <int N> // pass the argument as template parameter
int factorial ()
{
  if (N == 0)
    return 1;
  else
    return N * factorial<N-1>(); // ERROR: infinite recursion
}
```

All expressions must be instantiable, to determine the type of that expression.

> .h3[Note:] Instantiation != Evaluation

---

# Metaprogramming
## Constexpr If
In C++17 a special form of the `if`-statement is introduced, to allow conditionally switch between
blocks:

```c++
template <int N>
int factorial ()
{
  if constexpr (N == 0)
    return 1;
  else
    return N * factorial<N-1>(); // OK: not instantiated if N==0
}
```

The argument to `if constexpr` must be a constant expression, e.g., using a metafunction or a type-traits.

---

# Metaprogramming
## Type Traits vs. Concepts
- Type Traits formulate properties by using template specialization
- Concepts formulate properties by inspecting valid expressions

Type Traits can be used to define concepts:
```c++
template <typename T>
concept floating_point = std::is_floating_point<T>::value;
```

You can also use type traits in `requires` clauses
```c++
template <class T>
  requires std::is_floating_point_v<T>  // using the _v alias
auto sum (T const a, T const b)
{
  return a + b;
}
```

---

# Metaprogramming
## Preprocessor Macros
- The Preproccesor parses the code and makes some simple transformations in the first phase of
  the compile process
- Preprocessor commands start with the `#` symbol
- Often simple string replacement

### Some example commands
- `#include <...>`, `#include "..."` (include the content of that file at this position)
- `#define VAR [value]` and `#undef` (introduce replacement constant)

```c++
#define SIZE 100
int array[SIZE];
```

- `#define MACRO(a,b) (a) * (b)` (simple string replacement macro)

---

# Metaprogramming
## Preprocessor Macros

- `#if <condition>`, `#elif <condition>`, `#else`, `#endif`

```c++
#define SIZE 100
#if SIZE > 10
//... c++ code here
#elif SIZE > 50
//... c++ code here
#else
//
#endif
```

- Special predefined constants `__LINE__`, `__FILE__`, `__DATE__`, `__TIME__`
- Feature test macros (might be defined in `<version>`)

```c++
#if __cpp_lib_format >= 202106 // standard library has std::format
std::cout << std::format("{}\n", 42.0);
#endif
```
See https://en.cppreference.com/w/cpp/feature_test


---

# Metaprogramming
## Preprocessor Macros
- Preprocessor constants can be defined when invoking the compiler:

```bash
c++ -DVAR=value source.cc
```

- Important macros to define during compilation: `-DNDEBUG` (disable debugging code, e.g. `assert` macros)

- Since macros are expanded before the actual c++ compile process is started, the values can be
  used in constant expressions.

> .h3[Remark:] Try to minimize the usage of preprocessor macros. Replace with `constexpr` functions
> and constants instead. Also the `if constexpr` can be useful. Often there is a better replacement
> with c++ language features. Problem with macros: no inspection of c++ syntax, just simple string
> replacement.
