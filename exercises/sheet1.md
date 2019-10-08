# Exercise sheet 1 - 2019/10/16

## Exercise 1 (Introduction to Linux command line)
This exercise serves as introduction to the Linux command line. If your are not yet familiar with
the Linux terminal, please perform the following tasks on your local machine:
- Open the terminal
- Change to the `Desktop` directory
- Create a new directory `scprog`
- List files and directories on the `Desktop`
- Create a new file `exercise1.txt` on the `Desktop` directory with the line "Hello World"
- Copy the file `exercise1.txt` to the directory `scprog`
- Delete the remaining .txt file on the `Desktop`
- Change back to your home directory
- Find all files in the `Desktop` directory recursively containing the text "Hello"
- Edit the file `Desktop/scprog/exercise1.txt` and replace the word "World" by "Dresden"

You might need the following commands: `cat`, `cd`, `cp`, `echo`, `find`, `grep`, `ls`, `rm`, `sed`, `vim`. Familiarize yourself with
the commands, using the references given below or any other (online) resource and find out about possible arguments to the
commands that could be useful.

Create your own *cheat sheet* as Markdown `.md` file and store it in the `scprog` directory.

### Resources
- [Tutorial](https://tutorials.ubuntu.com/tutorial/command-line-for-beginners)
- [Divhints](https://devhints.io/), [Cheet Sheet](https://appletree.or.kr/quick_reference_cards/Unix-Linux/Linux%20Command%20Line%20Cheat%20Sheet.pdf)
- [Markdown](https://daringfireball.net/projects/markdown/), [Markdown @ GitLab](https://docs.gitlab.com/ee/user/markdown.html)


## Exercise 2 (Compiling code)
**>> Submit solution until 2019/10/30**

In the directory [material/sheet1/](/exercises/material/sheet1) you can find
an initial C++ example in the files `exercise2_impl.cc`, `exercise2_impl.h`, and `exercise2.cc`. Download the files and compile the code:

```bash
g++-7 -std=c++14 -Wall -O2 -I/usr/include/amdis/mtl4 -c exercise2_impl.cc
g++-7 -std=c++14 -Wall -O2 -I/usr/include/amdis/mtl4 -c exercise2.cc
g++-7 -o exercise2 exercise2_impl.o exercise2.o
```

This creates a new file `exercise2` in the current directory. You can now run the example by

```bash
./exercise2
```

Familiarize yourself with the options passed to the compiler `g++`, i.e. `-std=c++14`, `-Wall`, `-O2`, `-I`, `-c`, and `-o`. What are
the implications of these flags? Sometimes the option has an argument. Change the value (if meaningful), compile and run again.
What is the effect? What is the minimal necessary set of options to pass?

Document the output, results, and findings, write it into a file `solution.txt` or `solution.md` and commit into your repository. Follow the
instructions given in the [README.md](/README.md) of this repository.

### Resources
You can find a documentation of the compiler arguments on
- [GCC manual](https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/)


## Exercise 3 (Basic debugging)
**>> Submit solution until 2019/10/30**

In the [material/sheet1/](/exercises/material/sheet1) directory, you can
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