---
class: center, middle
# Introduction
---

# Scientific Programming with C++

## What is Scientific Programming?
- Efficient code for scientific application in Mathematics, Biology, Physics,...
- (High-performance) computing on CPUs, GPUs and other processors
- Requires knowledge about computer arithmetics, numerics and software development
- Analysis of performance, test for accuracy, provide type-safety

--

## Why C++?
- *Matlab* / *Python* high-level languages for fast prototyping
- Highly efficient numerical libraries written in C++
- Low-level programming language for fine control about data and processing
- Multi-paradigm development: OOP, Generic, Functional, Meta-programming,...
- Standardized, industry ready programming language

---

# Introductory example

.pure-g[.pure-u-14-24[
```c++
#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>

using namespace mtl;

int main(int argc, char** argv)
{
  int const size = 40, N = size * size;
  using matrix_t = compressed2D<double>;

  // Set up a matrix 1,600 x 1,600 with
  // 5-point-stencil
  matrix_t A{N, N};
  mat::laplacian_setup(A, size, size);

  // Compute b = A*x with x == 1
  dense_vector<double> x{N, 1.0}, b;
  b = A * x;

  std::cout << two_norm(b) << std::endl;
}
```
].pure-u-10-24[.gutter-64[
Even this small example contains:
- `modules` and `namespaces`,
- `functions` and `blocks`,
- `variables` and `types`,
- `classes` and `templates`
]]]

---

# Compiling C++ Code

-   C++ is a compiler based language, i.e., one has to translate the source
    code of the program into a machine executable format using another
    program, called the **compiler**. Examples: *g++*, *clang*, *MSVC*.
-   Source code files, or just *source files*, typically have a filename
    suffix like `.cc`, `.cxx`, or `.cpp` and build **translation units**.
-   Output of the compiler: collection of **object files**.
-   Executable generated, by combining object files and libraries by **linker**.

--

## Example
Source file `mat_vec.cc` compiled into executable `mat_vec`:

```
  c++ [options...] mat_vec.cc [-o mat_vec]
```

and afterwards run the program via `./mat_vec`.

---

# Entry-point into a C++ program

```c++
int main();
int main(int argc, char* argv[]); // or int main(argc, char** argv)
```

- Each C++ program must contain exactly one `main(...)` function, while both variants are allowed.
- Argument `argc` will be filled with number of command-line parameters and `argv` with character
  arrays (strings) of the command-line parameters.
- First parameter `argv[0]` contains name of the executed program.
- Returns a status code: `0` means no error.
- Comments start with `//` and span the rest of the line.
- Multi-line comments: `/* ... */`