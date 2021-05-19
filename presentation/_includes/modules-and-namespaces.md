---
class: center, middle
# Modules and Namespaces
---

# Modules and Namespaces
## Header Files
Up to now, all source code was placed into one file. For
reasonable programs, this is not desirable, especially if functions are
reused by different programs.

Until C++20, we had no real module system in C++ like, e.g., Python or
Java, to group similar functions or types. Instead, **header**
files are used to make C++ entities known to different source files.

As you remember, functions can be used if they were previously declared
or implemented. By separating declaration and implementation into header
and source file:

.pure-g[.pure-u-1-2[.padding-5[
```c++
// header file: f.hh

void f (int n, double f);
```
]].pure-u-1-2[.padding-5[
```c++
// source file: f.cc

void f (int const n, double f)
{ ... }
```
]]]

the function can be reused by just **including** the header file.

---

# Modules and Namespaces
## Header Files
Including another file into the current source code is
performed by the `#include` directive:

```c++
#include "filename" // or
#include <filename>
```

The first version is usually used for files in the same project, whereas
the second version is for files from other projects, e.g., the c++ standard library
or an external library.

```c++
#include "f.hh"   // contains declaration of "f"

int main ()
{
  f(42, 3.1415926);
}
```

---

# Modules and Namespaces
## Header Files

In order to compile a source file that includes another header file, we have to tell the compiler
where to find these files:

1. With `#include <filename>` the compiler searches in all default system locations, internal compiler
   locations, and all explicitly specified locations, see below.
2. With `#include "filename"` the compiler searches additionally in the same directory as the source
   file that includes `filename`.
3. Search directories can be explicitly specified by the compiler option `-I<dir>`

---

