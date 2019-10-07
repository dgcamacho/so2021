# Exercise sheet 1 - 2019/10/16

There will be an exercise sheet every week with some exercises to be worked on during the tutorial and some to be
submitted for review. The submission procedure is briefly described on the lecture repository startpage

https://gitlab.mn.tu-dresden.de/teaching/scprog/wi2019

and follows the way of code submission in many (scientific) software projects. Thus, it is a good way of learning
and training collaborative coding.

Code submission and code storage is organized using the [Git](https://git-scm.com/) version control system and the data is hosted
at the MatNat GitLab platform. Access to this platform is established during the first weeks in the semester. Therefore,
you need to register to the tutorial part of the lecture in [selma](https://selma.tu-dresden.de).

Additionally to the submission of your own code, the exercise sheets and lecture notes are provided in this Git repository.

## Exercise 1 (Introduction to Linux command line)

## Exercise 2 (Compiling code)
**Submit solution until 2019/10/30**

In the directory [material/sheet1/](https://gitlab.mn.tu-dresden.de/teaching/scprog/wi2019/blob/master/material/sheet1) you can find
an initial C++ example in the files `exercise2_impl.cc`, `exercise2_impl.h`, and `exercise2.cc`. Download the files, compile the code:

```bash
g++ -std=c++14 -march=native -O3 -ffast-math -o exercise2 exercise2_impl.cc exercise2.cc
```

This creates a new file `exercise2` in the current directory. You can now run the example by

```bash
./exercise2
```

Familiarize yourself with the options passed to the compiler `g++`, i.e. `-std=c++14`, `-march=native`, `-O3`, `-ffast-math`, and `-o`. What are
the implications of these flags? Sometimes the option has an argument. Change the value (if meaningful), compile and run again.
What is the effect? What is the minimal necessary set of options to pass?

Document the output, results, and findings, write it into a file `solution.txt` or `solution.md` and commit into your repository. Follow the
instructions given in the `README.md` of this repository.

### Resources
You can find a documentation of the compiler arguments on
- [GCC manual](https://gcc.gnu.org/onlinedocs/gcc-9.2.0/gcc/)

## Exercise 3 (Basic debugging)
In the [material/sheet1/](https://gitlab.mn.tu-dresden.de/teaching/scprog/wi2019/blob/master/material/sheet1) directory, you can
find a second exercise code for this exercise sheet, i.e. the files `exercise3_impl.cc`, `exercise3_impl.h`, and `exercise3.cc`.
Download, compile, and run again. What happens? The code should produce an error.

In order to find the error(s), compile the code again, but this time with debug options `-Og -g` instead of `-O3 -ffast-math`,
and start the program in a debugger:

```bash
gdb ./exercise3
```

This will open a terminal program with a command line to enter GDB commands.

Some important commands, sufficient for this exercise, are:
- `run`  (or `r`) `<arguments>`: start the program with given arguments, if any
- `break` (or `b`) `<file:line, file:function>`: to set a breakpoint at specific location
- `backtrace` (or `bt`): show hierarchy of called functions
- `continue` (or `c`): continue running after break
- `next` (or `n`): execute marked line
- `print` (or `p`) `<expressions>`: print content of variable/object
- `step` (or `s`): enter first function on marked line
- `watch <expression>`: break if value of expression changes

Use GDB to locate, find, and correct the bugs in the provided source code. Document
which bugs you have found and how.

### Resources
- [GDB Documentation](https://www.gnu.org/software/gdb/documentation/)
- Cheet Sheets: [darkdust.net](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf),
  [kapeli.com](https://kapeli.com/cheat_sheets/GDB.docset/Contents/Resources/Documents/index),
  [utexas.edu](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)