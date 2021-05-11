---
class: center, middle
# Advanced Datatypes
---

# Advanced Datatypes
## Type aliases
Often you do not always want to care about the actual datatype used in your program, e.g., if it is
`float` or `double` but instead give the types more reasonable names, e.g., `real`. In C++ you can
do this via `typedef`/`using`:

```c++
typedef <type> <alias_name>;   // or...
using <alias_name> = <type>;   // (suggested)
```

Afterwards, `<alias_name>` can be used like any other datatype:

```c++
using real_t   = double;
using string_t = char*;
using matrix_t = real_t**;  // pointer to pointer

string_t const str = "String";
matrix_t       A   = new real_t*[ 10 ];
real_t         f   = real_t( 3.1415926 );
```

---

# Advanced Datatypes
## Type aliases

> .h3[Remark:] A `real_t` datatype allows you to easily switch between `float` and
> `double` in your program.

To simplify the distinction between variables and datatypes, the following is strongly advised:

> .h3[Coding Principle:] Follow a strict convention in naming new types, e.g., with special
> prefix or suffix. Either use `_t` for your aliases, or specify type names always with CamelCase
> letters.

---

# Advanced Datatypes
## Predefined Types
The C++ library and the operating system usually define some abbreviations for often used types, e.g.,

-   unsigned integer with explicit size:
    `std::uint8`,
    `std::uint16` and
    `std::uint32` for 8, 16 and 32 bit
    respectively,

-   similar `std::int8`,
    `std::int16` and
    `std::int32` are defined for signed
    integers,

-   `std::size_t` : unsigned integer type for
    holding size information best suited for the local hardware

> .h3[Codeing Principle:] Use `std::size_t` for representing container size information and indices.

---

# Advanced Datatypes
## Structures
Working with vectors and matrices always involved several variables, e.g., the size and the arrays.
That results in many arguments to functions and hence, to possible errors. It would be much better to
store all associated data together. That is done with `struct`:

```c++
struct <name> {
  <type_1> <variable_1>;
  <type_2> <variable_2>;
  <type_2> <variable_3>;
};
```

By defining a `struct`, also a new datatype named `<name>` is defined.

---

# Advanced Datatypes
## Struct Example:

```c++
struct Vector {
    std::size_t size;
    real_t*     data;
};

struct Matrix {
    std::size_t nrows, ncols;
    real_t*     data;
};

// y += alpha * A * x
void mat_vec(real_t const   alpha,
             Matrix const&  A,
             Vector const&  x,
             Vector&        y);
```

---

# Advanced Datatypes
## Initializing Structure Members
A variable of the datatype a `struct` represents can be created by using the universal initialization
```c++
Vector x1{10, new real_t[10]};
Vector x2{};    // default initialization of all members
Vector x3;      // just definition, no initialization of the members
```

--

It is also possible to make a named initialization
```c++
Vector x4{.size = 10, .data = new real_t[10]};
```

--

Allocating an object of the type dynamically, can be done using the `new` operator:
```c++
Vector* x5 = new Vector{...};  // or without braces
```

---

# Advanced Datatypes
## Initializing and Accessing Structure Members
The individual variables in a struct are accessed via `.` operator, i.e.:

```c++
Vector  x;

x.size = 10;
x.data = new real_t[ x.size ];
```

If a pointer to a struct is given, the access can be simplified. Instead
of `*` (deref) and `.`, the operator `->` is provided:

```c++
Vector*  x = new Vector;

x->size = 10;
x->data = new real_t[ x->size ];

std::cout << (*x).size << std::endl; // alternative (note the operator precedence)
```

---

# Advanced Datatypes
# Accessing Structure
In case of a reference, e.g., `Vector&`, the standard `.` access has to be used:

```c++
Vector  x{...};
Vector& y = x;

std::cout << y.size << std::endl;
std::cout << y.data[5] << std::endl;
```

---

# Advanced Datatypes
## Structures and Functions
Structures can be supplied as normal function arguments, either as call-by-value or call-by-reference:

```c++
double dot (Vector const x, Vector const y);
void   set (Vector& y, real_t const alpha);
void   axpy (real_t const alpha, Vector const& x, Vector& y);
```

--

When passed by value (or by `const&`) the function argument can be initialized directly using curly braces `{...}`:

```c++
double* a = ...;
double* b = ...;

double result = dot({10, a}, {.size=10, .data=b});
```

---

# Advanced Datatypes
## Structures and Functions

When using call-by-value, a copy of the complete struct is actually
created. For large structs, this can be a significant overhead:

