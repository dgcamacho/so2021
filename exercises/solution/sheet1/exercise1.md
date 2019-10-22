# Introduction to Git

Part 1 using several of the commands learned in exercise0:
```bash
mkdir scprog
cd scprog
git init
echo -e "Hello \n\nWorld \n" > exercise1.txt
git add exercise1.txt
git commit -m "File exercise1.txt with Hello World added"
git log
git status
sed -i "s/World/Dresden/" exercise1.txt
git add exercise1.txt
git commit -m "Changed World to Dresden"
git reset HEAD~1
git checkout -- exercise1.txt
sed -i "s/World/Dresden/" exercise1.txt
git stash
```

Part 2. Assume your repository has the url `https://gitlab.mn.tu-dresden.de/spraetor/scprog.git`
```bash
git remote add origin https://gitlab.mn.tu-dresden.de/spraetor/scprog.git
git push -u origin master
```

Part 3: Merging, conflicts and resolution
```bash
cd ..
git clone https://gitlab.mn.tu-dresden.de/spraetor/scprog.git scprog2

cd scprog
# Edit line "World" and change it to "Leipzig" online in GitLab
sed -i "s/Hello/Hi/" exercise1.txt
git add exercise1.txt
git commit -m "Changed Hello to Hi"
git pull origin master
# Edit line "Hello" and change it to "I love" online in GitLab
git pull origin master
# --> merge conflict. Resolve in text editor.
git add exercise1.txt && git commit -m "merge conflict resolved"
git stash pop
# --> maybe resolve merge conflict
git checkout -b changed_file
echo "I love Dresden" > exercise1.txt
git add exercise1.txt && git commit -m "Overwritten file exercise1 with new content"
git push origin changed_file
# Use GitLab to create a merge request
```