# Modules and Namespaces
## Header Files
### Example
- The source file `mat_vec.cc` from the introductory example contains the line `#include <boost/numeric/mtl/mtl.hpp>`
- Thus, the compiler needs to know the directory `<dir>` that contains <br>`<dir>/boost/numeric/mtl/mtl.hpp`
- The corresponding library that provides this file is [MTL4](https://www.simunova.com/de/mtl4/)
- Download the source by using [subversion](https://subversion.apache.org/) into the directory `<libs>`

```bash
cd <libs>
svn checkout https://svn.simunova.com/svn/mtl4/trunk mtl4
```

- Compile the source file by

```bash
c++ -I<libs>/mtl4 mat_vec.cc -o mat_vec
```

---

# Modules and Namespaces
## Header Files

By convention, the filename suffix of the header file should be either
`.h` (like in C), `.hh`, `.hpp`, or `.hxx`.

The filename suffix for source files is, correspondingly
`.cc`, `.cpp`, or `.cxx`.

> .h3[Note:] C++ standard libraries are provided in header files without suffix. The functions
> imported from *C* are in files with the `c` prefix: `#include <cmath>` vs. `#include <math.h>`.

---

# Modules and Namespaces
## C++ Library
The C++ compiler comes with a set of standard include
files containing declarations of many functions:

[`<cstdlib>`](https://en.cppreference.com/w/cpp/header/cstdlib)
:   standard C functions, e.g.,
.font-md[
- `std::exit`: stop program,
- `std::atoi` and `std::atof`: string to `int` and `double` conversion,
- `std::qsort`: sort arrays,
- `std::malloc` and `std::free`: C-style dynamic memory  management,
]

[`<cmath>`](https://en.cppreference.com/w/cpp/header/cmath)
:   mathematical functions, e.g.,
.font-md[
-  `std::sqrt`: square root,
-  `std::abs`: absolute value,
-  `std::sin` and `std::cos`,
-  `std::log`: natural logarithm
]

---


# Modules and Namespaces
## C++ Library

[`<cstdio>`](https://en.cppreference.com/w/cpp/header/cstdio)
:   C-style IO functions, e.g.,
.font-md[
- `std::printf`: print variables to standard  output,
- `std::fopen`, `std::fclose`, `std::fread` and `std::fwrite`: file IO
]

[`<cstring>`](https://en.cppreference.com/w/cpp/header/cstring)
:   string functions, e.g.,
.font-md[
- `std::strlen`: string length,
- `std::strcat`: string concatenation,
- `std::strcmp`: string comparison,
- `std::strcpy`: string copy
]

[`<cctype>`](https://en.cppreference.com/w/cpp/header/cctype)
:   character tests, e.g.,
.font-md[
- `std::isdigit`: test for digit,
- `std::islower`: test for lower case,
- `std::isspace`: test for white-space
]

etc.
:   [`<cassert>`](https://en.cppreference.com/w/cpp/header/cassert),
    [`<cerrno>`](https://en.cppreference.com/w/cpp/header/cerrno),
    [`<cinttypes>`](https://en.cppreference.com/w/cpp/header/cinttypes),
    [`<climits>`](https://en.cppreference.com/w/cpp/header/climits),
    [`<ctime>`](https://en.cppreference.com/w/cpp/header/ctime).

---

# Modules and Namespaces
## C++ Library
Specific C++ functionality usually comes in the form of
the "*standard template library*". It is implemented via `class`es
(see later) and provided by the following header files:

`<iostream>`
:   file input/output functions and classes,

`<vector>`
:   dynamic containers similar to arrays,

`<valarray>`
:   similar to `vector` but better suited for numerics,

`<limits>`
:   functions for determining type limits, e.g. minimal or maximal
    values,

`<map>`
:   associative array, e.g. indices are arbitrary types,

`<list>`
:   provides standard list and iterators,

`<complex>`
:   provides complex datatype,

etc.
: The specific classes and their usage will be discussed later.

---

# Modules and Namespaces
## Libraries without Headers
BLAS or LAPACK are written in Fortran and no header files exist for C++. Therefore, we will have to
write them ourselves. Consider

```fortran
 SUBROUTINE DGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT,
$                   WORK, LWORK, INFO )

 CHARACTER          JOBU, JOBVT
 INTEGER            INFO, LDA, LDU, LDVT, LWORK, M, N
 DOUBLE PRECISION   A( LDA, * ), S( * ), U( LDU, * ),
$                   VT( LDVT, * ), WORK( * )
```

To define a C++ function corresponding to the above Fortran function
the datatypes have to be mapped to C++ types. In Fortran, every
variable is provided as a **pointer**, hence:

<table>
<tr><td><code class="remark-inline-code">CHARACTER</td><td> \(\to\) <code class="remark-inline-code">char *</code></td></tr>
<tr><td><code class="remark-inline-code">INTEGER</td><td> \(\to\) <code class="remark-inline-code">int *</code></td></tr>
<tr><td><code class="remark-inline-code">DOUBLE PRECISION</td><td> \(\to\) <code class="remark-inline-code">double *</code></td></tr>
</table>

---

# Modules and Namespaces
## Libraries without Headers
Fortran function names are in *lower case* and end with and **underscore** `_`, when seen from
C or C++. Hence, the name of the above Fortran function is `dgesvd_`:

```c++
void dgesvd_ (char* jobu, char* jobv, int* n, int* m,
              double* A, int* lda, double* S, double* U,
              int* ldu, double* V, int* ldv, double* work,
              int* lwork, int* info);
```

Furthermore, there is a difference between C and C++ functions.
Fortran only provides C-style functions, whereas the above is a C++
function. To tell the compiler, that a C-style function should be
declared, the `extern "C"` instruction is provided:

```c++
extern "C" {
  void dgesvd_ (char* jobu, char* jobv, int* n, int* m,
                double* A, int* lda, double* S, double* U,
                int* ldu, double* V, int* ldv, double* work,
                int* lwork, int* info);
}
```

---

# Modules and Namespaces
## Libraries without Headers
Afterwards, the function `dgesvd_` can be used like any other C++
function. To compute the SVD \(M = U \cdot S \cdot V^T\) of a matrix \(M\),
the code looks like:

```c++
int       n     = 10;
double *  M     = new double[ n*n ];
char      jobu  = 'O';                // overwrite M with U
char      jobv  = 'S';                // store V^T in VT
int       info  = 0;
int       lwork = 10*n*n;
double *  work  = new double[ work ]; // workspace for dgesvd
double *  S     = new double[ n ];
double *  VT    = new double[ n*n ];

... // fill M

dgesvd_(&jobu, &jobv, &n, &n, M, &n, S, M, &n, V, &ldv,
        work, &lwork, &info);
```

---

# Modules and Namespaces
## Header File Recursion
The `#include` directive can be seen as simple text replacement: the directive is
replaced by the content of the corresponding file.

.pure-g[.pure-u-1-2[.padding-5[
```c++
#include "f.hh"

int main ()
{
  f(42, 3.1415926);
}
```
]].pure-u-1-2[.padding-5[
```c++
void f (int n, double f);

int main ()
{
  f(42, 3.1415926);
}
```
]]]

This might lead to infinite loops, if you have **recursive**
`#include` directives in different files, e.g., "file1.hh" includes "file2.hh",
which by itself includes "file1.hh".

.pure-g[.pure-u-1-2[.padding-5[
```c++
// FILE: file1.hh

#include "file2.hh"

...
```
]].pure-u-1-2[.padding-5[
```c++
// FILE: file2.hh

#include "file1.hh"

...
```
]]]

---

# Modules and Namespaces
## Header File Encapsulation - Include guards
To prevent infinite loops, two other directives are provided:

```c++
#ifndef <NAME>
#define <NAME>
...
#endif
```

tests, if the symbol `<NAME>` was previously defined by the `#define` directive

If it was not defined, all source code between the `#ifndef` directive and the corresponding
`#endif` will be included by the C++ compiler. Otherwise, the source code will be omitted.

> .h3[Remark:] It is recommended to name the symbol `<NAME>` after the
> name of the header file, e.g. `FILE_HH`.

---

# Modules and Namespaces
## Header File Encapsulation - Include guards
Now, for the recursive example:

.pure-g[.pure-u-1-2[.padding-5[
```c++
// FILE: file1.hh

#ifndef FILE1_HH
#define FILE1_HH

#include "file2.hh"

#endif // FILE1_HH
```
]].pure-u-1-2[.padding-5[
```c++
// FILE: file2.hh

#ifndef FILE2_HH
#define FILE2_HH

#include "file1.hh"

#endif // FILE2_HH
```
]]]

If "file1.hh" is included by a source file, the symbol "FILE1_HH"
will be defined and the content of the header file included. Similar,
`#include "file2.hh"` will be replaced by the
content of "file2.hh". If now again "file1.hh" should be included,
"FILE1_HH" is already defined and the content of "file1.hh" is
omitted, stopping the recursion.

---

# Modules and Namespaces
## Header File Encapsulation - Include guards

An alternative is the non-standard but widely used `#pragma one`:


.pure-g[.pure-u-1-2[.padding-5[
```c++
// FILE: file1.hh
#pragma once

#include "file2.hh"
```
]].pure-u-1-2[.padding-5[
```c++
// FILE: file2.hh
#pragma once

#include "file1.hh"
```
]]]

> .h3[Coding Principle:] Always encapsulate your header files by an
> `#ifndef`-`#define`-`#endif` construct or the `#pragma once` alternative.

---

# Modules and Namespaces
## Inline Functions
It is also possible to implement a function in a header file. In that case, it has to be declared
`inline`, because otherwise, the function is defined in each source file, where the header is
included. If you then compile all source files together, you would have multiple instances of
the same function, which is not allowed.

```c++
#ifndef SQUARE_HH
#define SQUARE_HH

inline double square (double const x)
{
  return x*x;
}

#endif // SQUARE_HH
```

---

# Modules and Namespaces
## Using Libraries

Remember from the beginning: when you have multiple source files (translation units), each one can
be compiled into an **object file**. Combining multiple object files results in:
1. An executable. Exactly one function `main(...)` must be available in the object files.
2. A *shared* or *static* library

--

**Libraries** contains compiled code that we may use in our executable. Therefore:
1. provide the correct function prototypes (declarations), by including the library header files,
2. link against the corresponding library. The linker then resolves the missing symbols similar to
   the resolution of symbols from multiple object files. Therefore, add the option `-l<lib>` and maybe
   additionally the library location `-L<dir>` to the compiler.

---

# Modules and Namespaces
## Example (Linking BLAS)

BLAS is provided as FORTRAN or C library. We are using the C library in the following:
```c++
#include <iostream>                             // clas.cc
#include <cblas.h>
int main () {
  int const N = 3;
  double A[N*N] = {1.0,0.0,0.0,  0.0,1.0,0.0,  0.0,0.0,1.0};
  double x[N] = {1.0,1.0,1.0};
  double y[N] = {};

  // y += 0.5*x
  cblas_daxpy(N, 0.5, x, 1, y, 1);
  // y += 0.5*A*x
  cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, 0.5, A, N, x, 1, 1.0, y, 1);
  // |y|_2
  double two_norm = cblas_dnrm2(N, y, 1);

  std::cout << two_norm << std::endl;
}
```

---

# Modules and Namespaces
## Example (Linking BLAS)

- Compiling the code with
```bash
c++ cblas.cc
```
results in the error:
```
in function `main':
cblas.cc:(.text+0xf5): undefined reference to `cblas_daxpy'
/usr/bin/ld: cblas.cc:(.text+0x144): undefined reference to `cblas_dgemv'
/usr/bin/ld: cblas.cc:(.text+0x16a): undefined reference to `cblas_dnrm2'
collect2: error: ld returned 1 exit status
```

--

- Thus, we have to link against the BLAS library to resolve the symbols
```bash
c++ cblas.cc -lblas
```

--

- If the library file `libblas.so` or `libblas.a` is located in a directory, e.g., `<blasdir>`, then
```bash
c++ cblas.cc <blasdir>/libblas.so   # or...
c++ cblas.cc -L<blasdir> -lblas
```

---

# Modules and Namespaces
## Outlook: Real Modules with C++20
With C++20 modules are introduced as replacement for `#include` directives. Instead of making a textual
inclusion of a whole file, with modules you can control which functions are actually exported. This
allows to hide implementation details:

```c++
// file: linalg.ccm
export module linalg;

void mat_vec_impl(double const alpha, int const m, int const m,
                  double const* A, double const* x, double* y)
{
  // implementation of the matrix-vector product with low-level data-structures
}

export
template <class mdspan_t, class span_t>
void mat_vec(mdspan_t A, span_t x, span_t y)
{
  mat_vec_impl(1.0, A.extent(0), A.extent(1), A.data(), x.data(), y.data());
}
```

---

# Modules and Namespaces
## Outlook: Real Modules with C++20
With C++20 modules are introduced as replacement for `#include` directives. Instead of making a textual
inclusion of a whole file, with modules you can control which functions are actually exported. This
allows to hide implementation details:

```c++
// file: linalg.cc

#include <mdspan>
#include <span>     // in the future: import std.span

import linalg;

int main () {
  int const N = 3;
  double A[N*N] = {1.0,0.0,0.0,  0.0,1.0,0.0,  0.0,0.0,1.0};
  double x[N] = {1.0,1.0,1.0};
  double y[N] = {};

  mat_vec(std::mdspan{A,N,N}, std::span{x,N}, std::span{y,N});
}
```

---

# Modules and Namespaces
## Outlook: Real Modules with C++20
With C++20 modules are introduced as replacement for `#include` directives. Instead of making a textual
inclusion of a whole file, with modules you can control which functions are actually exported. This
allows to hide implementation details:

```bash
clang++ --std=c++2a --precompile linalg.ccm -o linalg.pcm
clang++ --std=c++2a -c linalg.pcm -o linalg_mod.o
clang++ --std=c++2a -fprebuilt-module-path=. linalg_mod.o linalg.cc -o linalg
```

--

> .h3[Remark:] While modules are part of the C++20 standard, they are not yet available in all
> compilers. Also the standard library is not yet provided with module base. This will be part of
> future c++ standards.

---

# Modules and Namespaces
## Namespaces

Larger projects may contain many names (functions, classes, etc.)
- Should be organized into logical units
- Multiple types with the same name? E.g. different `Matrix` implementations. \(\to\) might lead to name clashes
- Using functions and types from other libraries may introduce the same names.

**Solution 1**
: rename all occurrences of your own types with a unique prefix. Example: `cblas_`

**Solution 2**
: put each type and function into a different **namespace**.

---

# Modules and Namespaces
## Namespaces
A `namespace` is a mechanism in C++ to group types, variables and
functions, thereby defining the scope of these objects, similar to a
block. Till now, all objects were in the *global* namespace.

### Namespace definitions
```c++
namespace <identifier> {
  <body>
}
```

- `<identifier>` may be a previously unused identifier, or the name of an existing namespace
- `<body>` may be a sequence of declarations
- A name declared inside a namespace must be qualified when accessed from outside the namespace
  using the *name-resolution operator* (`operator::`)

---

# Modules and Namespaces
## Namespaces - Example
Qualified name lookup:

```c++
namespace scprog
{
  // A data type
  struct DenseMatrix { ... };
  struct DenseVector { ... };         // (1)

  // A function declaration/definition
  double* make_vector (int n) {       // (2)
    DenseVector v; ...                // directly refers to (1)
  }
}

int main() {
  scprog::DenseMatrix mat;            // qualified name lookup

  auto vec = scprog::make_vector(10); // OK, calls (2)
  auto vec2 = make_vector(10);        // ERROR: make_vector was not declaraed in this scope
}
```

---

# Modules and Namespaces
## Nested Namespaces
It is possible to have *namespaces* inside *namespaces*:

```c++
namespace scprog {
  namespace linalg {
    // A data type
    struct DenseMatrix { ... };
  }
}

// equivalent: [c++17]
namespace scprog::linalg { ... }

void foo();

int main() {
  scprog::linalg::DenseMatrix mat;

  ::foo();    // qualified call to function from global namespace
}
```

---

# Modules and Namespaces
## Namespace - Using Directives and Aliases

- Always using fully qualified names makes code easier to read
- Sometimes it is obvious from which namespace the names come from in
  which case one prefers to use unqalified names
- For this `using` and `using namespace` can be used
  * `using namespace X` imports all names from *namespace* `X` into the current one
  * `using X::foo` only imports the name `foo` from `X` into the current namespace
- Restrict the usage of `using` to source files and avoid `using` directives in header files.
- You may use *namespace* aliases:

```c++
namespace X = Complicated::Long::Namespace;

Complicated::Long::Namespace::foo;
X::foo;
```

---

# Modules and Namespaces
## Namespace - Example

```c++
namespace A { int x; }
namespace B { int y; int z; }
using namespace A;

int main() {
  using B::y;
  x = 1; // Refers to A::x
  y = 2; // Refers to B::y
  z = 3; // ERROR: z was not declared in this scope
  B::z = 3; // OK
}
```

--

> .h3[Remark:] Don't use (global) variables inside namesapces.


---

# Modules and Namespaces
## The `std` Namespace
All functions (and classes) of the C++ standard library, e.g. `sqrt` or
`vector` are part of the `std` namespace.

```c++
const real_t  PI     = M_PI;              // constant defined in cmath header
const real_t  sqrtPI = std::sqrt(PI);

std::cout << sqrtPI << std::endl;
```

If `std` functions are used a lot, it can be helpful to include the namespace into a local scope:

```c++
using namespace std;

const real_t  PI     = M_PI;
const real_t  sqrtPI = sqrt(PI);

cout << sqrtPI << endl;
```

---

# Modules and Namespaces
## The `std` Namespace
All functions (and classes) of the C++ standard library, e.g. `sqrt` or
`vector` are part of the `std` namespace.

```c++
const real_t  PI     = M_PI;              // constant defined in cmath header
const real_t  sqrtPI = std::sqrt(PI);

std::cout << sqrtPI << std::endl;
```

Since this imports **all** names from the `std` namespace, it is recommended to only import those
names actually used.

```c++
using std::sqrt;
const real_t  PI     = M_PI;
const real_t  sqrtPI = sqrt(PI);

std::cout << sqrtPI << std::endl;
```