```c++
struct QuadratureRule {
    real_t  points[  100 ];
    real_t  weights[ 100 ];
};

template <class Func>
double quadrature (QuadratureRule const rule, Func f);
```

> .h3[Note:] When a static array is stored in a `struct` and passed by value, all the array elements
> are copied. Also when structures with array members are returned from functions all elements are copied.

---

# Advanced Datatypes
## Structures and Functions
In such cases, call-by-reference with a `const` reference argument is necessary to avoid
this overhead:

```c++
template <class Func>
double quadrature (QuadratureRule const& rule, Func f);
```

Here, only a single pointer is supplied to the function instead of 200
`real_t` values.

---

# Advanced Datatypes
## Array of Structs
Like any other datatype, structs can also be allocated in the form of an array:

.pure-g[.pure-u-2-5[.padding-5[
```c++
struct Coord {
    real_t  x, y, z;
};

Coord coordinates[ 10 ];
```
]].pure-u-3-5[.padding-5[
```c++
#include <cmath>
...
for (std::size_t i = 0; i < 10; ++i)
{
  coordinates[i].x = std::cos(i * 36*M_PI / 180.0);
  coordinates[i].y = std::sin(i * 36*M_PI / 180.0);
  coordinates[i].z = i / 10.0;
}
```
]]]

for fixed sized array or...

---

# Advanced Datatypes
## Array of Structs
Like any other datatype, structs can also be allocated in the form of an array:

.pure-g[.pure-u-2-5[.padding-5[
```c++
struct Coord {
    real_t  x, y, z;
};

Coord* coordinates = new Coord[10];
```
]].pure-u-3-5[.padding-5[
```c++
#include <cmath>
...
for (std::size_t i = 0; i < 10; ++i)
{
  coordinates[i].x = std::cos(i * 36*M_PI / 180.0);
  coordinates[i].y = std::sin(i * 36*M_PI / 180.0);
  coordinates[i].z = i / 10.0;
}
```
]]]

... using dynamic memory management.

---

# Advanced Datatypes
## Struct of Arrays
The storage can also be inverted. Instead of an array of structures (AoS) one can store a structure
of arrays (SoA):

.pure-g[.pure-u-2-5[.padding-5[
```c++
struct Coordinates {
    real_t x[ 10 ];
    real_t y[ 10 ];
    real_t z[ 10 ];
};
Coordinates coordinates;
```
]].pure-u-3-5[.padding-5[
```c++
#include <cmath>
...
for (std::size_t i = 0; i < 10; ++i)
{
  coordinates.x[i] = std::cos(i * 36*M_PI / 180.0);
  coordinates.y[i] = std::sin(i * 36*M_PI / 180.0);
  coordinates.z[i] = i / 10.0;
}
```
]]]


For different applications and usage/access pattern either the one or the other representation might be
more efficient or convenient.

See also https://en.wikipedia.org/wiki/AoS_and_SoA

---

# Advanced Datatypes
Structures can be nested, i.e., a struct can be a member of another struct:

## Example1: Sparse Matrix in Coordinate Format
```c++
struct Triple {
  std::size_t row;
  std::size_t col;
  real_t      value;
};

struct TripleList {
  std::size_t size;
  Triple*     data;
}

struct SparseMatrix {
  std::size_t nrows;
  std::size_t ncols;
  TripleList  nonzeros;
};
```

---

# Advanced Datatypes
## Example1: Sparse Matrix in Coordinate Format
1d Laplacian 3-point stencil
\[
  A = \begin{pmatrix}
     2 & -1 &        & & & \\
    -1 &  2 & -1     & & & \\
       & -1 & \ddots & & & \\
       &    & -1     & 2 & -1 \\
       &    &        &-1 & 2
  \end{pmatrix}
\]

---

# Advanced Datatypes
## Example1: Sparse Matrix in Coordinate Format
The nested structures can be initialized directly using nested curly braces:
```c++
SparseMatrix mat{10,10, {28, new Triple[28]}};

std::size_t idx = 0;
mat.nonzeros.data[idx++] = {0,0, 2.0};
for (std::size_t i = 1; i < 10; ++i) {
  mat.nonzeros.data[idx++] = {i,i,    2.0};
  mat.nonzeros.data[idx++] = {i-1,i, -1.0};
  mat.nonzeros.data[idx++] = {i,i-1, -1.0};
}
assert(idx == 28);
```

---

# Advanced Datatypes
## Example1: Sparse Matrix in Coordinate Format
### Matrix-Vector product
```c++
void mat_vec(real_t const         alpha,
             SparseMatrix const&  A,
             Vector const&        x,
             Vector&              y)
{
  for (std::size_t i = 0; i < A.nonzeros.size; ++i) {
    auto const& [row,col,value] = A.nonzeros[i];    // structured binding also for structs

    y[ row ] += alpha * value * x[ col ];
  }
}
```

