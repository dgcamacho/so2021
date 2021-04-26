---
class: center, middle

<img src="images/git-logo.png">
.footnote[ Git Logo by Jason Long is licensed under the Creative Commons Attribution 3.0 Unported License. ]

---

# Git - An Open Source Distributed Version Control System

- **Open Source:** Developed by Linus Torvalds to manage the Linux-kernel source code
--

- **Control System:** Git can be used to store content - it is mostly used to store code due to the
  other features it provides.
--

- **Version Control System:** Code evolves and keeps changing. Also, many developers might add code
  in parallel. Version Control Systems helps in handling this by maintaining a history of what changes
  have happened.
--

- **Distributed Version Control System:** Git has a *remote* repository which is stored in a server and
  a *local* repository which is stored in the computer of each developer.

## Platforms provide remote repositores
E.g. [gitlab.mn.tu-dresden.de](https://gitlab.mn.tu-dresden.de),
[gitlab.com](https://gitlab.com), [github.com](https://github.com),
[bitbucket.org](https://bitbucket.org),

[fusionforge.zih.tu-dresden.de](https://fusionforge.zih.tu-dresden.de)

---

# Git - Version Control System
## Installation

On Linux available as package in all distributions, e.g., in Debian/Ubuntu
```
  sudo apt-get install git
```

On other platforms, see http://git-scm.com/downloads

## Documentation
- All Git commands are document with man-pages (e.g. type `man git-commit` to see documentation for
  the command `git commit`)
- Pro Git book: https://git-scm.com/book
- Git Reference Manual: https://git-scm.com/docs
- Game to learn git: https://ohmygit.org

---

# Git - Concepts

**Repository**
: A collection of Git objects (commits and trees) and references (branches and tags).

**Branch**
: A named reference to a commit. Every repository usually has at least the `master` or `main` branch
  and contains several more branches, like `issue/xyz` or `feature/abc`.

**Tag**
: A named reference to a commit. In contrast to a branch a tag is usually set once and not changed.
  A branch regularly gets new commits.

**Commit**
: A snapshot of a tree. Identified by a SHA1 hash. Each commit can have multiple parent commits. The
  commits form a directed acyclic graph.

**Tree**
: A collection of files (not directories!) with their path and other metadata. This means that Git
  does not track empty directories.

.footnote[Extracted from slides from http://db.in.tum.de/teaching/ss20/c++praktikum]

---

# Git - Creating a local Git Repository

`git init`
: Initialize a (local) Git repository

`git config --global user.name <name>`
: Sets the name that will be used in commits

`git config --global user.email <email>`
: Sets the e-mail address that will be used in commits

`git status`
: Shows information about the repository

```bash
$ mkdir repo && cd repo
$ git init
Initialized empty Git repository in /.../repo/.git/
$ git status
On branch master

No commits yet
nothing to commit (create/copy files and use "git add" to track)
```

---

# Git - Git Working Directory and Staging Area
When working with a Git repository, changes can live in any of the following places:
1. In the working directory (when you edit a file)
2. In the staging area (when you use `git add`)
3. In a commit (after a `git commit`)

Once a change is in a commit and it is referenced by at least one branch or tag
you can always restore it even if you remove the file.

.center[<img src="images/git-areas.png" width="70%">]

---

# Git - Committing Changes

`git add [-p] <path>...`
: Add changes to the staging area. Changes can be selected interactively when the `-p` option is used.

`git reset [-p] <path>...`
: Remove changes from the staging area without directly modifying the files. Can also be done
  interactively with `-p`.

`git commit [-m "<message>"]`
: Take all changes from the staging area and turn them into a commit. Includes a commit message and
  author and date information. The parent of the new commit is set to the newest commit of the
  current branch. Then the current branch is updated to point to the new commit.

`git checkout -- <path>...`
: Remove changes from the working directory by overwriting the given files or directories with their
  committed versions.

---

# Git - Committing Changes
### Example

```bash
$ echo "Hello World" > example.txt
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	example.txt

nothing added to commit but untracked files present (use "git add" to track)
```

---

# Git - Committing Changes
### Example

```bash
$ git add example.txt
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
	new file:   example.txt
```

---

# Git - Committing Changes
### Example

```bash
$ git commit -m "Add an example file to the repository"
[master (root-commit) 21dd78a] Add an example file to the repository
 1 file changed, 1 insertion(+)
 create mode 100644 example.txt
$ git status
On branch master
nothing to commit, working tree clean
```

---

# Git - Inspecting the Commit History

`git log [<branch>]`
: View the commit history of the current (or another) branch.

`git show [<commit>]`
: Show the changes introduced by the last (or the given) commit.

`git diff`
: View the changes in the working directory (without the staging area).

`git diff --staged`
: View the changes in the staging area (without the working directory).

`git diff HEAD`
: View the changes in the working directory and the staging area.

`git diff branch1..branch2`
: View the changes between two branches (or tags, commits).

---

# Git - Inspecting the Commit History
### Example

```bash
$ git log
commit 21dd78a1c82df10f7c335885c52ccb02824f8035 (HEAD -> master)
Author: Simon Praetorius <simon.praetorius@tu-dresden.de>
Date:   Mon Apr 26 12:03:30 2021 +0200

    Add an example file to the repository
```

---

# Git - Inspecting the Commit History
### Example

```bash
$ git show 21dd78a1c82df10f7c335885c52ccb02824f8035
commit 21dd78a1c82df10f7c335885c52ccb02824f8035 (HEAD -> master)
Author: Simon Praetorius <simon.praetorius@tu-dresden.de>
Date:   Mon Apr 26 12:03:30 2021 +0200

    Add an example file to the repository

diff --git a/example.txt b/example.txt
new file mode 100644
index 0000000..557db03
--- /dev/null
+++ b/example.txt
@@ -0,0 +1 @@
+Hello World
```

---

# Git - Working with Branches and Tags
`git branch`
: Show all (local) branches and which one is active.

`git branch <name>`
: Create a new branch that points to the current commit (`HEAD`).

.pure-g[.pure-u-4-5[
`git checkout <name>`
: Switch to another branch, i.e., change all files in the working directory so that they are equal
  to the tree of the other branch.

`git checkout -b <name>`
: Create a branch and switch to it.

`git tag`
: Show all tags.
]]

.pure-g[.pure-u-2-3[
`git tag [-s] <name>`
: Create a new tag that points to the current commit. Is signed with *PGP* when `-s` is given.
]]

<img src="images/git-branching1.png" style="position:absolute; right:50px; bottom:100px;">

---

# Git - Modifying the Commit History

`git merge <branch>...`
- Combines the current branch and one or more other branches with a special merge commit
- The merge commit has the latest commit of all merged branches as parent
- No commit is modified

`git rebase <branch>`
- Start from the given branch and reapply all diverging commits from the current branch one by one
- All diverging commits are changed (they get a new parent) so their SHA1 hash changes as well

---

# Git - Modifying the Commit History

.center[<img src="images/git-branching.png" width="70%">]

---

# Git - Dealing with Merge Conflicts

.center[<img src="images/git-xkcd.png">]

.footnote[xkcd comic: https://xkcd.com/1597]

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you

### Example
```bash
$ git checkout -b feature/new-message
Switched to a new branch 'feature/new-message'
$ echo "Hello You!" > example.txt
$ git add example.txt
$ git commit -m "Change message to Hello You!"
[feature/new-message 738d695] Changed message to Hello You!
 1 file changed, 1 insertion(+), 1 deletion(-)
```

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you

### Example
```bash
$ git checkout master
Switched to branch 'master'
$ cat example.txt
Hello World
$ echo "Hello World!" > example.txt
$ git add example.txt
$ git commit -m "Change message to Hello World!"
[master 80f1333] Changed message to Hello World!
 1 file changed, 1 insertion(+), 1 deletion(-)
```

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you

### Example
```bash
$ git merge feature/new-message
Auto-merging example.txt
CONFLICT (content): Merge conflict in example.txt
Automatic merge failed; fix conflicts and then commit the result.
```

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you
- `git status` also shows additional information on how to proceed

### Example
```bash
$ git status
On branch master
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
	both modified:   example.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you
- `git status` also shows additional information on how to proceed
- To fix the conflict you have to manually fix all conflicting files. Git inserts markers in the
  files to show where the conflicts arose:

### Example
```bash
$ cat example.txt
<<<<<<< HEAD
Hello World!
=======
Hello You!
>>>>>>> feature/new-message
```

---

# Git - Dealing with Merge Conflicts
- Using `merge` or `rebase` may cause *merge conflicts*
- This happens when two commits are merged that contain changes to the same file
- When a merge conflict happens, Git usually tells you
- `git status` also shows additional information on how to proceed
- To fix the conflict you have to manually fix all conflicting files. Git inserts markers in the
  files to show where the conflicts arose:

### Example
```bash
$ vim example.txt  # Fix the conflict manually or use tools like melt
$ git add example.txt
$ git commit       # An editors open where you can modify the commit message
[master f1312a0] Merge branch 'feature/new-message'
```

---

# Git - Working with Remote Git Repositories

`git clone <url>`
: Download the repository with all its commits, tags, and branches.

`git remote add origin <url>`
: Set the given url as remote repository for an already initialized local repository

`git push [origin <branch>]`
: Upload the current branch to a remote `<branch>` in the repository `origin`.

`git push -f`
: Force override the current branch on the remote repository. This is necessary
  when the local and remote branches have diverging histories, e.g., after using
  commands like `git rebase` or `git reset --hard`.

`git fetch`
: Download new commits, tags, and branches from a remote repository into an
  existing repository.

`git pull`
: Run `git fetch` and then update (i.e., `git merge`) the current branch to match
  the branch on the remote repository.

---

# Git - Summary

- Use git for all your coding, from the very beginning!
- Commit often, Push frequently!

.center[<img src="images/git-xkcd2.png">]

.footnote[xkcd comic: https://xkcd.com/1296]