---
class: center, middle
# Variables and Datatypes
---

# Variables and Datatypes

C++ is a **statically typed** language.
- Each identifier and expression has a property called *type*.
- The type restricts the *operations* that are permitted for those entities.
- It provides *semantic meaning* to the otherwise generic sequences of bits.
- The type is *fixed* and *known* to the compiler.

> .h3[C++-Standard (N4835) §7.1 (1):] An expression is a sequence of operators and operands that specifies a computation.
> An expression can result in a value and can cause side effect.

--

## Fundamental types

- The language defines datatypes that are built into the compiler
- Basic types categorized as *integral types*, *floating-point types*, and *void*

---

# Variables and Datatypes
## Integral types
- The boolean type `bool` with two possible values `true` and `false`.
- Character types `char`, `signed char` and `unsigned char`.
- Basic integer type: `int`, can be equipped with *modifiers*:
  * **Signedness**: `signed`, `unsigned`
  * **Size**: `short`, `long`, `long long`
- Additional basic types: `std::size_t`, `std::int32_t`,...

### Examples
```c++
true, false                 // bool
'c', '/', '\n', '0'         // char
0, 123, 635u, 745l, 9993ll  // int, int, unsigned, long, long long

1234567898765432            // smallest int type that can represent number
```

---

# Variables and Datatypes
### Representable range:
- Signed int: \(-2^{N-1}\ldots 2^{N-1}-1\) with \(N\) the width of the type in bits.
- Unsigned int: \(0\ldots 2^{N}-1\), arithmetic operations modulo \(2^N\)
- Representation by [two's complement](https://en.wikipedia.org/wiki/Two%27s_complement)

### Data models
- Defines width of integer types (`int`/`long`/pointer)
- 32 bit systems:
  * **LP32**: or 2/4/4 (`int` is 16-bit, `long` and pointer are 32-bit), e.g., Win16 API
  * **ILP32**: or 4/4/4 (`int`, `long`, and pointer are 32-bit), e.g., Win32 API, Linux, macOS
- 64 bit systems:
  * **LLP64**: or 4/4/8 (`int` and `long` are 32-bit, pointer is 64-bit), e.g., Win64 API
  * **LP64**: or 4/8/8 (`int` is 32-bit, `long` and pointer are 64-bit), e.g., Linux, macOS

---

# Variables and Datatypes
### Integer overflow and underflow
When doing arithmetic with integer types, the range of the types has to be considered. If the result
is bigger than the maximum value, the result becomes negative, e.g. using `short`:
\[ 32760 + 100 = -32676 \]
Here, an **overflow** occurred. Similar behavior can be observed if the result is less that the
minimum (**underflow**):
\[ -32760 - 100 = 32676 \]

> .h3[Remark:] If during the evaluation of an expression, the result is not mathematically defined or not in the
> range of representable values for its type, the [behavior is undefined](https://en.cppreference.com/w/cpp/language/ub).

---

# Variables and Datatypes
## Floating Point Datatypes

Floating point numbers \(x\) are represented as \( x = s \cdot m \cdot 2^e \)
with the sign \(s\), the mantissa \(m\) and the exponent \(e\).
In C++, we have the following floating point types, defined by IEEE-754

-   `float`: single precision, 23 bits for mantissa, 8 bits for exponent,<br>
    \(x \in [-3\cdot 10^{38} \ldots -10^{-38}, 0, 10^{-38} \ldots, 3\cdot 10^{38} ]\),
--
-   `double`: double precision, 52 bits for mantissa, 11 bits for exponent,<br>
    \(x \in [-2\cdot 10^{308} \ldots -10^{-308}, 0, 10^{-308} \ldots, 2\cdot 10^{308} ]\).
--
-   `long double`: extended precision floating point type. Does not necessarily map to types mandated by IEEE-754.

---

# Variables and Datatypes
## Floating Point Datatypes

Floating point numbers \(x\) are represented as \( x = s \cdot m \cdot 2^e \)
with the sign \(s\), the mantissa \(m\) and the exponent \(e\).
In C++, we have the following floating point types, defined by IEEE-754

-   `float`: single precision, 23 bits for mantissa, 8 bits for exponent,<br>
    \(x \in [-3\cdot 10^{38} \ldots -10^{-38}, 0, 10^{-38} \ldots, 3\cdot 10^{38} ]\),
-   `double`: double precision, 52 bits for mantissa, 11 bits for exponent,<br>
    \(x \in [-2\cdot 10^{308} \ldots -10^{-308}, 0, 10^{-308} \ldots, 2\cdot 10^{308} ]\).
-   `long double`: extended precision floating point type.

Floating point numbers are entered with a *dot*:<br>
    `4.0` (`double`) or `4.0f` (`float`) instead of just `4` (`int`)

---

# Variables and Datatypes
## Floating Point Datatypes

Floating point numbers \(x\) are represented as \( x = s \cdot m \cdot 2^e \)
with the sign \(s\), the mantissa \(m\) and the exponent \(e\).
In C++, we have the following floating point types, defined by IEEE-754

-   `float`: single precision, 23 bits for mantissa, 8 bits for exponent,<br>
    \(x \in [-3\cdot 10^{38} \ldots -10^{-38}, 0, 10^{-38} \ldots, 3\cdot 10^{38} ]\),
-   `double`: double precision, 52 bits for mantissa, 11 bits for exponent,<br>
    \(x \in [-2\cdot 10^{308} \ldots -10^{-308}, 0, 10^{-308} \ldots, 2\cdot 10^{308} ]\).
-   `long double`: extended precision floating point type.

Exponent is defined using scientific notation via 'E' or 'e':<br>
    `4.25E-4` or `4.25e-4` mean \(4.25 \cdot 10^{-4}\)

---

# Variables and Datatypes
## Floating Point Datatypes: Rounding
Since number of bits for representing numbers is limited, real numbers are **rounded**:

-   `float`: \(\tilde \pi = 3.141592\underline{7}41\),
-   `double`: \(\tilde \pi = 3.141592653589793\underline{1}16\)

This might also lead to wrong results:
\[\pi - 3.1415926 \approx 5.36\cdot 10^{-8}\] but in single precision
one obtains \[\pi - 3.1415926 = 1.41\cdot 10^{-7}.\] This effect is also
known as **cancellation**

---

# Variables and Datatypes
## Floating Point Datatypes: Absorption
When adding two numbers with a large difference in the exponent, the result might be equal to the
larger of the two addend, e.g. in single precision:

For \(x \in \)`float`: \(x + 1\cdot 10^{-8} = x\)

For any floating point type, the smallest number
\(\varepsilon\), such that \(1+\varepsilon\ne 1\)
is known as the **machine precision**:

-   for `float`: \(\varepsilon\approx 1.2 \cdot 10^{-7}\),
-   for `double`: \(\varepsilon\approx 2.2 \cdot 10^{-16}\).

Use `std::numeric_limits<T>::epsilon()` for `T=float/double` in code to get \(\varepsilon\).

---

# Variables and Datatypes
## Floating Point Datatypes: Absorption
When adding two numbers with a large difference in the exponent, the result might be equal to the
larger of the two addend, e.g. in single precision:

For \(x \in \)`float`: \(x + 1\cdot 10^{-8} = x\)

For any floating point type, the smallest number
\(\varepsilon\), such that \(1+\varepsilon\ne 1\)
is known as the **machine precision**:

-   for `float`: \(\varepsilon\approx 1.2 \cdot 10^{-7}\),
-   for `double`: \(\varepsilon\approx 2.2 \cdot 10^{-16}\).

> .h3[Coding Principle:] Always check if the range and the precision of the floating point type
> is enough for your application. If in doubt: use `double` precision.

---

# Variables and Datatypes
## Floating Point Datatypes: High precision
Some compilers and libraries provide extended floating point precision, e.g., `__float128` for
quad-precision with GCC (and Intel) compilers. Arithmetic is also defined in [IEEE 754-2008](https://irem.univ-reunion.fr/IMG/pdf/ieee-754-2008.pdf)
standard.

Only very few hardware directly supports this type. Typically emulated in software.

Other libraries even provide multi-precision floating point and large integer types, e.g.,
- [GNU GMP](https://gmplib.org/) (The GNU Multiple Precision Arithmetic Library),
- [MPFR](https://www.mpfr.org/) (C++), or
- [Boost.Multiprecision](https://www.boost.org/doc/libs/1_75_0/libs/multiprecision/doc/html/index.html)

---

### Example: area of a circle

```c++
#include <iostream>
#include <iomanip>
#include <limits>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using dec_float_50 = boost::multiprecision::cpp_dec_float_50;

template <class T>
T area_of_a_circle(T r) {
  using boost::math::constants::pi;
  return pi<T>() * r * r;
}

int main(int, char**) {
  dec_float_50 const r = dec_float_50{123} / 100;
  dec_float_50 const a = area_of_a_circle(r);

  // 4.7529155256159981904701331745635599135018975843146
  std::cout
    << std::setprecision(std::numeric_limits<dec_float_50>::digits10)
    << a
    << std::endl;
}
```

---

# Variables and Datatypes
## void
- Represents an empty set of values
- No variable can be declared of type `void` -> *incomplete type*
- Can be used as return type for functions. Any expression can be *explicitly* converted to type `void`

## Library type \(\rightarrow\) later
- C++ has no language fundamental types for *strings* and *complex numbers*.
- C++ provides a powerful standard library that implements many compound types

## Compound datatypes \(\rightarrow\) later
Reference and pointer types, Array types, Class and enumeration types, Function types, ...

---


# Variables and Datatypes
## Variables
Variables can be declared at (almost) **any** position in the source file. The declaration follows the scheme:

```c++
<typename> <variablename>; // or

<typename> <variablename1>, <variablename2>...;
```

> .h3[Remark:] Every statement in C++ is finished with a *semicolon*.

A name for a variable can contain any alphanumerical character plus `_`
and must not begin with a number. Also, they can not be identical to a
reserved name used by C++. Variable names are **case sensitive**.

---

# Variables and Datatypes
### Variables Examples:

```c++
int     n;
int     i, j, k;
float   pi, Pi, PI;
double  1_over_pi;      // ERROR
double  _1_over_pi;     // Ok
```

### Variables: Initial Values
When declaring a variable, one *can* provide an initial value:

```c++
int     n           = 10;
int     i, j, k;    // not initialized
float   pi          = 3.1415926;
double  _1_minus_pi = 1.0 - pi;
double  max         = 1.8e308;
```

---

# Variables and Datatypes

> .h3[Coding Principle:] *Resource allocation is initialization* (.h3[RAII]):
> Whenever a resource, e.g. variable, is allocated/declared, it should
> be initialized with some reasonable value.

What is wrong with:

```c++
int     n           = 10;
int     i, j, k;
float   pi;
double  _1_minus_pi = 1.0 - pi;
double  max         = 1.8e308;
```

The value of `_1_minus_pi` is not defined, but
only some compilers will give you a warning about that.

---

# Variables and Datatypes
### Variables: Usage
Variables can only be used **after** they have been declared:

```c++
double const  _1_minus_pi = 1.0 - pi;    // ERROR: "pi" is unknown
float const   pi          = 3.1415926;
double const  _2_plus_pi  = 2.0 + pi;    // Ok: "pi" is defined
```

### Type/Variable Qualifiers
Each type can be modified with the following **qualifiers**, one from each group:

-   **Constness qualifiers:** `const`: the value of the variable cannot be changed, or `volatile`
-   **Storage class specifiers:** `static`: the variable is declared only once in the whole program, or `extern`, `thread_local`

---

# Variables and Datatypes
### Type/Variable Qualifiers
Each type can be modified with the following **qualifiers**, one from each group:

-   **Constness qualifiers:**<br>&nbsp;&nbsp;&nbsp;`const`: the value of the variable cannot be changed, or `volatile`
-   **Storage class specifiers:**<br>&nbsp;&nbsp;&nbsp;`static`: static storage duration, or `extern`, `thread_local`

The modifiers can be combined:

```c++
int const           n           = 10;
int                 i, j, k;
float const         pi          = 3.1415926;
double const        _1_minus_pi = 1.0 - pi;
static double const max         = 1.8e308;
```

---

# Variables and Datatypes
### Type/Variable Qualifiers

The type qualifiers `const` (and `volatile`) act on the type to its left
```c++
unsigned int const n1 = 0; n1 = 1; // ERROR
const unsigned int n2 = 2; // alternative notation
```

Storage class specifiers act on the variable (identifier) independent of the position
```c++
static int const n3 = 0;
int const static n4 = 1;
int static const n5 = 2;
```

> .h3[Coding Principle:] Use `const` as much as possible.

---

# Variables and Datatypes
## Number conversion
Whenever a variable is initialized with an expression, the value of that expression must be converted to the type of the variable
- Initialization of value to smaller type \(\rightarrow\) *narrowing initialization* or *narrowing conversion*
- Use curly braces to get a compiler error for this case

```c++
int i0 = 1234567898765;   // warning: warning: implicit conversion from 'long' to 'int'
                          //          changes value from 1234567898765 to 1912284813
int i1{1234567898765};    // error: constant expression evaluates to 1234567898765 which
int i2 = {1234567898765}; //        cannot be narrowed to type 'int'
```

> .h3[Coding Principle:] Prefer *uniform initialization* with curly braces. Enable all warnings of
> the compiler by default. Use the compiler flag `-Wall`.

---

# Variables and Datatypes
## Number conversion
For floating point values we call a conversion to a smaller datatype (e.g. `double -> float`) a
floating point **conversion** (with possibly loss of precision) and otherwise a floating point **promotion**
(represent the value exactly in the larger type)

```c++
int i1 = 3.14;        // initializes to 3, no error
int i2 = {3.14};      // Narrowing ERROR: fractional part lost

unsigned u1 = -3;     // initializes to largest possible unsigned number
unsigned u2{-3};      // Narrowing ERROR: no negative values

float f1 = {3.14}     // ok. initializes to float number closest to 3.14
double d = 3.14;
float f2 = {d};       // Narrowing ERROR. Possible lost of accuracy

unsigned u3 = {3};
int      i3 = {2};
unsigned u4 = {i3};   // Narrowing ERROR: no negative values
int      i4 = {u3};   // Narrowing ERROR: not all values
```

---

# Variables and Datatypes
## Pointers and References

A **pointer** is a special datatype derived from a
base type, where the variable contains the memory position of another
variable. The syntax is:

```c++
<base type>* <pointer name>;
```

The memory position, i.e., the address, of an existing variable is
obtained by the *address operator* `&`, i.e., `&<variable>`

To obtain the value of the memory position, the pointer directs to, the
(unary) *dereference operator* `*`, i.e., `*<pointer name>`
is available (not to be mistaken with the binary multiplication
operator!).

---

# Variables and Datatypes
## Pointers and References
Example for the usage of pointers:

```c++
int  n  = 5;
int* p  = &n;       // take the address of n

int m1 = n  + 3;
int m2 = *p + 3;    // m2 equal to m1
 *p = 6;            // this changes the value of n to 6!
m2 = n + 4;         // evaluates to 10!
```

The value of a pointer, e.g., the address, can be assigned to another
pointer:

```c++
int* q = p;  // q now points to the same position
             // as p, hence, to n

n  = 2;
m1 = *p + *q // is equivalent to n+n
```

---

# Variables and Datatypes
## Pointers and References
A special pointer value, `nullptr`, exists for the case that no
standard variable is available to point to:

```c++
int* ptr = nullptr;
```

Dereferencing a `nullptr` pointer is *undefined behavior* and typically leads to a program abort.

> .h3[Coding Principle:] Always initialize a pointer with the address of an existing variable
> or with `nullptr`.
> .h3[RAII] is even *more important* when working with pointers than
> with standard variables, since undefined pointers almost always lead
> to hard to find errors.

---

# Variables and Datatypes
## Pointers and References
A *reference* is a special form of a "pointer", which can only be initialized with the address
of an existing variable. The syntax is:
```c++
<base type>& <reference name> = <object>;
```

One does not need to dereference references:
```c++
int   n = 5;
int&  r = n;
int   m = r + 3;  // m == n + 3
r = m;            // r still points to n and n == m
m = 0;            // r and n are unchanged

int& s = m;       // You cannot change the address where a reference points to:
r = s;            // r still points to n and n == m (== 0)
```

---

# Variables and Datatypes
## Pointers and References: Duality

*Reference* and *Pointers* are actually dual in th sene that derreferencing a pointer gives a reference
and taking the address of a reference gives a pointer. This is mirrored in the notation:
```c++
int variable = 1;       // allocates memory on the stack

int& ref  = variable;   // create a reference to the variable

int* ptr  = &ref;       // create a ptr to the location referred to by 'ref'
int& ref2 = *ptr;       // build a reference to the memory 'ptr' points to
```

> .h3[Remark:] The symbol `&` is always placed next to a reference as *operator* or in the declaration,
> the symbol `*` is always associate to pointers.

---

# Variables and Datatypes
## Pointers and References
Pointers (and references) can also be combined
with `const` in various forms:

```c++
int*               pn1;  // non-const pointer to non-const var.
int  const*        pn2;  // non-const pointer to const var.
int* const         pn3;  // const pointer to non-const var.
int  const* const  pn4;  // const pointer to const var.
```

If the pointer is constant, the address it is directing to cannot be
changed. If the variable is constant, the value of it cannot be
modified:

```c++
int          n   = 0;
int const    m   = 1;
int*        pn1 = &m; // Error: cannot initialize 'int *' with 'int const*'
int  const* pn2 = &n; // Ok: conversion from 'int *' to 'int const*'
int* const  pn3 = &n; // Ok
pn3 = &m;             // Error: cannot assign to 'pn3', variable 'pn3' declared const
```

---

# Variables and Datatypes
## Placeholder Type
For variables, `auto` specifies that the type of the variable that is being declared will be
automatically deduced from its initializer.
```c++
auto <variable name> = <expression>;            // (1.)

decltype(auto) <variable name> = <expression>;  // (2.)
```
1. type of `<variable name>` is deduced by stripping all (first-level) modifiers/qualifiers from the
  type of `<expression>` \(\rightarrow\) "raw type"
2. type `decltype(<expression>)`, possibly including modifiers and qualifiers

The placeholder `auto` may be accompanied by modifiers, such as `const` or `&`, which will participate in the type deduction.

---

# Variables and Datatypes
## Placeholder Type: Examples

```c++
auto x = 3+4;       // deduce the type from the expression: x <-- int <-- 3+4
auto y = long{3+4}; // explicitly committing to a type: y <-- long

auto z{3+4};            // same as variable x: z <-- int                      [C++17]
auto z1 = {3.4};        // ATTENTION: This gives 'std::initializer_list<int>' [C++17]
auto const z2 = 3+4;    // type of z2 is 'int const'

decltype(auto) x2 = x;  // type of x2 is 'int&'
decltype(x) x3 = x;     // extract the type from the expression 'x'
auto& x4 = x;           // type of x4 is 'int&'
```

> .h3[Almost-Always-Auto:] Preferring auto variables is motivated primarily by *correctness*,
> *performance*, *maintainability*, and *robustness* - and only lastly about typing convenience.
> (Herb Sutter, [GotW #94](https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almost-always-auto/))

---

# Variables and Datatypes
## Constrained Placeholders
Constrain the possible types that can be deduced by a type **concept**. This defines properties and
usage *requirements* and not explicit datatypes. Requires **C++20**.
```c++
<type-constraint> auto <variable name> = <expression>;
<type-constraint> decltype(auto) <variable name> = <expression>;
```

### Examples:
```c++
std::integral       auto x{3+4}; // Ok, deduces the type from expr 3+4 -> int,
                                 // must be integral type
std::floating_point auto y{3+4}; // error: deduced type 'int' does not satisfy
                                 // 'floating_point'
```

Compile the code with clang-11 or gcc-10, adding `#include <concepts>`, by
```
  c++ -std=c++20 <source-file> -o <output-name>
```