---

# Advanced Datatypes
## Example2: Sparse Matrix in Compressed Format
We can store sparse matrices even with more locality, using three arrays:

-   `indices`: stores column indices for all entries, sorted by row,
-   `values`: stores all coefficients in same order as in `indices` and
-   `offset`: stores at `offset[i]` the position of the first value corresponding to row `i` in the arrays
    `indices` and `values`. The last field contains the number of nonzeros.

This format is known as the *compressed row storage* format.

```c++
struct CRSMatrix {
  std::size_t    nrows, ncols;
  std::size_t*   offset;
  std::size_t*   indices;
  real_t*        values;
};
```

See, e.g., Y. Saad: Iterative methods for sparse linear systems, Section 2.3 Storage Schemes

---

# Advanced Datatypes
## Example2: Sparse Matrix in Compressed Format
For the matrix
\[
  A=\begin{pmatrix}
    1 & & 3 & \\
    & 2 & & -1 \\
    -4 & -1 & 1 & \\
    1 & & & 3
  \end{pmatrix}
\]

the corresponding source code is:

```c++
std::size_t offset[]  = { 0, 2, 4, 7, 9 };  // accumulated num of entries per row
std::size_t indices[] = { 0, 2,   1,  3,    0,  1, 2,   0, 3 };
real_t      values[]  = { 1, 3,   2, -1,   -4, -1, 1,   1, 3 };

CRSMatrix mat{4, 4, offset, indices, values};
```

---

# Advanced Datatypes
## Example2: Sparse Matrix in Compressed Format
### Matrix-Vector product
```c++
void mat_vec(real_t const      alpha,
             CRSMatrix const&  A,
             Vector const&     x,
             Vector&           y)
{
  for (std::size_t i = 0; i < A.nrows; ++i)
  {
    real_t f  = 0.0;
    std::size_t const lb = A.offset[ i ];
    std::size_t const ub = A.offset[ i+1 ];

    for (std::size_t j = lb; j < ub; ++j)
      f += A.values[ j ] * x[ A.indices[ j ] ];

    y[ i ] += alpha * f;
  }
}
```

---

# Advanced Datatypes
## Enumerations
A special datatype is available to define enumerations:

```c++
enum <enum_name> {
  <name_1>, <name_2>, <name_3>,...
};
```

### Example:

```c++
enum Symmetry { unsymmetric, symmetric, hermitian };

Symmetry s;

if (s == symmetric) { ... }
```

Enumerations are handled as integer datatypes by C++. By default, the
members of an enumeration are numbered from `0` to `n-1`, e.g., `<name_1> = 0, <name_2> = 1`, etc..

---

# Advanced Datatypes
## Enumerations
One can also define the value of the enumeration members
explicitly:

```c++
enum Symmetry { unsymmetric = 4, symmetric = 17, hermitian = 42 };
```

Since enumerations are equivalent to integer types, they can also be
used in `switch` statements:

```c++
switch (s)
{
  case symmetric:   ...; break;
  case hermitian:   ...; break;

  case unsymmetric:
  default:          ...;
}
```

---

# Advanced Datatypes
## Enumerations
Sometimes it is useful to specify the integer of enums explicitly

```c++
enum <enum_name> : <type> {
  <name_1>, <name_2>, <name_3>,...
};
```

### Example:

```c++
enum Symmetry : unsigned short { unsymmetric, symmetric, hermitian };
```

---

# Advanced Datatypes
## Enumerations

By default, the enum values are introduced in the scope where the enum is defined. If there are
other variables/functions/... with the same name it could clash. It is thus recommended to introduce
a corresponding *named scope* for the enum values:
```c++
enum class <enum_name> [: <type>] {
  <name_1>, <name_2>, ...
}
```
### Example:

```c++
enum class Symmetry { unsymmetric, symmetric, hermitian };

Symmetry s;
switch (s) {
  case Symmetry::unsymmetric:  ...;
}
```

---

# Advanced Datatypes
## Enumerations

By default, the enum values are introduced in the scope where the enum is defined. If there are
other variables/functions/... with the same name it could clash. It is thus recommended to introduce
a corresponding *named scope* for the enum values:
```c++
enum class <enum_name> [: <type>] {
  <name_1>, <name_2>, ...
}
```
### Example:

```c++
enum class Symmetry { unsymmetric, symmetric, hermitian };

Symmetry s;
switch (s) {
  using enum Symmetry;    // [c++20]
  case unsymmetric:  ...;
}
```
