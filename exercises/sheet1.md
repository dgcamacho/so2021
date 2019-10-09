# Exercise sheet 1 - 2019/10/16

## Exercise 0 (Introduction to Linux command line)
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
- What does the following command do: `du -s * | sort -nr > $HOME/user_space_report.txt` ?

You might need the following commands: `cat`, `cd`, `cp`, `du`, `echo`, `find`, `grep`, `ls`, `rm`, `sed`, `vim`.
Most of the commands support provide a usage help by `<command> --help`. Familiarize yourself with
the commands, using the references given below or any other (online) resource and find out about possible arguments to the
commands that could be useful.

Create your own *cheat sheet* as Markdown `.md` file and store it in the `scprog` directory.

### Resources
- [Tutorial](https://tutorials.ubuntu.com/tutorial/command-line-for-beginners)
- [Divhints](https://devhints.io/), [Cheat Sheet](https://appletree.or.kr/quick_reference_cards/Unix-Linux/Linux%20Command%20Line%20Cheat%20Sheet.pdf)
- [Markdown](https://daringfireball.net/projects/markdown/), [Markdown@GitLab](https://docs.gitlab.com/ee/user/markdown.html)


## Exercise 1 (Introduction to Git)
This exercise serves as an introduction to [Git](https://www.git-scm.com/) and [GitLab](https://gitlab.mn.tu-dresden.de).
Please perform the following tasks in a private repository. Below the lists of tasks is a list of
Git commands that might be useful.

Perform the following tasks, and document which Git command you have used, briefly describing
its purpose:
- Create a new folder on your computer, and *initialize* a new Git repository inside.
- Put a text file into the repository (its contents don't matter, you could take one of the source
  files of the lecture), *add* it to the files tracked by Git, and *commit* your changes to the repository,
  using a meaningful commit message.
- Check that your commit was successful by reading the *log* file, and take a look at the status of
  your working directory.
- Change something in the text file, *add* and *commit* those changes, assume you had made a mistake,
  and *revert* your commit (note that `git revert` is not the right command in this situation).
- Edit the file a second time, but *stash* your changes away to keep them save for using them at
  some later point in time.

Create a GitLab account by providing your Name, ZIH s-number, and **TU-Dresden!** email-address to the tutor.
You will receive an email to set your password and activate your account.
In GitLab, find the "Projects" tab and press the "New Project" button. Enter a project name and set visibility to
private. Follow the instructions under "Git global setup" and "Existing Git repository" to get your
private project repository on GitLab. Note that there are also options for completely new projects or
existing (non-Git) folders.

- Use the URL on the project page to create *another copy* of your repository on your computer
  (you can delete it afterwards).
- Browse your repository content under the "Files" tab, and perform a quick edit to your text file,
  *committing* the change directly from GitLab.
- Change a *different* line on your computer. *Pulling* the newest version from GitLab should silently
  incorporate both your changes.
- Edit the line you changed locally also on GitLab, but in a different way. This time, *pulling* from
  GitLab should cause a *merge conflict*. Check the difference to your last clean version, and try to
  *resolve* the conflict by either accepting one of the versions ("theirs"/"ours") or using an interactive
  *merge tool*. Resolving a conflict includes *committing* the merged files and explaining your
  reasoning and choices.
- Reapply the change you had *stashed* away, and check that the *difference* to your previous repository
  state is what you would expect.
- Create a new *branch* locally, edit the text file and *commit* your changes. Finally, *push* the new branch
  to the repository.
- Use GitLab to create a *Merge Request* of that branch to the master branch. If there are no *merge conflicts*,
  merge it and *delete* the created branch afterwards.

This exercise has left out several important Git concepts, but should suffice as a starting point for
those who have not used Git before. There are also several tabs in
GitLab that might be useful, e.g. the "Commits" and "Graph" tabs under "Repository", the "Issues"
and "Todos" tabs, and the "Wiki" tab. If and how you use these features is up to you.

### List of Git commands:
`git add <file/folder>`, `git checkout --ours/--theirs <file>`, `git clone <url>`,
`git commit`, `git init`, `git log`, `git mergetool`, `git pull`, `git push`, `git reset HEAD~`,
`git stash`, `git status`, `git stash pop`, `git checkout -b <branch>`, `git branch`

### Resources
- [Git manual](https://www.git-scm.com/book/en/v2)
- [Git reference](https://www.git-scm.com/docs)
- [cheat sheet](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf)

## Exercise 2 (Compiling code)
**>> Submit solution until 2019/10/30**

In the directory [material/sheet1/](/exercises/material/sheet1) you can find
an initial C++ example in the files `linear_algebra.cc`, `linear_algebra.h`, and `exercise2.cc`. Download the files and compile the code:

```bash
g++-7 -std=c++14 -Wall -O2 -c linear_algebra.cc
g++-7 -std=c++14 -Wall -O2 -c exercise2.cc
g++-7 -o exercise2 linear_algebra.o exercise2.o
```

This creates a new file `exercise2` in the current directory. You can now run the example by

```bash
./exercise2
```

Familiarize yourself with the options passed to the compiler `g++`, i.e. `-std=c++14`, `-Wall`, `-O2`, `-c`, and `-o`. What are
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
find a second exercise code for this exercise sheet, i.e. the file `exercise3.cc`.
Download and compile again, but this time with debug options `-Og -g` instead of `-O2`.
Run the code! What happens? The program should produce an error.

In order to find the error(s) start the program in a debugger:

```bash
gdb ./exercise3
```

This will open a terminal program with a command line interface to enter GDB commands.

Some important commands, sufficient for this exercise, are:
- `run`  (or `r`) `<arguments>`: start the program with given arguments, if any
- `break` (or `b`) `<file:line, file:function>`: to set a breakpoint at specific location
- `backtrace` (or `bt`): show hierarchy of called functions
- `continue` (or `c`): continue running after break
- `next` (or `n`): execute marked line
- `print` (or `p`) `<expressions>`: print content of variable/object
- `step` (or `s`): enter first function on marked line
- `watch <expression>`: break if value of expression changes

Where the angular brackets `<` and `>` must be omitted. The `<expression>` can be any function parameter (e.g. `x`),
or a class member (e.g. `x.data_`), or the current instance of the class (e.g. `*this`).

Use GDB to locate, find, and correct the bugs in the provided source code. Document
which bugs you have found and how.

### Resources
- [GDB Documentation](https://www.gnu.org/software/gdb/documentation/)
- Cheat Sheets: [darkdust.net](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf),
  [kapeli.com](https://kapeli.com/cheat_sheets/GDB.docset/Contents/Resources/Documents/index),
  [utexas.edu](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)