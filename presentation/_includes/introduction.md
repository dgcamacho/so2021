
---
class: middle

> .h3[Scott Meyers (2014):] If you’re not at all interested in performance, shouldn’t you
> be in the Python room down the hall?

---

# Scientific Programming with C++

## What is Scientific Programming?
- Efficient code for scientific applications in Mathematics, Biology, Physics,...
- (High-performance) computing on CPUs, GPUs and other processors
- Requires knowledge about computer arithmetics, numerics and software development
- Analysis of performance, test for accuracy, validation of results

--

## Why C++?
- *Matlab* / *Python* high-level languages for fast prototyping
- Highly efficient numerical libraries written in Fortran/C/C++
- Low-level programming language for fine control about data and processing
- Multi-paradigm development: OOP, Generic, Functional, Meta-programming,...
- Standardized, industry ready programming language

---
class: middle

> .h3[Bjarne Stroustrup (1994):] It would be nice if every kind of numeric software
> could be written in C++ without loss of efficiency, but unless something can be
> found that achieves this without compromising the C++ type system it may be
> preferable to rely on Fortran, Assembler or architecture-specific extensions.

<br>

.opacity-10[
> .h3[Todd L. Veldhuizen (2000):] C++ is now ready to compete with the performance
> of Fortran. Its performance problems have been solved by a combination of better
> optimizing compilers and template techniques. It's possible that C++ will be
> faster than Fortran for some applications.
]

---
class: middle

> .h3[Bjarne Stroustrup (1994)]: It would be nice if every kind of numeric software
> could be written in C++ without loss of efficiency, but unless something can be
> found that achieves this without compromising the C++ type system it may be
> preferable to rely on Fortran, Assembler or architecture-specific extensions.

<br>

> .h3[Todd L. Veldhuizen (2000)]: C++ is now ready to compete with the performance
> of Fortran. Its performance problems have been solved by a combination of better
> optimizing compilers and template techniques. It's possible that C++ will be
> faster than Fortran for some applications.

---

# Scientific Programming with C++

## About me
- Diploma (2011) and PhD (2015) in Mathematics @ TU-Dresden
- Specialization in Numerics and Scientific Computing
- Core software developer in [AMDiS](https://gitlab.mn.tu-dresden.de/amdis) and [Dune](https://dune-project.org)
- Contributions in multiple open-source projects, e.g., MTL4, Scotch, meshconv,...
- Programming with C++ for > 10 years
- Love Open-Source, cooking, guitar and piano playing

Reach me via [@praetori:tu-dresden.de](https://matrix.tu-dresden.de/#/room/@praetori:tu-dresden.de)
on matrix.

### List of projects
- https://gitlab.mn.tu-dresden.de/spraetor
- https://github.com/spraetor

---

# Scientific Programming with C++

## About this Course
- **Lecture** on Tuesdays, 16:40 - 18:10, **Tutorial** Wednesday, 13:00 - 14:30
- Course on OPAL: [t1p.de/scprog-so2021-opal](https://t1p.de/scprog-so2021-opal)
- Course in matrix: [#scprog-so2021:tu-dresden.de](https://matrix.tu-dresden.de/#/room/#scprog-so2021:tu-dresden.de)
- **Requirement:** Sign up for this course in OPAL (and in Selma for the exam)

### Exercises
- Weekly, see [gitlab.mn.tu-dresden.de/teaching/scprog/so2021-tutorial](https://gitlab.mn.tu-dresden.de/teaching/scprog/so2021-tutorial)
- Some exercises can be submitted (marked explicitly). **Not** mandatory.
- Submitted exercises get reviewed. **No** extra credit for the exam.
- Write code! Read code! Perform review of code!
- Submission to *Git* platform \(\rightarrow\) you get an account to GitLab, explained in first tutorial.

---

# Scientific Programming with C++

## About this Course
### Lecture material and literature
- Sources of lecture notes and presentation uploaded weekly to git platform:
  [gitlab.mn.tu-dresden.de/teaching/scprog/so2021](https://gitlab.mn.tu-dresden.de/teaching/scprog/so2021)
  * Contributions are very welcome
- Lecture is based on C++ lecture by Peter Gottschling, and
  * *Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers*, Peter Gottschling (2016)
    [english](https://katalog.slub-dresden.de/id/0-168021375X), [german](https://katalog.slub-dresden.de/id/0-1664569537)
- Short and compact introduction to the C++ basics:
  * *C++ - kurz & gut* (german), Kyle Loudon and Rainer Grimm (2018) [slub](https://katalog.slub-dresden.de/id/0-1680134132)
  * *C++ Primer*, Stanley Lippman, Josee Lajoie, and Barbara E. Moo (2013) [slub](https://katalog.slub-dresden.de/id/0-1680337130)

---

# Introductory Example

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

-   C++ is a compiler based language:
    * Translate the source code into a machine executable format \(\rightarrow\) **compiler**
    * Examples: *g++*, *clang*, *MSVC*.
-   Source code files, or just *source files*, typically have a filename
    suffix `.cc`, `.cxx`, or `.cpp` and build **translation units**.
-   Output of the compiler: collection of **object files**, suffix `.o`
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
- `main()` returns a status code: `0` means no error.
- Comments start with `//` and span the rest of the line.
- Multi-line comments: `/* ... */`