# Scientific Programming with C++

## Lecture notes

| Topic                                  | Download                 |
|----------------------------------------|--------------------------|
| Scientific Programming with C++        | [lecture.pdf][]          |

[lecture.pdf]: https://gitlab.mn.tu-dresden.de/teaching/scprog/so2021/-/jobs/artifacts/master/raw/lecture/lecture.pdf?job=build


## Exercise sheets

| Week | Topic                                  | Download        |
|------|----------------------------------------|-----------------|
| 01   | Overview and Motivation for the Course | [sheet01.pdf][] |
| 02   | Basic Syntax and Types                 | [sheet02.pdf][] |

[sheet01.pdf]: https://gitlab.mn.tu-dresden.de/teaching/scprog_java/wi2020/-/jobs/artifacts/master/raw/exercises/sheet01.pdf?job=build


## General information

*Summary of the lecture*

*general information about the structure of lecture and tutorial*


In this module SCPROG the exercises and projects will be submitted online into a version
control system [Git](https://git-scm.com/) hosted at the MatNat [GitLab](https://gitlab.mn.tu-dresden.de)
platform, which is a web-based Git repository manager similar to [GitHub](https://github.com)
and [Bitbucket](https://bitbucket.org).

Handing in solutions to exercises and projects digitally on such a platform is a
good way of learning and training collaborative coding, which is commonplace in
Scientific Computing research groups.

Additionally to the learning effect, you can collect points for submitted exercises
that may eventually lead to an improvement in you final exam by at most a grade 0.3. To
reach this bonus, you have to gain 66% of the possible exercise points (max. = 100).

In order to allow fast correction and evaluation of submitted solutions, we require
a predefined structure of the repositories and coding styles to be followed. Not
following these rules for repositories may result in your solution not being reviewed.
You will then have to reformat it and submit again. Not following the style guidelines
may result in point deduction, with the amount of points depending on the impact your
style could have on actual collaborative projects.

# Your Repository on GitLab
## Account
In the first tutorial we will create an account on the local GitLab platform,
using the ZIH-Login (s...-number) for the account user name associated to your TU-Dresden
email address. This ensures that you will get credit for your submissions.

## Project Name
Please form groups of up to two members and exchange contact details so you can find
each other on GitLab. One of you should create a *private* (!) project, and invite the rest
of the group. The name of your project is `scprog-Name1Name2`, where `Name1`
is the last name of the first student, `Name2` that of the second student. These
names should be sorted alphabetically. If your lineup changes for any reason during the
course of the semester, please create a new project that reflects this and inform your
tutors.

## Directory Structure
Your repository should consist of two levels of directories, one for the exercise sheets and
one for the individual exercises. This results in a tree structure like this:

```
sheet1
 +-- exercise1
 |    +-- main.cc
 |    +-- solution.txt
 |    \-- <header and source files>
 |
 +-- exercise2
 |    \-- <files as above>
 |
 \-- (...)

sheet2
 +-- exercise1
 +-- exercise2
 \-- (...)

(...)
```

You are free to name and structure your C++ files in any way you like, but there
should always be a file named `main.cc` that is a sample application of your implemented
classes. Often the content is given in the exercise, if it isn’t you are free to choose
sensible test cases yourselves. Make sure that this file `main.cc` can be compiled with
the command given in the lecture, or alternatively provide a [MakeFile](http://www.c-howto.de/tutorial/makefiles/)
or [CMakeLists.txt](https://cmake.org/cmake/help/latest/) that builds the exercise.

The file `solution.txt` is meant for the output of your `main.cc` and for answering
questions that appear in the exercises. If an exercise is of theoretical nature and doesn’t
include actual coding, this is the only file you have to submit. Optionally you can
submit a [Markdown](https://docs.gitlab.com/ee/user/markdown.html) file `solution.md`
instead. This allows basic formatting of the text.

## Access to the Repository
Please give your tutor @spraetor write access (at least Reporter status) to your project so that
your submissions can be graded.

# Submission of Exercises
On each exercise sheet some exercises are marked for submission with in sum 10 possible exercise points.
You have approximately two weeks for each of these exercises, where the final date is written
next to the exercise. In order to get your solutions reviewed, it has to be committed to your
GitLab repository following the procedure:

1. For each exercise sheet create a new branch called `sheetX` where `X` is the number of
   the sheet.
2. Create the new directory following the directory structure as above
3. Commit your solutions to the branch
4. Create a merge request to your master branch

After final review of your submission (and maybe inclusion of your corrections)
you get a comment in the MergeRequest section of GitLab and a :thumbsup:. This allows you to merge
your branch into your `master` branch.


# Style Guidelines
All programs you submit should follow basic programming rules like the following:

- **Formatting**
  - Put each instruction on a separate line (two lines if it is very large)
  - Use spaces to separate variable names, functions and operators
  - Indent your lines to visually mark different lines belonging to different scopes
- **Variable names**
  - The name should reflect the purpose of the variable
  - Variable names start with a lowercase letter, types with an uppercase letter
  - The rest of the name format for identifiers is up to you
  - Simple counting integers and similar variables are exceptions
- **Comments**
  - Comments allow others to understand your intentions
  - Tutors can only give you points if they understand what you were trying to do
  - *Guideline:* one comment per class, per function, per algorithm subtask, per tricky or "exotic" source line
  - Don't comment to much either, this may visually drown the actual code or diverge from what is actually coded (!)
  - Leave out trivial comments ("This is the constructor")
- **Language constructs**
  - You may use any construct you want, even if it has not yet been introduced in the lecture
  - Avoid constructs that have been superseded by better alternatives in the lecture
  - Declare variables and references as `const` where it is possible
  - Separate interface and implementation by correctly using public and private
  - Use smart pointers instead of raw pointers once the lecture has introduced them

Optionally, see [Google C++ Style Guide](http://google.github.io/styleguide/cppguide.html) for
more rules and guidelines on the coding style. Also, see the
[C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
for a comprehensive list of best practice programming rules for C++.

# More reading
Online references and literature useful for completing the exercises are listed below:

- **Online-References:**
  - [cppreference.com](http://en.cppreference.com), [BLAS](http://www.netlib.org/blas),
    [LAPACK](http://www.netlib.org/lapack/), [DUNE](https://www.dune-project.org/doxygen/),
    [Git](https://git-scm.com/docs), [Boost](https://www.boost.org/doc/libs/1_71_0/),
    [CMake](https://cmake.org/cmake/help/latest/)
- **Cheat-sheets:**
  - [Divhints](https://devhints.io/), [Git](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf),
    [Linux Command Line](https://appletree.or.kr/quick_reference_cards/Unix-Linux/Linux%20Command%20Line%20Cheat%20Sheet.pdf)
- **Tutorials:**
  - [MTL4](http://old.simunova.com/docs/mtl4/html/tutorial.html), [Git](https://git-scm.com/book/en/v2)
- **Compiler:**
  - [GCC](https://gcc.gnu.org/), [Clang](http://clang.llvm.org/), [Intel Icc](https://software.intel.com/en-us/c-compilers)
- **Books:**
  - Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers, Peter Gottschling, 2015:
    [slub](http://katalogbeta.slub-dresden.de/id/0017278767/#detail), [online](http://proquest.tech.safaribooksonline.de/9780134383682)
  - *References:* Die C++ Programmiersprache (Bjarne Stroustrup),
    C++ Kurz & Gut (Kyle Loudon, Rainer Grimm): [slub](http://katalogbeta.slub-dresden.de/id/0012713756/#detail)
  - *Beginners:* C++ Primer (Stanley Lippman, Josee Lajoie, Barbara E. Moo): [online](http://proquest.tech.safaribooksonline.de/9780133053043)
  - *Intermediate level:* Effective Modern C++ (Scott Meyers): [slub](http://katalogbeta.slub-dresden.de/id/0013617247/#detail), [online](http://proquest.tech.safaribooksonline.de/9781491908419),
    C++ Templates: The Complete Guide (David Vandevoorde, Nicolai M. Josuttis): [online](http://proquest.tech.safaribooksonline.de/0201734842)
  - *Experts:* Modern C++ Design (Andrei Alexandrescu): [online](http://proquest.tech.safaribooksonline.de/0201704315),
    C++ Template Metaprogramming (David Abrahams, Aleksey Gurovoy): [online](http://proquest.tech.safaribooksonline.de/0321227255)
