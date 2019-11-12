# Compiling code
The compiler translates code from one language into another language, typically a high-level language to (close to) machine code.
There are multiple different compilers that have different command-line parameters, but all have in common some (categories of)
arguments:
- compiling/linking/output
- choice of the c++ standard
- warning flags
- optimization flags
- include path handling
- linking flags

The compiler `g++` is from the family `GCC` - the GNU compiler collection. `clang` has very similar flags than `g++`, whereas the
Microsoft Visual C++ compiler `VC` is quite different.

You can find a documentation of all the argument by inspecting the manual pages:
```bash
man g++
```

The compiling happens in two phases (here described in a simplified way)
1. Translation (individual translation units are transformed into object files / libraries)
2. Linking (libraries and object files are combined into a single executable)

## Documentation of the options

This documentation is copied from the man pages of g++.

- Compiling C++ Programs:
  C++ source files conventionally use one of the suffixes `.C`, `.cc`, `.cpp`, `.CPP`, `.c++`, `.cp`, or `.cxx`; C++ header files
  often use  `.hh`, `.hpp`, `.H`, or (for shared template code) `.tcc`; and preprocessed C++ files use the suffix `.ii`. GCC recognizes
  files with these names and compiles them as C++ programs even if you call the compiler the same way as for compiling C programs
  (usually with the name gcc).

  However, the use of gcc does not add the C++ library.  g++ is a program that calls GCC and automatically specifies linking against the
  C++ library.  It treats `.c`, `.h` and `.i` files as C++ source files instead of C source files unless `-x` is used.  This program is
  also useful when precompiling a C header file with a `.h` extension for use in C++ compilations.  On many systems, g++ is also installed
  with the name c++.

- `-c`:
  Compile or assemble the source files, but do not link.  The linking stage simply is not done.  The ultimate output is in the form
  of an object file for each source file.

  By default, the object file name for a source file is made by replacing the suffix `.cc`, `.cxx`, `.cpp`, etc., with `.o`.

  Unrecognized input files, not requiring compilation or assembly, are ignored.

- `-o FILE`:
  Place output in file file.  This applies to whatever sort of output is being produced, whether it be an executable file, an object
  file, an assembler file or preprocessed C code.

  If `-o` is not specified, the default is to put an executable file in `a.out`, the object file for `source.suffix` in `source.o`, its
  assembler file in `source.s`, a precompiled header file in `source.suffix.gch`, and all preprocessed C source on standard output.

- `-std=`:
  Determine the language standard.   This option is currently only supported when compiling C or C++.

    * `c++98`, `c++03`:
      The 1998 ISO C++ standard plus the 2003 technical corrigendum and some additional defect reports. Same as -ansi for C++ code.
    * `c++11`, `c++0x`:
      The 2011 ISO C++ standard plus amendments.  The name `c++0x` is deprecated.
    * `c++14`, `c++1y`:
      The 2014 ISO C++ standard plus amendments.  The name `c++1y` is deprecated.
    * `c++1z`:
      The next revision of the ISO C++ standard, tentatively planned for 2017.  Support is highly experimental, and will almost certainly
      change in incompatible ways in future releases.
    * `gnu++XYZ`:
      GNU dialect of `-std=c++XYZ`.

  (This is for g++ 7.3, more recent versions support the standards `c++17` and `c++2a` for the c++2017 standard and the upcomming c++2020
  standard)

- `-W`:
  Warnings are diagnostic messages that report constructions that are not inherently erroneous but that are risky or suggest there may have
  been an error.

    * `-fsyntax-only`:
      Check the code for syntax errors, but don't do anything beyond that.
    * `-w`:
      Inhibit all warning messages.
    * `-Werror`:
      Make all warnings into errors.
    * `-Wpedantic`, `-pedantic`:
      Issue all the warnings demanded by strict ISO C and ISO C++.
    * `-Wall`:
      This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to
      prevent the warning), even in conjunction with macros.
    * `-Wextra`:
      This enables some extra warning flags that are not enabled by `-Wall`.

  I recommend to always activate at least `-pedantic -Wall`.

- `-g`:
  Produce debugging information in the operating system's native format.  GDB can work with this debugging information.

- `-O`:
  These options control various sorts of optimizations.

  Without any optimization option, the compiler's goal is to reduce the cost of compilation and to make debugging produce the expected
  results.  Statements are independent: if you stop the program with a breakpoint between statements, you can then assign a new value to
  any variable or change the program counter to any other statement in the function and get exactly the results you expect from the source
  code.

  Turning on optimization flags makes the compiler attempt to improve the performance and/or code size at the expense of compilation time
  and possibly the ability to debug the program.

  The compiler performs optimization based on the knowledge it has of the program.  Compiling multiple files at once to a single output file
  mode allows the compiler to use information gained from all of the files when compiling each of them.

    * `-O0` Reduce compilation time and make debugging produce the expected results.  This is the default.
    * `-O`, `-O1`:
      Optimize.  Optimizing compilation takes somewhat more time, and a lot more memory for a large function.

      With `-O`, the compiler tries to reduce code size and execution time, without performing any optimizations that take a great deal of
      compilation time.
    * `-O2`:
      Optimize even more.  GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.  As compared to `-O`,
      this option increases both compilation time and the performance of the generated code.
    * `-O3`: Optimize yet more.
    * `-Os`: Optimize for size.
    * `-Ofast`:
      Disregard strict standards compliance. `-Ofast` enables all `-O3` optimizations.  It also enables optimizations that are not valid
      for all standard-compliant programs.
    * `-Og`:
      Optimize debugging experience.  `-Og` enables optimizations that do not interfere with debugging. It should be the optimization level
      of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation
      and a good debugging experience.

## Output of the code
Compile the code with
```
g++[-7] -std=c++14 -Wall -O2 -c linear_algebra.cc
g++[-7] -std=c++14 -Wall -O2 -c exercise2.cc
g++[-7] -o exercise2 linear_algebra.o exercise2.o
```
where the version number `-7` is only necessary if you want to choose a specific version of g++.

The output of `./exercise2` is:
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

Simple timing `time ./exercise2` gives the information
```
real  0m0.565s
user  0m0.540s
sys   0m0.024s
```

where
- `real`: Elapsed real (wall clock) time used by the process
- `user`: Total number of CPU-seconds that the process used directly (in user mode), in seconds.
- `sys`: Total number of CPU-seconds used by the system on behalf of the process (in kernel mode), in seconds.

For me the user time here is the most interesting.

Recompile with `-O0` instead of `-O2` gives: `user	0m10.221s` and `-Ofast` instead of `-O2`: `user	0m0.545s`, so, nearly the same as before.

The minimal standard that is required is: c++11, because some includes of c++11 are used. Thus, the minimal compile command is
```
g++[-7] linear_algebra.cc exercise2.cc
```
it produces an output `a.out` without any optimization (level `-O0`), compiles and links directly. The G++-7 compiler has as standard c++ version
c++14 already set.