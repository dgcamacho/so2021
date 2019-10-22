# Linux command line

Start the application `Terminal`
```bash
cd Desktop
mkdir scprog
ls
echo "Hello World" > exercise1.txt
cp exercise1.txt scprog
rm exercise1.txt
cd $HOME  # or cd ~ or just cd
grep -r "Hello" Desktop/*
sed -i "s/World/Dresden/" Desktop/scprog/exercise1.txt
```

The command `du -s * | sort -nr > $HOME/user_space_report.txt` does
1. `du`: Summarize disk usage of the set of FILEs, recursively for directories. (-s: total for each argument)
2. `sort`: Write sorted concatenation of all FILE(s) to standard output. (-r: reverse sorting, -n: numeric numbers)
3. `>`: forwards standard output to file

In summary, the command prints a list of all files and directories in the current directory sorted by its accumulated file size (in KB)
to the output file `user_space_report.txt` in the home directory.