# Basic debugging
Compiling the code with
```
g++ -O0 -g -o exercise3 linear_algebra.cc exercise3.cc
```
and running the executable with `./exercise3` results in the output
```
exercise3: linear_algebra.cc:179: void scprog::DenseMatrix::mult(const scprog::DenseVector&, scprog::DenseVector&) const: Assertion `x.size() == cols()' failed.
Aborted (core dumped)
```

(This might look slightly different on your system.)

We can see here already that there is an error in the function `mult()` of the type `DenseMatrix` and is related to the problem that some sizes do not match.

First thing you could do, if you have the source code, look into the file `inear_algebra.cc` at line `179` to get a better understanding of the error message.
```c++
// computes the matrix-vector product, y = Ax.
void DenseMatrix::mult(DenseVector const& x, DenseVector& y) const
{
  assert(x.size() == cols()); //< line 179
  assert(y.size() == rows());
  for (size_type r = 0; r < rows(); ++r) {
    y[r] = value_type(0);
    value_type const* row = (*this)[r];
    for (size_type c = 0; c < cols(); ++c)
      y[r] += row[c]*x[c];
  }
}
```
So, this function computes a matrix * vector product, with `x` is the input vector and `y` is the output vector. And the size of the input vector `x`
should be the same as the number of columns in the matrix `cols()`. So, either the matrix has wrong size, or the vector has wrong size. Let's find out
what is the input vector and what is the matrix, i.e. where these objects are created.

Therefore, one could use a debugger, like GDB
```
gdb ./exercise3
```

## Debugging with GDB
When starting the debugger GDB, after some text you get the information:
```
Reading symbols from ./exercise3...done.
```
This refers to *debug symbols* in the executable. If you compile your code without `-g` you will get the information *"No debugging symbols found"*.
The next line introduces a command terminal in the program GDB:
```
(gdb)
```
and you can start typing debugger commands.

- First the program should be run: `r` or `run`. The result is the same error, but with some extra information:
```
Program received signal SIGABRT, Aborted.
__GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:51
51	../sysdeps/unix/sysv/linux/raise.c: No such file or directory.
```
  The program is aborted due to some interrupt signal from a function defined somewhere in a system code `raise.c`. This is not so interesting for us.
  What we want to know is where this error came from starting from the beginning of the program. This is referred to as stack trace.

- Call `bt` or `backtrace` to show the hierarchy of called functions:
```
(...)
#4  0x00000000004014b8 in scprog::DenseMatrix::mult (this=this@entry=0x7fffffff8340, x=..., y=...) at linear_algebra.cc:179
#5  0x0000000000401666 in scprog::operator* (A=..., x=...) at linear_algebra.cc:171
#6  0x0000000000401eb9 in scprog::cg (A=..., x=..., b=..., iter=...) at linear_algebra.cc:309
#7  0x0000000000402f3b in main (argc=<optimized out>, argv=<optimized out>) at exercise3.cc:23
```
  So, it shows us a position in the stack, the function name and the source-code file and line.

  We could now easily follow the functions and arguments to see that the `A` and `x` passed to `mult()` are actually the same `A` and `x` as passed
  to the function `cg()` and thus refer to the variables `A` and `x` in the `main()`. This same naming is just a coincidence. Variable names are
  not fixed to function parameter names.

- What is wrong with the sizes? Therefore, 1. kill the process, 2. set a breakpoint in the line of the error, 3. inspect the variables:
```
(gdb) kill
Kill the program being debugged? (y or n) y
(gdb) break exercise3.cc:23
Breakpoint 2 at 0x402f1e: file exercise3.cc, line 23.
(gdb) run
23	  int err = cg(A, x, b, iter);
(gdb) print A
$1 = {data_ = {...}, rows_ = 2500, cols_ = 2500}
(gdb) print x.size()
$2 = 50
```
  Note: in some environments, the command `print x` will give you also the size of the vector, in other environments not. The function `x.size()` is only
  available if optimization is turned off completely, i.e. with option `-O0`. You could also ask for `A.cols()` in that case.

  So, the result is: the number of rows and columns of the matrix is each square the number of entries in the vector. In line 14 the matrix is created and in
  line 17 of exercise3.cc the vector x is created. Both use the size information `n` as argument, but the matrix is created, using the function `laplacian_setup()`.
  The documentation in `linear_algebra.hh:277` says:
```c++
/// Setup a matrix according to a Laplacian equation on a 2D-grid using a five-point-stencil.
/// Results in a matrix A of size (m*n) x (m*n)
void laplacian_setup(DenseMatrix& A, std::size_t m, std::size_t n);
```
  So, the arguments do not have the meaning of number of rows and number of columns, but grid points in 1 direction of a 2d finite-difference grid. Thus, the
  resulting matrix size is `n*n` and thus the vector(s) must be resized similarly. `-->` change line 17 to `DenseVector x(n*n);`

- Compiling and running again raises the next error:
```
exercise3: linear_algebra.cc:28: scprog::DenseVector& scprog::DenseVector::operator-=(const scprog::DenseVector&): Assertion `size() == that.size()' failed.
Aborted (core dumped)
```
  that is of similar nature and can be found as above.  `-->` change line 10 to `DenseVector b(n*n, 1.0);`

- Compiling and running again raises the next error:
```
iteration 0: resid 50
finished! error code = 1
0 iterations
50 is actual final residual.
1 is actual relative tolerance achieved.
Relative tol: 1e-06  Absolute tol: 0
Convergence:  1
ERROR: Linear system could not be solved.
       |b-A*x| = 50, |b-A*x|/|b| = 1
Aborted (core dumped)
```
  This is now of different nature. It is a meaningful error message: "Linear system could not be solved". Inspecting the output gives already the idea:
  there are no iterations performed in the cg method.

  The solution to this problem is to read the documentation in `linear_Algebra:459`:
```c++
/// Apply the conjugate gradient algorithm to the linear system A*x = b and return an error code
/**
  * \param A  The system matrix
  * \param x  The solution vector. Must be of correct size.
  * \param b  The load vector of the linear system
  * \param iter  An iteration object controlling number of iterations and break tolerances.
  *
  * \return The error code of the \ref BasicIteration object. err=0 means no error.
  **/
int cg(DenseMatrix const& A, DenseVector& x, DenseVector const& b, BasicIteration& iter);
```
  So, the iteration object `BasicIteration` control the number of iterations to perform. So, look up the documentation of `linear_algebra:297`:
```c++
/// Constructor
/**
  * \param r0        initial residual r0 = b - A*x
  * \param max_iter  the maximal number of solver iterations
  * \param rtol      relative tolerance: |b - A*x| < rtol * |r0|
  * \param atol      absolute tolerance: |b - A*x| < atol
  * \param cycle     the print cycle of the solver iterations
  **/
template <class Vector>
BasicIteration(Vector const& r0, int max_iter, real_type rtol, real_type atol = real_type(0), int cycle = 100)
```
  The second argument is the number of solver iteration.

  In `exercise3.cc:20` this iteration object is created. `-->` change line 20 to `BasicIteration iter(b, 100, 1.e-6, 0, 10);` to
  get the final successful output
```
iteration 0: resid 50
iteration 10: resid 134.623
iteration 20: resid 72.458
iteration 30: resid 22.7491
iteration 40: resid 2.48896
iteration 50: resid 0.509456
iteration 60: resid 0.0418141
iteration 70: resid 0.00130868
finished! error code = 0
79 iterations
4.81968e-05 is actual final residual.
9.63936e-07 is actual relative tolerance achieved.
Relative tol: 1e-06  Absolute tol: 0
Convergence:  0.839168
```
